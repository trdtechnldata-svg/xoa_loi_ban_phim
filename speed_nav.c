#include "speed_nav.h"
#include "styles.h"
#include <stdint.h>

static lv_obj_t *list, *slider, *up, *down;
static bool syncing;

static lv_coord_t limit(void) {
    lv_coord_t n = lv_obj_get_scroll_y(list) + lv_obj_get_scroll_bottom(list);
    return n > 0 ? n : 0;
}
static lv_coord_t clamp(lv_coord_t y, lv_coord_t max) {
    return y < 0 ? 0 : y > max ? max : y;
}
static void sync_scroll(lv_event_t *e) {
    (void)e;
    if (!slider || syncing) return;
    syncing = true;
    lv_coord_t max = limit(), y = clamp(lv_obj_get_scroll_y(list), max);
    lv_slider_set_range(slider, 0, max > 0 ? max : 1);
    /* A vertical LVGL slider has its maximum at the top. */
    lv_slider_set_value(slider, max - y, LV_ANIM_OFF);
    if (y == 0) lv_obj_add_state(up, LV_STATE_DISABLED);
    else lv_obj_clear_state(up, LV_STATE_DISABLED);
    if (y == max) lv_obj_add_state(down, LV_STATE_DISABLED);
    else lv_obj_clear_state(down, LV_STATE_DISABLED);
    syncing = false;
}
static void slide(lv_event_t *e) {
    (void)e;
    if (syncing) return;
    lv_coord_t max = limit();
    lv_obj_scroll_to_y(list, clamp(max - lv_slider_get_value(slider), max), LV_ANIM_OFF);
    sync_scroll(NULL);
}
static void arrow(lv_event_t *e) {
    lv_coord_t step = (intptr_t)lv_event_get_user_data(e) < 0 ? -62 : 62;
    lv_obj_scroll_to_y(list, clamp(lv_obj_get_scroll_y(list) + step, limit()), LV_ANIM_OFF);
    sync_scroll(NULL);
}
static lv_obj_t *make_arrow(lv_obj_t *screen, int y, const char *symbol, intptr_t direction) {
    lv_obj_t *btn = lv_btn_create(screen);
    if (!btn) return NULL;
    ui_style_apply(btn, UI_STYLE_BTN);
    lv_obj_set_pos(btn, 8, y); lv_obj_set_size(btn, 40, 40);
    lv_obj_clear_flag(btn, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_add_event_cb(btn, arrow, LV_EVENT_PRESSED, (void *)direction);
    lv_obj_add_event_cb(btn, arrow, LV_EVENT_LONG_PRESSED_REPEAT, (void *)direction);
    lv_obj_t *label = lv_label_create(btn);
    if (!label) return NULL;
    lv_label_set_text(label, symbol); lv_obj_center(label);
    return btn;
}
lv_obj_t *speed_nav_create(lv_obj_t *screen) {
    /* Root and navigation never scroll. Only the model list moves. */
    lv_obj_clear_flag(screen, LV_OBJ_FLAG_SCROLLABLE);
    list = lv_obj_create(screen);
    if (!list) return NULL;
    lv_obj_remove_style_all(list);
    lv_obj_set_pos(list, 60, 64); lv_obj_set_size(list, 404, 244);
    lv_obj_set_style_pad_all(list, 0, LV_PART_MAIN);
    lv_obj_set_scroll_dir(list, LV_DIR_VER);
    lv_obj_set_scrollbar_mode(list, LV_SCROLLBAR_MODE_OFF);
    lv_obj_clear_flag(list, LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM);
    up = make_arrow(screen, 64, LV_SYMBOL_UP, -1);
    down = make_arrow(screen, 268, LV_SYMBOL_DOWN, 1);
    slider = lv_slider_create(screen);
    if (!up || !down || !slider) return NULL;
    lv_obj_remove_style_all(slider);
    /* A broad track is easy to touch even on a resistive panel. */
    lv_obj_set_pos(slider, 8, 128); lv_obj_set_size(slider, 40, 116);
    lv_obj_set_style_bg_opa(slider, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_set_style_bg_color(slider, lv_color_hex(0x192D44), LV_PART_MAIN);
    lv_obj_set_style_radius(slider, 8, LV_PART_MAIN);
    lv_obj_set_style_bg_opa(slider, LV_OPA_TRANSP, LV_PART_INDICATOR);
    lv_obj_set_style_bg_opa(slider, LV_OPA_COVER, LV_PART_KNOB);
    lv_obj_set_style_bg_color(slider, lv_color_hex(0x2DD4BF), LV_PART_KNOB);
    lv_obj_set_style_radius(slider, 8, LV_PART_KNOB);
    lv_obj_set_style_pad_all(slider, 0, LV_PART_KNOB);
    lv_obj_clear_flag(slider, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_add_event_cb(slider, slide, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_add_event_cb(list, sync_scroll, LV_EVENT_SCROLL, NULL);
    return list;
}
void speed_nav_finish(void) {
    lv_obj_update_layout(list);
    sync_scroll(NULL);
}
