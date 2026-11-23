#include "jk_ble.h"
#include "jk_protocol.h"
#include <Arduino.h>
#include <NimBLEDevice.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include <string.h>
#include <stdio.h>
namespace {
portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;
JkSnapshot model{};
QueueHandle_t jobs = nullptr;
TaskHandle_t task = nullptr;
NimBLEClient *client = nullptr;
NimBLERemoteCharacteristic *characteristic = nullptr;
bool link = false, acceptNotify = false, scanEnded = false, resetRx = false;
bool cancelOpen = false, connectQueued = false, sessionActive = false;
uint8_t ring[1024];
unsigned head = 0, used = 0;
uint32_t drops = 0;
JkProtocol parser;
enum class Op : uint8_t { Scan, Connect, Disconnect, Profile };
struct Job {
    Op op;
    JkDevice device;
    JkProfile profile;
};
void status(JkState state, const char *msg) {
    portENTER_CRITICAL(&mux);
    if (!sessionActive) {
        portEXIT_CRITICAL(&mux);
        return;
    }
    model.state = state;
    snprintf(model.status, sizeof(model.status), "%s", msg);
    model.revision++;
    portEXIT_CRITICAL(&mux);
}
void stopNotifications() {
    portENTER_CRITICAL(&mux);
    acceptNotify = false;
    head = used = 0;
    portEXIT_CRITICAL(&mux);
    parser.reset();
    characteristic = nullptr;
}
class ScanCallbacks : public NimBLEScanCallbacks {
    void onResult(const NimBLEAdvertisedDevice *d) override {
        JkDevice item{};
        auto name = d->getName();
        auto addr = d->getAddress();
        auto mac = addr.toString();
        snprintf(item.name, sizeof(item.name), "%s", name.empty() ? "(Khong ten)" : name.c_str());
        snprintf(item.address, sizeof(item.address), "%s", mac.c_str());
        item.rssi = d->getRSSI();
        item.addressType = addr.getType();
        item.likelyJk =
            d->isAdvertisingService(NimBLEUUID("FFE0")) || strstr(item.name, "JK") || strstr(item.name, "jk");
        portENTER_CRITICAL(&mux);
        if (model.state == JkState::Scanning) {
            unsigned i = 0;
            for (; i < model.deviceCount; i++)
                if (model.devices[i].addressType == item.addressType &&
                    !strcmp(model.devices[i].address, item.address))
                    break;
            if (i < JK_MAX_DEVICES) {
                model.devices[i] = item;
                if (i == model.deviceCount)
                    model.deviceCount++;
                model.revision++;
            }
        }
        portEXIT_CRITICAL(&mux);
    }
    void onScanEnd(const NimBLEScanResults &, int) override {
        portENTER_CRITICAL(&mux);
        scanEnded = true;
        portEXIT_CRITICAL(&mux);
    }
} scanCallbacks;
class ClientCallbacks : public NimBLEClientCallbacks {
    void onConnect(NimBLEClient *) override {
        portENTER_CRITICAL(&mux);
        link = true;
        portEXIT_CRITICAL(&mux);
    }
    void onDisconnect(NimBLEClient *, int reason) override {
        Serial.printf("[JK] Disconnected: reason=%d\n", reason);
        portENTER_CRITICAL(&mux);
        link = false;
        acceptNotify = false;
        resetRx = true;
        portEXIT_CRITICAL(&mux);
    }
} clientCallbacks;
void notify(NimBLERemoteCharacteristic *c, uint8_t *p, size_t n, bool) {
    portENTER_CRITICAL(&mux);
    if (acceptNotify && link && c == characteristic) {
        if (n > sizeof(ring) - used) {
            head = used = 0;
            drops++;
            resetRx = true;
        } else
            for (size_t i = 0; i < n; i++) {
                ring[(head + used) % sizeof(ring)] = p[i];
                used++;
            }
    }
    portEXIT_CRITICAL(&mux);
}
bool linked() {
    portENTER_CRITICAL(&mux);
    bool v = link;
    portEXIT_CRITICAL(&mux);
    return v;
}
void disconnectClient() {
    stopNotifications();
    if (client && client->isConnected())
        client->disconnect();
    // No further attribute access until the old connection has actually closed.
    uint32_t start = millis();
    while (client && client->isConnected() && (uint32_t)(millis() - start) < 1500)
        vTaskDelay(pdMS_TO_TICKS(10));
    portENTER_CRITICAL(&mux);
    model.linkUp = false;
    model.data.valid = false;
    portEXIT_CRITICAL(&mux);
}
bool cancelled() {
    portENTER_CRITICAL(&mux);
    bool result = cancelOpen;
    portEXIT_CRITICAL(&mux);
    return result;
}
bool pauseOpen(uint32_t duration) {
    uint32_t start = millis();
    while ((uint32_t)(millis() - start) < duration) {
        if (cancelled())
            return false;
        vTaskDelay(pdMS_TO_TICKS(10));
    }
    return !cancelled();
}
// All GATT operations stay on this worker; no display or BLE calls in the UI thread.
bool openJk(const JkDevice &device) {
    const char *failure = "Ket noi that bai";
    char message[72];
    for (unsigned attempt = 1; attempt <= 3 && !cancelled(); attempt++) {
        disconnectClient();
        if (client->isConnected()) {
            failure = "Chua ngat duoc ket noi cu";
            break;
        }
        if (!pauseOpen(attempt == 1 ? 150 : 800))
            break;
        snprintf(message, sizeof(message), "Dang ket noi BMS (%u/3)...", attempt);
        status(JkState::Connecting, message);
        Serial.printf("[JK] Connect %s type=%u attempt=%u/3\n", device.address, device.addressType, attempt);
        if (!client->connect(NimBLEAddress(std::string(device.address), device.addressType), true, false,
                             true)) {
            failure = "Ket noi that bai. QUET lai va thu lai";
            Serial.printf("[JK] Connect failed: lastError=%d\n", client->getLastError());
            continue;
        }
        // Let the link / automatic MTU exchange settle before starting GATT discovery.
        if (!pauseOpen(350) || !linked()) {
            failure = "Mat lien ket truoc khi doc dich vu";
            continue;
        }
        status(JkState::Discovering, "Dang doc dich vu FFE0/FFE1...");
        NimBLERemoteService *service = client->getService(NimBLEUUID("FFE0"));
        if (!service && linked() && pauseOpen(250)) {
            // Some peripherals fail filtered discovery. Refresh the complete service table once.
            const auto &services = client->getServices(true);
            Serial.printf("[JK] Full discovery: %u services, lastError=%d\n", (unsigned)services.size(),
                          client->getLastError());
            if (linked())
                service = client->getService(NimBLEUUID("FFE0"));
        }
        if (cancelled())
            break;
        if (!service || !linked()) {
            failure = linked() ? "Chua doc duoc FFE0. Hay QUET lai" : "Mat ket noi khi doc FFE0";
            Serial.printf("[JK] FFE0 discovery failed: lastError=%d\n", client->getLastError());
            continue;
        }
        characteristic = service->getCharacteristic(NimBLEUUID("FFE1"));
        if (!characteristic || !linked()) {
            failure = "Chua doc duoc FFE1. Hay thu lai";
            Serial.printf("[JK] FFE1 discovery failed: lastError=%d\n", client->getLastError());
            continue;
        }
        if (!characteristic->canNotify() ||
            (!characteristic->canWrite() && !characteristic->canWriteNoResponse())) {
            failure = "FFE1 khong ho tro notify/write JK";
            break;
        }
        portENTER_CRITICAL(&mux);
        head = used = 0;
        resetRx = false;
        acceptNotify = true;
        portEXIT_CRITICAL(&mux);
        if (!characteristic->subscribe(true, notify)) {
            failure = "Dang ky notify FFE1 that bai";
            Serial.printf("[JK] Subscribe failed: lastError=%d\n", client->getLastError());
            continue;
        }
        if (linked() && !cancelled()) {
            portENTER_CRITICAL(&mux);
            if (!sessionActive || cancelOpen) {
                portEXIT_CRITICAL(&mux);
                break;
            }
            model.linkUp = true;
            portEXIT_CRITICAL(&mux);
            Serial.println("[JK] FFE0/FFE1 ready");
            return true;
        }
        failure = "Mat ket noi sau khi dang ky notify";
    }
    disconnectClient();
    status(cancelled() ? JkState::Disconnected : JkState::Error,
           cancelled() ? "Da dung ket noi BMS" : failure);
    return false;
}
bool stopScan(NimBLEScan *scan) {
    scan->stop();
    uint32_t started = millis();
    while (scan->isScanning() && (uint32_t)(millis() - started) < 1000)
        vTaskDelay(pdMS_TO_TICKS(10));
    return !scan->isScanning();
}
bool writeRequest(uint8_t reg) {
    if (!characteristic || !linked())
        return false;
    uint8_t bytes[20];
    JkProtocol::command(reg, bytes);
    bool response = !characteristic->canWriteNoResponse();
    return characteristic->writeValue(bytes, sizeof(bytes), response);
}
void receiveData() {
    uint8_t chunk[128];
    unsigned n = 0;
    bool reset;
    portENTER_CRITICAL(&mux);
    reset = resetRx;
    resetRx = false;
    if (reset) {
        head = used = 0;
    } else {
        while (n < sizeof(chunk) && used) {
            chunk[n++] = ring[head];
            head = (head + 1) % sizeof(ring);
            used--;
        }
    }
    model.rxDrops = drops;
    portEXIT_CRITICAL(&mux);
    if (reset)
        parser.reset();
    uint8_t frame[300];
    for (unsigned i = 0; i < n; i++)
        if (parser.push(chunk[i], frame)) {
            JkData data{};
            JkInfo info{};
            portENTER_CRITICAL(&mux);
            JkProfile profile = model.profile;
            portEXIT_CRITICAL(&mux);
            if (JkProtocol::decodeData(frame, 300, profile, data)) {
                data.updatedMs = millis();
                portENTER_CRITICAL(&mux);
                if (sessionActive && link && model.state == JkState::Connected) {
                    data.sequence = model.data.sequence + 1;
                    model.data = data;
                    model.revision++;
                }
                portEXIT_CRITICAL(&mux);
            } else if (JkProtocol::decodeInfo(frame, 300, info)) {
                portENTER_CRITICAL(&mux);
                if (sessionActive && link && model.state == JkState::Connected) {
                    model.info = info;
                    model.revision++;
                }
                portEXIT_CRITICAL(&mux);
            }
        }
    portENTER_CRITICAL(&mux);
    model.badFrames = parser.badFrames;
    portEXIT_CRITICAL(&mux);
}
void worker(void *) {
    NimBLEDevice::init("JK BMS Display");
    NimBLEScan *scan = NimBLEDevice::getScan();
    scan->setScanCallbacks(&scanCallbacks, true);
    scan->setActiveScan(true);
    scan->setInterval(100);
    scan->setWindow(80);
    scan->setMaxResults(0);
    client = NimBLEDevice::createClient();
    if (!client) {
        status(JkState::Error, "Khong tao duoc BLE client");
        vTaskDelete(nullptr);
        return;
    }
    client->setClientCallbacks(&clientCallbacks, false);
    client->setSelfDelete(false, false);
    client->setConnectTimeout(JK_CONNECT_TIMEOUT_MS + 3000);
    // 30-50 ms interval, no latency, 6 s supervision timeout for brief RF losses.
    client->setConnectionParams(24, 40, 0, 600);
    client->setConnectRetries(0);
    status(JkState::Idle, "Bam QUET de tim BMS");
    uint32_t lastRequest = 0, infoRequestAt = 0, connectedAt = 0;
    bool needInfo = false, recoveryAvailable = true;
    for (;;) {
        portENTER_CRITICAL(&mux);
        bool active = sessionActive;
        portEXIT_CRITICAL(&mux);
        if (!active) {
            if (scan->isScanning()) scan->stop();
            if (client->isConnected() || characteristic) disconnectClient();
            vTaskDelay(pdMS_TO_TICKS(20));
            continue;
        }
        Job job{};
        if (xQueueReceive(jobs, &job, 0) == pdTRUE) {
            if (job.op == Op::Scan) {
                scan->stop();
                disconnectClient();
                if (client->isConnected()) {
                    status(JkState::Error, "Chua ngat duoc ket noi cu");
                    continue;
                }
                scan->clearResults();
                portENTER_CRITICAL(&mux);
                model.deviceCount = 0;
                model.info = {};
                scanEnded = false;
                portEXIT_CRITICAL(&mux);
                status(JkState::Scanning, "Dang quet Bluetooth LE...");
                if (!scan->start(JK_SCAN_MS, false, true))
                    status(JkState::Error, "Khong bat dau quet duoc");
            } else if (job.op == Op::Disconnect) {
                scan->stop();
                disconnectClient();
                status(client->isConnected() ? JkState::Error : JkState::Disconnected,
                       client->isConnected() ? "Chua ngat duoc BMS. Thu lai"
                                             : "Da ngat. Chon BMS de noi lai");
            } else if (job.op == Op::Profile) {
                parser.reset();
                portENTER_CRITICAL(&mux);
                head = used = 0;
                model.profile = job.profile;
                model.data = {};
                model.revision++;
                portEXIT_CRITICAL(&mux);
                lastRequest = millis() - JK_REQUEST_INTERVAL_MS;
            } else if (job.op == Op::Connect) {
                bool scanStopped = stopScan(scan);
                portENTER_CRITICAL(&mux);
                model.selected = job.device;
                model.data = {};
                model.info = {};
                scanEnded = false;
                portEXIT_CRITICAL(&mux);
                bool opened = false;
                if (scanStopped)
                    opened = openJk(job.device);
                else
                    status(JkState::Error, "Chua dung duoc quet BLE. Thu lai");
                portENTER_CRITICAL(&mux);
                connectQueued = false;
                portEXIT_CRITICAL(&mux);
                if (!opened)
                    continue;
                recoveryAvailable = true;
                status(JkState::Connected, "Da noi. Dang cho du lieu...");
                connectedAt = millis();
                lastRequest = connectedAt;
                needInfo = true;
                infoRequestAt = connectedAt;
                if (!writeRequest(0x97)) {
                    disconnectClient();
                    status(JkState::Connected, "Loi gui lenh. Dang noi lai...");
                    continue;
                }
            }
        }
        portENTER_CRITICAL(&mux);
        JkState state = model.state;
        bool ended = scanEnded;
        scanEnded = false;
        portEXIT_CRITICAL(&mux);
        if (state == JkState::Scanning && ended && !scan->isScanning())
            status(JkState::Idle, "Quet xong. Cham thiet bi de noi");
        if (state == JkState::Connected) {
            if (!linked()) {
                stopNotifications();
                portENTER_CRITICAL(&mux);
                model.linkUp = false;
                model.data.valid = false;
                portEXIT_CRITICAL(&mux);
                if (recoveryAvailable && !cancelled()) {
                    recoveryAvailable = false;
                    portENTER_CRITICAL(&mux);
                    JkDevice selected = model.selected;
                    portEXIT_CRITICAL(&mux);
                    Serial.println("[JK] Recovering selected BMS connection");
                    if (openJk(selected)) {
                        connectedAt = lastRequest = infoRequestAt = millis();
                        needInfo = true;
                        status(JkState::Connected, "Da noi lai. Dang cho du lieu...");
                        if (!writeRequest(0x97)) {
                            disconnectClient();
                            status(JkState::Error, "Khong gui duoc lenh doc");
                        }
                    }
                } else {
                    status(JkState::Disconnected, "Mat ket noi. Chon BMS de noi lai");
                }

            } else {
                receiveData();
                if ((uint32_t)(millis() - connectedAt) >= 30000) {
                    portENTER_CRITICAL(&mux);
                    bool fresh =
                        model.data.valid && (uint32_t)(millis() - model.data.updatedMs) < JK_STALE_MS;
                    portEXIT_CRITICAL(&mux);
                    if (fresh)
                        recoveryAvailable = true;
                }
                if (needInfo && (uint32_t)(millis() - infoRequestAt) >= 250) {
                    needInfo = false;
                    lastRequest = millis();
                    if (!writeRequest(0x96)) {
                        disconnectClient();
                        status(JkState::Connected, "Loi gui lenh. Dang noi lai...");
                    }
                } else if (!needInfo && (uint32_t)(millis() - lastRequest) >= JK_REQUEST_INTERVAL_MS) {
                    lastRequest = millis();
                    if (!writeRequest(0x96)) {
                        disconnectClient();
                        status(JkState::Connected, "Loi gui lenh. Dang noi lai...");
                    }
                }
                portENTER_CRITICAL(&mux);
                bool valid = model.data.valid;
                uint32_t last = valid ? model.data.updatedMs : connectedAt;
                if ((uint32_t)(millis() - last) > JK_STALE_MS)
                    snprintf(model.status, sizeof(model.status), "Chua co du lieu. Kiem tra JK02-24/32S");
                else if (valid)
                    snprintf(model.status, sizeof(model.status), "Dang doc du lieu JK BMS");
                portEXIT_CRITICAL(&mux);
            }
        }
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
bool send(const Job &job) {
    return jobs && xQueueSend(jobs, &job, 0) == pdTRUE;
}
} // namespace
bool jk_ble_begin() {
    portENTER_CRITICAL(&mux);
    sessionActive = true;
    portEXIT_CRITICAL(&mux);
    if (jobs) return jk_ble_scan(); // Reopen reuses the same client/task/queue.
    model.profile = JK_DEFAULT_32S ? JkProfile::JK02_32S : JkProfile::JK02_24S;
    model.state = JkState::Starting;
    snprintf(model.status, sizeof(model.status), "Dang khoi tao Bluetooth...");
    jobs = xQueueCreate(4, sizeof(Job));
    if (!jobs) {
        status(JkState::Error, "Khong du RAM cho BLE queue");
        return false;
    }
    // Background BLE I/O only, no fixed core assignment and no display calls in callbacks.
    if (xTaskCreate(worker, "jk_ble", 6144, nullptr, 1, &task) != pdPASS) {
        vQueueDelete(jobs);
        jobs = nullptr;
        status(JkState::Error, "Khong du RAM cho BLE task");
        return false;
    }
    Job first{};
    first.op = Op::Scan;
    return send(first);
}
void jk_ble_snapshot(JkSnapshot &out) {
    portENTER_CRITICAL(&mux);
    out = model;
    portEXIT_CRITICAL(&mux);
}
bool jk_ble_scan() {
    Job j{};
    j.op = Op::Scan;
    portENTER_CRITICAL(&mux);
    cancelOpen = true;
    portEXIT_CRITICAL(&mux);
    return send(j);
}
bool jk_ble_connect(const JkDevice &device) {
    Job j{};
    j.op = Op::Connect;
    j.device = device;
    portENTER_CRITICAL(&mux);
    bool busy = connectQueued || model.linkUp || model.state == JkState::Connecting ||
                model.state == JkState::Discovering || model.state == JkState::Connected;
    if (!busy) {
        connectQueued = true;
        cancelOpen = false;
    }
    portEXIT_CRITICAL(&mux);
    if (busy)
        return false;
    if (send(j))
        return true;
    portENTER_CRITICAL(&mux);
    connectQueued = false;
    portEXIT_CRITICAL(&mux);
    return false;
}
bool jk_ble_disconnect() {
    Job j{};
    j.op = Op::Disconnect;
    portENTER_CRITICAL(&mux);
    cancelOpen = true;
    portEXIT_CRITICAL(&mux);
    return send(j);
}
bool jk_ble_profile(JkProfile profile) {
    Job j{};
    j.op = Op::Profile;
    j.profile = profile;
    return send(j);
}


void jk_ble_suspend() {
    portENTER_CRITICAL(&mux);
    sessionActive = false;
    cancelOpen = true;
    model.state = JkState::Disconnected;
    model.linkUp = false;
    model.data.valid = false;
    snprintf(model.status, sizeof(model.status), "Da dong JK BMS");
    model.revision++;
    portEXIT_CRITICAL(&mux);
    if (jobs) xQueueReset(jobs);
    // In-flight BLE calls return on the worker; never block HOME on GATT.
}
