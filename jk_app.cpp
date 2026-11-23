#include "jk_app.h"
#include "jk_ble.h"
#include "jk_ui.h"
#include "jk_display.h"
#include <Arduino.h>
extern void jk_tool_return_home();
namespace {
bool active = false, waitForRelease = false;
uint32_t releaseAt = 0;
JkSnapshot view{};
bool eatTouch(bool pressed) {
    if (!waitForRelease) return false;
    if (pressed) releaseAt = 0;
    else if (!releaseAt) releaseAt = millis();
    else if ((uint32_t)(millis() - releaseAt) >= 45) waitForRelease = false;
    return true;
}
}
void jk_app_open() {
    if (active) return;
    active = true;
    waitForRelease = true;
    releaseAt = 0;
    jk_ui_begin();
    if (!jk_ble_begin()) Serial.println("[JK] Worker unavailable; HOME remains usable");
    Serial.println("[JK] App opened");
}
bool jk_app_is_open() { return active; }
bool jk_app_capture_touch(uint16_t, uint16_t, bool pressed) {
    return active || eatTouch(pressed);
}
void jk_app_poll() {
    if (!active) return;
    jk_ble_snapshot(view);
    uint16_t x = 0, y = 0;
    bool pressed = jk_display_touch(x, y);
    if (!eatTouch(pressed)) jk_ui_touch(x, y, pressed, view);
    if (jk_ui_exit_requested()) {
        jk_ble_suspend();
        active = false;
        waitForRelease = true;
        releaseAt = 0;
        jk_tool_return_home();
        Serial.println("[JK] HOME restored");
        return;
    }
    jk_ui_tick(view);
}
