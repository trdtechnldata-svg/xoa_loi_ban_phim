#ifndef UI_NATIVE_STYLES_H
#define UI_NATIVE_STYLES_H
#include <lvgl.h>
#ifdef __cplusplus
extern "C" {
#endif
typedef enum { UI_STYLE_SCREEN, UI_STYLE_OBJ, UI_STYLE_BTN, UI_STYLE_LABEL, UI_STYLE_BAR, UI_STYLE_SPINNER, UI_STYLE_TEXTAREA, UI_STYLE_DROPDOWN, UI_STYLE_KEYBOARD, UI_STYLE_SEPARATOR, UI_STYLE_VALUE, UI_STYLE_CENTER, UI_STYLE_ACCENT, UI_STYLE_DANGER } ui_style_kind_t;
void ui_styles_init(void);
void ui_style_apply(lv_obj_t *obj, ui_style_kind_t kind);
void ui_style_font(lv_obj_t *obj, unsigned size);
bool ui_objects_ready(void);
#ifdef __cplusplus
}
#endif
#endif
