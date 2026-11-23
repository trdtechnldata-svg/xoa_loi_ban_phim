#include "jk_ui.h"
#include "jk_ble.h"
#include "jk_display.h"
#include <Arduino.h>
#include <string.h>
#include <stdio.h>
namespace {
const uint16_t BG = 0x0863, CARD = 0x1106, EDGE = 0x224B, WHITE = 0xF7BF, MUTED = 0x8CD5, TEAL = 0x4F3A,
               RED = 0xFC10, YELLOW = 0xFED0;
unsigned page = 3, top = 0, overviewTop = 0;
const unsigned OVERVIEW_ROWS = 13;
unsigned &scrollTop() { return page == 0 ? overviewTop : top; }
bool dirty = true, down = false, dragged = false;
int startX, startY;
unsigned startTop;
bool exitRequested = false;
// Rail is a separate touch target; a gesture here can never select a BMS row.
unsigned railMode = 0;
int thumbOffset = 0;
uint32_t repeatAt = 0;
const int RAIL_X = 430, RAIL_W = 38, TRACK_Y = 116, TRACK_H = 116;
unsigned maxTop(const JkSnapshot &s) {
    unsigned count = page == 0 ? OVERVIEW_ROWS : s.deviceCount;
    return count > 4 ? count - 4 : 0;
}
void scrollTo(int value, const JkSnapshot &s) {
    if (value < 0)
        value = 0;
    if (value > (int)maxTop(s))
        value = maxTop(s);
    if (scrollTop() != (unsigned)value) {
        scrollTop() = value;
        dirty = true;
    }
}
int thumbHeight(const JkSnapshot &s) {
    unsigned count = page == 0 ? OVERVIEW_ROWS : s.deviceCount;
    int h = count > 4 ? TRACK_H * 4 / count : TRACK_H;
    return h < 24 ? 24 : h;
}
int thumbY(const JkSnapshot &s) {
    return TRACK_Y + (maxTop(s) ? scrollTop() * (TRACK_H - thumbHeight(s)) / maxTop(s) : 0);
}
void dragThumb(int y, const JkSnapshot &s) {
    int travel = TRACK_H - thumbHeight(s);
    if (travel <= 0) {
        scrollTo(0, s);
        return;
    }
    int pos = y - thumbOffset - TRACK_Y;
    if (pos < 0)
        pos = 0;
    if (pos > travel)
        pos = travel;
    scrollTo((pos * maxTop(s) + travel / 2) / travel, s);
}
uint32_t lastDraw = 0, releasedAt = 0;
JkState lastState = JkState::Starting;
char transient[64]{};
JkSnapshot painted{};
unsigned paintedPage = 99;
bool paintedLive = false;
TFT_eSPI &lcd() {
    return jk_display();
}
void text(int x, int y, const char *s, unsigned size, uint16_t color = WHITE, uint16_t bg = CARD,
          unsigned maxChars = 80) {
    char clipped[96];
    unsigned n = (unsigned)strlen(s);
    if (n > maxChars)
        n = maxChars;
    if (n > 95)
        n = 95;
    memcpy(clipped, s, n);
    clipped[n] = 0;
    lcd().setTextFont(1);
    lcd().setTextSize(size);
    lcd().setTextColor(color, bg);
    lcd().setCursor(x, y);
    lcd().print(clipped);
}
void card(int x, int y, int w, int h, uint16_t color = CARD) {
    lcd().fillRoundRect(x, y, w, h, 8, color);
    lcd().drawRoundRect(x, y, w, h, 8, EDGE);
}
void button(int x, int y, int w, int h, const char *label, uint16_t color = EDGE) {
    lcd().fillRoundRect(x, y, w, h, 6, color);
    text(x + (w - (int)strlen(label) * 6) / 2, y + (h - 8) / 2, label, 1, WHITE, color);
}
bool in(int x, int y, int w, int h, int px, int py) {
    return px >= x && px < x + w && py >= y && py < y + h;
}
const char *stateName(JkState s) {
    switch (s) {
    case JkState::Starting:
        return "Khoi tao BLE...";
    case JkState::Idle:
        return "San sang";
    case JkState::Scanning:
        return "Dang quet...";
    case JkState::Connecting:
        return "Dang ket noi...";
    case JkState::Discovering:
        return "Tim dich vu JK...";
    case JkState::Connected:
        return "Da ket noi";
    case JkState::Disconnected:
        return "Da ngat";
    default:
        return "Loi ket noi";
    }
}
void notice(bool ok) {
    if (!ok)
        snprintf(transient, sizeof(transient), "BLE dang ban. Thu lai sau.");
    else
        transient[0] = 0;
    dirty = true;
}
void navigation(const JkSnapshot &s) {
    lcd().fillRect(426,78,42,192,BG);
    button(RAIL_X,78,RAIL_W,34,"");
    text(RAIL_X+13,87,"^",2,scrollTop()?TEAL:MUTED,EDGE);
    button(RAIL_X,236,RAIL_W,34,"");
    text(RAIL_X+13,245,"v",2,scrollTop()<maxTop(s)?TEAL:MUTED,EDGE);
    lcd().fillRoundRect(RAIL_X+3,TRACK_Y,RAIL_W-6,TRACK_H,6,CARD);
    lcd().fillRoundRect(RAIL_X+3,thumbY(s),RAIL_W-6,thumbHeight(s),6,maxTop(s)?TEAL:EDGE);
}
void overview(const JkSnapshot &s) {
    const JkData &d=s.data;
    bool live=d.valid&&s.linkUp&&(uint32_t)(millis()-d.updatedMs)<=JK_STALE_MS;
    const char *names[]={"SOC","PACK VOLTAGE","CURRENT","POWER","TEMP 1","TEMP 2","MOS TEMP",
        "BALANCE CURRENT","REMAINING CAPACITY","NOMINAL CAPACITY","CYCLE COUNT","SOH",
        "CHARGE MOS","DISCHARGE MOS","BALANCING","UPTIME","ERROR FLAGS","MODEL",
        "HARDWARE","SOFTWARE","DEVICE NAME","SERIAL","SETUP PASS","MAC","FRAME","BLUETOOTH"};
    char values[26][34]{};
    if(live) {
        snprintf(values[0],34,"%u%%",(unsigned)d.soc);
        snprintf(values[1],34,"%.2f V",(double)d.voltage);
        snprintf(values[2],34,"%.2f A",(double)d.current);
        snprintf(values[3],34,"%.1f W",(double)d.power);
        snprintf(values[4],34,"%.1f C",(double)d.temp1);
        snprintf(values[5],34,"%.1f C",(double)d.temp2);
        snprintf(values[6],34,"%.1f C",(double)d.mosTemp);
        snprintf(values[7],34,"%.3f A",(double)d.balanceCurrent);
        snprintf(values[8],34,"%.2f Ah",(double)d.remainingAh);
        snprintf(values[9],34,"%.2f Ah",(double)d.capacityAh);
        snprintf(values[10],34,"%lu",(unsigned long)d.cycles);
        snprintf(values[11],34,"%u%%",(unsigned)d.soh);
        snprintf(values[12],34,"%s",d.charge?"ON":"OFF");
        snprintf(values[13],34,"%s",d.discharge?"ON":"OFF");
        snprintf(values[14],34,"%s",d.balancing?"ON":"OFF");
        snprintf(values[15],34,"%lu s",(unsigned long)d.uptime);
        snprintf(values[16],34,"%08lX",(unsigned long)d.errors);
    } else for(unsigned i=0;i<17;i++) strcpy(values[i],"--");
    const char *info[]={s.info.model,s.info.hardware,s.info.software,s.info.deviceName,s.info.serial,s.info.setupPass};
    for(unsigned i=0;i<6;i++) snprintf(values[17+i],34,"%s",s.info.valid&&*info[i]?info[i]:"--");
    snprintf(values[23],34,"%s",*s.selected.address?s.selected.address:"--");
    snprintf(values[24],34,"%s",s.profile==JkProfile::JK02_32S?"JK02-32S":"JK02-24S");
    snprintf(values[25],34,"%s",stateName(s.state));
    text(12,55,"Keo thanh ben phai de xem du thong tin",1,MUTED,BG,65);
    navigation(s);
    for(unsigned row=0;row<4;row++) for(unsigned col=0;col<2;col++) {
        unsigned i=(overviewTop+row)*2+col;
        int x=12+col*210,y=78+row*48;
        card(x,y,198,43);
        text(x+8,y+4,names[i],1,MUTED,CARD,30);
        unsigned size=strlen(values[i])>14?1:2;
        text(x+8,y+23,values[i],size,i<17?(live?TEAL:MUTED):WHITE,CARD,30);
    }
    char b[64];snprintf(b,sizeof(b),"Thong tin %u-%u / %u | BLE de chon BMS",overviewTop*2+1,(overviewTop+4)*2,26U);
    text(12,272,b,1,MUTED,BG,76);
}
void cells(const JkSnapshot &s) {
    bool live = s.data.valid && s.linkUp && (uint32_t)(millis() - s.data.updatedMs) <= JK_STALE_MS;
    char b[80];
    if (live)
        snprintf(b, sizeof(b), "%u cells | Min %.3f V | Max %.3f V | dV %.3f V", (unsigned)s.data.cellCount,
                 (double)s.data.minCell, (double)s.data.maxCell, (double)s.data.deltaCell);
    else
        strcpy(b, "Chua co du lieu cell moi");
    text(12, 51, b, 1, live ? MUTED : YELLOW, BG, 76);
    unsigned capacity = s.profile == JkProfile::JK02_32S ? 32 : 24;
    for (unsigned i = 0; i < 32; i++) {
        int x = 12 + (i % 4) * 117, y = 75 + (i / 4) * 24;
        card(x, y, 106, 22);
        snprintf(b, sizeof(b), "%02u", i + 1);
        text(x + 4, y + 7, b, 1, MUTED);
        bool active = live && i < capacity && s.data.cellMv[i] &&
                      (!s.data.enabledMask || ((s.data.enabledMask >> i) & 1u));
        if (active)
            snprintf(b, sizeof(b), "%.3f", s.data.cellMv[i] * 0.001);
        else
            strcpy(b, "--.---");
        text(x + 23, y + 3, b, 2, active ? TEAL : MUTED, CARD, 6);
    }
}
void bluetooth(const JkSnapshot &s) {
    char b[64];
    snprintf(b, sizeof(b), "%u BLE devices | Keo de xem them", (unsigned)s.deviceCount);
    text(12, 53, b, 1, MUTED, BG, 48);
    button(326, 44, 142, 26, s.profile == JkProfile::JK02_32S ? "FRAME: JK02-32S" : "FRAME: JK02-24S");
    if (top > maxTop(s))
        top = maxTop(s);
    navigation(s);
    for (unsigned v = 0; v < 4; v++) {
        unsigned index = top + v;
        int y = 78 + v * 48;
        card(12, y, 404, 43);
        if (index >= s.deviceCount) {
            if (!s.deviceCount && v == 0)
                text(24, y + 15,
                     s.state == JkState::Scanning ? "Dang tim Bluetooth LE..." : "Bam QUET, sau do chon BMS.",
                     1, MUTED);
            continue;
        }
        const JkDevice &d = s.devices[index];
        text(24, y + 6, d.name, 2, d.likelyJk ? TEAL : WHITE, CARD, 30);
        text(24, y + 27, d.address, 1, MUTED);
        snprintf(b, sizeof(b), "%d dBm%s", d.rssi, d.likelyJk ? "  JK" : "");
        text(312, y + 28, b, 1, MUTED);
    }
}
void draw(const JkSnapshot &s) {
    if (dirty || paintedPage != page) {
        lcd().fillScreen(BG);
    } else {
        lcd().fillRect(0, 0, 480, 40, BG);
    }
    text(12, 13, "JK BMS", 2, WHITE, BG);
    text(116, 18, stateName(s.state), 1, s.state == JkState::Error ? RED : TEAL, BG, 20);
    button(324, 8, 76, 30, page == 3 ? "QUET" : "BLE");
    button(408, 8, 60, 30, "HOME");
    if (s.linkUp || s.state == JkState::Connecting || s.state == JkState::Discovering)
        button(244, 8, 72, 30, "NGAT");
    if (page != 3) {
        char b[76];
        snprintf(b, sizeof(b), "%s  %s", s.selected.name, s.selected.address);
        text(12, 43, b, 1, MUTED, BG, 76);
    }
    if (page == 0)
        overview(s);
    else if (page == 1)
        cells(s);
    else
        bluetooth(s);
    const char *labels[] = {"TONG QUAN", "CELL PIN"};
    for (unsigned i = 0; i < 2; i++)
        button(4 + i * 240, 284, 232, 32, labels[i], i == page ? 0x1371 : EDGE);
    if (transient[0])
        text(12, 272, transient, 1, RED, BG, 76);
    else if (page == 3) {
        lcd().fillRect(0, 271, 480, 11, BG);
        text(12, 272, s.status, 1, s.state == JkState::Error ? RED : MUTED, BG, 76);
    }
}
} // namespace
void jk_ui_begin() {
    dirty = true;
    page = 3;
    top = overviewTop = 0;
    down = dragged = false;
    railMode = 0;
    releasedAt = 0;
    lastState = JkState::Starting;
    paintedPage = 99;
    transient[0] = 0;
    exitRequested = false;
}
bool jk_ui_exit_requested() { return exitRequested; }
void jk_ui_tick(const JkSnapshot &s) {
    if (s.state == JkState::Connected && lastState != JkState::Connected) {
        page = 0;
        dirty = true;
    }
    if (s.state != lastState) {
        lastState = s.state;
        transient[0] = 0;
        dirty = true;
    }
    bool live = s.data.valid && s.linkUp && (uint32_t)(millis() - s.data.updatedMs) <= JK_STALE_MS;
    bool changed = dirty || page != paintedPage || s.state != painted.state || s.profile != painted.profile ||
                   s.linkUp != painted.linkUp || live != paintedLive || strcmp(s.status, painted.status);
    if (page == 3)
        changed = changed || s.deviceCount != painted.deviceCount ||
                  memcmp(s.devices, painted.devices, sizeof(s.devices)) || strcmp(s.status, painted.status);
    else
        changed = changed || s.data.sequence != painted.data.sequence ||
                  memcmp(&s.info, &painted.info, sizeof(s.info));
    if (!changed)
        return;
    if ((uint32_t)(millis() - lastDraw) < 250 && !dirty)
        return;
    lastDraw = millis();
    draw(s);
    painted = s;
    paintedPage = page;
    paintedLive = live;
    dirty = false;
}
void jk_ui_touch(uint16_t x, uint16_t y, bool pressed, const JkSnapshot &s) {
    if (pressed) {
        releasedAt = 0;
        if (!down) {
            down = true;
            dragged = false;
            startX = x;
            startY = y;
            startTop = scrollTop();
            railMode = 0;
            if ((page == 0 || page == 3) && in(RAIL_X, 78, RAIL_W, 192, x, y)) {
                if (y < 112) {
                    railMode = 1;
                    scrollTo((int)scrollTop() - 1, s);
                } else if (y >= 236) {
                    railMode = 2;
                    scrollTo((int)scrollTop() + 1, s);
                } else {
                    railMode = 3;
                    int ty = thumbY(s), h = thumbHeight(s);
                    thumbOffset = y >= ty && y < ty + h ? y - ty : h / 2;
                    dragThumb(y, s);
                }
                repeatAt = millis() + 400;
            }
        }
        if (railMode) {
            if (railMode == 3)
                dragThumb(y, s);
            else if ((int32_t)(millis() - repeatAt) >= 0 &&
                     in(RAIL_X, railMode == 1 ? 78 : 236, RAIL_W, 34, x, y)) {
                scrollTo((int)scrollTop() + (railMode == 1 ? -1 : 1), s);
                repeatAt = millis() + 160;
            }
            return;
        }
        if (abs((int)y - startY) > 10 || abs((int)x - startX) > 10)
            dragged = true;
        if ((page == 0 || page == 3) && dragged && startX >= 12 && startX < 416 && startY >= 78 && startY < 270) {
            int n = (int)startTop + (startY - (int)y) / 48;
            int max = maxTop(s);
            if (n < 0)
                n = 0;
            if (n > max)
                n = max;
            if (scrollTop() != (unsigned)n) {
                scrollTop() = n;
                dirty = true;
            }
        }
        return;
    }
    if (!down)
        return;
    // Tolerate a short missing sample on a resistive panel, without treating a drag as a tap.
    if (!releasedAt) {
        releasedAt = millis();
        return;
    }
    if ((uint32_t)(millis() - releasedAt) < 45)
        return;
    down = false;
    if (dragged || railMode)
        return;
    int px = startX, py = startY;
    if (in(408, 8, 60, 30, px, py)) {
        exitRequested = true;
        return;
    }
    if (py >= 284) {
        page = px < 240 ? 0 : 1;
        dirty = true;
        return;
    }
    if (in(324, 8, 76, 30, px, py)) {
        if (page == 3) {
            notice(jk_ble_scan());
            top = 0;
        }
        page = 3;
        dirty = true;
        return;
    }
    if (in(244, 8, 72, 30, px, py) &&
        (s.linkUp || s.state == JkState::Connecting || s.state == JkState::Discovering)) {
        notice(jk_ble_disconnect());
        return;
    }
    if (page == 3 && in(326, 44, 142, 26, px, py)) {
        notice(jk_ble_profile(s.profile == JkProfile::JK02_32S ? JkProfile::JK02_24S : JkProfile::JK02_32S));
        return;
    }
    if (page == 3 && py >= 78 && py < 270 && px >= 12 && px < 416 && (py - 78) % 48 < 43) {
        unsigned index = top + (py - 78) / 48;
        if (index < s.deviceCount)
            notice(jk_ble_connect(s.devices[index]));
    }
}
