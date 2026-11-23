#include "styles.h"
static bool initialized;
static lv_style_t base, skin[14], pressed, checked, keys, key_pressed, indicator, arc_main, arc_indicator;
static lv_style_t fonts[8];
void ui_styles_init(void) {
    if (initialized) return;
    initialized = true;
    lv_style_init(&base);
    lv_style_set_shadow_width(&base, 0);
    lv_style_set_outline_width(&base, 0);
    lv_style_set_border_width(&base, 0);
    lv_style_set_bg_grad_dir(&base, LV_GRAD_DIR_NONE);
    lv_style_set_text_color(&base, lv_color_hex(0xE2E8F0));
    lv_style_set_text_opa(&base, LV_OPA_COVER);
    lv_style_set_align(&base, LV_ALIGN_TOP_LEFT);
    lv_style_init(&skin[0]);
    lv_style_set_bg_color(&skin[0], lv_color_hex(0x152A43));
    lv_style_set_bg_grad_color(&skin[0], lv_color_hex(0x080F20));
    lv_style_set_bg_grad_dir(&skin[0], LV_GRAD_DIR_VER);
    lv_style_set_bg_opa(&skin[0], LV_OPA_COVER);
    lv_style_set_radius(&skin[0], 0);
    lv_style_set_pad_all(&skin[0], 0);
    lv_style_init(&skin[1]);
    lv_style_set_bg_color(&skin[1], lv_color_hex(0x152238));
    lv_style_set_bg_opa(&skin[1], LV_OPA_COVER);
    lv_style_set_radius(&skin[1], 10);
    lv_style_set_border_width(&skin[1], 1);
    lv_style_set_border_color(&skin[1], lv_color_hex(0x334A63));
    lv_style_init(&skin[2]);
    lv_style_set_bg_color(&skin[2], lv_color_hex(0x1B2C43));
    lv_style_set_bg_opa(&skin[2], LV_OPA_COVER);
    lv_style_set_radius(&skin[2], 10);
    lv_style_set_pad_all(&skin[2], 0);
    lv_style_set_border_width(&skin[2], 1);
    lv_style_set_border_color(&skin[2], lv_color_hex(0x334A63));
    lv_style_init(&skin[3]);
    lv_style_set_bg_opa(&skin[3], LV_OPA_TRANSP);
    lv_style_set_pad_all(&skin[3], 0);
    lv_style_init(&skin[4]);
    lv_style_set_bg_color(&skin[4], lv_color_hex(0x24354B));
    lv_style_set_radius(&skin[4], 8);
    lv_style_init(&skin[5]);
    lv_style_init(&skin[6]);
    lv_style_set_bg_color(&skin[6], lv_color_hex(0x152238));
    lv_style_set_bg_opa(&skin[6], LV_OPA_COVER);
    lv_style_set_radius(&skin[6], 10);
    lv_style_set_border_width(&skin[6], 1);
    lv_style_set_border_color(&skin[6], lv_color_hex(0x334A63));
    lv_style_set_pad_all(&skin[6], 7);
    lv_style_init(&skin[7]);
    lv_style_set_bg_color(&skin[7], lv_color_hex(0x152238));
    lv_style_set_bg_opa(&skin[7], LV_OPA_COVER);
    lv_style_set_radius(&skin[7], 10);
    lv_style_set_border_width(&skin[7], 1);
    lv_style_set_border_color(&skin[7], lv_color_hex(0x334A63));
    lv_style_set_pad_all(&skin[7], 7);
    lv_style_init(&skin[8]);
    lv_style_set_bg_color(&skin[8], lv_color_hex(0x0B1220));
    lv_style_set_bg_opa(&skin[8], LV_OPA_COVER);
    lv_style_set_radius(&skin[8], 0);
    lv_style_set_pad_all(&skin[8], 4);
    lv_style_set_pad_row(&skin[8], 5);
    lv_style_set_pad_column(&skin[8], 5);
    lv_style_init(&skin[9]);
    lv_style_set_bg_color(&skin[9], lv_color_hex(0x24354B));
    lv_style_set_bg_opa(&skin[9], LV_OPA_COVER);
    lv_style_set_radius(&skin[9], 0);
    lv_style_set_pad_all(&skin[9], 0);
    lv_style_init(&skin[10]);
    lv_style_set_text_color(&skin[10], lv_color_hex(0x5EEAD4));
    lv_style_init(&skin[11]);
    lv_style_set_text_align(&skin[11], LV_TEXT_ALIGN_CENTER);
    lv_style_init(&skin[12]);
    lv_style_set_bg_color(&skin[12], lv_color_hex(0x134E4A));
    lv_style_set_border_color(&skin[12], lv_color_hex(0x238B80));
    lv_style_init(&skin[13]);
    lv_style_set_bg_color(&skin[13], lv_color_hex(0x4C2634));
    lv_style_set_border_color(&skin[13], lv_color_hex(0x9F4561));
    lv_style_init(&pressed);
    lv_style_init(&checked);
    lv_style_init(&keys);
    lv_style_init(&key_pressed);
    lv_style_init(&indicator);
    lv_style_init(&arc_main);
    lv_style_init(&arc_indicator);
    lv_style_set_bg_color(&pressed, lv_color_hex(0x29526A));
    lv_style_set_bg_color(&checked, lv_color_hex(0x0F766E));
    lv_style_set_bg_color(&keys, lv_color_hex(0x1B2C43));
    lv_style_set_text_color(&keys, lv_color_hex(0xE2E8F0));
    lv_style_set_radius(&keys, 7);
    lv_style_set_border_width(&keys, 0);
    lv_style_set_shadow_width(&keys, 0);
    lv_style_set_text_font(&keys, &lv_font_montserrat_18);
    lv_style_set_bg_color(&key_pressed, lv_color_hex(0x0F766E));
    lv_style_set_bg_color(&indicator, lv_color_hex(0x2DD4BF));
    lv_style_set_bg_opa(&indicator, LV_OPA_COVER);
    lv_style_set_radius(&indicator, 8);
    lv_style_set_outline_width(&indicator, 0);
    lv_style_set_arc_color(&arc_main, lv_color_hex(0x24354B));
    lv_style_set_arc_width(&arc_main, 8);
    lv_style_set_arc_color(&arc_indicator, lv_color_hex(0x2DD4BF));
    lv_style_set_arc_width(&arc_indicator, 8);
    lv_style_init(&fonts[0]);
    lv_style_set_text_font(&fonts[0], &lv_font_montserrat_14);
    lv_style_init(&fonts[1]);
    lv_style_set_text_font(&fonts[1], &lv_font_montserrat_16);
    lv_style_init(&fonts[2]);
    lv_style_set_text_font(&fonts[2], &lv_font_montserrat_18);
    lv_style_init(&fonts[3]);
    lv_style_set_text_font(&fonts[3], &lv_font_montserrat_20);
    lv_style_init(&fonts[4]);
    lv_style_set_text_font(&fonts[4], &lv_font_montserrat_22);
    lv_style_init(&fonts[5]);
    lv_style_set_text_font(&fonts[5], &lv_font_montserrat_24);
    lv_style_init(&fonts[6]);
    lv_style_set_text_font(&fonts[6], &lv_font_montserrat_28);
    lv_style_init(&fonts[7]);
    lv_style_set_text_font(&fonts[7], &lv_font_montserrat_32);
}
void ui_style_apply(lv_obj_t *obj, ui_style_kind_t kind) {
    if (kind <= UI_STYLE_SEPARATOR) lv_obj_add_style(obj, &base, LV_PART_MAIN);
    lv_obj_add_style(obj, &skin[kind], LV_PART_MAIN);
    if (kind == UI_STYLE_BTN) {
        lv_obj_add_style(obj, &pressed, LV_PART_MAIN | LV_STATE_PRESSED);
        lv_obj_add_style(obj, &checked, LV_PART_MAIN | LV_STATE_CHECKED);
    }
    if (kind == UI_STYLE_BAR) lv_obj_add_style(obj, &indicator, LV_PART_INDICATOR);
    if (kind == UI_STYLE_SPINNER) {
        lv_obj_add_style(obj, &arc_main, LV_PART_MAIN);
        lv_obj_add_style(obj, &arc_indicator, LV_PART_INDICATOR);
    }
    if (kind == UI_STYLE_KEYBOARD) {
        lv_obj_add_style(obj, &keys, LV_PART_ITEMS);
        lv_obj_add_style(obj, &key_pressed, LV_PART_ITEMS | LV_STATE_PRESSED);
    }
}
void ui_style_font(lv_obj_t *obj, unsigned size) {
    unsigned index = 1;
    switch(size) {
        case 14: index = 0; break;
        case 16: index = 1; break;
        case 18: index = 2; break;
        case 20: index = 3; break;
        case 22: index = 4; break;
        case 24: index = 5; break;
        case 28: index = 6; break;
        case 32: index = 7; break;
    }
    lv_obj_add_style(obj, &fonts[index], LV_PART_MAIN);
}
