#pragma once
#include <lvgl.h>
#ifdef __cplusplus
extern "C" {
#endif
// The launcher callback requests entry; the loop owns all UI changes.
// Compatibility no-op: this version programs in loop(), with no worker allocation.
bool charger1000_prepare_worker(void);
void charger1000_launcher_event(lv_event_t *event);
void charger1000_poll(void);
bool charger1000_is_open(void);
// Existing home draw/input hooks: the flashing UI creates no LVGL widgets.
bool charger1000_draw_overlay(lv_event_t *event);
bool charger1000_capture_touch(uint16_t x, uint16_t y, bool pressed);
#ifdef __cplusplus
}
#endif
