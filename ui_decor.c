#include "ui_decor.h"
#include "charger1000.h"
#include <stdint.h>
#include <stddef.h>
/* Frames and icons are drawn directly. They allocate no LVGL widgets. */
static void frame(lv_draw_ctx_t *ctx, int ox, int oy, int x, int y,
                  int w, int h, int radius, uint32_t color, uint32_t border) {
    lv_draw_rect_dsc_t d;
    lv_draw_rect_dsc_init(&d);
    d.bg_color = lv_color_hex(color); d.bg_opa = LV_OPA_COVER;
    d.radius = radius; d.border_width = 1;
    d.border_color = lv_color_hex(border); d.border_opa = LV_OPA_COVER;
    lv_area_t a = { ox+x, oy+y, ox+x+w-1, oy+y+h-1 };
    lv_draw_rect(ctx, &d, &a);
}
static void caption(lv_draw_ctx_t *ctx, int ox, int oy, int x, int y,
                    int w, int h, const char *text, const lv_font_t *font, uint32_t color) {
    lv_draw_label_dsc_t d;
    lv_draw_label_dsc_init(&d); d.font = font; d.color = lv_color_hex(color);
    lv_area_t a = { ox+x, oy+y, ox+x+w-1, oy+y+h-1 };
    lv_draw_label(ctx, &d, &a, text, NULL);
}
static void stroke(lv_draw_ctx_t *ctx, int ox, int oy, int x1, int y1, int x2, int y2) {
    lv_draw_line_dsc_t d; lv_draw_line_dsc_init(&d);
    d.color = lv_color_hex(0xFFFFFF); d.width = 2; d.round_start = 1; d.round_end = 1;
    lv_point_t a = {ox+x1,oy+y1}, b = {ox+x2,oy+y2};
    lv_draw_line(ctx, &d, &a, &b);
}
static void icon_rect(lv_draw_ctx_t *ctx, int ox, int oy, int x, int y, int w, int h, int radius) {
    lv_draw_rect_dsc_t d; lv_draw_rect_dsc_init(&d);
    d.bg_opa = LV_OPA_TRANSP; d.radius = radius;
    d.border_width = 2; d.border_color = lv_color_hex(0xFFFFFF); d.border_opa = LV_OPA_COVER;
    lv_area_t a = {ox+x,oy+y,ox+x+w-1,oy+y+h-1}; lv_draw_rect(ctx,&d,&a);
}
static void screen_draw(lv_event_t *e) {
    if (charger1000_draw_overlay(e)) return;
    lv_obj_t *obj = lv_event_get_target(e);
    lv_draw_ctx_t *ctx = lv_event_get_draw_ctx(e);
    lv_area_t a; lv_obj_get_coords(obj,&a);
    switch ((unsigned)(uintptr_t)lv_event_get_user_data(e)) {
    case UI_DECOR_MAIN:
        frame(ctx,a.x1,a.y1,16,59,448,1,0,0x243D57,0x243D57);
        frame(ctx,a.x1,a.y1,220,315,40,3,1,0x7490AB,0x7490AB);
        caption(ctx,a.x1,a.y1,16,9,350,28,"BMS SERVICE",&lv_font_montserrat_24,0xF3F7FF);
        break;
    case UI_DECOR_MAIN_2:
        frame(ctx,a.x1,a.y1,12,48,144,182,10,0x132238,0x273D56);
        frame(ctx,a.x1,a.y1,166,48,302,182,10,0x132238,0x273D56);
        frame(ctx,a.x1,a.y1,22,79,124,1,0,0x20334B,0x20334B);
        frame(ctx,a.x1,a.y1,22,100,124,1,0,0x20334B,0x20334B);
        frame(ctx,a.x1,a.y1,22,121,124,1,0,0x20334B,0x20334B);
        frame(ctx,a.x1,a.y1,22,142,124,1,0,0x20334B,0x20334B);
        frame(ctx,a.x1,a.y1,22,163,124,1,0,0x20334B,0x20334B);
        frame(ctx,a.x1,a.y1,22,184,124,1,0,0x20334B,0x20334B);
        frame(ctx,a.x1,a.y1,22,205,124,1,0,0x20334B,0x20334B);
        frame(ctx,a.x1,a.y1,172,54,94,19,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,172,75,94,19,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,172,96,94,19,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,172,117,94,19,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,172,138,94,19,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,172,159,94,19,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,172,180,94,19,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,172,201,94,19,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,270,54,94,19,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,270,75,94,19,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,270,96,94,19,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,270,117,94,19,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,270,138,94,19,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,270,159,94,19,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,270,180,94,19,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,270,201,94,19,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,368,54,94,19,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,368,75,94,19,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,368,96,94,19,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,368,117,94,19,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,368,138,94,19,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,368,159,94,19,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,12,238,456,26,8,0x132238,0x273D56);
        frame(ctx,a.x1,a.y1,12,272,222,38,9,0x132238,0x273D56);
        frame(ctx,a.x1,a.y1,246,272,222,38,9,0x132238,0x273D56);
        caption(ctx,a.x1,a.y1,253,56,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,253,77,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,253,98,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,253,119,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,253,140,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,253,161,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,253,182,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,253,203,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,351,56,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,351,77,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,351,98,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,351,119,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,351,140,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,351,161,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,351,182,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,351,203,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,449,56,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,449,77,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,449,98,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,449,119,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,449,140,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,449,161,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,22,283,92,18,"DIEN AP",&lv_font_montserrat_14,0x8196B0);
        caption(ctx,a.x1,a.y1,256,283,92,18,"DONG DIEN",&lv_font_montserrat_14,0x8196B0);
        break;
    case UI_DECOR_MAIN_READ_B1:
        frame(ctx,a.x1,a.y1,12,48,144,182,10,0x132238,0x273D56);
        frame(ctx,a.x1,a.y1,166,48,302,182,10,0x132238,0x273D56);
        frame(ctx,a.x1,a.y1,22,79,124,1,0,0x20334B,0x20334B);
        frame(ctx,a.x1,a.y1,22,100,124,1,0,0x20334B,0x20334B);
        frame(ctx,a.x1,a.y1,22,121,124,1,0,0x20334B,0x20334B);
        frame(ctx,a.x1,a.y1,22,142,124,1,0,0x20334B,0x20334B);
        frame(ctx,a.x1,a.y1,22,163,124,1,0,0x20334B,0x20334B);
        frame(ctx,a.x1,a.y1,22,184,124,1,0,0x20334B,0x20334B);
        frame(ctx,a.x1,a.y1,22,205,124,1,0,0x20334B,0x20334B);
        frame(ctx,a.x1,a.y1,172,54,142,22,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,172,78,142,22,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,172,102,142,22,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,172,126,142,22,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,172,150,142,22,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,172,174,142,22,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,172,198,142,22,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,320,54,142,22,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,320,78,142,22,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,320,102,142,22,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,320,126,142,22,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,320,150,142,22,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,320,174,142,22,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,320,198,142,22,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,12,238,456,26,8,0x132238,0x273D56);
        frame(ctx,a.x1,a.y1,12,272,222,38,9,0x132238,0x273D56);
        frame(ctx,a.x1,a.y1,246,272,222,38,9,0x132238,0x273D56);
        caption(ctx,a.x1,a.y1,301,56,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,301,80,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,301,104,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,301,128,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,301,152,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,301,176,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,301,200,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,449,56,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,449,80,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,449,104,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,449,128,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,449,152,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,449,176,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,449,200,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,22,283,92,18,"DIEN AP",&lv_font_montserrat_14,0x8196B0);
        caption(ctx,a.x1,a.y1,256,283,92,18,"DONG DIEN",&lv_font_montserrat_14,0x8196B0);
        break;
    case UI_DECOR_MAIN_24KW:
        frame(ctx,a.x1,a.y1,12,48,144,182,10,0x132238,0x273D56);
        frame(ctx,a.x1,a.y1,166,48,302,182,10,0x132238,0x273D56);
        frame(ctx,a.x1,a.y1,22,79,124,1,0,0x20334B,0x20334B);
        frame(ctx,a.x1,a.y1,22,100,124,1,0,0x20334B,0x20334B);
        frame(ctx,a.x1,a.y1,22,121,124,1,0,0x20334B,0x20334B);
        frame(ctx,a.x1,a.y1,22,142,124,1,0,0x20334B,0x20334B);
        frame(ctx,a.x1,a.y1,22,163,124,1,0,0x20334B,0x20334B);
        frame(ctx,a.x1,a.y1,22,184,124,1,0,0x20334B,0x20334B);
        frame(ctx,a.x1,a.y1,22,205,124,1,0,0x20334B,0x20334B);
        frame(ctx,a.x1,a.y1,172,54,94,19,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,172,75,94,19,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,172,96,94,19,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,172,117,94,19,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,172,138,94,19,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,172,159,94,19,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,172,180,94,19,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,270,54,94,19,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,270,75,94,19,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,270,96,94,19,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,270,117,94,19,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,270,138,94,19,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,270,159,94,19,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,270,180,94,19,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,368,54,94,19,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,368,75,94,19,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,368,96,94,19,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,368,117,94,19,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,368,138,94,19,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,12,238,456,26,8,0x132238,0x273D56);
        frame(ctx,a.x1,a.y1,12,272,222,38,9,0x132238,0x273D56);
        frame(ctx,a.x1,a.y1,246,272,222,38,9,0x132238,0x273D56);
        caption(ctx,a.x1,a.y1,253,56,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,253,77,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,253,98,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,253,119,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,253,140,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,253,161,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,253,182,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,351,56,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,351,77,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,351,98,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,351,119,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,351,140,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,351,161,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,351,182,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,449,56,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,449,77,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,449,98,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,449,119,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,449,140,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,22,283,92,18,"DIEN AP",&lv_font_montserrat_14,0x8196B0);
        caption(ctx,a.x1,a.y1,256,283,92,18,"DONG DIEN",&lv_font_montserrat_14,0x8196B0);
        break;
    case UI_DECOR_PIN_1K2_MAIN:
        frame(ctx,a.x1,a.y1,12,48,144,182,10,0x132238,0x273D56);
        frame(ctx,a.x1,a.y1,166,48,302,182,10,0x132238,0x273D56);
        frame(ctx,a.x1,a.y1,22,79,124,1,0,0x20334B,0x20334B);
        frame(ctx,a.x1,a.y1,22,100,124,1,0,0x20334B,0x20334B);
        frame(ctx,a.x1,a.y1,22,121,124,1,0,0x20334B,0x20334B);
        frame(ctx,a.x1,a.y1,22,142,124,1,0,0x20334B,0x20334B);
        frame(ctx,a.x1,a.y1,22,163,124,1,0,0x20334B,0x20334B);
        frame(ctx,a.x1,a.y1,22,184,124,1,0,0x20334B,0x20334B);
        frame(ctx,a.x1,a.y1,22,205,124,1,0,0x20334B,0x20334B);
        frame(ctx,a.x1,a.y1,172,54,94,19,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,172,75,94,19,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,172,96,94,19,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,172,117,94,19,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,172,138,94,19,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,172,159,94,19,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,172,180,94,19,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,270,54,94,19,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,270,75,94,19,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,270,96,94,19,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,270,117,94,19,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,270,138,94,19,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,270,159,94,19,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,270,180,94,19,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,368,54,94,19,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,368,75,94,19,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,368,96,94,19,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,368,117,94,19,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,368,138,94,19,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,368,159,94,19,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,12,238,456,26,8,0x132238,0x273D56);
        frame(ctx,a.x1,a.y1,12,272,222,38,9,0x132238,0x273D56);
        frame(ctx,a.x1,a.y1,246,272,222,38,9,0x132238,0x273D56);
        caption(ctx,a.x1,a.y1,253,56,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,253,77,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,253,98,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,253,119,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,253,140,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,253,161,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,253,182,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,351,56,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,351,77,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,351,98,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,351,119,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,351,140,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,351,161,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,351,182,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,449,56,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,449,77,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,449,98,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,449,119,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,449,140,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,449,161,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,22,283,92,18,"DIEN AP",&lv_font_montserrat_14,0x8196B0);
        caption(ctx,a.x1,a.y1,256,283,92,18,"DONG DIEN",&lv_font_montserrat_14,0x8196B0);
        break;
    case UI_DECOR_BMS_JK:
        frame(ctx,a.x1,a.y1,12,48,144,160,10,0x132238,0x273D56);
        frame(ctx,a.x1,a.y1,166,48,302,194,10,0x132238,0x273D56);
        frame(ctx,a.x1,a.y1,172,54,94,21,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,172,77,94,21,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,172,100,94,21,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,172,123,94,21,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,172,146,94,21,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,172,169,94,21,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,172,192,94,21,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,172,215,94,21,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,270,54,94,21,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,270,77,94,21,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,270,100,94,21,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,270,123,94,21,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,270,146,94,21,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,270,169,94,21,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,270,192,94,21,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,270,215,94,21,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,368,54,94,21,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,368,77,94,21,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,368,100,94,21,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,368,123,94,21,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,368,146,94,21,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,368,169,94,21,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,368,192,94,21,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,368,215,94,21,5,0x192D44,0x2C4661);
        frame(ctx,a.x1,a.y1,12,248,456,24,6,0x132238,0x273D56);
        frame(ctx,a.x1,a.y1,12,280,456,30,8,0x132238,0x273D56);
        caption(ctx,a.x1,a.y1,16,10,118,28,"JK BMS",&lv_font_montserrat_22,0xF3F7FF);
        caption(ctx,a.x1,a.y1,253,56,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,253,79,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,253,102,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,253,125,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,253,148,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,253,171,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,253,194,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,253,217,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,351,56,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,351,79,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,351,102,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,351,125,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,351,148,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,351,171,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,351,194,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,351,217,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,449,56,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,449,79,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,449,102,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,449,125,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,449,148,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,449,171,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,449,194,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,449,217,12,18,"V",&lv_font_montserrat_14,0x66839D);
        caption(ctx,a.x1,a.y1,22,252,52,18,"PASS",&lv_font_montserrat_14,0x8196B0);
        caption(ctx,a.x1,a.y1,252,286,22,18,"V",&lv_font_montserrat_14,0x8196B0);
        caption(ctx,a.x1,a.y1,360,286,22,18,"A",&lv_font_montserrat_14,0x8196B0);
        break;
    case UI_DECOR_READ_A1:
        frame(ctx,a.x1,a.y1,12,48,186,202,10,0x132238,0x273D56);
        frame(ctx,a.x1,a.y1,210,48,258,202,10,0x132238,0x273D56);
        frame(ctx,a.x1,a.y1,12,270,222,40,10,0x132238,0x273D56);
        frame(ctx,a.x1,a.y1,246,270,222,40,10,0x132238,0x273D56);
        caption(ctx,a.x1,a.y1,22,283,92,18,"DIEN AP",&lv_font_montserrat_14,0x8196B0);
        caption(ctx,a.x1,a.y1,256,283,92,18,"DONG DIEN",&lv_font_montserrat_14,0x8196B0);
        break;
    }
}
static void app_draw(lv_event_t *e) {
    unsigned app = (unsigned)(uintptr_t)lv_event_get_user_data(e);
    if (app >= 12) return;
    lv_draw_ctx_t *ctx = lv_event_get_draw_ctx(e);
    lv_area_t a; lv_obj_get_coords(lv_event_get_target(e), &a);
    int ox = a.x1 + 28, oy = a.y1;
    static const uint32_t top[12] = {0x13B899, 0x4F8BFF, 0xA27BFF, 0x29BCD3, 0xF2B34D, 0x26BC99, 0x448CFF, 0xFF9E59, 0xA477F5, 0x54B5E5, 0xF47787, 0x43C4F0};
    static const uint32_t bottom[12] = {0x087D77, 0x2752CD, 0x7146C6, 0x087EAB, 0xD17A24, 0x087C6C, 0x2452C7, 0xDA5D3F, 0x6542B5, 0x2973B8, 0xBD3E62, 0x2369C0};
    /* Row gradient avoids version-specific draw-descriptor gradient fields. */
    static const uint8_t inset[13] = {9,7,5,4,3,2,2,1,1,1,0,0,0};
    lv_draw_rect_dsc_t d; lv_draw_rect_dsc_init(&d);
    d.bg_opa = LV_OPA_COVER; d.radius = 0; d.border_width = 0;
    for (int row = 0; row < 48; ++row) {
        int edge = row < 13 ? inset[row] : (row >= 35 ? inset[47-row] : 0);
        d.bg_color = lv_color_mix(lv_color_hex(top[app]), lv_color_hex(bottom[app]),
                                 (uint8_t)(255 - row * 255 / 47));
        lv_area_t strip = {ox+edge,oy+row,ox+47-edge,oy+row};
        lv_draw_rect(ctx,&d,&strip);
    }
    switch(app) {
    case 0:
        icon_rect(ctx,ox,oy,12,15,26,20,4);
        icon_rect(ctx,ox,oy,38,21,3,8,1);
        stroke(ctx,ox,oy,24,18,20,25);
        stroke(ctx,ox,oy,20,25,27,25);
        stroke(ctx,ox,oy,27,25,23,32);
        break;
    case 1:
        icon_rect(ctx,ox,oy,12,15,26,20,4);
        icon_rect(ctx,ox,oy,38,21,3,8,1);
        stroke(ctx,ox,oy,24,18,20,25);
        stroke(ctx,ox,oy,20,25,27,25);
        stroke(ctx,ox,oy,27,25,23,32);
        break;
    case 2:
        icon_rect(ctx,ox,oy,12,15,26,20,4);
        icon_rect(ctx,ox,oy,38,21,3,8,1);
        stroke(ctx,ox,oy,24,18,20,25);
        stroke(ctx,ox,oy,20,25,27,25);
        stroke(ctx,ox,oy,27,25,23,32);
        break;
    case 3:
        icon_rect(ctx,ox,oy,12,15,26,20,4);
        icon_rect(ctx,ox,oy,38,21,3,8,1);
        stroke(ctx,ox,oy,24,18,20,25);
        stroke(ctx,ox,oy,20,25,27,25);
        stroke(ctx,ox,oy,27,25,23,32);
        break;
    case 4:
        icon_rect(ctx,ox,oy,12,15,26,20,4);
        icon_rect(ctx,ox,oy,38,21,3,8,1);
        stroke(ctx,ox,oy,24,18,20,25);
        stroke(ctx,ox,oy,20,25,27,25);
        stroke(ctx,ox,oy,27,25,23,32);
        break;
    case 5:
        stroke(ctx,ox,oy,23,10,23,38);
        stroke(ctx,ox,oy,23,10,33,19);
        stroke(ctx,ox,oy,33,19,15,32);
        stroke(ctx,ox,oy,15,16,33,29);
        stroke(ctx,ox,oy,33,29,23,38);
        break;
    case 6:
        icon_rect(ctx,ox,oy,15,15,20,20,3);
        icon_rect(ctx,ox,oy,21,21,8,8,1);
        stroke(ctx,ox,oy,11,19,15,19);
        stroke(ctx,ox,oy,11,25,15,25);
        stroke(ctx,ox,oy,11,31,15,31);
        stroke(ctx,ox,oy,35,19,39,19);
        stroke(ctx,ox,oy,35,25,39,25);
        stroke(ctx,ox,oy,35,31,39,31);
        stroke(ctx,ox,oy,19,11,19,15);
        stroke(ctx,ox,oy,25,11,25,15);
        stroke(ctx,ox,oy,31,11,31,15);
        stroke(ctx,ox,oy,19,35,19,39);
        stroke(ctx,ox,oy,25,35,25,39);
        stroke(ctx,ox,oy,31,35,31,39);
        break;
    case 7:
        stroke(ctx,ox,oy,11,33,10,25);
        stroke(ctx,ox,oy,10,25,15,16);
        stroke(ctx,ox,oy,15,16,24,12);
        stroke(ctx,ox,oy,24,12,33,16);
        stroke(ctx,ox,oy,33,16,38,25);
        stroke(ctx,ox,oy,38,25,37,33);
        stroke(ctx,ox,oy,24,29,32,19);
        stroke(ctx,ox,oy,22,30,26,30);
        break;
    case 8:
        icon_rect(ctx,ox,oy,11,12,28,22,3);
        stroke(ctx,ox,oy,25,34,25,39);
        stroke(ctx,ox,oy,19,39,31,39);
        stroke(ctx,ox,oy,16,25,20,21);
        stroke(ctx,ox,oy,20,21,25,27);
        stroke(ctx,ox,oy,25,27,33,18);
        break;
    case 9:
        stroke(ctx,ox,oy,25,10,38,15);
        stroke(ctx,ox,oy,38,15,35,30);
        stroke(ctx,ox,oy,35,30,25,39);
        stroke(ctx,ox,oy,25,39,15,30);
        stroke(ctx,ox,oy,15,30,12,15);
        stroke(ctx,ox,oy,12,15,25,10);
        stroke(ctx,ox,oy,18,24,23,29);
        stroke(ctx,ox,oy,23,29,32,20);
        break;
    case 10:
        stroke(ctx,ox,oy,36,19,32,13);
        stroke(ctx,ox,oy,32,13,23,11);
        stroke(ctx,ox,oy,23,11,15,15);
        stroke(ctx,ox,oy,15,15,11,24);
        stroke(ctx,ox,oy,11,24,15,33);
        stroke(ctx,ox,oy,15,33,24,37);
        stroke(ctx,ox,oy,24,37,33,33);
        stroke(ctx,ox,oy,33,33,37,27);
        stroke(ctx,ox,oy,36,11,36,20);
        stroke(ctx,ox,oy,36,20,27,20);
        break;    case 11:
        stroke(ctx,ox,oy,24,10,24,29);
        stroke(ctx,ox,oy,16,22,24,30);
        stroke(ctx,ox,oy,24,30,32,22);
        stroke(ctx,ox,oy,12,30,12,38);
        stroke(ctx,ox,oy,12,38,36,38);
        stroke(ctx,ox,oy,36,38,36,30);
        break;

    }
}
void ui_decor_transparent(lv_obj_t *obj) {
    lv_obj_set_style_bg_opa(obj, LV_OPA_TRANSP, LV_PART_MAIN);
    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN);
    lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN);
    lv_obj_set_style_bg_opa(obj, LV_OPA_20, LV_PART_MAIN | LV_STATE_PRESSED);
}
void ui_decor_app(lv_obj_t *obj, unsigned app) {
    ui_decor_transparent(obj);
    lv_obj_add_event_cb(obj, app_draw, LV_EVENT_DRAW_MAIN, (void *)(uintptr_t)app);
}
void ui_decor_screen(lv_obj_t *obj, ui_decor_id_t id) {
    lv_obj_add_event_cb(obj, screen_draw, LV_EVENT_DRAW_MAIN, (void *)(uintptr_t)id);
}
