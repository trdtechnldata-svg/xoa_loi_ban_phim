#pragma once
#include <lvgl.h>
#ifdef __cplusplus
extern "C" {
#endif
typedef enum { BATTERY_LFP35, BATTERY_B1, BATTERY_A1, BATTERY_LFP24, BATTERY_LFP12, BATTERY_PAGE_COUNT } battery_page_t;
bool battery_tabs_attach(lv_obj_t *screen, battery_page_t page);
#ifdef __cplusplus
}
#endif
