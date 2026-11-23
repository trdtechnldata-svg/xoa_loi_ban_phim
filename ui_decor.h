#ifndef UI_DECOR_H
#define UI_DECOR_H
#include <lvgl.h>
#ifdef __cplusplus
extern "C" {
#endif
typedef enum { UI_DECOR_MAIN, UI_DECOR_MAIN_2, UI_DECOR_MAIN_READ_B1, UI_DECOR_MAIN_24KW, UI_DECOR_PIN_1K2_MAIN, UI_DECOR_BMS_JK, UI_DECOR_READ_A1 } ui_decor_id_t;
void ui_decor_screen(lv_obj_t *obj, ui_decor_id_t id);
void ui_decor_app(lv_obj_t *obj, unsigned app);
void ui_decor_transparent(lv_obj_t *obj);
#ifdef __cplusplus
}
#endif
#endif
