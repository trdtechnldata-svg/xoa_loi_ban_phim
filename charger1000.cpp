#include "charger1000.h"
#include "charger1000_protocol.h"
#include "charger1000_config.h"
#include "charger1000_diagnostics.h"
#include "esp_heap_caps.h"
#include "styles.h"
#include "screens.h"
#include <Arduino.h>
#include <ESP32-TWAI-CAN.hpp>
#include "esp_flash.h"
#include "esp_partition.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdio.h>

extern uint8_t xoa;
extern bool g_eez_event_is_available;

namespace {
struct ViewState { int screen, option, target, progress; uint8_t error; uint8_t reason; int32_t code; };
bool openRequested, active, busy, canReady;
// Reuse the existing home root. No screen, buttons, bars or labels are allocated.
static const unsigned MAX_HOME_CHILDREN = 64;
lv_obj_t *homeChildren[MAX_HOME_CHILDREN];
bool homeWasHidden[MAX_HOME_CHILDREN];
unsigned homeChildCount;
bool touchDown, eatUntilRelease;
int pendingAction = -1;
int32_t uiPulseX = -1, uiPulseY = -1;
ViewState shown = {0, 1, 0, 0, 0, 0, 0};

void render(const ViewState &v) {
    shown = v;
    if (active) lv_obj_invalidate(objects.main);
}
bool hideHome() {
    homeChildCount = lv_obj_get_child_cnt(objects.main);
    if (homeChildCount > MAX_HOME_CHILDREN) {
        Serial.println("[CHARGER] Home child snapshot capacity exceeded");
        homeChildCount = 0;
        return false;
    }
    for (unsigned i = 0; i < homeChildCount; ++i) {
        homeChildren[i] = lv_obj_get_child(objects.main, i);
        homeWasHidden[i] = lv_obj_has_flag(homeChildren[i], LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(homeChildren[i], LV_OBJ_FLAG_HIDDEN);
    }
    return true;
}
void restoreHome() {
    for (unsigned i = 0; i < homeChildCount; ++i) {
        if (homeWasHidden[i]) lv_obj_add_flag(homeChildren[i], LV_OBJ_FLAG_HIDDEN);
        else lv_obj_clear_flag(homeChildren[i], LV_OBJ_FLAG_HIDDEN);
        homeChildren[i] = nullptr;
    }
    homeChildCount = 0;
}
void logMemory(const char *stage) {
    const uint32_t caps = MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT;
    Serial.printf("[CHARGER] %s: ESP free=%u, internal free=%u, largest=%u\n",
                  stage, (unsigned)ESP.getFreeHeap(),
                  (unsigned)heap_caps_get_free_size(caps),
                  (unsigned)heap_caps_get_largest_free_block(caps));
}
void publish() { charger1000::hienThiManHinh(); }
void menu() {
    charger1000::screenState = 0;
    publish();
}

bool slotReady(uint32_t address) {
    const char *name = address == CHARGER_FW24_OFFSET ? "fw24" :
                       address == CHARGER_FW15_OFFSET ? "fw15" : nullptr;
    if (!name) return false;
    const esp_partition_t *p = esp_partition_find_first(ESP_PARTITION_TYPE_DATA,
                                                        (esp_partition_subtype_t)0x40, name);
    uint32_t flashSize = 0;
    bool ok = esp_flash_get_size(esp_flash_default_chip, &flashSize) == ESP_OK && p &&
              p->address == address && p->size == CHARGER_FW_SLOT_SIZE &&
              (uint64_t)address + CHARGER_FW_SLOT_SIZE <= flashSize;
    if (!ok) Serial.println("[CHARGER] Missing/resized firmware partition; refusing raw reads (E1)");
    return ok;
}

void runSession() {
    Serial.println("[CHARGER] Synchronous session running");
    logMemory("session entry");
    using namespace charger1000;
    // Same SELECT sequence and whole-session retry as the supplied OLED code.
    delay(200);
    progressVal = 0; screenState = 1; hienThiManHinh();
    delay(300);
    bool result = false;
    if (!slotReady(diaChiFlashFileHienTai)) {
        maLoiCuoi = LOI_FILE;
    } else {
        clearDiagnostic();
        result = napQuaCan(diaChiFlashFileHienTai);
        if (!result && maLoiCuoi != LOI_FILE) {
            delay(1000); progressVal = 0; hienThiManHinh();
            clearDiagnostic();
            result = napQuaCan(diaChiFlashFileHienTai);
        }
    }
    screenState = result ? targetScreen : 4;
    Diagnostics d = getDiagnostic();
    Serial.printf("[CHARGER] Session finished: E%u, %s, code=%ld\n",
                  (unsigned)maLoiCuoi, diagnosticLabel(d.reason), (long)d.code);
    hienThiManHinh();
}
void start() {
    using namespace charger1000;
    if (busy) return;
    Serial.printf("[CHARGER] SELECT: option=%d, canReady=%d\n",currentOption,(int)canReady);
    clearDiagnostic();
    if (!canReady) {
        setDiagnostic(DIAG_CAN_RELEASE,-1);
        maLoiCuoi=LOI_CAN; screenState=4; publish();
        return;
    }
    diaChiFlashFileHienTai = currentOption == 1 ? DIA_CHI_FILE_24 : DIA_CHI_FILE_15;
    targetScreen = currentOption == 1 ? 2 : 3;
    screenState = 1; progressVal = 0; maLoiCuoi = LOI_KHONG;
    busy = true;
    render({1,currentOption,targetScreen,0,LOI_KHONG,0,0});
    lv_refr_now(nullptr);
    logMemory("before synchronous session");
    Serial.printf("[CHARGER] Loop stack minimum before=%u\n",(unsigned)uxTaskGetStackHighWaterMark(nullptr));
    // Invoked only by poll(), outside LVGL input/draw handlers. Like the OLED
    // source, programming is synchronous; its display callbacks refresh TFT.
    runSession();
    busy = false;
    Serial.printf("[CHARGER] Loop stack minimum after=%u\n",(unsigned)uxTaskGetStackHighWaterMark(nullptr));
}

void controls(unsigned action) {
    if (busy) return;
    using namespace charger1000;
    if (action == 0) {
        // Restore the original wrapper only after the flashing driver is uninstalled.
        if (!ESP32Can.begin(ESP32Can.convertSpeed(250), TOOL_CAN_TX, TOOL_CAN_RX, 5, 5)) {
            screenState = 4; maLoiCuoi = LOI_CAN; setDiagnostic(DIAG_CAN_RESTORE, -1); publish();
            Serial.println("[CHARGER] Could not restore diagnostic CAN (E2)");
            return;
        }
        g_eez_event_is_available = false;
        xoa = 0;
        restoreHome();
        active = false; touchDown = false; eatUntilRelease = true;
        pendingAction = -1; uiPulseX = uiPulseY = -1;
        lv_obj_invalidate(objects.main);
        lv_refr_now(nullptr);
        Serial.println("[CHARGER] Home restored; diagnostic CAN running");
        return;
    }
    if (screenState >= 2) { menu(); return; }
    if (screenState != 0) return;
    if (action == 1 || action == 2) { currentOption = (int)action; publish(); }
    else if (action == 3) { currentOption = currentOption == 1 ? 2 : 1; publish(); }
    else if (action == 4) start();
}

} // namespace

namespace charger1000 {
void hienThiManHinh() {
    // All protocol calls now run in loop(). No task, queue or extra stack.
    Diagnostics d = getDiagnostic();
    ViewState v = {screenState,currentOption,targetScreen,progressVal,maLoiCuoi,d.reason,d.code};
    if (screenState >= 2) busy = false;
    render(v);
    if (active) lv_refr_now(nullptr);
}
}
extern "C" bool charger1000_prepare_worker(void) {
    // Compatibility entry point for older sketches; intentionally allocates nothing.
    Serial.println("[CHARGER] Main-loop mode: no worker stack reserved");
    return true;
}
extern "C" void charger1000_launcher_event(lv_event_t *) { openRequested = true; }
extern "C" bool charger1000_is_open(void) { return active || openRequested; }
extern "C" void charger1000_poll(void) {
    if (openRequested && !active) {
        openRequested = false;
        Serial.println("[CHARGER] Open requested");
        logMemory("before overlay");
        if (!objects.main || !hideHome()) return;
        charger1000::clearDiagnostic();
        xoa = 0; g_eez_event_is_available = false;
        active = true; busy = false;
        touchDown = false; pendingAction = -1;
        uiPulseX = uiPulseY = -1;
        charger1000::screenState = 0;
        Serial.println("[CHARGER] Releasing diagnostic CAN");
        canReady = ESP32Can.end();
        Serial.printf("[CHARGER] CAN released=%d\n", (int)canReady);
        if (!canReady) {
            charger1000::screenState = 4; charger1000::maLoiCuoi = charger1000::LOI_CAN;
            charger1000::setDiagnostic(charger1000::DIAG_CAN_RELEASE, -1);
            charger1000::Diagnostics d = charger1000::getDiagnostic();
            render({4, charger1000::currentOption, 0, 0, charger1000::LOI_CAN, d.reason, d.code});
        } else render({0, charger1000::currentOption, 0, 0, 0, 0, 0});
        lv_refr_now(nullptr); // Redraw all 320 rows using the existing 20-row buffer.
        logMemory("overlay ready");
    }
    if (!active) return;
    // Execute touch actions outside LVGL input/draw callbacks.
    if (pendingAction >= 0) {
        unsigned action = (unsigned)pendingAction;
        pendingAction = -1;
        controls(action);
    }
}

extern "C" bool charger1000_capture_touch(uint16_t x, uint16_t y, bool pressed) {
    if (eatUntilRelease) {
        if (!pressed) eatUntilRelease = false;
        return true;
    }
    if (!active) return openRequested;
    if (!pressed) {
        if (touchDown) {
            touchDown = false;
            uiPulseX = uiPulseY = -1;
            lv_obj_invalidate(objects.main);
        }
        return true;
    }
    if (!touchDown) {
        touchDown = true;
        uiPulseX = x; uiPulseY = y;
        lv_obj_invalidate(objects.main);
        if (!busy && pendingAction < 0) {
            if (x >= 388 && x < 464 && y >= 8 && y < 42) pendingAction = 0;
            else if (x >= 12 && x < 234 && y >= 262 && y < 308) pendingAction = 3;
            else if (x >= 246 && x < 468 && y >= 262 && y < 308 && canReady) pendingAction = 4;
            else if (shown.screen == 0 && x >= 12 && x < 468) {
                if (y >= 66 && y < 132) pendingAction = 1;
                else if (y >= 146 && y < 212) pendingAction = 2;
            }
        }
    }
    return true;
}

namespace {
void drawRect(lv_draw_ctx_t *ctx, const lv_area_t &root, int x, int y, int w, int h,
              uint32_t fill, uint32_t border, int radius = 10, int borderWidth = 1) {
    lv_draw_rect_dsc_t d; lv_draw_rect_dsc_init(&d);
    d.bg_color = lv_color_hex(fill); d.bg_opa = LV_OPA_COVER;
    d.border_color = lv_color_hex(border); d.border_opa = LV_OPA_COVER;
    d.border_width = borderWidth; d.radius = radius;
    lv_area_t a = { (lv_coord_t)(root.x1+x), (lv_coord_t)(root.y1+y),
                    (lv_coord_t)(root.x1+x+w-1), (lv_coord_t)(root.y1+y+h-1) };
    lv_draw_rect(ctx, &d, &a);
}
void drawText(lv_draw_ctx_t *ctx, const lv_area_t &root, int x, int y, int w, int h,
              const char *text, const lv_font_t *font, uint32_t color, bool center = true) {
    lv_draw_label_dsc_t d; lv_draw_label_dsc_init(&d);
    d.font = font; d.color = lv_color_hex(color);
    d.align = center ? LV_TEXT_ALIGN_CENTER : LV_TEXT_ALIGN_LEFT;
    lv_area_t a = { (lv_coord_t)(root.x1+x), (lv_coord_t)(root.y1+y),
                    (lv_coord_t)(root.x1+x+w-1), (lv_coord_t)(root.y1+y+h-1) };
    lv_draw_label(ctx, &d, &a, text, nullptr);
}
void drawButton(lv_draw_ctx_t *ctx, const lv_area_t &root, int x, int y, int w, int h,
                const char *text, bool enabled) {
    bool down = enabled && uiPulseX >= x && uiPulseX < x+w && uiPulseY >= y && uiPulseY < y+h;
    drawRect(ctx,root,x,y,w,h,down ? 0x29526A : 0x1B2C43,0x334A63);
    drawText(ctx,root,x,y+(h-22)/2,w,24,text,&lv_font_montserrat_18,enabled?0xE2E8F0:0x576C85);
}
}
extern "C" bool charger1000_draw_overlay(lv_event_t *event) {
    if (!active || lv_event_get_target(event) != objects.main) return false;
    lv_draw_ctx_t *ctx = lv_event_get_draw_ctx(event);
    lv_area_t r; lv_obj_get_coords(objects.main, &r);
    drawRect(ctx,r,0,0,480,320,0x0B1424,0x0B1424,0,0);
    drawText(ctx,r,16,10,352,30,"NAP SAC 1000W",&lv_font_montserrat_24,0xE2E8F0,false);
    drawButton(ctx,r,388,8,76,34,"BACK",!busy);
    if (shown.screen == 0) {
        drawRect(ctx,r,12,66,456,66,0x1B2C43,shown.option==1?0x5EEAD4:0x334A63,10,shown.option==1?2:1);
        drawText(ctx,r,12,87,456,26,shown.option==1?"> 1. Pin 2.4":"1. Pin 2.4",&lv_font_montserrat_18,0xE2E8F0);
        drawRect(ctx,r,12,146,456,66,0x1B2C43,shown.option==2?0x5EEAD4:0x334A63,10,shown.option==2?2:1);
        drawText(ctx,r,12,167,456,26,shown.option==2?"> 2. Pin 1.5":"2. Pin 1.5",&lv_font_montserrat_18,0xE2E8F0);
    } else {
        drawRect(ctx,r,12,60,456,182,0x152238,0x334A63);
        if (shown.screen == 1) {
            drawText(ctx,r,32,84,416,40,shown.target==2?"CAN 2.4...":"CAN 1.5...",&lv_font_montserrat_28,0xE2E8F0);
            char percent[12]; snprintf(percent,sizeof(percent),"%d%%",shown.progress);
            drawText(ctx,r,32,136,416,40,percent,&lv_font_montserrat_32,0xE2E8F0);
            drawRect(ctx,r,32,198,416,18,0x24354B,0x24354B,8,0);
            int percentValue = shown.progress < 0 ? 0 : (shown.progress > 100 ? 100 : shown.progress);
            int width = percentValue * 416 / 100;
            if (width) drawRect(ctx,r,32,198,width,18,0x2DD4BF,0x2DD4BF,8,0);
        } else if (shown.screen == 2 || shown.screen == 3) {
            drawText(ctx,r,32,84,416,40,shown.screen==2?"PIN 2.4 OK":"PIN 1.5 OK",&lv_font_montserrat_28,0xE2E8F0);
            drawText(ctx,r,32,146,416,44,">>>SUCCESS",&lv_font_montserrat_32,0x5EEAD4);
        } else {
            char error[24]; snprintf(error,sizeof(error),"FAILED E%d",shown.error);
            drawText(ctx,r,32,84,416,40,error,&lv_font_montserrat_28,0xFF8796);
            if (shown.error == charger1000::LOI_CAN && shown.reason) {
                char reason[64];
                snprintf(reason,sizeof(reason),"%s / 0x%lX",charger1000::diagnosticLabel(shown.reason),(unsigned long)(uint32_t)shown.code);
                drawText(ctx,r,32,146,416,32,reason,&lv_font_montserrat_18,0x9FB4CF);
            }
        }
    }
    drawButton(ctx,r,12,262,222,46,"NEXT",!busy);
    drawButton(ctx,r,246,262,222,46,"SELECT",!busy && canReady);
    return true;
}
