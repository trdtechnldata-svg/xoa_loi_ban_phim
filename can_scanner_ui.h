#pragma once
#include <lvgl.h>
#ifdef __cplusplus
extern "C" {
#endif
void can_scanner_draw_event(lv_event_t *event);
bool can_scanner_capture_touch(uint16_t x, uint16_t y, bool pressed);
#ifdef __cplusplus
}
#endif
