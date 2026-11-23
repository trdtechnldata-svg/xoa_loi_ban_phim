#pragma once
#include <lvgl.h>
#ifdef __cplusplus
extern "C" {
#endif
lv_obj_t *speed_nav_create(lv_obj_t *screen);
void speed_nav_finish(void);
#ifdef __cplusplus
}
#endif
