/* Hand-maintained LVGL 8.3 UI. No EEZ runtime or editor is required. */
#include "screens.h"
#include "styles.h"
#include "ui_decor.h"
#include "speed_nav.h"
#include "battery_tabs.h"
#include "can_scanner_ui.h"
#include "charger1000.h"
#include "actions.h"
#include <stddef.h>
objects_t objects;
lv_obj_t *tick_value_change_obj;
static bool ui_objects_ok = true;
bool ui_objects_ready(void) { return ui_objects_ok; }
void create_screen_main(void) {
    lv_obj_t *w[30];
    w[0] = lv_obj_create(0);
    if (!w[0]) { ui_objects_ok = false; return; }
    objects.main = w[0];
    ui_style_apply(w[0], UI_STYLE_SCREEN);
    lv_obj_set_pos(w[0], 0, 0);
    lv_obj_set_size(w[0], 480, 320);
    w[1] = lv_btn_create(w[0]);
    if (!w[1]) { ui_objects_ok = false; return; }
    objects.but_reset = w[1];
    ui_style_apply(w[1], UI_STYLE_BTN);
    lv_obj_add_event_cb(w[1], action_su_kien_tong, LV_EVENT_PRESSED, (void *)0);
    lv_obj_set_pos(w[1], 244, 226);
    lv_obj_set_size(w[1], 104, 78);
    ui_decor_app(w[1], 10);
    w[2] = lv_label_create(w[1]);
    if (!w[2]) { ui_objects_ok = false; return; }
    ui_style_apply(w[2], UI_STYLE_LABEL);
    lv_label_set_text(w[2], "Xoa loi");
    lv_obj_set_pos(w[2], 0, 54);
    lv_obj_set_size(w[2], 104, 22);
    ui_style_font(w[2], 14);
    lv_obj_set_style_align(w[2], LV_ALIGN_TOP_LEFT, LV_PART_MAIN);
    lv_obj_set_style_text_align(w[2], LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    w[3] = lv_btn_create(w[0]);
    if (!w[3]) { ui_objects_ok = false; return; }
    objects.read_pin_lfp = w[3];
    ui_style_apply(w[3], UI_STYLE_BTN);
    lv_obj_add_event_cb(w[3], action_su_kien_tong, LV_EVENT_PRESSED, (void *)0);
    lv_obj_set_pos(w[3], 16, 66);
    lv_obj_set_size(w[3], 104, 78);
    ui_decor_app(w[3], 0);
    w[4] = lv_label_create(w[3]);
    if (!w[4]) { ui_objects_ok = false; return; }
    ui_style_apply(w[4], UI_STYLE_LABEL);
    lv_label_set_text(w[4], "LFP 3.5kW");
    lv_obj_set_pos(w[4], 0, 54);
    lv_obj_set_size(w[4], 104, 22);
    ui_style_font(w[4], 14);
    lv_obj_set_style_align(w[4], LV_ALIGN_TOP_LEFT, LV_PART_MAIN);
    lv_obj_set_style_text_align(w[4], LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    w[5] = lv_btn_create(w[0]);
    if (!w[5]) { ui_objects_ok = false; return; }
    objects.read_pin_b1 = w[5];
    ui_style_apply(w[5], UI_STYLE_BTN);
    lv_obj_add_event_cb(w[5], action_su_kien_tong, LV_EVENT_PRESSED, (void *)0);
    lv_obj_set_pos(w[5], 130, 66);
    lv_obj_set_size(w[5], 104, 78);
    ui_decor_app(w[5], 1);
    w[6] = lv_label_create(w[5]);
    if (!w[6]) { ui_objects_ok = false; return; }
    ui_style_apply(w[6], UI_STYLE_LABEL);
    lv_label_set_text(w[6], "Pin B1");
    lv_obj_set_pos(w[6], 0, 54);
    lv_obj_set_size(w[6], 104, 22);
    ui_style_font(w[6], 14);
    lv_obj_set_style_align(w[6], LV_ALIGN_TOP_LEFT, LV_PART_MAIN);
    lv_obj_set_style_text_align(w[6], LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    w[7] = lv_btn_create(w[0]);
    if (!w[7]) { ui_objects_ok = false; return; }
    objects.read_pin_a1 = w[7];
    ui_style_apply(w[7], UI_STYLE_BTN);
    lv_obj_add_event_cb(w[7], action_su_kien_tong, LV_EVENT_PRESSED, (void *)0);
    lv_obj_set_pos(w[7], 244, 66);
    lv_obj_set_size(w[7], 104, 78);
    ui_decor_app(w[7], 2);
    w[8] = lv_label_create(w[7]);
    if (!w[8]) { ui_objects_ok = false; return; }
    ui_style_apply(w[8], UI_STYLE_LABEL);
    lv_label_set_text(w[8], "Klara A1");
    lv_obj_set_pos(w[8], 0, 54);
    lv_obj_set_size(w[8], 104, 22);
    ui_style_font(w[8], 14);
    lv_obj_set_style_align(w[8], LV_ALIGN_TOP_LEFT, LV_PART_MAIN);
    lv_obj_set_style_text_align(w[8], LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    w[9] = lv_btn_create(w[0]);
    if (!w[9]) { ui_objects_ok = false; return; }
    objects.load_ban_phim = w[9];
    ui_style_apply(w[9], UI_STYLE_BTN);
    lv_obj_add_event_cb(w[9], action_su_kien_tong, LV_EVENT_PRESSED, (void *)0);
    lv_obj_set_pos(w[9], 16, 6);
    lv_obj_set_size(w[9], 360, 50);
    ui_decor_transparent(w[9]);
    w[10] = lv_label_create(w[9]);
    if (!w[10]) { ui_objects_ok = false; return; }
    objects.text_gioi_thieu = w[10];
    ui_style_apply(w[10], UI_STYLE_LABEL);
    lv_label_set_long_mode(w[10], LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_label_set_text(w[10], "Diagnostic workstation");
    lv_obj_set_pos(w[10], 0, 28);
    lv_obj_set_size(w[10], 348, 18);
    ui_style_font(w[10], 14);
    lv_obj_set_style_align(w[10], LV_ALIGN_TOP_LEFT, LV_PART_MAIN);
    w[11] = lv_btn_create(w[0]);
    if (!w[11]) { ui_objects_ok = false; return; }
    objects.nut_bao_hanh = w[11];
    ui_style_apply(w[11], UI_STYLE_BTN);
    lv_obj_add_event_cb(w[11], action_su_kien_tong, LV_EVENT_PRESSED, (void *)0);
    lv_obj_set_pos(w[11], 130, 226);
    lv_obj_set_size(w[11], 104, 78);
    ui_decor_app(w[11], 9);
    w[12] = lv_label_create(w[11]);
    if (!w[12]) { ui_objects_ok = false; return; }
    objects.text_bao_hanh = w[12];
    ui_style_apply(w[12], UI_STYLE_LABEL);
    lv_label_set_text(w[12], "Bao hanh");
    lv_obj_set_pos(w[12], 0, 54);
    lv_obj_set_size(w[12], 104, 22);
    ui_style_font(w[12], 14);
    lv_obj_set_style_align(w[12], LV_ALIGN_TOP_LEFT, LV_PART_MAIN);
    lv_obj_set_style_text_align(w[12], LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    w[13] = lv_btn_create(w[0]);
    if (!w[13]) { ui_objects_ok = false; return; }
    objects.speed_up = w[13];
    ui_style_apply(w[13], UI_STYLE_BTN);
    lv_obj_add_event_cb(w[13], action_su_kien_tong, LV_EVENT_PRESSED, (void *)0);
    lv_obj_set_pos(w[13], 358, 146);
    lv_obj_set_size(w[13], 104, 78);
    ui_decor_app(w[13], 7);
    w[14] = lv_label_create(w[13]);
    if (!w[14]) { ui_objects_ok = false; return; }
    ui_style_apply(w[14], UI_STYLE_LABEL);
    lv_label_set_text(w[14], "Speed Up");
    lv_obj_set_pos(w[14], 0, 54);
    lv_obj_set_size(w[14], 104, 22);
    ui_style_font(w[14], 14);
    lv_obj_set_style_align(w[14], LV_ALIGN_TOP_LEFT, LV_PART_MAIN);
    lv_obj_set_style_text_align(w[14], LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    w[15] = lv_label_create(w[0]);
    if (!w[15]) { ui_objects_ok = false; return; }
    objects.batt_text = w[15];
    ui_style_apply(w[15], UI_STYLE_LABEL);
    lv_label_set_text(w[15], "100%");
    lv_obj_set_pos(w[15], 408, 14);
    lv_obj_set_size(w[15], 58, 22);
    ui_style_font(w[15], 16);
    w[16] = lv_bar_create(w[0]);
    if (!w[16]) { ui_objects_ok = false; return; }
    objects.batt_bar = w[16];
    ui_style_apply(w[16], UI_STYLE_BAR);
    lv_bar_set_value(w[16], 50, LV_ANIM_OFF);
    lv_obj_set_pos(w[16], 408, 42);
    lv_obj_set_size(w[16], 54, 6);
    w[17] = lv_btn_create(w[0]);
    if (!w[17]) { ui_objects_ok = false; return; }
    objects.can_read_butt = w[17];
    ui_style_apply(w[17], UI_STYLE_BTN);
    lv_obj_add_event_cb(w[17], action_su_kien_tong, LV_EVENT_PRESSED, (void *)0);
    lv_obj_set_pos(w[17], 244, 146);
    lv_obj_set_size(w[17], 104, 78);
    ui_decor_app(w[17], 6);
    w[18] = lv_label_create(w[17]);
    if (!w[18]) { ui_objects_ok = false; return; }
    ui_style_apply(w[18], UI_STYLE_LABEL);
    lv_label_set_text(w[18], "CAN Scanner");
    lv_obj_set_pos(w[18], 0, 54);
    lv_obj_set_size(w[18], 104, 22);
    ui_style_font(w[18], 14);
    lv_obj_set_style_align(w[18], LV_ALIGN_TOP_LEFT, LV_PART_MAIN);
    lv_obj_set_style_text_align(w[18], LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    w[19] = lv_btn_create(w[0]);
    if (!w[19]) { ui_objects_ok = false; return; }
    objects.butt_24 = w[19];
    ui_style_apply(w[19], UI_STYLE_BTN);
    lv_obj_add_event_cb(w[19], action_su_kien_tong, LV_EVENT_PRESSED, (void *)0);
    lv_obj_set_pos(w[19], 358, 66);
    lv_obj_set_size(w[19], 104, 78);
    ui_decor_app(w[19], 3);
    w[20] = lv_label_create(w[19]);
    if (!w[20]) { ui_objects_ok = false; return; }
    ui_style_apply(w[20], UI_STYLE_LABEL);
    lv_label_set_text(w[20], "Pin 2.4kW");
    lv_obj_set_pos(w[20], 0, 54);
    lv_obj_set_size(w[20], 104, 22);
    ui_style_font(w[20], 14);
    lv_obj_set_style_align(w[20], LV_ALIGN_TOP_LEFT, LV_PART_MAIN);
    lv_obj_set_style_text_align(w[20], LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    w[21] = lv_btn_create(w[0]);
    if (!w[21]) { ui_objects_ok = false; return; }
    ui_style_apply(w[21], UI_STYLE_SEPARATOR);
    lv_obj_set_pos(w[21], 0, 0);
    lv_obj_set_size(w[21], 0, 0);
    w[22] = lv_btn_create(w[0]);
    if (!w[22]) { ui_objects_ok = false; return; }
    objects.butt_bms_jk = w[22];
    ui_style_apply(w[22], UI_STYLE_BTN);
    lv_obj_add_event_cb(w[22], action_su_kien_tong, LV_EVENT_PRESSED, (void *)0);
    lv_obj_set_pos(w[22], 130, 146);
    lv_obj_set_size(w[22], 104, 78);
    ui_decor_app(w[22], 5);
    w[23] = lv_label_create(w[22]);
    if (!w[23]) { ui_objects_ok = false; return; }
    ui_style_apply(w[23], UI_STYLE_LABEL);
    lv_label_set_text(w[23], "JK BMS");
    lv_obj_set_pos(w[23], 0, 54);
    lv_obj_set_size(w[23], 104, 22);
    ui_style_font(w[23], 14);
    lv_obj_set_style_align(w[23], LV_ALIGN_TOP_LEFT, LV_PART_MAIN);
    lv_obj_set_style_text_align(w[23], LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    w[24] = lv_btn_create(w[0]);
    if (!w[24]) { ui_objects_ok = false; return; }
    objects.butt_1_2kw = w[24];
    ui_style_apply(w[24], UI_STYLE_BTN);
    lv_obj_add_event_cb(w[24], action_su_kien_tong, LV_EVENT_PRESSED, (void *)0);
    lv_obj_set_pos(w[24], 16, 146);
    lv_obj_set_size(w[24], 104, 78);
    ui_decor_app(w[24], 4);
    w[25] = lv_label_create(w[24]);
    if (!w[25]) { ui_objects_ok = false; return; }
    ui_style_apply(w[25], UI_STYLE_LABEL);
    lv_label_set_text(w[25], "Pin 1.2kW");
    lv_obj_set_pos(w[25], 0, 54);
    lv_obj_set_size(w[25], 104, 22);
    ui_style_font(w[25], 14);
    lv_obj_set_style_align(w[25], LV_ALIGN_TOP_LEFT, LV_PART_MAIN);
    lv_obj_set_style_text_align(w[25], LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    w[26] = lv_btn_create(w[0]);
    if (!w[26]) { ui_objects_ok = false; return; }
    objects.btn_test_hmi = w[26];
    ui_style_apply(w[26], UI_STYLE_BTN);
    lv_obj_add_event_cb(w[26], action_su_kien_tong, LV_EVENT_PRESSED, (void *)0);
    lv_obj_set_pos(w[26], 16, 226);
    lv_obj_set_size(w[26], 104, 78);
    ui_decor_app(w[26], 8);
    w[27] = lv_label_create(w[26]);
    if (!w[27]) { ui_objects_ok = false; return; }
    ui_style_apply(w[27], UI_STYLE_LABEL);
    lv_label_set_text(w[27], "HMI Test");
    lv_obj_set_pos(w[27], 0, 54);
    lv_obj_set_size(w[27], 104, 22);
    ui_style_font(w[27], 14);
    lv_obj_set_style_align(w[27], LV_ALIGN_TOP_LEFT, LV_PART_MAIN);
    lv_obj_set_style_text_align(w[27], LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    w[28] = lv_btn_create(w[0]);
    if (!w[28]) { ui_objects_ok = false; return; }
    ui_style_apply(w[28], UI_STYLE_SEPARATOR);
    lv_obj_set_pos(w[28], 0, 0);
    lv_obj_set_size(w[28], 0, 0);
    w[29] = lv_label_create(w[28]);
    if (!w[29]) { ui_objects_ok = false; return; }
    ui_style_apply(w[29], UI_STYLE_LABEL);
    lv_obj_set_pos(w[29], 0, 0);
    lv_obj_set_size(w[29], LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_style_align(w[29], LV_ALIGN_CENTER, LV_PART_MAIN);
    lv_label_set_text(w[29], "");
    ui_style_font(w[29], 18);
    /* Twelfth app; original objects_t and screen indices stay intact. */
    lv_obj_t *flash_app = lv_btn_create(objects.main);
    if (!flash_app) { ui_objects_ok = false; return; }
    ui_style_apply(flash_app, UI_STYLE_BTN);
    lv_obj_set_pos(flash_app, 358, 226); lv_obj_set_size(flash_app, 104, 78);
    ui_decor_app(flash_app, 11);
    lv_obj_add_event_cb(flash_app, charger1000_launcher_event, LV_EVENT_CLICKED, NULL);
    lv_obj_t *flash_caption = lv_label_create(flash_app);
    if (!flash_caption) { ui_objects_ok = false; return; }
    ui_style_apply(flash_caption, UI_STYLE_LABEL); ui_style_font(flash_caption, 14);
    lv_obj_set_pos(flash_caption, 0, 54); lv_obj_set_size(flash_caption, 104, 22);
    lv_obj_set_style_text_align(flash_caption, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    lv_label_set_text(flash_caption, "Nap 1000W");
}
void tick_screen_main(void) {}
void create_screen_main_2(void) {
    lv_obj_t *w[80];
    w[0] = lv_obj_create(0);
    if (!w[0]) { ui_objects_ok = false; return; }
    objects.main_2 = w[0];
    ui_style_apply(w[0], UI_STYLE_SCREEN);
    lv_obj_set_pos(w[0], 0, 0);
    lv_obj_set_size(w[0], 480, 320);
    w[1] = lv_btn_create(w[0]);
    if (!w[1]) { ui_objects_ok = false; return; }
    objects.nut_back = w[1];
    ui_style_apply(w[1], UI_STYLE_BTN);
    lv_obj_add_event_cb(w[1], action_su_kien_tong, LV_EVENT_PRESSED, (void *)0);
    lv_obj_set_pos(w[1], 388, 8);
    lv_obj_set_size(w[1], 76, 32);
    w[2] = lv_label_create(w[1]);
    if (!w[2]) { ui_objects_ok = false; return; }
    ui_style_apply(w[2], UI_STYLE_LABEL);
    lv_obj_set_pos(w[2], 0, 0);
    lv_obj_set_size(w[2], LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_style_align(w[2], LV_ALIGN_CENTER, LV_PART_MAIN);
    lv_label_set_text(w[2], "BACK");
    ui_style_font(w[2], 16);
    w[3] = lv_label_create(w[0]);
    if (!w[3]) { ui_objects_ok = false; return; }
    ui_style_apply(w[3], UI_STYLE_LABEL);
    lv_label_set_text(w[3], "SOC");
    lv_obj_set_pos(w[3], 22, 58);
    lv_obj_set_size(w[3], 56, 20);
    ui_style_font(w[3], 14);
    w[4] = lv_label_create(w[0]);
    if (!w[4]) { ui_objects_ok = false; return; }
    ui_style_apply(w[4], UI_STYLE_LABEL);
    lv_label_set_text(w[4], "Cycle");
    lv_obj_set_pos(w[4], 22, 79);
    lv_obj_set_size(w[4], 56, 20);
    ui_style_font(w[4], 14);
    w[5] = lv_label_create(w[0]);
    if (!w[5]) { ui_objects_ok = false; return; }
    ui_style_apply(w[5], UI_STYLE_LABEL);
    lv_label_set_text(w[5], "Delvol");
    lv_obj_set_pos(w[5], 22, 100);
    lv_obj_set_size(w[5], 56, 20);
    ui_style_font(w[5], 14);
    w[6] = lv_label_create(w[0]);
    if (!w[6]) { ui_objects_ok = false; return; }
    ui_style_apply(w[6], UI_STYLE_LABEL);
    lv_label_set_text(w[6], "Vmax");
    lv_obj_set_pos(w[6], 22, 121);
    lv_obj_set_size(w[6], 56, 20);
    ui_style_font(w[6], 14);
    w[7] = lv_label_create(w[0]);
    if (!w[7]) { ui_objects_ok = false; return; }
    ui_style_apply(w[7], UI_STYLE_LABEL);
    lv_label_set_text(w[7], "Vmin");
    lv_obj_set_pos(w[7], 22, 142);
    lv_obj_set_size(w[7], 56, 20);
    ui_style_font(w[7], 14);
    w[8] = lv_label_create(w[0]);
    if (!w[8]) { ui_objects_ok = false; return; }
    ui_style_apply(w[8], UI_STYLE_LABEL);
    lv_label_set_text(w[8], "RCAP");
    lv_obj_set_pos(w[8], 22, 163);
    lv_obj_set_size(w[8], 56, 20);
    ui_style_font(w[8], 14);
    w[9] = lv_label_create(w[0]);
    if (!w[9]) { ui_objects_ok = false; return; }
    ui_style_apply(w[9], UI_STYLE_LABEL);
    lv_label_set_text(w[9], "SOH");
    lv_obj_set_pos(w[9], 22, 184);
    lv_obj_set_size(w[9], 56, 20);
    ui_style_font(w[9], 14);
    w[10] = lv_label_create(w[0]);
    if (!w[10]) { ui_objects_ok = false; return; }
    ui_style_apply(w[10], UI_STYLE_LABEL);
    lv_label_set_text(w[10], "T_6:");
    lv_obj_set_pos(w[10], 390, 243);
    lv_obj_set_size(w[10], 39, 18);
    ui_style_font(w[10], 14);
    w[11] = lv_label_create(w[0]);
    if (!w[11]) { ui_objects_ok = false; return; }
    ui_style_apply(w[11], UI_STYLE_LABEL);
    lv_label_set_text(w[11], "T_5:");
    lv_obj_set_pos(w[11], 316, 243);
    lv_obj_set_size(w[11], 39, 18);
    ui_style_font(w[11], 14);
    w[12] = lv_label_create(w[0]);
    if (!w[12]) { ui_objects_ok = false; return; }
    objects.soc = w[12];
    ui_style_apply(w[12], UI_STYLE_LABEL);
    lv_label_set_text(w[12], "00");
    ui_style_apply(w[12], UI_STYLE_VALUE);
    lv_obj_set_pos(w[12], 81, 56);
    lv_obj_set_size(w[12], 68, 22);
    ui_style_font(w[12], 16);
    w[13] = lv_label_create(w[0]);
    if (!w[13]) { ui_objects_ok = false; return; }
    objects.cycle = w[13];
    ui_style_apply(w[13], UI_STYLE_LABEL);
    lv_label_set_text(w[13], "00");
    ui_style_apply(w[13], UI_STYLE_VALUE);
    lv_obj_set_pos(w[13], 81, 77);
    lv_obj_set_size(w[13], 68, 22);
    ui_style_font(w[13], 16);
    w[14] = lv_label_create(w[0]);
    if (!w[14]) { ui_objects_ok = false; return; }
    objects.del_vol = w[14];
    ui_style_apply(w[14], UI_STYLE_LABEL);
    lv_label_set_text(w[14], "00");
    ui_style_apply(w[14], UI_STYLE_VALUE);
    lv_obj_set_pos(w[14], 81, 98);
    lv_obj_set_size(w[14], 68, 22);
    ui_style_font(w[14], 16);
    w[15] = lv_label_create(w[0]);
    if (!w[15]) { ui_objects_ok = false; return; }
    objects.v_max_lfp = w[15];
    ui_style_apply(w[15], UI_STYLE_LABEL);
    lv_label_set_text(w[15], "00");
    ui_style_apply(w[15], UI_STYLE_VALUE);
    lv_obj_set_pos(w[15], 81, 119);
    lv_obj_set_size(w[15], 68, 22);
    ui_style_font(w[15], 16);
    w[16] = lv_label_create(w[0]);
    if (!w[16]) { ui_objects_ok = false; return; }
    objects.v_min_lfp = w[16];
    ui_style_apply(w[16], UI_STYLE_LABEL);
    lv_label_set_text(w[16], "00");
    ui_style_apply(w[16], UI_STYLE_VALUE);
    lv_obj_set_pos(w[16], 81, 140);
    lv_obj_set_size(w[16], 68, 22);
    ui_style_font(w[16], 16);
    w[17] = lv_label_create(w[0]);
    if (!w[17]) { ui_objects_ok = false; return; }
    objects.soh_lfp = w[17];
    ui_style_apply(w[17], UI_STYLE_LABEL);
    lv_label_set_text(w[17], "00");
    ui_style_apply(w[17], UI_STYLE_VALUE);
    lv_obj_set_pos(w[17], 81, 182);
    lv_obj_set_size(w[17], 68, 22);
    ui_style_font(w[17], 16);
    w[18] = lv_label_create(w[0]);
    if (!w[18]) { ui_objects_ok = false; return; }
    objects.rcap_lfp = w[18];
    ui_style_apply(w[18], UI_STYLE_LABEL);
    lv_label_set_text(w[18], "00");
    ui_style_apply(w[18], UI_STYLE_VALUE);
    lv_obj_set_pos(w[18], 81, 161);
    lv_obj_set_size(w[18], 68, 22);
    ui_style_font(w[18], 16);
    w[19] = lv_label_create(w[0]);
    if (!w[19]) { ui_objects_ok = false; return; }
    objects.avg_lfp = w[19];
    ui_style_apply(w[19], UI_STYLE_LABEL);
    lv_label_set_text(w[19], "00");
    ui_style_apply(w[19], UI_STYLE_VALUE);
    lv_obj_set_pos(w[19], 81, 203);
    lv_obj_set_size(w[19], 68, 22);
    ui_style_font(w[19], 16);
    w[20] = lv_label_create(w[0]);
    if (!w[20]) { ui_objects_ok = false; return; }
    objects.t_6 = w[20];
    ui_style_apply(w[20], UI_STYLE_LABEL);
    lv_label_set_text(w[20], "00");
    ui_style_apply(w[20], UI_STYLE_VALUE);
    lv_obj_set_pos(w[20], 428, 242);
    lv_obj_set_size(w[20], 33, 20);
    ui_style_font(w[20], 14);
    w[21] = lv_label_create(w[0]);
    if (!w[21]) { ui_objects_ok = false; return; }
    ui_style_apply(w[21], UI_STYLE_LABEL);
    lv_label_set_text(w[21], "08");
    lv_obj_set_pos(w[21], 176, 203);
    lv_obj_set_size(w[21], 23, 18);
    ui_style_font(w[21], 14);
    lv_obj_set_style_text_color(w[21], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[22] = lv_label_create(w[0]);
    if (!w[22]) { ui_objects_ok = false; return; }
    ui_style_apply(w[22], UI_STYLE_LABEL);
    lv_label_set_text(w[22], "09");
    lv_obj_set_pos(w[22], 274, 56);
    lv_obj_set_size(w[22], 23, 18);
    ui_style_font(w[22], 14);
    lv_obj_set_style_text_color(w[22], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[23] = lv_label_create(w[0]);
    if (!w[23]) { ui_objects_ok = false; return; }
    ui_style_apply(w[23], UI_STYLE_LABEL);
    lv_label_set_text(w[23], "10");
    lv_obj_set_pos(w[23], 274, 77);
    lv_obj_set_size(w[23], 23, 18);
    ui_style_font(w[23], 14);
    lv_obj_set_style_text_color(w[23], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[24] = lv_label_create(w[0]);
    if (!w[24]) { ui_objects_ok = false; return; }
    ui_style_apply(w[24], UI_STYLE_LABEL);
    lv_label_set_text(w[24], "11");
    lv_obj_set_pos(w[24], 274, 98);
    lv_obj_set_size(w[24], 23, 18);
    ui_style_font(w[24], 14);
    lv_obj_set_style_text_color(w[24], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[25] = lv_label_create(w[0]);
    if (!w[25]) { ui_objects_ok = false; return; }
    ui_style_apply(w[25], UI_STYLE_LABEL);
    lv_label_set_text(w[25], "12");
    lv_obj_set_pos(w[25], 274, 119);
    lv_obj_set_size(w[25], 23, 18);
    ui_style_font(w[25], 14);
    lv_obj_set_style_text_color(w[25], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[26] = lv_label_create(w[0]);
    if (!w[26]) { ui_objects_ok = false; return; }
    ui_style_apply(w[26], UI_STYLE_LABEL);
    lv_label_set_text(w[26], "13");
    lv_obj_set_pos(w[26], 274, 140);
    lv_obj_set_size(w[26], 23, 18);
    ui_style_font(w[26], 14);
    lv_obj_set_style_text_color(w[26], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[27] = lv_label_create(w[0]);
    if (!w[27]) { ui_objects_ok = false; return; }
    ui_style_apply(w[27], UI_STYLE_LABEL);
    lv_label_set_text(w[27], "14");
    lv_obj_set_pos(w[27], 274, 161);
    lv_obj_set_size(w[27], 23, 18);
    ui_style_font(w[27], 14);
    lv_obj_set_style_text_color(w[27], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[28] = lv_label_create(w[0]);
    if (!w[28]) { ui_objects_ok = false; return; }
    ui_style_apply(w[28], UI_STYLE_LABEL);
    lv_label_set_text(w[28], "15");
    lv_obj_set_pos(w[28], 274, 182);
    lv_obj_set_size(w[28], 23, 18);
    ui_style_font(w[28], 14);
    lv_obj_set_style_text_color(w[28], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[29] = lv_label_create(w[0]);
    if (!w[29]) { ui_objects_ok = false; return; }
    ui_style_apply(w[29], UI_STYLE_LABEL);
    lv_label_set_text(w[29], "16");
    lv_obj_set_pos(w[29], 274, 203);
    lv_obj_set_size(w[29], 23, 18);
    ui_style_font(w[29], 14);
    lv_obj_set_style_text_color(w[29], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[30] = lv_label_create(w[0]);
    if (!w[30]) { ui_objects_ok = false; return; }
    objects.cell_8 = w[30];
    ui_style_apply(w[30], UI_STYLE_LABEL);
    lv_label_set_text(w[30], "000");
    ui_style_apply(w[30], UI_STYLE_VALUE);
    lv_obj_set_pos(w[30], 201, 202);
    lv_obj_set_size(w[30], 50, 20);
    ui_style_font(w[30], 14);
    w[31] = lv_label_create(w[0]);
    if (!w[31]) { ui_objects_ok = false; return; }
    objects.cell_9 = w[31];
    ui_style_apply(w[31], UI_STYLE_LABEL);
    lv_label_set_text(w[31], "000");
    ui_style_apply(w[31], UI_STYLE_VALUE);
    lv_obj_set_pos(w[31], 299, 55);
    lv_obj_set_size(w[31], 50, 20);
    ui_style_font(w[31], 14);
    w[32] = lv_label_create(w[0]);
    if (!w[32]) { ui_objects_ok = false; return; }
    objects.cell_10 = w[32];
    ui_style_apply(w[32], UI_STYLE_LABEL);
    lv_label_set_text(w[32], "000");
    ui_style_apply(w[32], UI_STYLE_VALUE);
    lv_obj_set_pos(w[32], 299, 76);
    lv_obj_set_size(w[32], 50, 20);
    ui_style_font(w[32], 14);
    w[33] = lv_label_create(w[0]);
    if (!w[33]) { ui_objects_ok = false; return; }
    objects.cell_11 = w[33];
    ui_style_apply(w[33], UI_STYLE_LABEL);
    lv_label_set_text(w[33], "000");
    ui_style_apply(w[33], UI_STYLE_VALUE);
    lv_obj_set_pos(w[33], 299, 97);
    lv_obj_set_size(w[33], 50, 20);
    ui_style_font(w[33], 14);
    w[34] = lv_label_create(w[0]);
    if (!w[34]) { ui_objects_ok = false; return; }
    objects.cell_12 = w[34];
    ui_style_apply(w[34], UI_STYLE_LABEL);
    lv_label_set_text(w[34], "000");
    ui_style_apply(w[34], UI_STYLE_VALUE);
    lv_obj_set_pos(w[34], 299, 118);
    lv_obj_set_size(w[34], 50, 20);
    ui_style_font(w[34], 14);
    w[35] = lv_label_create(w[0]);
    if (!w[35]) { ui_objects_ok = false; return; }
    objects.cell_13 = w[35];
    ui_style_apply(w[35], UI_STYLE_LABEL);
    lv_label_set_text(w[35], "000");
    ui_style_apply(w[35], UI_STYLE_VALUE);
    lv_obj_set_pos(w[35], 299, 139);
    lv_obj_set_size(w[35], 50, 20);
    ui_style_font(w[35], 14);
    w[36] = lv_label_create(w[0]);
    if (!w[36]) { ui_objects_ok = false; return; }
    objects.cell_14 = w[36];
    ui_style_apply(w[36], UI_STYLE_LABEL);
    lv_label_set_text(w[36], "000");
    ui_style_apply(w[36], UI_STYLE_VALUE);
    lv_obj_set_pos(w[36], 299, 160);
    lv_obj_set_size(w[36], 50, 20);
    ui_style_font(w[36], 14);
    w[37] = lv_label_create(w[0]);
    if (!w[37]) { ui_objects_ok = false; return; }
    ui_style_apply(w[37], UI_STYLE_LABEL);
    lv_label_set_text(w[37], "17");
    lv_obj_set_pos(w[37], 372, 56);
    lv_obj_set_size(w[37], 23, 18);
    ui_style_font(w[37], 14);
    lv_obj_set_style_text_color(w[37], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[38] = lv_label_create(w[0]);
    if (!w[38]) { ui_objects_ok = false; return; }
    ui_style_apply(w[38], UI_STYLE_LABEL);
    lv_label_set_text(w[38], "18");
    lv_obj_set_pos(w[38], 372, 77);
    lv_obj_set_size(w[38], 23, 18);
    ui_style_font(w[38], 14);
    lv_obj_set_style_text_color(w[38], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[39] = lv_label_create(w[0]);
    if (!w[39]) { ui_objects_ok = false; return; }
    ui_style_apply(w[39], UI_STYLE_LABEL);
    lv_label_set_text(w[39], "19");
    lv_obj_set_pos(w[39], 372, 98);
    lv_obj_set_size(w[39], 23, 18);
    ui_style_font(w[39], 14);
    lv_obj_set_style_text_color(w[39], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[40] = lv_label_create(w[0]);
    if (!w[40]) { ui_objects_ok = false; return; }
    ui_style_apply(w[40], UI_STYLE_LABEL);
    lv_label_set_text(w[40], "20");
    lv_obj_set_pos(w[40], 372, 119);
    lv_obj_set_size(w[40], 23, 18);
    ui_style_font(w[40], 14);
    lv_obj_set_style_text_color(w[40], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[41] = lv_label_create(w[0]);
    if (!w[41]) { ui_objects_ok = false; return; }
    ui_style_apply(w[41], UI_STYLE_LABEL);
    lv_label_set_text(w[41], "21");
    lv_obj_set_pos(w[41], 372, 140);
    lv_obj_set_size(w[41], 23, 18);
    ui_style_font(w[41], 14);
    lv_obj_set_style_text_color(w[41], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[42] = lv_label_create(w[0]);
    if (!w[42]) { ui_objects_ok = false; return; }
    objects.cell_15 = w[42];
    ui_style_apply(w[42], UI_STYLE_LABEL);
    lv_label_set_text(w[42], "000");
    ui_style_apply(w[42], UI_STYLE_VALUE);
    lv_obj_set_pos(w[42], 299, 181);
    lv_obj_set_size(w[42], 50, 20);
    ui_style_font(w[42], 14);
    w[43] = lv_label_create(w[0]);
    if (!w[43]) { ui_objects_ok = false; return; }
    objects.cell_16 = w[43];
    ui_style_apply(w[43], UI_STYLE_LABEL);
    lv_label_set_text(w[43], "000");
    ui_style_apply(w[43], UI_STYLE_VALUE);
    lv_obj_set_pos(w[43], 299, 202);
    lv_obj_set_size(w[43], 50, 20);
    ui_style_font(w[43], 14);
    w[44] = lv_label_create(w[0]);
    if (!w[44]) { ui_objects_ok = false; return; }
    objects.cell_17 = w[44];
    ui_style_apply(w[44], UI_STYLE_LABEL);
    lv_label_set_text(w[44], "000");
    ui_style_apply(w[44], UI_STYLE_VALUE);
    lv_obj_set_pos(w[44], 397, 55);
    lv_obj_set_size(w[44], 50, 20);
    ui_style_font(w[44], 14);
    w[45] = lv_label_create(w[0]);
    if (!w[45]) { ui_objects_ok = false; return; }
    objects.cell_18 = w[45];
    ui_style_apply(w[45], UI_STYLE_LABEL);
    lv_label_set_text(w[45], "000");
    ui_style_apply(w[45], UI_STYLE_VALUE);
    lv_obj_set_pos(w[45], 397, 76);
    lv_obj_set_size(w[45], 50, 20);
    ui_style_font(w[45], 14);
    w[46] = lv_label_create(w[0]);
    if (!w[46]) { ui_objects_ok = false; return; }
    objects.cell_19 = w[46];
    ui_style_apply(w[46], UI_STYLE_LABEL);
    lv_label_set_text(w[46], "000");
    ui_style_apply(w[46], UI_STYLE_VALUE);
    lv_obj_set_pos(w[46], 397, 97);
    lv_obj_set_size(w[46], 50, 20);
    ui_style_font(w[46], 14);
    w[47] = lv_label_create(w[0]);
    if (!w[47]) { ui_objects_ok = false; return; }
    objects.cell_20 = w[47];
    ui_style_apply(w[47], UI_STYLE_LABEL);
    lv_label_set_text(w[47], "000");
    ui_style_apply(w[47], UI_STYLE_VALUE);
    lv_obj_set_pos(w[47], 397, 118);
    lv_obj_set_size(w[47], 50, 20);
    ui_style_font(w[47], 14);
    w[48] = lv_label_create(w[0]);
    if (!w[48]) { ui_objects_ok = false; return; }
    objects.cell_21 = w[48];
    ui_style_apply(w[48], UI_STYLE_LABEL);
    lv_label_set_text(w[48], "000");
    ui_style_apply(w[48], UI_STYLE_VALUE);
    lv_obj_set_pos(w[48], 397, 139);
    lv_obj_set_size(w[48], 50, 20);
    ui_style_font(w[48], 14);
    w[49] = lv_label_create(w[0]);
    if (!w[49]) { ui_objects_ok = false; return; }
    ui_style_apply(w[49], UI_STYLE_LABEL);
    lv_label_set_text(w[49], "01");
    lv_obj_set_pos(w[49], 176, 56);
    lv_obj_set_size(w[49], 23, 18);
    ui_style_font(w[49], 14);
    lv_obj_set_style_text_color(w[49], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[50] = lv_label_create(w[0]);
    if (!w[50]) { ui_objects_ok = false; return; }
    ui_style_apply(w[50], UI_STYLE_LABEL);
    lv_label_set_text(w[50], "02");
    lv_obj_set_pos(w[50], 176, 77);
    lv_obj_set_size(w[50], 23, 18);
    ui_style_font(w[50], 14);
    lv_obj_set_style_text_color(w[50], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[51] = lv_label_create(w[0]);
    if (!w[51]) { ui_objects_ok = false; return; }
    ui_style_apply(w[51], UI_STYLE_LABEL);
    lv_label_set_text(w[51], "03");
    lv_obj_set_pos(w[51], 176, 98);
    lv_obj_set_size(w[51], 23, 18);
    ui_style_font(w[51], 14);
    lv_obj_set_style_text_color(w[51], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[52] = lv_label_create(w[0]);
    if (!w[52]) { ui_objects_ok = false; return; }
    ui_style_apply(w[52], UI_STYLE_LABEL);
    lv_label_set_text(w[52], "04");
    lv_obj_set_pos(w[52], 176, 119);
    lv_obj_set_size(w[52], 23, 18);
    ui_style_font(w[52], 14);
    lv_obj_set_style_text_color(w[52], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[53] = lv_label_create(w[0]);
    if (!w[53]) { ui_objects_ok = false; return; }
    ui_style_apply(w[53], UI_STYLE_LABEL);
    lv_label_set_text(w[53], "05");
    lv_obj_set_pos(w[53], 176, 140);
    lv_obj_set_size(w[53], 23, 18);
    ui_style_font(w[53], 14);
    lv_obj_set_style_text_color(w[53], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[54] = lv_label_create(w[0]);
    if (!w[54]) { ui_objects_ok = false; return; }
    ui_style_apply(w[54], UI_STYLE_LABEL);
    lv_label_set_text(w[54], "06");
    lv_obj_set_pos(w[54], 176, 161);
    lv_obj_set_size(w[54], 23, 18);
    ui_style_font(w[54], 14);
    lv_obj_set_style_text_color(w[54], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[55] = lv_label_create(w[0]);
    if (!w[55]) { ui_objects_ok = false; return; }
    ui_style_apply(w[55], UI_STYLE_LABEL);
    lv_label_set_text(w[55], "07");
    lv_obj_set_pos(w[55], 176, 182);
    lv_obj_set_size(w[55], 23, 18);
    ui_style_font(w[55], 14);
    lv_obj_set_style_text_color(w[55], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[56] = lv_label_create(w[0]);
    if (!w[56]) { ui_objects_ok = false; return; }
    objects.cell_1 = w[56];
    ui_style_apply(w[56], UI_STYLE_LABEL);
    lv_label_set_text(w[56], "000");
    ui_style_apply(w[56], UI_STYLE_VALUE);
    lv_obj_set_pos(w[56], 201, 55);
    lv_obj_set_size(w[56], 50, 20);
    ui_style_font(w[56], 14);
    w[57] = lv_label_create(w[0]);
    if (!w[57]) { ui_objects_ok = false; return; }
    objects.cell_2 = w[57];
    ui_style_apply(w[57], UI_STYLE_LABEL);
    lv_label_set_text(w[57], "000");
    ui_style_apply(w[57], UI_STYLE_VALUE);
    lv_obj_set_pos(w[57], 201, 76);
    lv_obj_set_size(w[57], 50, 20);
    ui_style_font(w[57], 14);
    w[58] = lv_label_create(w[0]);
    if (!w[58]) { ui_objects_ok = false; return; }
    objects.cell_3 = w[58];
    ui_style_apply(w[58], UI_STYLE_LABEL);
    lv_label_set_text(w[58], "000");
    ui_style_apply(w[58], UI_STYLE_VALUE);
    lv_obj_set_pos(w[58], 201, 97);
    lv_obj_set_size(w[58], 50, 20);
    ui_style_font(w[58], 14);
    w[59] = lv_label_create(w[0]);
    if (!w[59]) { ui_objects_ok = false; return; }
    objects.cell_4 = w[59];
    ui_style_apply(w[59], UI_STYLE_LABEL);
    lv_label_set_text(w[59], "000");
    ui_style_apply(w[59], UI_STYLE_VALUE);
    lv_obj_set_pos(w[59], 201, 118);
    lv_obj_set_size(w[59], 50, 20);
    ui_style_font(w[59], 14);
    w[60] = lv_label_create(w[0]);
    if (!w[60]) { ui_objects_ok = false; return; }
    objects.cell_5 = w[60];
    ui_style_apply(w[60], UI_STYLE_LABEL);
    lv_label_set_text(w[60], "000");
    ui_style_apply(w[60], UI_STYLE_VALUE);
    lv_obj_set_pos(w[60], 201, 139);
    lv_obj_set_size(w[60], 50, 20);
    ui_style_font(w[60], 14);
    w[61] = lv_label_create(w[0]);
    if (!w[61]) { ui_objects_ok = false; return; }
    objects.cell_6 = w[61];
    ui_style_apply(w[61], UI_STYLE_LABEL);
    lv_label_set_text(w[61], "000");
    ui_style_apply(w[61], UI_STYLE_VALUE);
    lv_obj_set_pos(w[61], 201, 160);
    lv_obj_set_size(w[61], 50, 20);
    ui_style_font(w[61], 14);
    w[62] = lv_label_create(w[0]);
    if (!w[62]) { ui_objects_ok = false; return; }
    objects.cell_7 = w[62];
    ui_style_apply(w[62], UI_STYLE_LABEL);
    lv_label_set_text(w[62], "000");
    ui_style_apply(w[62], UI_STYLE_VALUE);
    lv_obj_set_pos(w[62], 201, 181);
    lv_obj_set_size(w[62], 50, 20);
    ui_style_font(w[62], 14);
    w[63] = lv_label_create(w[0]);
    if (!w[63]) { ui_objects_ok = false; return; }
    objects.cell_22 = w[63];
    ui_style_apply(w[63], UI_STYLE_LABEL);
    lv_label_set_text(w[63], "000");
    ui_style_apply(w[63], UI_STYLE_VALUE);
    lv_obj_set_pos(w[63], 397, 160);
    lv_obj_set_size(w[63], 50, 20);
    ui_style_font(w[63], 14);
    w[64] = lv_label_create(w[0]);
    if (!w[64]) { ui_objects_ok = false; return; }
    ui_style_apply(w[64], UI_STYLE_LABEL);
    lv_label_set_text(w[64], "22");
    lv_obj_set_pos(w[64], 372, 161);
    lv_obj_set_size(w[64], 23, 18);
    ui_style_font(w[64], 14);
    lv_obj_set_style_text_color(w[64], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[65] = lv_label_create(w[0]);
    if (!w[65]) { ui_objects_ok = false; return; }
    ui_style_apply(w[65], UI_STYLE_LABEL);
    lv_label_set_text(w[65], "T_3:");
    lv_obj_set_pos(w[65], 168, 243);
    lv_obj_set_size(w[65], 39, 18);
    ui_style_font(w[65], 14);
    w[66] = lv_label_create(w[0]);
    if (!w[66]) { ui_objects_ok = false; return; }
    ui_style_apply(w[66], UI_STYLE_LABEL);
    lv_label_set_text(w[66], "T_4:");
    lv_obj_set_pos(w[66], 242, 243);
    lv_obj_set_size(w[66], 39, 18);
    ui_style_font(w[66], 14);
    w[67] = lv_label_create(w[0]);
    if (!w[67]) { ui_objects_ok = false; return; }
    ui_style_apply(w[67], UI_STYLE_LABEL);
    lv_label_set_text(w[67], "AVG");
    lv_obj_set_pos(w[67], 22, 205);
    lv_obj_set_size(w[67], 56, 20);
    ui_style_font(w[67], 14);
    w[68] = lv_label_create(w[0]);
    if (!w[68]) { ui_objects_ok = false; return; }
    objects.t_5 = w[68];
    ui_style_apply(w[68], UI_STYLE_LABEL);
    lv_label_set_text(w[68], "00");
    ui_style_apply(w[68], UI_STYLE_VALUE);
    lv_obj_set_pos(w[68], 354, 242);
    lv_obj_set_size(w[68], 33, 20);
    ui_style_font(w[68], 14);
    w[69] = lv_label_create(w[0]);
    if (!w[69]) { ui_objects_ok = false; return; }
    objects.t_3 = w[69];
    ui_style_apply(w[69], UI_STYLE_LABEL);
    lv_label_set_text(w[69], "00");
    ui_style_apply(w[69], UI_STYLE_VALUE);
    lv_obj_set_pos(w[69], 206, 242);
    lv_obj_set_size(w[69], 33, 20);
    ui_style_font(w[69], 14);
    w[70] = lv_label_create(w[0]);
    if (!w[70]) { ui_objects_ok = false; return; }
    objects.t_4 = w[70];
    ui_style_apply(w[70], UI_STYLE_LABEL);
    lv_label_set_text(w[70], "00");
    ui_style_apply(w[70], UI_STYLE_VALUE);
    lv_obj_set_pos(w[70], 280, 242);
    lv_obj_set_size(w[70], 33, 20);
    ui_style_font(w[70], 14);
    w[71] = lv_label_create(w[0]);
    if (!w[71]) { ui_objects_ok = false; return; }
    objects.text_vol_lfp = w[71];
    ui_style_apply(w[71], UI_STYLE_LABEL);
    lv_label_set_text(w[71], "00");
    ui_style_apply(w[71], UI_STYLE_VALUE);
    lv_obj_set_pos(w[71], 114, 279);
    lv_obj_set_size(w[71], 112, 28);
    ui_style_font(w[71], 22);
    w[72] = lv_label_create(w[0]);
    if (!w[72]) { ui_objects_ok = false; return; }
    objects.ampe_lfp = w[72];
    ui_style_apply(w[72], UI_STYLE_LABEL);
    lv_label_set_text(w[72], "00");
    ui_style_apply(w[72], UI_STYLE_VALUE);
    lv_obj_set_pos(w[72], 348, 279);
    lv_obj_set_size(w[72], 112, 28);
    ui_style_font(w[72], 22);
    w[73] = lv_label_create(w[0]);
    if (!w[73]) { ui_objects_ok = false; return; }
    ui_style_apply(w[73], UI_STYLE_LABEL);
    lv_label_set_text(w[73], "T_1:");
    lv_obj_set_pos(w[73], 20, 243);
    lv_obj_set_size(w[73], 39, 18);
    ui_style_font(w[73], 14);
    w[74] = lv_label_create(w[0]);
    if (!w[74]) { ui_objects_ok = false; return; }
    ui_style_apply(w[74], UI_STYLE_LABEL);
    lv_label_set_text(w[74], "T_2:");
    lv_obj_set_pos(w[74], 94, 243);
    lv_obj_set_size(w[74], 39, 18);
    ui_style_font(w[74], 14);
    w[75] = lv_label_create(w[0]);
    if (!w[75]) { ui_objects_ok = false; return; }
    objects.t_2 = w[75];
    ui_style_apply(w[75], UI_STYLE_LABEL);
    lv_label_set_text(w[75], "00");
    ui_style_apply(w[75], UI_STYLE_VALUE);
    lv_obj_set_pos(w[75], 58, 242);
    lv_obj_set_size(w[75], 33, 20);
    ui_style_font(w[75], 14);
    w[76] = lv_label_create(w[0]);
    if (!w[76]) { ui_objects_ok = false; return; }
    objects.t_1 = w[76];
    ui_style_apply(w[76], UI_STYLE_LABEL);
    lv_label_set_text(w[76], "00");
    ui_style_apply(w[76], UI_STYLE_VALUE);
    lv_obj_set_pos(w[76], 132, 242);
    lv_obj_set_size(w[76], 33, 20);
    ui_style_font(w[76], 14);
    w[77] = lv_btn_create(w[0]);
    if (!w[77]) { ui_objects_ok = false; return; }
    ui_style_apply(w[77], UI_STYLE_SEPARATOR);
    lv_obj_set_pos(w[77], 0, 0);
    lv_obj_set_size(w[77], 0, 0);
    w[78] = lv_label_create(w[0]);
    if (!w[78]) { ui_objects_ok = false; return; }
    ui_style_apply(w[78], UI_STYLE_LABEL);
    lv_label_set_text(w[78], "%");
    lv_obj_set_pos(w[78], 133, 58);
    lv_obj_set_size(w[78], 16, 20);
    ui_style_font(w[78], 14);
    w[79] = lv_label_create(w[0]);
    if (!w[79]) { ui_objects_ok = false; return; }
    ui_style_apply(w[79], UI_STYLE_LABEL);
    lv_label_set_long_mode(w[79], LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_label_set_text(w[79], "LFP 3.5 kW");
    ui_style_apply(w[79], UI_STYLE_VALUE);
    lv_obj_set_pos(w[79], 16, 10);
    lv_obj_set_size(w[79], 350, 28);
    ui_style_font(w[79], 22);
}
void tick_screen_main_2(void) {}
void create_screen_main_thong_bao(void) {
    lv_obj_t *w[3];
    w[0] = lv_obj_create(0);
    if (!w[0]) { ui_objects_ok = false; return; }
    objects.main_thong_bao = w[0];
    ui_style_apply(w[0], UI_STYLE_SCREEN);
    lv_obj_set_pos(w[0], 0, 0);
    lv_obj_set_size(w[0], 480, 320);
    w[1] = lv_label_create(w[0]);
    if (!w[1]) { ui_objects_ok = false; return; }
    ui_style_apply(w[1], UI_STYLE_LABEL);
    lv_obj_set_pos(w[1], 64, 190);
    lv_obj_set_size(w[1], 352, 76);
    lv_label_set_text(w[1], "DANG XOA LOI\nVui long cho...");
    ui_style_font(w[1], 24);
    ui_style_apply(w[1], UI_STYLE_CENTER);
    w[2] = lv_spinner_create(w[0], 1000, 60);
    if (!w[2]) { ui_objects_ok = false; return; }
    ui_style_apply(w[2], UI_STYLE_SPINNER);
    lv_obj_set_pos(w[2], 192, 60);
    lv_obj_set_size(w[2], 96, 96);
}
void tick_screen_main_thong_bao(void) {}
void create_screen_main_read_b1(void) {
    lv_obj_t *w[63];
    w[0] = lv_obj_create(0);
    if (!w[0]) { ui_objects_ok = false; return; }
    objects.main_read_b1 = w[0];
    ui_style_apply(w[0], UI_STYLE_SCREEN);
    lv_obj_set_pos(w[0], 0, 0);
    lv_obj_set_size(w[0], 480, 320);
    w[1] = lv_label_create(w[0]);
    if (!w[1]) { ui_objects_ok = false; return; }
    ui_style_apply(w[1], UI_STYLE_LABEL);
    lv_label_set_text(w[1], "SOC");
    lv_obj_set_pos(w[1], 22, 58);
    lv_obj_set_size(w[1], 56, 20);
    ui_style_font(w[1], 14);
    w[2] = lv_label_create(w[0]);
    if (!w[2]) { ui_objects_ok = false; return; }
    ui_style_apply(w[2], UI_STYLE_LABEL);
    lv_label_set_text(w[2], "Cycle");
    lv_obj_set_pos(w[2], 22, 79);
    lv_obj_set_size(w[2], 56, 20);
    ui_style_font(w[2], 14);
    w[3] = lv_label_create(w[0]);
    if (!w[3]) { ui_objects_ok = false; return; }
    ui_style_apply(w[3], UI_STYLE_LABEL);
    lv_label_set_text(w[3], "Delvol");
    lv_obj_set_pos(w[3], 22, 100);
    lv_obj_set_size(w[3], 56, 20);
    ui_style_font(w[3], 14);
    w[4] = lv_label_create(w[0]);
    if (!w[4]) { ui_objects_ok = false; return; }
    ui_style_apply(w[4], UI_STYLE_LABEL);
    lv_label_set_text(w[4], "Vmax");
    lv_obj_set_pos(w[4], 22, 121);
    lv_obj_set_size(w[4], 56, 20);
    ui_style_font(w[4], 14);
    w[5] = lv_label_create(w[0]);
    if (!w[5]) { ui_objects_ok = false; return; }
    ui_style_apply(w[5], UI_STYLE_LABEL);
    lv_label_set_text(w[5], "Vmin");
    lv_obj_set_pos(w[5], 22, 142);
    lv_obj_set_size(w[5], 56, 20);
    ui_style_font(w[5], 14);
    w[6] = lv_label_create(w[0]);
    if (!w[6]) { ui_objects_ok = false; return; }
    ui_style_apply(w[6], UI_STYLE_LABEL);
    lv_label_set_text(w[6], "SOH");
    lv_obj_set_pos(w[6], 22, 184);
    lv_obj_set_size(w[6], 56, 20);
    ui_style_font(w[6], 14);
    w[7] = lv_label_create(w[0]);
    if (!w[7]) { ui_objects_ok = false; return; }
    ui_style_apply(w[7], UI_STYLE_LABEL);
    lv_label_set_text(w[7], "RCAP");
    lv_obj_set_pos(w[7], 22, 163);
    lv_obj_set_size(w[7], 56, 20);
    ui_style_font(w[7], 14);
    w[8] = lv_label_create(w[0]);
    if (!w[8]) { ui_objects_ok = false; return; }
    objects.soc_b1 = w[8];
    ui_style_apply(w[8], UI_STYLE_LABEL);
    lv_label_set_text(w[8], "00");
    ui_style_apply(w[8], UI_STYLE_VALUE);
    lv_obj_set_pos(w[8], 81, 56);
    lv_obj_set_size(w[8], 68, 22);
    ui_style_font(w[8], 16);
    w[9] = lv_label_create(w[0]);
    if (!w[9]) { ui_objects_ok = false; return; }
    objects.cycle_b1 = w[9];
    ui_style_apply(w[9], UI_STYLE_LABEL);
    lv_label_set_text(w[9], "00");
    ui_style_apply(w[9], UI_STYLE_VALUE);
    lv_obj_set_pos(w[9], 81, 77);
    lv_obj_set_size(w[9], 68, 22);
    ui_style_font(w[9], 16);
    w[10] = lv_label_create(w[0]);
    if (!w[10]) { ui_objects_ok = false; return; }
    objects.del_vol_b1 = w[10];
    ui_style_apply(w[10], UI_STYLE_LABEL);
    lv_label_set_text(w[10], "00");
    ui_style_apply(w[10], UI_STYLE_VALUE);
    lv_obj_set_pos(w[10], 81, 98);
    lv_obj_set_size(w[10], 68, 22);
    ui_style_font(w[10], 16);
    w[11] = lv_label_create(w[0]);
    if (!w[11]) { ui_objects_ok = false; return; }
    objects.v_max_b1 = w[11];
    ui_style_apply(w[11], UI_STYLE_LABEL);
    lv_label_set_text(w[11], "00");
    ui_style_apply(w[11], UI_STYLE_VALUE);
    lv_obj_set_pos(w[11], 81, 119);
    lv_obj_set_size(w[11], 68, 22);
    ui_style_font(w[11], 16);
    w[12] = lv_label_create(w[0]);
    if (!w[12]) { ui_objects_ok = false; return; }
    objects.v_min_b1 = w[12];
    ui_style_apply(w[12], UI_STYLE_LABEL);
    lv_label_set_text(w[12], "00");
    ui_style_apply(w[12], UI_STYLE_VALUE);
    lv_obj_set_pos(w[12], 81, 140);
    lv_obj_set_size(w[12], 68, 22);
    ui_style_font(w[12], 16);
    w[13] = lv_label_create(w[0]);
    if (!w[13]) { ui_objects_ok = false; return; }
    objects.soh_b1 = w[13];
    ui_style_apply(w[13], UI_STYLE_LABEL);
    lv_label_set_text(w[13], "00");
    ui_style_apply(w[13], UI_STYLE_VALUE);
    lv_obj_set_pos(w[13], 81, 182);
    lv_obj_set_size(w[13], 68, 22);
    ui_style_font(w[13], 16);
    w[14] = lv_label_create(w[0]);
    if (!w[14]) { ui_objects_ok = false; return; }
    objects.rcap_b1 = w[14];
    ui_style_apply(w[14], UI_STYLE_LABEL);
    lv_label_set_text(w[14], "00");
    ui_style_apply(w[14], UI_STYLE_VALUE);
    lv_obj_set_pos(w[14], 81, 161);
    lv_obj_set_size(w[14], 68, 22);
    ui_style_font(w[14], 16);
    w[15] = lv_label_create(w[0]);
    if (!w[15]) { ui_objects_ok = false; return; }
    objects.avg_b1 = w[15];
    ui_style_apply(w[15], UI_STYLE_LABEL);
    lv_label_set_text(w[15], "00");
    ui_style_apply(w[15], UI_STYLE_VALUE);
    lv_obj_set_pos(w[15], 81, 203);
    lv_obj_set_size(w[15], 68, 22);
    ui_style_font(w[15], 16);
    w[16] = lv_label_create(w[0]);
    if (!w[16]) { ui_objects_ok = false; return; }
    ui_style_apply(w[16], UI_STYLE_LABEL);
    lv_label_set_text(w[16], "08");
    lv_obj_set_pos(w[16], 324, 56);
    lv_obj_set_size(w[16], 23, 18);
    ui_style_font(w[16], 14);
    lv_obj_set_style_text_color(w[16], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[17] = lv_label_create(w[0]);
    if (!w[17]) { ui_objects_ok = false; return; }
    ui_style_apply(w[17], UI_STYLE_LABEL);
    lv_label_set_text(w[17], "09");
    lv_obj_set_pos(w[17], 324, 80);
    lv_obj_set_size(w[17], 23, 18);
    ui_style_font(w[17], 14);
    lv_obj_set_style_text_color(w[17], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[18] = lv_label_create(w[0]);
    if (!w[18]) { ui_objects_ok = false; return; }
    ui_style_apply(w[18], UI_STYLE_LABEL);
    lv_label_set_text(w[18], "10");
    lv_obj_set_pos(w[18], 324, 104);
    lv_obj_set_size(w[18], 23, 18);
    ui_style_font(w[18], 14);
    lv_obj_set_style_text_color(w[18], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[19] = lv_label_create(w[0]);
    if (!w[19]) { ui_objects_ok = false; return; }
    ui_style_apply(w[19], UI_STYLE_LABEL);
    lv_label_set_long_mode(w[19], LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_label_set_text(w[19], "11");
    lv_obj_set_pos(w[19], 324, 128);
    lv_obj_set_size(w[19], 23, 18);
    ui_style_font(w[19], 14);
    lv_obj_set_style_text_color(w[19], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[20] = lv_label_create(w[0]);
    if (!w[20]) { ui_objects_ok = false; return; }
    ui_style_apply(w[20], UI_STYLE_LABEL);
    lv_label_set_text(w[20], "12");
    lv_obj_set_pos(w[20], 324, 152);
    lv_obj_set_size(w[20], 23, 18);
    ui_style_font(w[20], 14);
    lv_obj_set_style_text_color(w[20], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[21] = lv_label_create(w[0]);
    if (!w[21]) { ui_objects_ok = false; return; }
    ui_style_apply(w[21], UI_STYLE_LABEL);
    lv_label_set_text(w[21], "13");
    lv_obj_set_pos(w[21], 324, 176);
    lv_obj_set_size(w[21], 23, 18);
    ui_style_font(w[21], 14);
    lv_obj_set_style_text_color(w[21], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[22] = lv_label_create(w[0]);
    if (!w[22]) { ui_objects_ok = false; return; }
    ui_style_apply(w[22], UI_STYLE_LABEL);
    lv_label_set_text(w[22], "14");
    lv_obj_set_pos(w[22], 324, 200);
    lv_obj_set_size(w[22], 23, 18);
    ui_style_font(w[22], 14);
    lv_obj_set_style_text_color(w[22], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[23] = lv_label_create(w[0]);
    if (!w[23]) { ui_objects_ok = false; return; }
    objects.cell_8_b1 = w[23];
    ui_style_apply(w[23], UI_STYLE_LABEL);
    lv_label_set_text(w[23], "000");
    ui_style_apply(w[23], UI_STYLE_VALUE);
    lv_obj_set_pos(w[23], 349, 55);
    lv_obj_set_size(w[23], 98, 20);
    ui_style_font(w[23], 14);
    w[24] = lv_label_create(w[0]);
    if (!w[24]) { ui_objects_ok = false; return; }
    objects.cell_9_b1 = w[24];
    ui_style_apply(w[24], UI_STYLE_LABEL);
    lv_label_set_text(w[24], "000");
    ui_style_apply(w[24], UI_STYLE_VALUE);
    lv_obj_set_pos(w[24], 349, 79);
    lv_obj_set_size(w[24], 98, 20);
    ui_style_font(w[24], 14);
    w[25] = lv_label_create(w[0]);
    if (!w[25]) { ui_objects_ok = false; return; }
    objects.cell_10_b1 = w[25];
    ui_style_apply(w[25], UI_STYLE_LABEL);
    lv_label_set_text(w[25], "000");
    ui_style_apply(w[25], UI_STYLE_VALUE);
    lv_obj_set_pos(w[25], 349, 103);
    lv_obj_set_size(w[25], 98, 20);
    ui_style_font(w[25], 14);
    w[26] = lv_label_create(w[0]);
    if (!w[26]) { ui_objects_ok = false; return; }
    objects.cell_11_b1 = w[26];
    ui_style_apply(w[26], UI_STYLE_LABEL);
    lv_label_set_text(w[26], "000");
    ui_style_apply(w[26], UI_STYLE_VALUE);
    lv_obj_set_pos(w[26], 349, 127);
    lv_obj_set_size(w[26], 98, 20);
    ui_style_font(w[26], 14);
    w[27] = lv_label_create(w[0]);
    if (!w[27]) { ui_objects_ok = false; return; }
    objects.cell_12_b1 = w[27];
    ui_style_apply(w[27], UI_STYLE_LABEL);
    lv_label_set_text(w[27], "000");
    ui_style_apply(w[27], UI_STYLE_VALUE);
    lv_obj_set_pos(w[27], 349, 151);
    lv_obj_set_size(w[27], 98, 20);
    ui_style_font(w[27], 14);
    w[28] = lv_label_create(w[0]);
    if (!w[28]) { ui_objects_ok = false; return; }
    objects.cell_13_b1 = w[28];
    ui_style_apply(w[28], UI_STYLE_LABEL);
    lv_label_set_text(w[28], "000");
    ui_style_apply(w[28], UI_STYLE_VALUE);
    lv_obj_set_pos(w[28], 349, 175);
    lv_obj_set_size(w[28], 98, 20);
    ui_style_font(w[28], 14);
    w[29] = lv_label_create(w[0]);
    if (!w[29]) { ui_objects_ok = false; return; }
    objects.cell_14_b1 = w[29];
    ui_style_apply(w[29], UI_STYLE_LABEL);
    lv_label_set_text(w[29], "000");
    ui_style_apply(w[29], UI_STYLE_VALUE);
    lv_obj_set_pos(w[29], 349, 199);
    lv_obj_set_size(w[29], 98, 20);
    ui_style_font(w[29], 14);
    w[30] = lv_label_create(w[0]);
    if (!w[30]) { ui_objects_ok = false; return; }
    ui_style_apply(w[30], UI_STYLE_LABEL);
    lv_label_set_text(w[30], "01");
    lv_obj_set_pos(w[30], 176, 56);
    lv_obj_set_size(w[30], 23, 18);
    ui_style_font(w[30], 14);
    lv_obj_set_style_text_color(w[30], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[31] = lv_label_create(w[0]);
    if (!w[31]) { ui_objects_ok = false; return; }
    ui_style_apply(w[31], UI_STYLE_LABEL);
    lv_label_set_text(w[31], "02");
    lv_obj_set_pos(w[31], 176, 80);
    lv_obj_set_size(w[31], 23, 18);
    ui_style_font(w[31], 14);
    lv_obj_set_style_text_color(w[31], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[32] = lv_label_create(w[0]);
    if (!w[32]) { ui_objects_ok = false; return; }
    ui_style_apply(w[32], UI_STYLE_LABEL);
    lv_label_set_text(w[32], "03");
    lv_obj_set_pos(w[32], 176, 104);
    lv_obj_set_size(w[32], 23, 18);
    ui_style_font(w[32], 14);
    lv_obj_set_style_text_color(w[32], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[33] = lv_label_create(w[0]);
    if (!w[33]) { ui_objects_ok = false; return; }
    ui_style_apply(w[33], UI_STYLE_LABEL);
    lv_label_set_text(w[33], "04");
    lv_obj_set_pos(w[33], 176, 128);
    lv_obj_set_size(w[33], 23, 18);
    ui_style_font(w[33], 14);
    lv_obj_set_style_text_color(w[33], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[34] = lv_label_create(w[0]);
    if (!w[34]) { ui_objects_ok = false; return; }
    ui_style_apply(w[34], UI_STYLE_LABEL);
    lv_label_set_text(w[34], "05");
    lv_obj_set_pos(w[34], 176, 152);
    lv_obj_set_size(w[34], 23, 18);
    ui_style_font(w[34], 14);
    lv_obj_set_style_text_color(w[34], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[35] = lv_label_create(w[0]);
    if (!w[35]) { ui_objects_ok = false; return; }
    ui_style_apply(w[35], UI_STYLE_LABEL);
    lv_label_set_text(w[35], "06");
    lv_obj_set_pos(w[35], 176, 176);
    lv_obj_set_size(w[35], 23, 18);
    ui_style_font(w[35], 14);
    lv_obj_set_style_text_color(w[35], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[36] = lv_label_create(w[0]);
    if (!w[36]) { ui_objects_ok = false; return; }
    ui_style_apply(w[36], UI_STYLE_LABEL);
    lv_label_set_text(w[36], "07");
    lv_obj_set_pos(w[36], 176, 200);
    lv_obj_set_size(w[36], 23, 18);
    ui_style_font(w[36], 14);
    lv_obj_set_style_text_color(w[36], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[37] = lv_label_create(w[0]);
    if (!w[37]) { ui_objects_ok = false; return; }
    objects.cell_1_b1 = w[37];
    ui_style_apply(w[37], UI_STYLE_LABEL);
    lv_label_set_text(w[37], "000");
    ui_style_apply(w[37], UI_STYLE_VALUE);
    lv_obj_set_pos(w[37], 201, 55);
    lv_obj_set_size(w[37], 98, 20);
    ui_style_font(w[37], 14);
    w[38] = lv_label_create(w[0]);
    if (!w[38]) { ui_objects_ok = false; return; }
    objects.cell_2_b1 = w[38];
    ui_style_apply(w[38], UI_STYLE_LABEL);
    lv_label_set_text(w[38], "000");
    ui_style_apply(w[38], UI_STYLE_VALUE);
    lv_obj_set_pos(w[38], 201, 79);
    lv_obj_set_size(w[38], 98, 20);
    ui_style_font(w[38], 14);
    w[39] = lv_label_create(w[0]);
    if (!w[39]) { ui_objects_ok = false; return; }
    objects.cell_3_b1 = w[39];
    ui_style_apply(w[39], UI_STYLE_LABEL);
    lv_label_set_text(w[39], "000");
    ui_style_apply(w[39], UI_STYLE_VALUE);
    lv_obj_set_pos(w[39], 201, 103);
    lv_obj_set_size(w[39], 98, 20);
    ui_style_font(w[39], 14);
    w[40] = lv_label_create(w[0]);
    if (!w[40]) { ui_objects_ok = false; return; }
    objects.cell_4_b1 = w[40];
    ui_style_apply(w[40], UI_STYLE_LABEL);
    lv_label_set_text(w[40], "000");
    ui_style_apply(w[40], UI_STYLE_VALUE);
    lv_obj_set_pos(w[40], 201, 127);
    lv_obj_set_size(w[40], 98, 20);
    ui_style_font(w[40], 14);
    w[41] = lv_label_create(w[0]);
    if (!w[41]) { ui_objects_ok = false; return; }
    objects.cell_5_b1 = w[41];
    ui_style_apply(w[41], UI_STYLE_LABEL);
    lv_label_set_text(w[41], "000");
    ui_style_apply(w[41], UI_STYLE_VALUE);
    lv_obj_set_pos(w[41], 201, 151);
    lv_obj_set_size(w[41], 98, 20);
    ui_style_font(w[41], 14);
    w[42] = lv_label_create(w[0]);
    if (!w[42]) { ui_objects_ok = false; return; }
    objects.cell_6_b1 = w[42];
    ui_style_apply(w[42], UI_STYLE_LABEL);
    lv_label_set_text(w[42], "000");
    ui_style_apply(w[42], UI_STYLE_VALUE);
    lv_obj_set_pos(w[42], 201, 175);
    lv_obj_set_size(w[42], 98, 20);
    ui_style_font(w[42], 14);
    w[43] = lv_label_create(w[0]);
    if (!w[43]) { ui_objects_ok = false; return; }
    objects.cell_7_b1 = w[43];
    ui_style_apply(w[43], UI_STYLE_LABEL);
    lv_label_set_text(w[43], "000");
    ui_style_apply(w[43], UI_STYLE_VALUE);
    lv_obj_set_pos(w[43], 201, 199);
    lv_obj_set_size(w[43], 98, 20);
    ui_style_font(w[43], 14);
    w[44] = lv_label_create(w[0]);
    if (!w[44]) { ui_objects_ok = false; return; }
    ui_style_apply(w[44], UI_STYLE_LABEL);
    lv_label_set_text(w[44], "AVG");
    lv_obj_set_pos(w[44], 22, 205);
    lv_obj_set_size(w[44], 56, 20);
    ui_style_font(w[44], 14);
    w[45] = lv_label_create(w[0]);
    if (!w[45]) { ui_objects_ok = false; return; }
    ui_style_apply(w[45], UI_STYLE_LABEL);
    lv_label_set_text(w[45], "T_5:");
    lv_obj_set_pos(w[45], 316, 243);
    lv_obj_set_size(w[45], 39, 18);
    ui_style_font(w[45], 14);
    w[46] = lv_label_create(w[0]);
    if (!w[46]) { ui_objects_ok = false; return; }
    ui_style_apply(w[46], UI_STYLE_LABEL);
    lv_label_set_text(w[46], "T_3:");
    lv_obj_set_pos(w[46], 168, 243);
    lv_obj_set_size(w[46], 39, 18);
    ui_style_font(w[46], 14);
    w[47] = lv_label_create(w[0]);
    if (!w[47]) { ui_objects_ok = false; return; }
    ui_style_apply(w[47], UI_STYLE_LABEL);
    lv_label_set_text(w[47], "T_4:");
    lv_obj_set_pos(w[47], 242, 243);
    lv_obj_set_size(w[47], 39, 18);
    ui_style_font(w[47], 14);
    w[48] = lv_label_create(w[0]);
    if (!w[48]) { ui_objects_ok = false; return; }
    objects.t_5_b1 = w[48];
    ui_style_apply(w[48], UI_STYLE_LABEL);
    lv_label_set_text(w[48], "00");
    ui_style_apply(w[48], UI_STYLE_VALUE);
    lv_obj_set_pos(w[48], 354, 242);
    lv_obj_set_size(w[48], 33, 20);
    ui_style_font(w[48], 14);
    w[49] = lv_label_create(w[0]);
    if (!w[49]) { ui_objects_ok = false; return; }
    objects.t_3_b1 = w[49];
    ui_style_apply(w[49], UI_STYLE_LABEL);
    lv_label_set_text(w[49], "00");
    ui_style_apply(w[49], UI_STYLE_VALUE);
    lv_obj_set_pos(w[49], 206, 242);
    lv_obj_set_size(w[49], 33, 20);
    ui_style_font(w[49], 14);
    w[50] = lv_label_create(w[0]);
    if (!w[50]) { ui_objects_ok = false; return; }
    objects.t_4_b1 = w[50];
    ui_style_apply(w[50], UI_STYLE_LABEL);
    lv_label_set_text(w[50], "00");
    ui_style_apply(w[50], UI_STYLE_VALUE);
    lv_obj_set_pos(w[50], 280, 242);
    lv_obj_set_size(w[50], 33, 20);
    ui_style_font(w[50], 14);
    w[51] = lv_label_create(w[0]);
    if (!w[51]) { ui_objects_ok = false; return; }
    objects.text_vol_b1 = w[51];
    ui_style_apply(w[51], UI_STYLE_LABEL);
    lv_label_set_text(w[51], "00");
    ui_style_apply(w[51], UI_STYLE_VALUE);
    lv_obj_set_pos(w[51], 114, 279);
    lv_obj_set_size(w[51], 112, 28);
    ui_style_font(w[51], 22);
    w[52] = lv_label_create(w[0]);
    if (!w[52]) { ui_objects_ok = false; return; }
    objects.ampe_b1 = w[52];
    ui_style_apply(w[52], UI_STYLE_LABEL);
    lv_label_set_text(w[52], "00");
    ui_style_apply(w[52], UI_STYLE_VALUE);
    lv_obj_set_pos(w[52], 348, 279);
    lv_obj_set_size(w[52], 112, 28);
    ui_style_font(w[52], 22);
    w[53] = lv_label_create(w[0]);
    if (!w[53]) { ui_objects_ok = false; return; }
    ui_style_apply(w[53], UI_STYLE_LABEL);
    lv_label_set_text(w[53], "T_1:");
    lv_obj_set_pos(w[53], 20, 243);
    lv_obj_set_size(w[53], 39, 18);
    ui_style_font(w[53], 14);
    w[54] = lv_label_create(w[0]);
    if (!w[54]) { ui_objects_ok = false; return; }
    ui_style_apply(w[54], UI_STYLE_LABEL);
    lv_label_set_text(w[54], "T_2:");
    lv_obj_set_pos(w[54], 94, 243);
    lv_obj_set_size(w[54], 39, 18);
    ui_style_font(w[54], 14);
    w[55] = lv_label_create(w[0]);
    if (!w[55]) { ui_objects_ok = false; return; }
    objects.t_1_b1 = w[55];
    ui_style_apply(w[55], UI_STYLE_LABEL);
    lv_label_set_text(w[55], "00");
    ui_style_apply(w[55], UI_STYLE_VALUE);
    lv_obj_set_pos(w[55], 58, 242);
    lv_obj_set_size(w[55], 33, 20);
    ui_style_font(w[55], 14);
    w[56] = lv_label_create(w[0]);
    if (!w[56]) { ui_objects_ok = false; return; }
    objects.t_2_b1 = w[56];
    ui_style_apply(w[56], UI_STYLE_LABEL);
    lv_label_set_text(w[56], "00");
    ui_style_apply(w[56], UI_STYLE_VALUE);
    lv_obj_set_pos(w[56], 132, 242);
    lv_obj_set_size(w[56], 33, 20);
    ui_style_font(w[56], 14);
    w[57] = lv_btn_create(w[0]);
    if (!w[57]) { ui_objects_ok = false; return; }
    objects.nut_back_1 = w[57];
    ui_style_apply(w[57], UI_STYLE_BTN);
    lv_obj_add_event_cb(w[57], action_su_kien_tong, LV_EVENT_PRESSED, (void *)0);
    lv_obj_set_pos(w[57], 388, 8);
    lv_obj_set_size(w[57], 76, 32);
    w[58] = lv_label_create(w[57]);
    if (!w[58]) { ui_objects_ok = false; return; }
    ui_style_apply(w[58], UI_STYLE_LABEL);
    lv_obj_set_pos(w[58], 0, 0);
    lv_obj_set_size(w[58], LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_style_align(w[58], LV_ALIGN_CENTER, LV_PART_MAIN);
    lv_label_set_text(w[58], "BACK");
    ui_style_font(w[58], 16);
    w[59] = lv_label_create(w[0]);
    if (!w[59]) { ui_objects_ok = false; return; }
    ui_style_apply(w[59], UI_STYLE_LABEL);
    lv_label_set_text(w[59], "T_6:");
    lv_obj_set_pos(w[59], 390, 243);
    lv_obj_set_size(w[59], 39, 18);
    ui_style_font(w[59], 14);
    w[60] = lv_label_create(w[0]);
    if (!w[60]) { ui_objects_ok = false; return; }
    objects.t_6_b1 = w[60];
    ui_style_apply(w[60], UI_STYLE_LABEL);
    lv_label_set_text(w[60], "00");
    ui_style_apply(w[60], UI_STYLE_VALUE);
    lv_obj_set_pos(w[60], 428, 242);
    lv_obj_set_size(w[60], 33, 20);
    ui_style_font(w[60], 14);
    w[61] = lv_label_create(w[0]);
    if (!w[61]) { ui_objects_ok = false; return; }
    ui_style_apply(w[61], UI_STYLE_LABEL);
    lv_label_set_text(w[61], "%");
    lv_obj_set_pos(w[61], 133, 58);
    lv_obj_set_size(w[61], 16, 20);
    ui_style_font(w[61], 14);
    w[62] = lv_label_create(w[0]);
    if (!w[62]) { ui_objects_ok = false; return; }
    ui_style_apply(w[62], UI_STYLE_LABEL);
    lv_label_set_long_mode(w[62], LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_label_set_text(w[62], "BATTERY B1");
    ui_style_apply(w[62], UI_STYLE_VALUE);
    lv_obj_set_pos(w[62], 16, 10);
    lv_obj_set_size(w[62], 350, 28);
    ui_style_font(w[62], 22);
}
void tick_screen_main_read_b1(void) {}
void create_screen_ban_phim(void) {
    lv_obj_t *w[9];
    w[0] = lv_obj_create(0);
    if (!w[0]) { ui_objects_ok = false; return; }
    objects.ban_phim = w[0];
    ui_style_apply(w[0], UI_STYLE_SCREEN);
    lv_obj_set_pos(w[0], 0, 0);
    lv_obj_set_size(w[0], 480, 320);
    w[1] = lv_dropdown_create(w[0]);
    if (!w[1]) { ui_objects_ok = false; return; }
    objects.dd_cars = w[1];
    ui_style_apply(w[1], UI_STYLE_DROPDOWN);
    lv_obj_set_pos(w[1], 8, 8);
    lv_obj_set_size(w[1], 242, 36);
    lv_dropdown_set_options(w[1], "Hinh 1\nHinh 2\nHinh 3\nHinh 4");
    w[2] = lv_label_create(w[0]);
    if (!w[2]) { ui_objects_ok = false; return; }
    objects.label_show_selection = w[2];
    ui_style_apply(w[2], UI_STYLE_LABEL);
    lv_obj_set_pos(w[2], 258, 12);
    lv_obj_set_size(w[2], 128, 28);
    lv_label_set_long_mode(w[2], LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_label_set_text(w[2], "");
    ui_style_font(w[2], 16);
    w[3] = lv_textarea_create(w[0]);
    if (!w[3]) { ui_objects_ok = false; return; }
    objects.ta_new_options = w[3];
    ui_style_apply(w[3], UI_STYLE_TEXTAREA);
    lv_obj_set_pos(w[3], 8, 52);
    lv_obj_set_size(w[3], 380, 44);
    lv_textarea_set_max_length(w[3], 128);
    lv_textarea_set_one_line(w[3], false);
    lv_textarea_set_password_mode(w[3], false);
    lv_obj_clear_flag(w[3], LV_OBJ_FLAG_SCROLL_WITH_ARROW);
    w[4] = lv_btn_create(w[0]);
    if (!w[4]) { ui_objects_ok = false; return; }
    objects.btn_add_option = w[4];
    ui_style_apply(w[4], UI_STYLE_BTN);
    lv_obj_set_pos(w[4], 396, 52);
    lv_obj_set_size(w[4], 76, 44);
    w[5] = lv_label_create(w[4]);
    if (!w[5]) { ui_objects_ok = false; return; }
    ui_style_apply(w[5], UI_STYLE_LABEL);
    lv_obj_set_pos(w[5], 0, 0);
    lv_obj_set_size(w[5], LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_style_align(w[5], LV_ALIGN_CENTER, LV_PART_MAIN);
    lv_label_set_text(w[5], "Add");
    ui_style_font(w[5], 18);
    w[6] = lv_keyboard_create(w[0]);
    if (!w[6]) { ui_objects_ok = false; return; }
    objects.kb_input = w[6];
    ui_style_apply(w[6], UI_STYLE_KEYBOARD);
    lv_obj_set_pos(w[6], 4, 104);
    lv_obj_set_size(w[6], 472, 212);
    lv_keyboard_set_mode(w[6], LV_KEYBOARD_MODE_TEXT_UPPER);
    w[7] = lv_btn_create(w[0]);
    if (!w[7]) { ui_objects_ok = false; return; }
    objects.nut_back_2 = w[7];
    ui_style_apply(w[7], UI_STYLE_BTN);
    lv_obj_set_pos(w[7], 394, 8);
    lv_obj_set_size(w[7], 78, 36);
    lv_obj_add_event_cb(w[7], action_su_kien_tong, LV_EVENT_PRESSED, (void *)0);
    w[8] = lv_label_create(w[7]);
    if (!w[8]) { ui_objects_ok = false; return; }
    ui_style_apply(w[8], UI_STYLE_LABEL);
    lv_obj_set_pos(w[8], 0, 0);
    lv_obj_set_size(w[8], LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_style_align(w[8], LV_ALIGN_CENTER, LV_PART_MAIN);
    lv_label_set_text(w[8], "BACK");
    ui_style_font(w[8], 18);
    lv_keyboard_set_textarea(objects.kb_input, objects.ta_new_options);
}
void tick_screen_ban_phim(void) {}
void create_screen_read_a1(void) {
    lv_obj_t *w[28];
    w[0] = lv_obj_create(0);
    if (!w[0]) { ui_objects_ok = false; return; }
    objects.read_a1 = w[0];
    ui_style_apply(w[0], UI_STYLE_SCREEN);
    lv_obj_set_pos(w[0], 0, 0);
    lv_obj_set_size(w[0], 480, 320);
    w[1] = lv_btn_create(w[0]);
    if (!w[1]) { ui_objects_ok = false; return; }
    objects.nut_back_3 = w[1];
    ui_style_apply(w[1], UI_STYLE_BTN);
    lv_obj_set_pos(w[1], 388, 8);
    lv_obj_set_size(w[1], 76, 32);
    lv_obj_add_event_cb(w[1], action_su_kien_tong, LV_EVENT_PRESSED, (void *)0);
    w[2] = lv_label_create(w[1]);
    if (!w[2]) { ui_objects_ok = false; return; }
    ui_style_apply(w[2], UI_STYLE_LABEL);
    lv_obj_set_pos(w[2], 0, 0);
    lv_obj_set_size(w[2], LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_style_align(w[2], LV_ALIGN_CENTER, LV_PART_MAIN);
    lv_label_set_text(w[2], "BACK");
    ui_style_font(w[2], 18);
    w[3] = lv_label_create(w[0]);
    if (!w[3]) { ui_objects_ok = false; return; }
    ui_style_apply(w[3], UI_STYLE_LABEL);
    lv_obj_set_pos(w[3], 346, 68);
    lv_obj_set_size(w[3], 58, 24);
    lv_label_set_text(w[3], "T_5:");
    ui_style_font(w[3], 16);
    w[4] = lv_label_create(w[0]);
    if (!w[4]) { ui_objects_ok = false; return; }
    ui_style_apply(w[4], UI_STYLE_LABEL);
    lv_obj_set_pos(w[4], 220, 144);
    lv_obj_set_size(w[4], 58, 24);
    lv_label_set_text(w[4], "T_3:");
    ui_style_font(w[4], 16);
    w[5] = lv_label_create(w[0]);
    if (!w[5]) { ui_objects_ok = false; return; }
    ui_style_apply(w[5], UI_STYLE_LABEL);
    lv_obj_set_pos(w[5], 220, 182);
    lv_obj_set_size(w[5], 58, 24);
    lv_label_set_text(w[5], "T_4:");
    ui_style_font(w[5], 16);
    w[6] = lv_label_create(w[0]);
    if (!w[6]) { ui_objects_ok = false; return; }
    objects.t_5_a1 = w[6];
    ui_style_apply(w[6], UI_STYLE_LABEL);
    lv_obj_set_pos(w[6], 406, 64);
    lv_obj_set_size(w[6], 50, 28);
    lv_label_set_text(w[6], "00");
    ui_style_font(w[6], 22);
    ui_style_apply(w[6], UI_STYLE_VALUE);
    w[7] = lv_label_create(w[0]);
    if (!w[7]) { ui_objects_ok = false; return; }
    objects.t_3_a1 = w[7];
    ui_style_apply(w[7], UI_STYLE_LABEL);
    lv_obj_set_pos(w[7], 280, 140);
    lv_obj_set_size(w[7], 50, 28);
    lv_label_set_text(w[7], "00");
    ui_style_font(w[7], 22);
    ui_style_apply(w[7], UI_STYLE_VALUE);
    w[8] = lv_label_create(w[0]);
    if (!w[8]) { ui_objects_ok = false; return; }
    objects.t_4_a1 = w[8];
    ui_style_apply(w[8], UI_STYLE_LABEL);
    lv_obj_set_pos(w[8], 280, 178);
    lv_obj_set_size(w[8], 50, 28);
    lv_label_set_text(w[8], "00");
    ui_style_font(w[8], 22);
    ui_style_apply(w[8], UI_STYLE_VALUE);
    w[9] = lv_label_create(w[0]);
    if (!w[9]) { ui_objects_ok = false; return; }
    ui_style_apply(w[9], UI_STYLE_LABEL);
    lv_obj_set_pos(w[9], 220, 68);
    lv_obj_set_size(w[9], 58, 24);
    lv_label_set_text(w[9], "T_1:");
    ui_style_font(w[9], 16);
    w[10] = lv_label_create(w[0]);
    if (!w[10]) { ui_objects_ok = false; return; }
    ui_style_apply(w[10], UI_STYLE_LABEL);
    lv_obj_set_pos(w[10], 220, 106);
    lv_obj_set_size(w[10], 58, 24);
    lv_label_set_text(w[10], "T_2:");
    ui_style_font(w[10], 16);
    w[11] = lv_label_create(w[0]);
    if (!w[11]) { ui_objects_ok = false; return; }
    objects.t_1_a1 = w[11];
    ui_style_apply(w[11], UI_STYLE_LABEL);
    lv_obj_set_pos(w[11], 280, 64);
    lv_obj_set_size(w[11], 50, 28);
    lv_label_set_text(w[11], "00");
    ui_style_font(w[11], 22);
    ui_style_apply(w[11], UI_STYLE_VALUE);
    w[12] = lv_label_create(w[0]);
    if (!w[12]) { ui_objects_ok = false; return; }
    objects.t_2_a1 = w[12];
    ui_style_apply(w[12], UI_STYLE_LABEL);
    lv_obj_set_pos(w[12], 280, 102);
    lv_obj_set_size(w[12], 50, 28);
    lv_label_set_text(w[12], "00");
    ui_style_font(w[12], 22);
    ui_style_apply(w[12], UI_STYLE_VALUE);
    w[13] = lv_label_create(w[0]);
    if (!w[13]) { ui_objects_ok = false; return; }
    ui_style_apply(w[13], UI_STYLE_LABEL);
    lv_obj_set_pos(w[13], 346, 106);
    lv_obj_set_size(w[13], 58, 24);
    lv_label_set_text(w[13], "T_6:");
    ui_style_font(w[13], 16);
    w[14] = lv_label_create(w[0]);
    if (!w[14]) { ui_objects_ok = false; return; }
    objects.t_6_a1 = w[14];
    ui_style_apply(w[14], UI_STYLE_LABEL);
    lv_obj_set_pos(w[14], 406, 102);
    lv_obj_set_size(w[14], 50, 28);
    lv_label_set_text(w[14], "00");
    ui_style_font(w[14], 22);
    ui_style_apply(w[14], UI_STYLE_VALUE);
    w[15] = lv_label_create(w[0]);
    if (!w[15]) { ui_objects_ok = false; return; }
    ui_style_apply(w[15], UI_STYLE_LABEL);
    lv_obj_set_pos(w[15], 16, 68);
    lv_obj_set_size(w[15], 80, 24);
    lv_label_set_text(w[15], "SOC     :");
    ui_style_font(w[15], 16);
    w[16] = lv_label_create(w[0]);
    if (!w[16]) { ui_objects_ok = false; return; }
    ui_style_apply(w[16], UI_STYLE_LABEL);
    lv_obj_set_pos(w[16], 16, 106);
    lv_obj_set_size(w[16], 80, 24);
    lv_label_set_text(w[16], "Delvol :");
    ui_style_font(w[16], 16);
    w[17] = lv_label_create(w[0]);
    if (!w[17]) { ui_objects_ok = false; return; }
    ui_style_apply(w[17], UI_STYLE_LABEL);
    lv_obj_set_pos(w[17], 16, 144);
    lv_obj_set_size(w[17], 80, 24);
    lv_label_set_text(w[17], "Vmax :");
    ui_style_font(w[17], 16);
    w[18] = lv_label_create(w[0]);
    if (!w[18]) { ui_objects_ok = false; return; }
    ui_style_apply(w[18], UI_STYLE_LABEL);
    lv_obj_set_pos(w[18], 16, 182);
    lv_obj_set_size(w[18], 80, 24);
    lv_label_set_text(w[18], "Vmin :");
    ui_style_font(w[18], 16);
    w[19] = lv_label_create(w[0]);
    if (!w[19]) { ui_objects_ok = false; return; }
    objects.soc_a1 = w[19];
    ui_style_apply(w[19], UI_STYLE_LABEL);
    lv_obj_set_pos(w[19], 100, 64);
    lv_obj_set_size(w[19], 90, 30);
    lv_label_set_text(w[19], "00");
    ui_style_font(w[19], 22);
    ui_style_apply(w[19], UI_STYLE_VALUE);
    w[20] = lv_label_create(w[0]);
    if (!w[20]) { ui_objects_ok = false; return; }
    objects.del_vol_a1 = w[20];
    ui_style_apply(w[20], UI_STYLE_LABEL);
    lv_obj_set_pos(w[20], 100, 102);
    lv_obj_set_size(w[20], 90, 30);
    lv_label_set_text(w[20], "00");
    ui_style_font(w[20], 22);
    ui_style_apply(w[20], UI_STYLE_VALUE);
    w[21] = lv_label_create(w[0]);
    if (!w[21]) { ui_objects_ok = false; return; }
    objects.v_max_a1 = w[21];
    ui_style_apply(w[21], UI_STYLE_LABEL);
    lv_obj_set_pos(w[21], 100, 140);
    lv_obj_set_size(w[21], 90, 30);
    lv_label_set_text(w[21], "00");
    ui_style_font(w[21], 22);
    ui_style_apply(w[21], UI_STYLE_VALUE);
    w[22] = lv_label_create(w[0]);
    if (!w[22]) { ui_objects_ok = false; return; }
    objects.v_min_a1 = w[22];
    ui_style_apply(w[22], UI_STYLE_LABEL);
    lv_obj_set_pos(w[22], 100, 178);
    lv_obj_set_size(w[22], 90, 30);
    lv_label_set_text(w[22], "00");
    ui_style_font(w[22], 22);
    ui_style_apply(w[22], UI_STYLE_VALUE);
    w[23] = lv_label_create(w[0]);
    if (!w[23]) { ui_objects_ok = false; return; }
    objects.text_vol_a1 = w[23];
    ui_style_apply(w[23], UI_STYLE_LABEL);
    lv_label_set_text(w[23], "00");
    ui_style_apply(w[23], UI_STYLE_VALUE);
    lv_obj_set_pos(w[23], 112, 279);
    lv_obj_set_size(w[23], 112, 28);
    ui_style_font(w[23], 22);
    w[24] = lv_label_create(w[0]);
    if (!w[24]) { ui_objects_ok = false; return; }
    ui_style_apply(w[24], UI_STYLE_LABEL);
    lv_obj_set_pos(w[24], 346, 144);
    lv_obj_set_size(w[24], 58, 24);
    lv_label_set_text(w[24], "T_7:");
    ui_style_font(w[24], 16);
    w[25] = lv_label_create(w[0]);
    if (!w[25]) { ui_objects_ok = false; return; }
    objects.t_7_a1 = w[25];
    ui_style_apply(w[25], UI_STYLE_LABEL);
    lv_obj_set_pos(w[25], 406, 140);
    lv_obj_set_size(w[25], 50, 28);
    lv_label_set_text(w[25], "00");
    ui_style_font(w[25], 22);
    ui_style_apply(w[25], UI_STYLE_VALUE);
    w[26] = lv_label_create(w[0]);
    if (!w[26]) { ui_objects_ok = false; return; }
    objects.ampe_a1 = w[26];
    ui_style_apply(w[26], UI_STYLE_LABEL);
    lv_label_set_text(w[26], "00");
    ui_style_apply(w[26], UI_STYLE_VALUE);
    lv_obj_set_pos(w[26], 346, 279);
    lv_obj_set_size(w[26], 112, 28);
    ui_style_font(w[26], 22);
    w[27] = lv_label_create(w[0]);
    if (!w[27]) { ui_objects_ok = false; return; }
    ui_style_apply(w[27], UI_STYLE_LABEL);
    lv_obj_set_pos(w[27], 16, 10);
    lv_obj_set_size(w[27], 330, 30);
    lv_label_set_long_mode(w[27], LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_label_set_text(w[27], "KLARA A1");
    ui_style_font(w[27], 22);
    ui_style_apply(w[27], UI_STYLE_VALUE);
}
void tick_screen_read_a1(void) {}
void create_screen_thong_tin_bao_hanh(void) {
    lv_obj_t *w[4];
    w[0] = lv_obj_create(0);
    if (!w[0]) { ui_objects_ok = false; return; }
    objects.thong_tin_bao_hanh = w[0];
    ui_style_apply(w[0], UI_STYLE_SCREEN);
    lv_obj_set_pos(w[0], 0, 0);
    lv_obj_set_size(w[0], 480, 320);
    w[1] = lv_btn_create(w[0]);
    if (!w[1]) { ui_objects_ok = false; return; }
    objects.back_home = w[1];
    ui_style_apply(w[1], UI_STYLE_BTN);
    lv_obj_set_pos(w[1], 379, 252);
    lv_obj_set_size(w[1], 84, 53);
    lv_obj_add_event_cb(w[1], action_su_kien_tong, LV_EVENT_PRESSED, (void *)0);
    w[2] = lv_label_create(w[1]);
    if (!w[2]) { ui_objects_ok = false; return; }
    ui_style_apply(w[2], UI_STYLE_LABEL);
    lv_obj_set_pos(w[2], 1, 1);
    lv_obj_set_size(w[2], LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_style_align(w[2], LV_ALIGN_CENTER, LV_PART_MAIN);
    lv_label_set_text(w[2], "BACK");
    ui_style_font(w[2], 18);
    w[3] = lv_label_create(w[0]);
    if (!w[3]) { ui_objects_ok = false; return; }
    ui_style_apply(w[3], UI_STYLE_LABEL);
    lv_obj_set_pos(w[3], 32, 65);
    lv_obj_set_size(w[3], 417, 66);
    lv_label_set_long_mode(w[3], LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_label_set_text(w[3], "SHOPEE: THIET BI SO");
    ui_style_font(w[3], 16);
}
void tick_screen_thong_tin_bao_hanh(void) {}
void create_screen_sceen_speed_up(void) {
    lv_obj_t *w[32];
    w[0] = lv_obj_create(0);
    if (!w[0]) { ui_objects_ok = false; return; }
    objects.sceen_speed_up = w[0];
    ui_style_apply(w[0], UI_STYLE_SCREEN);
    lv_obj_set_pos(w[0], 0, 0);
    lv_obj_set_size(w[0], 480, 320);
    w[1] = lv_btn_create(w[0]);
    if (!w[1]) { ui_objects_ok = false; return; }
    objects.back_main_speed_up_7 = w[1];
    ui_style_apply(w[1], UI_STYLE_BTN);
    lv_obj_set_pos(w[1], 16, 12);
    lv_obj_set_size(w[1], 448, 40);
    lv_obj_add_event_cb(w[1], action_su_kien_tong, LV_EVENT_CLICKED, (void *)0);
    w[2] = lv_label_create(w[1]);
    if (!w[2]) { ui_objects_ok = false; return; }
    objects.back_mo_toc_4 = w[2];
    ui_style_apply(w[2], UI_STYLE_LABEL);
    lv_obj_set_pos(w[2], 0, 0);
    lv_obj_set_size(w[2], LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_style_align(w[2], LV_ALIGN_CENTER, LV_PART_MAIN);
    lv_label_set_text(w[2], "BACK");
    ui_style_font(w[2], 18);
    lv_obj_t *speed_list = speed_nav_create(w[0]);
    if (!speed_list) { ui_objects_ok = false; return; }
    w[3] = lv_btn_create(speed_list);
    if (!w[3]) { ui_objects_ok = false; return; }
    objects.klara_s1_60v = w[3];
    ui_style_apply(w[3], UI_STYLE_BTN);
    lv_obj_set_pos(w[3], 0, 0);
    lv_obj_set_size(w[3], 198, 54);
    lv_obj_add_event_cb(w[3], action_su_kien_tong, LV_EVENT_CLICKED, (void *)0);
    w[4] = lv_label_create(w[3]);
    if (!w[4]) { ui_objects_ok = false; return; }
    ui_style_apply(w[4], UI_STYLE_LABEL);
    lv_obj_set_pos(w[4], 0, 0);
    lv_obj_set_size(w[4], LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_style_align(w[4], LV_ALIGN_CENTER, LV_PART_MAIN);
    lv_label_set_text(w[4], "KLARA S1 60V");
    ui_style_font(w[4], 16);
    w[5] = lv_btn_create(speed_list);
    if (!w[5]) { ui_objects_ok = false; return; }
    objects.klara_s1_48v_backup = w[5];
    ui_style_apply(w[5], UI_STYLE_BTN);
    lv_obj_set_pos(w[5], 206, 0);
    lv_obj_set_size(w[5], 198, 54);
    lv_obj_add_event_cb(w[5], action_su_kien_tong, LV_EVENT_CLICKED, (void *)0);
    w[6] = lv_label_create(w[5]);
    if (!w[6]) { ui_objects_ok = false; return; }
    ui_style_apply(w[6], UI_STYLE_LABEL);
    lv_obj_set_pos(w[6], 0, 0);
    lv_obj_set_size(w[6], LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_style_align(w[6], LV_ALIGN_CENTER, LV_PART_MAIN);
    lv_label_set_text(w[6], "KLARA S1 48V\n    BACK UP");
    ui_style_font(w[6], 16);
    w[7] = lv_btn_create(speed_list);
    if (!w[7]) { ui_objects_ok = false; return; }
    objects.klara_s1_72v = w[7];
    ui_style_apply(w[7], UI_STYLE_BTN);
    lv_obj_set_pos(w[7], 0, 62);
    lv_obj_set_size(w[7], 198, 54);
    lv_obj_add_event_cb(w[7], action_su_kien_tong, LV_EVENT_CLICKED, (void *)0);
    w[8] = lv_label_create(w[7]);
    if (!w[8]) { ui_objects_ok = false; return; }
    ui_style_apply(w[8], UI_STYLE_LABEL);
    lv_obj_set_pos(w[8], 0, 0);
    lv_obj_set_size(w[8], LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_style_align(w[8], LV_ALIGN_CENTER, LV_PART_MAIN);
    lv_label_set_text(w[8], "KLARA S1 72V");
    ui_style_font(w[8], 16);
    w[9] = lv_btn_create(speed_list);
    if (!w[9]) { ui_objects_ok = false; return; }
    objects.klara_a1_48v = w[9];
    ui_style_apply(w[9], UI_STYLE_BTN);
    lv_obj_set_pos(w[9], 206, 62);
    lv_obj_set_size(w[9], 198, 54);
    lv_obj_add_event_cb(w[9], action_su_kien_tong, LV_EVENT_CLICKED, (void *)0);
    w[10] = lv_label_create(w[9]);
    if (!w[10]) { ui_objects_ok = false; return; }
    ui_style_apply(w[10], UI_STYLE_LABEL);
    lv_obj_set_pos(w[10], 0, 0);
    lv_obj_set_size(w[10], LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_style_align(w[10], LV_ALIGN_CENTER, LV_PART_MAIN);
    lv_label_set_text(w[10], "KLARA A1 48V");
    ui_style_font(w[10], 16);
    w[11] = lv_btn_create(speed_list);
    if (!w[11]) { ui_objects_ok = false; return; }
    objects.klara_a1_60v = w[11];
    ui_style_apply(w[11], UI_STYLE_BTN);
    lv_obj_set_pos(w[11], 0, 124);
    lv_obj_set_size(w[11], 198, 54);
    lv_obj_add_event_cb(w[11], action_su_kien_tong, LV_EVENT_CLICKED, (void *)0);
    w[12] = lv_label_create(w[11]);
    if (!w[12]) { ui_objects_ok = false; return; }
    ui_style_apply(w[12], UI_STYLE_LABEL);
    lv_obj_set_pos(w[12], 0, 0);
    lv_obj_set_size(w[12], LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_style_align(w[12], LV_ALIGN_CENTER, LV_PART_MAIN);
    lv_label_set_text(w[12], "KLARA A1 60V");
    ui_style_font(w[12], 16);
    w[13] = lv_btn_create(speed_list);
    if (!w[13]) { ui_objects_ok = false; return; }
    objects.klara_a1_72v = w[13];
    ui_style_apply(w[13], UI_STYLE_BTN);
    lv_obj_set_pos(w[13], 206, 124);
    lv_obj_set_size(w[13], 198, 54);
    lv_obj_add_event_cb(w[13], action_su_kien_tong, LV_EVENT_CLICKED, (void *)0);
    w[14] = lv_label_create(w[13]);
    if (!w[14]) { ui_objects_ok = false; return; }
    ui_style_apply(w[14], UI_STYLE_LABEL);
    lv_obj_set_pos(w[14], 0, 0);
    lv_obj_set_size(w[14], LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_style_align(w[14], LV_ALIGN_CENTER, LV_PART_MAIN);
    lv_label_set_text(w[14], "KLARA A1 72V");
    ui_style_font(w[14], 16);
    w[15] = lv_btn_create(speed_list);
    if (!w[15]) { ui_objects_ok = false; return; }
    objects.klara_a1_60v_backup = w[15];
    ui_style_apply(w[15], UI_STYLE_BTN);
    lv_obj_set_pos(w[15], 0, 186);
    lv_obj_set_size(w[15], 198, 54);
    lv_obj_add_event_cb(w[15], action_su_kien_tong, LV_EVENT_CLICKED, (void *)0);
    w[16] = lv_label_create(w[15]);
    if (!w[16]) { ui_objects_ok = false; return; }
    ui_style_apply(w[16], UI_STYLE_LABEL);
    lv_obj_set_pos(w[16], 0, 2);
    lv_obj_set_size(w[16], LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_style_align(w[16], LV_ALIGN_CENTER, LV_PART_MAIN);
    lv_label_set_text(w[16], "KLARA A1 60V\n    BACK UP");
    ui_style_font(w[16], 16);
    w[17] = lv_btn_create(speed_list);
    if (!w[17]) { ui_objects_ok = false; return; }
    objects.impes_48v = w[17];
    ui_style_apply(w[17], UI_STYLE_BTN);
    lv_obj_set_pos(w[17], 206, 186);
    lv_obj_set_size(w[17], 198, 54);
    lv_obj_add_event_cb(w[17], action_su_kien_tong, LV_EVENT_CLICKED, (void *)0);
    w[18] = lv_label_create(w[17]);
    if (!w[18]) { ui_objects_ok = false; return; }
    ui_style_apply(w[18], UI_STYLE_LABEL);
    lv_obj_set_pos(w[18], 0, 0);
    lv_obj_set_size(w[18], LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_style_align(w[18], LV_ALIGN_CENTER, LV_PART_MAIN);
    lv_label_set_text(w[18], "IMPES 48V");
    ui_style_font(w[18], 16);
    w[19] = lv_btn_create(speed_list);
    if (!w[19]) { ui_objects_ok = false; return; }
    objects.klara_s1_48v = w[19];
    ui_style_apply(w[19], UI_STYLE_BTN);
    lv_obj_set_pos(w[19], 0, 248);
    lv_obj_set_size(w[19], 198, 54);
    lv_obj_add_event_cb(w[19], action_su_kien_tong, LV_EVENT_CLICKED, (void *)0);
    w[20] = lv_label_create(w[19]);
    if (!w[20]) { ui_objects_ok = false; return; }
    ui_style_apply(w[20], UI_STYLE_LABEL);
    lv_obj_set_pos(w[20], 0, 0);
    lv_obj_set_size(w[20], LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_style_align(w[20], LV_ALIGN_CENTER, LV_PART_MAIN);
    lv_label_set_text(w[20], "KLARA S1 48V");
    ui_style_font(w[20], 16);
    w[21] = lv_btn_create(speed_list);
    if (!w[21]) { ui_objects_ok = false; return; }
    objects.klara_a1_zin_speed = w[21];
    ui_style_apply(w[21], UI_STYLE_BTN);
    lv_obj_set_pos(w[21], 206, 248);
    lv_obj_set_size(w[21], 198, 54);
    lv_obj_add_event_cb(w[21], action_su_kien_tong, LV_EVENT_CLICKED, (void *)0);
    w[22] = lv_label_create(w[21]);
    if (!w[22]) { ui_objects_ok = false; return; }
    ui_style_apply(w[22], UI_STYLE_LABEL);
    lv_obj_set_pos(w[22], 0, 0);
    lv_obj_set_size(w[22], LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_style_align(w[22], LV_ALIGN_CENTER, LV_PART_MAIN);
    lv_label_set_text(w[22], " KLARA A1\nZIN SPEED");
    ui_style_font(w[22], 16);
    w[23] = lv_btn_create(speed_list);
    if (!w[23]) { ui_objects_ok = false; return; }
    objects.klara_s1_zin_speed = w[23];
    ui_style_apply(w[23], UI_STYLE_BTN);
    lv_obj_set_pos(w[23], 0, 310);
    lv_obj_set_size(w[23], 198, 54);
    lv_obj_add_event_cb(w[23], action_su_kien_tong, LV_EVENT_CLICKED, (void *)0);
    w[24] = lv_label_create(w[23]);
    if (!w[24]) { ui_objects_ok = false; return; }
    ui_style_apply(w[24], UI_STYLE_LABEL);
    lv_obj_set_pos(w[24], 0, 0);
    lv_obj_set_size(w[24], LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_style_align(w[24], LV_ALIGN_CENTER, LV_PART_MAIN);
    lv_label_set_text(w[24], " KLARA S1\nZIN SPEED");
    ui_style_font(w[24], 16);
    w[25] = lv_btn_create(speed_list);
    if (!w[25]) { ui_objects_ok = false; return; }
    objects.impes_zin = w[25];
    ui_style_apply(w[25], UI_STYLE_BTN);
    lv_obj_set_pos(w[25], 206, 310);
    lv_obj_set_size(w[25], 198, 54);
    lv_obj_add_event_cb(w[25], action_su_kien_tong, LV_EVENT_CLICKED, (void *)0);
    w[26] = lv_label_create(w[25]);
    if (!w[26]) { ui_objects_ok = false; return; }
    ui_style_apply(w[26], UI_STYLE_LABEL);
    lv_obj_set_pos(w[26], 0, 0);
    lv_obj_set_size(w[26], LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_style_align(w[26], LV_ALIGN_CENTER, LV_PART_MAIN);
    lv_label_set_text(w[26], "IMPES ZIN");
    ui_style_font(w[26], 16);
    w[27] = lv_btn_create(speed_list);
    if (!w[27]) { ui_objects_ok = false; return; }
    objects.impes_48v_backup = w[27];
    ui_style_apply(w[27], UI_STYLE_BTN);
    lv_obj_set_pos(w[27], 0, 372);
    lv_obj_set_size(w[27], 198, 54);
    lv_obj_add_event_cb(w[27], action_su_kien_tong, LV_EVENT_CLICKED, (void *)0);
    w[28] = lv_label_create(w[27]);
    if (!w[28]) { ui_objects_ok = false; return; }
    ui_style_apply(w[28], UI_STYLE_LABEL);
    lv_obj_set_pos(w[28], 0, 0);
    lv_obj_set_size(w[28], LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_style_align(w[28], LV_ALIGN_CENTER, LV_PART_MAIN);
    lv_label_set_text(w[28], "IMPES 48V\n  BACKUP");
    ui_style_font(w[28], 16);
    w[29] = lv_obj_create(speed_list);
    if (!w[29]) { ui_objects_ok = false; return; }
    ui_style_apply(w[29], UI_STYLE_SEPARATOR);
    lv_obj_set_pos(w[29], 0, 434);
    lv_obj_set_size(w[29], 404, 8);
    w[30] = lv_btn_create(speed_list);
    if (!w[30]) { ui_objects_ok = false; return; }
    objects.klara_s1_61 = w[30];
    ui_style_apply(w[30], UI_STYLE_BTN);
    lv_obj_set_pos(w[30], 206, 372);
    lv_obj_set_size(w[30], 198, 54);
    lv_obj_add_event_cb(w[30], action_su_kien_tong, LV_EVENT_CLICKED, (void *)0);
    w[31] = lv_label_create(w[30]);
    if (!w[31]) { ui_objects_ok = false; return; }
    ui_style_apply(w[31], UI_STYLE_LABEL);
    lv_obj_set_pos(w[31], 0, 0);
    lv_obj_set_size(w[31], LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_style_align(w[31], LV_ALIGN_CENTER, LV_PART_MAIN);
    lv_label_set_text(w[31], "IMPES 60V");
    ui_style_font(w[31], 16);
    speed_nav_finish();
}
void tick_screen_sceen_speed_up(void) {}
void create_screen_update_speed_trang_thai(void) {
    lv_obj_t *w[6];
    w[0] = lv_obj_create(0);
    if (!w[0]) { ui_objects_ok = false; return; }
    objects.update_speed_trang_thai = w[0];
    ui_style_apply(w[0], UI_STYLE_SCREEN);
    lv_obj_set_pos(w[0], 0, 0);
    lv_obj_set_size(w[0], 480, 320);
    w[1] = lv_bar_create(w[0]);
    if (!w[1]) { ui_objects_ok = false; return; }
    objects.bar_speed_up = w[1];
    ui_style_apply(w[1], UI_STYLE_BAR);
    lv_obj_set_pos(w[1], 32, 130);
    lv_obj_set_size(w[1], 416, 18);
    lv_bar_set_value(w[1], 25, LV_ANIM_OFF);
    w[2] = lv_label_create(w[0]);
    if (!w[2]) { ui_objects_ok = false; return; }
    ui_style_apply(w[2], UI_STYLE_LABEL);
    lv_obj_set_pos(w[2], 32, 240);
    lv_obj_set_size(w[2], 416, 28);
    lv_label_set_text(w[2], "DANG CAP NHAT");
    ui_style_font(w[2], 18);
    ui_style_apply(w[2], UI_STYLE_CENTER);
    w[3] = lv_label_create(w[0]);
    if (!w[3]) { ui_objects_ok = false; return; }
    objects.text_speed_up = w[3];
    ui_style_apply(w[3], UI_STYLE_LABEL);
    lv_obj_set_pos(w[3], 32, 170);
    lv_obj_set_size(w[3], 416, 48);
    lv_label_set_text(w[3], "50%");
    ui_style_font(w[3], 32);
    ui_style_apply(w[3], UI_STYLE_CENTER);
    w[4] = lv_label_create(w[0]);
    if (!w[4]) { ui_objects_ok = false; return; }
    ui_style_apply(w[4], UI_STYLE_LABEL);
    lv_obj_set_pos(w[4], 32, 52);
    lv_obj_set_size(w[4], 100, 30);
    lv_label_set_text(w[4], "MCU>>");
    ui_style_font(w[4], 18);
    w[5] = lv_label_create(w[0]);
    if (!w[5]) { ui_objects_ok = false; return; }
    objects.text_loai_xe = w[5];
    ui_style_apply(w[5], UI_STYLE_LABEL);
    lv_obj_set_pos(w[5], 148, 46);
    lv_obj_set_size(w[5], 300, 38);
    lv_label_set_text(w[5], "IMPES 48V");
    ui_style_font(w[5], 24);
}
void tick_screen_update_speed_trang_thai(void) {}
void create_screen_read_can_screen(void) {
    lv_obj_t *w[9];
    w[0] = lv_obj_create(0);
    if (!w[0]) { ui_objects_ok = false; return; }
    objects.read_can_screen = w[0];
    ui_style_apply(w[0], UI_STYLE_SCREEN);
    lv_obj_set_pos(w[0], 0, 0);
    lv_obj_set_size(w[0], 480, 320);
    w[1] = lv_obj_create(w[0]);
    if (!w[1]) { ui_objects_ok = false; return; }
    ui_style_apply(w[1], UI_STYLE_OBJ);
    lv_obj_set_pos(w[1], 14, 75);
    lv_obj_set_size(w[1], 452, 240);
    w[2] = lv_obj_create(w[0]);
    if (!w[2]) { ui_objects_ok = false; return; }
    ui_style_apply(w[2], UI_STYLE_OBJ);
    lv_obj_set_pos(w[2], 14, 15);
    lv_obj_set_size(w[2], 302, 50);
    w[3] = lv_btn_create(w[0]);
    if (!w[3]) { ui_objects_ok = false; return; }
    objects.nut_back_4 = w[3];
    ui_style_apply(w[3], UI_STYLE_BTN);
    lv_obj_set_pos(w[3], 392, 15);
    lv_obj_set_size(w[3], 74, 45);
    lv_obj_add_event_cb(w[3], action_su_kien_tong, LV_EVENT_PRESSED, (void *)0);
    w[4] = lv_label_create(w[3]);
    if (!w[4]) { ui_objects_ok = false; return; }
    ui_style_apply(w[4], UI_STYLE_LABEL);
    lv_obj_set_pos(w[4], 0, 0);
    lv_obj_set_size(w[4], LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_style_align(w[4], LV_ALIGN_CENTER, LV_PART_MAIN);
    lv_label_set_text(w[4], "BACK");
    ui_style_font(w[4], 18);
    w[5] = lv_label_create(w[0]);
    if (!w[5]) { ui_objects_ok = false; return; }
    objects.text_id_can = w[5];
    ui_style_apply(w[5], UI_STYLE_LABEL);
    lv_obj_set_pos(w[5], 29, 107);
    lv_obj_set_size(w[5], LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_label_set_text(w[5], "ID");
    ui_style_font(w[5], 18);
    w[6] = lv_label_create(w[0]);
    if (!w[6]) { ui_objects_ok = false; return; }
    ui_style_apply(w[6], UI_STYLE_LABEL);
    lv_obj_set_pos(w[6], 29, 75);
    lv_obj_set_size(w[6], LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_label_set_text(w[6], "ID");
    ui_style_font(w[6], 16);
    w[7] = lv_label_create(w[0]);
    if (!w[7]) { ui_objects_ok = false; return; }
    objects.text_data_can = w[7];
    ui_style_apply(w[7], UI_STYLE_LABEL);
    lv_obj_set_pos(w[7], 98, 107);
    lv_obj_set_size(w[7], 360, 194);
    lv_label_set_long_mode(w[7], LV_LABEL_LONG_CLIP);
    lv_label_set_text(w[7], "DATA");
    ui_style_font(w[7], 18);
    w[8] = lv_label_create(w[0]);
    if (!w[8]) { ui_objects_ok = false; return; }
    ui_style_apply(w[8], UI_STYLE_LABEL);
    lv_obj_set_pos(w[8], 98, 76);
    lv_obj_set_size(w[8], LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_label_set_text(w[8], "DATA");
    ui_style_font(w[8], 16);
}
void tick_screen_read_can_screen(void) {}
void create_screen_main_24kw(void) {
    lv_obj_t *w[67];
    w[0] = lv_obj_create(0);
    if (!w[0]) { ui_objects_ok = false; return; }
    objects.main_24kw = w[0];
    ui_style_apply(w[0], UI_STYLE_SCREEN);
    lv_obj_set_pos(w[0], 0, 0);
    lv_obj_set_size(w[0], 480, 320);
    w[1] = lv_btn_create(w[0]);
    if (!w[1]) { ui_objects_ok = false; return; }
    objects.nut_back_24 = w[1];
    ui_style_apply(w[1], UI_STYLE_BTN);
    lv_obj_add_event_cb(w[1], action_su_kien_tong, LV_EVENT_PRESSED, (void *)0);
    lv_obj_set_pos(w[1], 388, 8);
    lv_obj_set_size(w[1], 76, 32);
    w[2] = lv_label_create(w[1]);
    if (!w[2]) { ui_objects_ok = false; return; }
    ui_style_apply(w[2], UI_STYLE_LABEL);
    lv_obj_set_pos(w[2], 0, 0);
    lv_obj_set_size(w[2], LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_style_align(w[2], LV_ALIGN_CENTER, LV_PART_MAIN);
    lv_label_set_text(w[2], "BACK");
    ui_style_font(w[2], 16);
    w[3] = lv_label_create(w[0]);
    if (!w[3]) { ui_objects_ok = false; return; }
    ui_style_apply(w[3], UI_STYLE_LABEL);
    lv_label_set_text(w[3], "SOC");
    lv_obj_set_pos(w[3], 22, 58);
    lv_obj_set_size(w[3], 56, 20);
    ui_style_font(w[3], 14);
    w[4] = lv_label_create(w[0]);
    if (!w[4]) { ui_objects_ok = false; return; }
    ui_style_apply(w[4], UI_STYLE_LABEL);
    lv_label_set_text(w[4], "Cycle");
    lv_obj_set_pos(w[4], 22, 79);
    lv_obj_set_size(w[4], 56, 20);
    ui_style_font(w[4], 14);
    w[5] = lv_label_create(w[0]);
    if (!w[5]) { ui_objects_ok = false; return; }
    ui_style_apply(w[5], UI_STYLE_LABEL);
    lv_label_set_text(w[5], "Delvol");
    lv_obj_set_pos(w[5], 22, 100);
    lv_obj_set_size(w[5], 56, 20);
    ui_style_font(w[5], 14);
    w[6] = lv_label_create(w[0]);
    if (!w[6]) { ui_objects_ok = false; return; }
    ui_style_apply(w[6], UI_STYLE_LABEL);
    lv_label_set_text(w[6], "Vmax");
    lv_obj_set_pos(w[6], 22, 121);
    lv_obj_set_size(w[6], 56, 20);
    ui_style_font(w[6], 14);
    w[7] = lv_label_create(w[0]);
    if (!w[7]) { ui_objects_ok = false; return; }
    ui_style_apply(w[7], UI_STYLE_LABEL);
    lv_label_set_text(w[7], "Vmin");
    lv_obj_set_pos(w[7], 22, 142);
    lv_obj_set_size(w[7], 56, 20);
    ui_style_font(w[7], 14);
    w[8] = lv_label_create(w[0]);
    if (!w[8]) { ui_objects_ok = false; return; }
    ui_style_apply(w[8], UI_STYLE_LABEL);
    lv_label_set_text(w[8], "RCAP");
    lv_obj_set_pos(w[8], 22, 163);
    lv_obj_set_size(w[8], 56, 20);
    ui_style_font(w[8], 14);
    w[9] = lv_label_create(w[0]);
    if (!w[9]) { ui_objects_ok = false; return; }
    ui_style_apply(w[9], UI_STYLE_LABEL);
    lv_label_set_text(w[9], "SOH");
    lv_obj_set_pos(w[9], 22, 184);
    lv_obj_set_size(w[9], 56, 20);
    ui_style_font(w[9], 14);
    w[10] = lv_label_create(w[0]);
    if (!w[10]) { ui_objects_ok = false; return; }
    objects.soc_24 = w[10];
    ui_style_apply(w[10], UI_STYLE_LABEL);
    lv_label_set_text(w[10], "00");
    ui_style_apply(w[10], UI_STYLE_VALUE);
    lv_obj_set_pos(w[10], 81, 56);
    lv_obj_set_size(w[10], 68, 22);
    ui_style_font(w[10], 16);
    w[11] = lv_label_create(w[0]);
    if (!w[11]) { ui_objects_ok = false; return; }
    objects.cycle_24 = w[11];
    ui_style_apply(w[11], UI_STYLE_LABEL);
    lv_label_set_text(w[11], "00");
    ui_style_apply(w[11], UI_STYLE_VALUE);
    lv_obj_set_pos(w[11], 81, 77);
    lv_obj_set_size(w[11], 68, 22);
    ui_style_font(w[11], 16);
    w[12] = lv_label_create(w[0]);
    if (!w[12]) { ui_objects_ok = false; return; }
    objects.del_vol_24 = w[12];
    ui_style_apply(w[12], UI_STYLE_LABEL);
    lv_label_set_text(w[12], "00");
    ui_style_apply(w[12], UI_STYLE_VALUE);
    lv_obj_set_pos(w[12], 81, 98);
    lv_obj_set_size(w[12], 68, 22);
    ui_style_font(w[12], 16);
    w[13] = lv_label_create(w[0]);
    if (!w[13]) { ui_objects_ok = false; return; }
    objects.v_max_lfp_24 = w[13];
    ui_style_apply(w[13], UI_STYLE_LABEL);
    lv_label_set_text(w[13], "00");
    ui_style_apply(w[13], UI_STYLE_VALUE);
    lv_obj_set_pos(w[13], 81, 119);
    lv_obj_set_size(w[13], 68, 22);
    ui_style_font(w[13], 16);
    w[14] = lv_label_create(w[0]);
    if (!w[14]) { ui_objects_ok = false; return; }
    objects.v_min_lfp_24 = w[14];
    ui_style_apply(w[14], UI_STYLE_LABEL);
    lv_label_set_text(w[14], "00");
    ui_style_apply(w[14], UI_STYLE_VALUE);
    lv_obj_set_pos(w[14], 81, 140);
    lv_obj_set_size(w[14], 68, 22);
    ui_style_font(w[14], 16);
    w[15] = lv_label_create(w[0]);
    if (!w[15]) { ui_objects_ok = false; return; }
    objects.soh_lfp_24 = w[15];
    ui_style_apply(w[15], UI_STYLE_LABEL);
    lv_label_set_text(w[15], "00");
    ui_style_apply(w[15], UI_STYLE_VALUE);
    lv_obj_set_pos(w[15], 81, 182);
    lv_obj_set_size(w[15], 68, 22);
    ui_style_font(w[15], 16);
    w[16] = lv_label_create(w[0]);
    if (!w[16]) { ui_objects_ok = false; return; }
    objects.rcap_lfp_24 = w[16];
    ui_style_apply(w[16], UI_STYLE_LABEL);
    lv_label_set_text(w[16], "00");
    ui_style_apply(w[16], UI_STYLE_VALUE);
    lv_obj_set_pos(w[16], 81, 161);
    lv_obj_set_size(w[16], 68, 22);
    ui_style_font(w[16], 16);
    w[17] = lv_label_create(w[0]);
    if (!w[17]) { ui_objects_ok = false; return; }
    objects.avg_lfp_24 = w[17];
    ui_style_apply(w[17], UI_STYLE_LABEL);
    lv_label_set_text(w[17], "00");
    ui_style_apply(w[17], UI_STYLE_VALUE);
    lv_obj_set_pos(w[17], 81, 203);
    lv_obj_set_size(w[17], 68, 22);
    ui_style_font(w[17], 16);
    w[18] = lv_label_create(w[0]);
    if (!w[18]) { ui_objects_ok = false; return; }
    ui_style_apply(w[18], UI_STYLE_LABEL);
    lv_label_set_text(w[18], "08");
    lv_obj_set_pos(w[18], 274, 56);
    lv_obj_set_size(w[18], 23, 18);
    ui_style_font(w[18], 14);
    lv_obj_set_style_text_color(w[18], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[19] = lv_label_create(w[0]);
    if (!w[19]) { ui_objects_ok = false; return; }
    ui_style_apply(w[19], UI_STYLE_LABEL);
    lv_label_set_text(w[19], "09");
    lv_obj_set_pos(w[19], 274, 77);
    lv_obj_set_size(w[19], 23, 18);
    ui_style_font(w[19], 14);
    lv_obj_set_style_text_color(w[19], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[20] = lv_label_create(w[0]);
    if (!w[20]) { ui_objects_ok = false; return; }
    ui_style_apply(w[20], UI_STYLE_LABEL);
    lv_label_set_text(w[20], "10");
    lv_obj_set_pos(w[20], 274, 98);
    lv_obj_set_size(w[20], 23, 18);
    ui_style_font(w[20], 14);
    lv_obj_set_style_text_color(w[20], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[21] = lv_label_create(w[0]);
    if (!w[21]) { ui_objects_ok = false; return; }
    ui_style_apply(w[21], UI_STYLE_LABEL);
    lv_label_set_text(w[21], " 11");
    lv_obj_set_pos(w[21], 274, 119);
    lv_obj_set_size(w[21], 23, 18);
    ui_style_font(w[21], 14);
    lv_obj_set_style_text_color(w[21], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[22] = lv_label_create(w[0]);
    if (!w[22]) { ui_objects_ok = false; return; }
    ui_style_apply(w[22], UI_STYLE_LABEL);
    lv_label_set_text(w[22], "12");
    lv_obj_set_pos(w[22], 274, 140);
    lv_obj_set_size(w[22], 23, 18);
    ui_style_font(w[22], 14);
    lv_obj_set_style_text_color(w[22], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[23] = lv_label_create(w[0]);
    if (!w[23]) { ui_objects_ok = false; return; }
    ui_style_apply(w[23], UI_STYLE_LABEL);
    lv_label_set_text(w[23], "13");
    lv_obj_set_pos(w[23], 274, 161);
    lv_obj_set_size(w[23], 23, 18);
    ui_style_font(w[23], 14);
    lv_obj_set_style_text_color(w[23], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[24] = lv_label_create(w[0]);
    if (!w[24]) { ui_objects_ok = false; return; }
    ui_style_apply(w[24], UI_STYLE_LABEL);
    lv_label_set_text(w[24], "14");
    lv_obj_set_pos(w[24], 274, 182);
    lv_obj_set_size(w[24], 23, 18);
    ui_style_font(w[24], 14);
    lv_obj_set_style_text_color(w[24], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[25] = lv_label_create(w[0]);
    if (!w[25]) { ui_objects_ok = false; return; }
    ui_style_apply(w[25], UI_STYLE_LABEL);
    lv_label_set_text(w[25], "15");
    lv_obj_set_pos(w[25], 372, 56);
    lv_obj_set_size(w[25], 23, 18);
    ui_style_font(w[25], 14);
    lv_obj_set_style_text_color(w[25], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[26] = lv_label_create(w[0]);
    if (!w[26]) { ui_objects_ok = false; return; }
    ui_style_apply(w[26], UI_STYLE_LABEL);
    lv_label_set_text(w[26], "16");
    lv_obj_set_pos(w[26], 372, 77);
    lv_obj_set_size(w[26], 23, 18);
    ui_style_font(w[26], 14);
    lv_obj_set_style_text_color(w[26], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[27] = lv_label_create(w[0]);
    if (!w[27]) { ui_objects_ok = false; return; }
    objects.cell_24_8 = w[27];
    ui_style_apply(w[27], UI_STYLE_LABEL);
    lv_label_set_text(w[27], "000");
    ui_style_apply(w[27], UI_STYLE_VALUE);
    lv_obj_set_pos(w[27], 299, 55);
    lv_obj_set_size(w[27], 50, 20);
    ui_style_font(w[27], 14);
    w[28] = lv_label_create(w[0]);
    if (!w[28]) { ui_objects_ok = false; return; }
    objects.cell_24_9 = w[28];
    ui_style_apply(w[28], UI_STYLE_LABEL);
    lv_label_set_text(w[28], "000");
    ui_style_apply(w[28], UI_STYLE_VALUE);
    lv_obj_set_pos(w[28], 299, 76);
    lv_obj_set_size(w[28], 50, 20);
    ui_style_font(w[28], 14);
    w[29] = lv_label_create(w[0]);
    if (!w[29]) { ui_objects_ok = false; return; }
    objects.cell_24_10 = w[29];
    ui_style_apply(w[29], UI_STYLE_LABEL);
    lv_label_set_text(w[29], "000");
    ui_style_apply(w[29], UI_STYLE_VALUE);
    lv_obj_set_pos(w[29], 299, 97);
    lv_obj_set_size(w[29], 50, 20);
    ui_style_font(w[29], 14);
    w[30] = lv_label_create(w[0]);
    if (!w[30]) { ui_objects_ok = false; return; }
    objects.cell_24_11 = w[30];
    ui_style_apply(w[30], UI_STYLE_LABEL);
    lv_label_set_text(w[30], "000");
    ui_style_apply(w[30], UI_STYLE_VALUE);
    lv_obj_set_pos(w[30], 299, 118);
    lv_obj_set_size(w[30], 50, 20);
    ui_style_font(w[30], 14);
    w[31] = lv_label_create(w[0]);
    if (!w[31]) { ui_objects_ok = false; return; }
    objects.cell_24_12 = w[31];
    ui_style_apply(w[31], UI_STYLE_LABEL);
    lv_label_set_text(w[31], "000");
    ui_style_apply(w[31], UI_STYLE_VALUE);
    lv_obj_set_pos(w[31], 299, 139);
    lv_obj_set_size(w[31], 50, 20);
    ui_style_font(w[31], 14);
    w[32] = lv_label_create(w[0]);
    if (!w[32]) { ui_objects_ok = false; return; }
    objects.cell_24_13 = w[32];
    ui_style_apply(w[32], UI_STYLE_LABEL);
    lv_label_set_text(w[32], "000");
    ui_style_apply(w[32], UI_STYLE_VALUE);
    lv_obj_set_pos(w[32], 299, 160);
    lv_obj_set_size(w[32], 50, 20);
    ui_style_font(w[32], 14);
    w[33] = lv_label_create(w[0]);
    if (!w[33]) { ui_objects_ok = false; return; }
    objects.cell_24_14 = w[33];
    ui_style_apply(w[33], UI_STYLE_LABEL);
    lv_label_set_text(w[33], "000");
    ui_style_apply(w[33], UI_STYLE_VALUE);
    lv_obj_set_pos(w[33], 299, 181);
    lv_obj_set_size(w[33], 50, 20);
    ui_style_font(w[33], 14);
    w[34] = lv_label_create(w[0]);
    if (!w[34]) { ui_objects_ok = false; return; }
    ui_style_apply(w[34], UI_STYLE_LABEL);
    lv_label_set_text(w[34], "17");
    lv_obj_set_pos(w[34], 372, 98);
    lv_obj_set_size(w[34], 23, 18);
    ui_style_font(w[34], 14);
    lv_obj_set_style_text_color(w[34], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[35] = lv_label_create(w[0]);
    if (!w[35]) { ui_objects_ok = false; return; }
    ui_style_apply(w[35], UI_STYLE_LABEL);
    lv_label_set_text(w[35], "18");
    lv_obj_set_pos(w[35], 372, 119);
    lv_obj_set_size(w[35], 23, 18);
    ui_style_font(w[35], 14);
    lv_obj_set_style_text_color(w[35], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[36] = lv_label_create(w[0]);
    if (!w[36]) { ui_objects_ok = false; return; }
    ui_style_apply(w[36], UI_STYLE_LABEL);
    lv_label_set_text(w[36], "19");
    lv_obj_set_pos(w[36], 372, 140);
    lv_obj_set_size(w[36], 23, 18);
    ui_style_font(w[36], 14);
    lv_obj_set_style_text_color(w[36], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[37] = lv_label_create(w[0]);
    if (!w[37]) { ui_objects_ok = false; return; }
    objects.cell_24_15 = w[37];
    ui_style_apply(w[37], UI_STYLE_LABEL);
    lv_label_set_text(w[37], "000");
    ui_style_apply(w[37], UI_STYLE_VALUE);
    lv_obj_set_pos(w[37], 397, 55);
    lv_obj_set_size(w[37], 50, 20);
    ui_style_font(w[37], 14);
    w[38] = lv_label_create(w[0]);
    if (!w[38]) { ui_objects_ok = false; return; }
    objects.cell_24_16 = w[38];
    ui_style_apply(w[38], UI_STYLE_LABEL);
    lv_label_set_text(w[38], "000");
    ui_style_apply(w[38], UI_STYLE_VALUE);
    lv_obj_set_pos(w[38], 397, 76);
    lv_obj_set_size(w[38], 50, 20);
    ui_style_font(w[38], 14);
    w[39] = lv_label_create(w[0]);
    if (!w[39]) { ui_objects_ok = false; return; }
    objects.cell_24_17 = w[39];
    ui_style_apply(w[39], UI_STYLE_LABEL);
    lv_label_set_text(w[39], "000");
    ui_style_apply(w[39], UI_STYLE_VALUE);
    lv_obj_set_pos(w[39], 397, 97);
    lv_obj_set_size(w[39], 50, 20);
    ui_style_font(w[39], 14);
    w[40] = lv_label_create(w[0]);
    if (!w[40]) { ui_objects_ok = false; return; }
    objects.cell_24_18 = w[40];
    ui_style_apply(w[40], UI_STYLE_LABEL);
    lv_label_set_text(w[40], "000");
    ui_style_apply(w[40], UI_STYLE_VALUE);
    lv_obj_set_pos(w[40], 397, 118);
    lv_obj_set_size(w[40], 50, 20);
    ui_style_font(w[40], 14);
    w[41] = lv_label_create(w[0]);
    if (!w[41]) { ui_objects_ok = false; return; }
    objects.cell_24_19 = w[41];
    ui_style_apply(w[41], UI_STYLE_LABEL);
    lv_label_set_text(w[41], "000");
    ui_style_apply(w[41], UI_STYLE_VALUE);
    lv_obj_set_pos(w[41], 397, 139);
    lv_obj_set_size(w[41], 50, 20);
    ui_style_font(w[41], 14);
    w[42] = lv_label_create(w[0]);
    if (!w[42]) { ui_objects_ok = false; return; }
    ui_style_apply(w[42], UI_STYLE_LABEL);
    lv_label_set_text(w[42], " 01");
    lv_obj_set_pos(w[42], 176, 56);
    lv_obj_set_size(w[42], 23, 18);
    ui_style_font(w[42], 14);
    lv_obj_set_style_text_color(w[42], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[43] = lv_label_create(w[0]);
    if (!w[43]) { ui_objects_ok = false; return; }
    ui_style_apply(w[43], UI_STYLE_LABEL);
    lv_label_set_text(w[43], "02");
    lv_obj_set_pos(w[43], 176, 77);
    lv_obj_set_size(w[43], 23, 18);
    ui_style_font(w[43], 14);
    lv_obj_set_style_text_color(w[43], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[44] = lv_label_create(w[0]);
    if (!w[44]) { ui_objects_ok = false; return; }
    ui_style_apply(w[44], UI_STYLE_LABEL);
    lv_label_set_text(w[44], "03");
    lv_obj_set_pos(w[44], 176, 98);
    lv_obj_set_size(w[44], 23, 18);
    ui_style_font(w[44], 14);
    lv_obj_set_style_text_color(w[44], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[45] = lv_label_create(w[0]);
    if (!w[45]) { ui_objects_ok = false; return; }
    ui_style_apply(w[45], UI_STYLE_LABEL);
    lv_label_set_text(w[45], "04");
    lv_obj_set_pos(w[45], 176, 119);
    lv_obj_set_size(w[45], 23, 18);
    ui_style_font(w[45], 14);
    lv_obj_set_style_text_color(w[45], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[46] = lv_label_create(w[0]);
    if (!w[46]) { ui_objects_ok = false; return; }
    ui_style_apply(w[46], UI_STYLE_LABEL);
    lv_label_set_text(w[46], "05");
    lv_obj_set_pos(w[46], 176, 140);
    lv_obj_set_size(w[46], 23, 18);
    ui_style_font(w[46], 14);
    lv_obj_set_style_text_color(w[46], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[47] = lv_label_create(w[0]);
    if (!w[47]) { ui_objects_ok = false; return; }
    ui_style_apply(w[47], UI_STYLE_LABEL);
    lv_label_set_text(w[47], "06");
    lv_obj_set_pos(w[47], 176, 161);
    lv_obj_set_size(w[47], 23, 18);
    ui_style_font(w[47], 14);
    lv_obj_set_style_text_color(w[47], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[48] = lv_label_create(w[0]);
    if (!w[48]) { ui_objects_ok = false; return; }
    ui_style_apply(w[48], UI_STYLE_LABEL);
    lv_label_set_text(w[48], "07");
    lv_obj_set_pos(w[48], 176, 182);
    lv_obj_set_size(w[48], 23, 18);
    ui_style_font(w[48], 14);
    lv_obj_set_style_text_color(w[48], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[49] = lv_label_create(w[0]);
    if (!w[49]) { ui_objects_ok = false; return; }
    objects.cell_24_1 = w[49];
    ui_style_apply(w[49], UI_STYLE_LABEL);
    lv_label_set_text(w[49], "000");
    ui_style_apply(w[49], UI_STYLE_VALUE);
    lv_obj_set_pos(w[49], 201, 55);
    lv_obj_set_size(w[49], 50, 20);
    ui_style_font(w[49], 14);
    w[50] = lv_label_create(w[0]);
    if (!w[50]) { ui_objects_ok = false; return; }
    objects.cell_24_2 = w[50];
    ui_style_apply(w[50], UI_STYLE_LABEL);
    lv_label_set_text(w[50], "000");
    ui_style_apply(w[50], UI_STYLE_VALUE);
    lv_obj_set_pos(w[50], 201, 76);
    lv_obj_set_size(w[50], 50, 20);
    ui_style_font(w[50], 14);
    w[51] = lv_label_create(w[0]);
    if (!w[51]) { ui_objects_ok = false; return; }
    objects.cell_24_3 = w[51];
    ui_style_apply(w[51], UI_STYLE_LABEL);
    lv_label_set_text(w[51], "000");
    ui_style_apply(w[51], UI_STYLE_VALUE);
    lv_obj_set_pos(w[51], 201, 97);
    lv_obj_set_size(w[51], 50, 20);
    ui_style_font(w[51], 14);
    w[52] = lv_label_create(w[0]);
    if (!w[52]) { ui_objects_ok = false; return; }
    objects.cell_24_4 = w[52];
    ui_style_apply(w[52], UI_STYLE_LABEL);
    lv_label_set_text(w[52], "000");
    ui_style_apply(w[52], UI_STYLE_VALUE);
    lv_obj_set_pos(w[52], 201, 118);
    lv_obj_set_size(w[52], 50, 20);
    ui_style_font(w[52], 14);
    w[53] = lv_label_create(w[0]);
    if (!w[53]) { ui_objects_ok = false; return; }
    objects.cell_24_5 = w[53];
    ui_style_apply(w[53], UI_STYLE_LABEL);
    lv_label_set_text(w[53], "000");
    ui_style_apply(w[53], UI_STYLE_VALUE);
    lv_obj_set_pos(w[53], 201, 139);
    lv_obj_set_size(w[53], 50, 20);
    ui_style_font(w[53], 14);
    w[54] = lv_label_create(w[0]);
    if (!w[54]) { ui_objects_ok = false; return; }
    objects.cell_24_6 = w[54];
    ui_style_apply(w[54], UI_STYLE_LABEL);
    lv_label_set_text(w[54], "000");
    ui_style_apply(w[54], UI_STYLE_VALUE);
    lv_obj_set_pos(w[54], 201, 160);
    lv_obj_set_size(w[54], 50, 20);
    ui_style_font(w[54], 14);
    w[55] = lv_label_create(w[0]);
    if (!w[55]) { ui_objects_ok = false; return; }
    objects.cell_24_7 = w[55];
    ui_style_apply(w[55], UI_STYLE_LABEL);
    lv_label_set_text(w[55], "000");
    ui_style_apply(w[55], UI_STYLE_VALUE);
    lv_obj_set_pos(w[55], 201, 181);
    lv_obj_set_size(w[55], 50, 20);
    ui_style_font(w[55], 14);
    w[56] = lv_label_create(w[0]);
    if (!w[56]) { ui_objects_ok = false; return; }
    ui_style_apply(w[56], UI_STYLE_LABEL);
    lv_label_set_text(w[56], "T_FET:");
    lv_obj_set_pos(w[56], 318, 243);
    lv_obj_set_size(w[56], 39, 18);
    ui_style_font(w[56], 14);
    w[57] = lv_label_create(w[0]);
    if (!w[57]) { ui_objects_ok = false; return; }
    ui_style_apply(w[57], UI_STYLE_LABEL);
    lv_label_set_text(w[57], "AVG");
    lv_obj_set_pos(w[57], 22, 205);
    lv_obj_set_size(w[57], 56, 20);
    ui_style_font(w[57], 14);
    w[58] = lv_label_create(w[0]);
    if (!w[58]) { ui_objects_ok = false; return; }
    objects.t_3_24 = w[58];
    ui_style_apply(w[58], UI_STYLE_LABEL);
    lv_label_set_text(w[58], "00");
    ui_style_apply(w[58], UI_STYLE_VALUE);
    lv_obj_set_pos(w[58], 356, 242);
    lv_obj_set_size(w[58], 33, 20);
    ui_style_font(w[58], 14);
    w[59] = lv_label_create(w[0]);
    if (!w[59]) { ui_objects_ok = false; return; }
    objects.text_vol_lfp_24 = w[59];
    ui_style_apply(w[59], UI_STYLE_LABEL);
    lv_label_set_text(w[59], "00");
    ui_style_apply(w[59], UI_STYLE_VALUE);
    lv_obj_set_pos(w[59], 114, 279);
    lv_obj_set_size(w[59], 112, 28);
    ui_style_font(w[59], 22);
    w[60] = lv_label_create(w[0]);
    if (!w[60]) { ui_objects_ok = false; return; }
    objects.ampe_lfp_24 = w[60];
    ui_style_apply(w[60], UI_STYLE_LABEL);
    lv_label_set_text(w[60], "00");
    ui_style_apply(w[60], UI_STYLE_VALUE);
    lv_obj_set_pos(w[60], 348, 279);
    lv_obj_set_size(w[60], 112, 28);
    ui_style_font(w[60], 22);
    w[61] = lv_label_create(w[0]);
    if (!w[61]) { ui_objects_ok = false; return; }
    ui_style_apply(w[61], UI_STYLE_LABEL);
    lv_label_set_text(w[61], "T_1:");
    lv_obj_set_pos(w[61], 20, 243);
    lv_obj_set_size(w[61], 39, 18);
    ui_style_font(w[61], 14);
    w[62] = lv_label_create(w[0]);
    if (!w[62]) { ui_objects_ok = false; return; }
    ui_style_apply(w[62], UI_STYLE_LABEL);
    lv_label_set_text(w[62], "T_2:");
    lv_obj_set_pos(w[62], 169, 243);
    lv_obj_set_size(w[62], 39, 18);
    ui_style_font(w[62], 14);
    w[63] = lv_label_create(w[0]);
    if (!w[63]) { ui_objects_ok = false; return; }
    objects.t_1_24 = w[63];
    ui_style_apply(w[63], UI_STYLE_LABEL);
    lv_label_set_text(w[63], "00");
    ui_style_apply(w[63], UI_STYLE_VALUE);
    lv_obj_set_pos(w[63], 207, 242);
    lv_obj_set_size(w[63], 33, 20);
    ui_style_font(w[63], 14);
    w[64] = lv_label_create(w[0]);
    if (!w[64]) { ui_objects_ok = false; return; }
    objects.t_2_24 = w[64];
    ui_style_apply(w[64], UI_STYLE_LABEL);
    lv_label_set_text(w[64], "00");
    ui_style_apply(w[64], UI_STYLE_VALUE);
    lv_obj_set_pos(w[64], 58, 242);
    lv_obj_set_size(w[64], 33, 20);
    ui_style_font(w[64], 14);
    w[65] = lv_label_create(w[0]);
    if (!w[65]) { ui_objects_ok = false; return; }
    ui_style_apply(w[65], UI_STYLE_LABEL);
    lv_label_set_text(w[65], "%");
    lv_obj_set_pos(w[65], 133, 58);
    lv_obj_set_size(w[65], 16, 20);
    ui_style_font(w[65], 14);
    w[66] = lv_label_create(w[0]);
    if (!w[66]) { ui_objects_ok = false; return; }
    ui_style_apply(w[66], UI_STYLE_LABEL);
    lv_label_set_long_mode(w[66], LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_label_set_text(w[66], "LFP 2.4 kW");
    ui_style_apply(w[66], UI_STYLE_VALUE);
    lv_obj_set_pos(w[66], 16, 10);
    lv_obj_set_size(w[66], 350, 28);
    ui_style_font(w[66], 22);
}
void tick_screen_main_24kw(void) {}
void create_screen_bms_jk(void) {
    lv_obj_t *w[88];
    w[0] = lv_obj_create(0);
    if (!w[0]) { ui_objects_ok = false; return; }
    objects.bms_jk = w[0];
    ui_style_apply(w[0], UI_STYLE_SCREEN);
    lv_obj_set_pos(w[0], 0, 0);
    lv_obj_set_size(w[0], 480, 320);
    w[1] = lv_btn_create(w[0]);
    if (!w[1]) { ui_objects_ok = false; return; }
    objects.nut_back_jk = w[1];
    ui_style_apply(w[1], UI_STYLE_BTN);
    lv_obj_add_event_cb(w[1], action_su_kien_tong, LV_EVENT_PRESSED, (void *)0);
    lv_obj_set_pos(w[1], 388, 8);
    lv_obj_set_size(w[1], 76, 32);
    w[2] = lv_label_create(w[1]);
    if (!w[2]) { ui_objects_ok = false; return; }
    ui_style_apply(w[2], UI_STYLE_LABEL);
    lv_obj_set_pos(w[2], 0, 0);
    lv_obj_set_size(w[2], LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_style_align(w[2], LV_ALIGN_CENTER, LV_PART_MAIN);
    lv_label_set_text(w[2], "BACK");
    ui_style_font(w[2], 18);
    w[3] = lv_label_create(w[0]);
    if (!w[3]) { ui_objects_ok = false; return; }
    ui_style_apply(w[3], UI_STYLE_LABEL);
    lv_label_set_text(w[3], "SOC");
    lv_obj_set_pos(w[3], 22, 57);
    lv_obj_set_size(w[3], 56, 20);
    ui_style_font(w[3], 14);
    w[4] = lv_label_create(w[0]);
    if (!w[4]) { ui_objects_ok = false; return; }
    ui_style_apply(w[4], UI_STYLE_LABEL);
    lv_label_set_text(w[4], "Cycle");
    lv_obj_set_pos(w[4], 22, 99);
    lv_obj_set_size(w[4], 56, 20);
    ui_style_font(w[4], 14);
    w[5] = lv_label_create(w[0]);
    if (!w[5]) { ui_objects_ok = false; return; }
    ui_style_apply(w[5], UI_STYLE_LABEL);
    lv_label_set_text(w[5], "Delvol");
    lv_obj_set_pos(w[5], 22, 162);
    lv_obj_set_size(w[5], 56, 20);
    ui_style_font(w[5], 14);
    w[6] = lv_label_create(w[0]);
    if (!w[6]) { ui_objects_ok = false; return; }
    ui_style_apply(w[6], UI_STYLE_LABEL);
    lv_label_set_text(w[6], "RCAP");
    lv_obj_set_pos(w[6], 22, 141);
    lv_obj_set_size(w[6], 56, 20);
    ui_style_font(w[6], 14);
    w[7] = lv_label_create(w[0]);
    if (!w[7]) { ui_objects_ok = false; return; }
    ui_style_apply(w[7], UI_STYLE_LABEL);
    lv_label_set_text(w[7], "SOH");
    lv_obj_set_pos(w[7], 22, 120);
    lv_obj_set_size(w[7], 56, 20);
    ui_style_font(w[7], 14);
    w[8] = lv_label_create(w[0]);
    if (!w[8]) { ui_objects_ok = false; return; }
    objects.soc_jk = w[8];
    ui_style_apply(w[8], UI_STYLE_LABEL);
    lv_label_set_text(w[8], "00");
    ui_style_apply(w[8], UI_STYLE_VALUE);
    lv_obj_set_pos(w[8], 81, 55);
    lv_obj_set_size(w[8], 68, 22);
    ui_style_font(w[8], 16);
    w[9] = lv_label_create(w[0]);
    if (!w[9]) { ui_objects_ok = false; return; }
    objects.cycle_jk = w[9];
    ui_style_apply(w[9], UI_STYLE_LABEL);
    lv_label_set_text(w[9], "00");
    ui_style_apply(w[9], UI_STYLE_VALUE);
    lv_obj_set_pos(w[9], 81, 97);
    lv_obj_set_size(w[9], 68, 22);
    ui_style_font(w[9], 16);
    w[10] = lv_label_create(w[0]);
    if (!w[10]) { ui_objects_ok = false; return; }
    objects.del_vol_jk = w[10];
    ui_style_apply(w[10], UI_STYLE_LABEL);
    lv_label_set_text(w[10], "00");
    ui_style_apply(w[10], UI_STYLE_VALUE);
    lv_obj_set_pos(w[10], 81, 160);
    lv_obj_set_size(w[10], 68, 22);
    ui_style_font(w[10], 16);
    w[11] = lv_label_create(w[0]);
    if (!w[11]) { ui_objects_ok = false; return; }
    objects.soh_jk = w[11];
    ui_style_apply(w[11], UI_STYLE_LABEL);
    lv_label_set_text(w[11], "00");
    ui_style_apply(w[11], UI_STYLE_VALUE);
    lv_obj_set_pos(w[11], 81, 118);
    lv_obj_set_size(w[11], 68, 22);
    ui_style_font(w[11], 16);
    w[12] = lv_label_create(w[0]);
    if (!w[12]) { ui_objects_ok = false; return; }
    objects.rcap_jk = w[12];
    ui_style_apply(w[12], UI_STYLE_LABEL);
    lv_label_set_text(w[12], "00");
    ui_style_apply(w[12], UI_STYLE_VALUE);
    lv_obj_set_pos(w[12], 81, 139);
    lv_obj_set_size(w[12], 68, 22);
    ui_style_font(w[12], 16);
    w[13] = lv_label_create(w[0]);
    if (!w[13]) { ui_objects_ok = false; return; }
    objects.avg_jk = w[13];
    ui_style_apply(w[13], UI_STYLE_LABEL);
    lv_label_set_text(w[13], "00");
    ui_style_apply(w[13], UI_STYLE_VALUE);
    lv_obj_set_pos(w[13], 81, 181);
    lv_obj_set_size(w[13], 68, 22);
    ui_style_font(w[13], 16);
    w[14] = lv_label_create(w[0]);
    if (!w[14]) { ui_objects_ok = false; return; }
    ui_style_apply(w[14], UI_STYLE_LABEL);
    lv_label_set_text(w[14], "08");
    lv_obj_set_pos(w[14], 176, 217);
    lv_obj_set_size(w[14], 23, 18);
    ui_style_font(w[14], 14);
    lv_obj_set_style_text_color(w[14], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[15] = lv_label_create(w[0]);
    if (!w[15]) { ui_objects_ok = false; return; }
    ui_style_apply(w[15], UI_STYLE_LABEL);
    lv_label_set_text(w[15], "09");
    lv_obj_set_pos(w[15], 274, 56);
    lv_obj_set_size(w[15], 23, 18);
    ui_style_font(w[15], 14);
    lv_obj_set_style_text_color(w[15], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[16] = lv_label_create(w[0]);
    if (!w[16]) { ui_objects_ok = false; return; }
    ui_style_apply(w[16], UI_STYLE_LABEL);
    lv_label_set_text(w[16], "10");
    lv_obj_set_pos(w[16], 274, 79);
    lv_obj_set_size(w[16], 23, 18);
    ui_style_font(w[16], 14);
    lv_obj_set_style_text_color(w[16], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[17] = lv_label_create(w[0]);
    if (!w[17]) { ui_objects_ok = false; return; }
    ui_style_apply(w[17], UI_STYLE_LABEL);
    lv_label_set_text(w[17], "11");
    lv_obj_set_pos(w[17], 274, 102);
    lv_obj_set_size(w[17], 23, 18);
    ui_style_font(w[17], 14);
    lv_obj_set_style_text_color(w[17], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[18] = lv_label_create(w[0]);
    if (!w[18]) { ui_objects_ok = false; return; }
    ui_style_apply(w[18], UI_STYLE_LABEL);
    lv_label_set_text(w[18], "12");
    lv_obj_set_pos(w[18], 274, 125);
    lv_obj_set_size(w[18], 23, 18);
    ui_style_font(w[18], 14);
    lv_obj_set_style_text_color(w[18], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[19] = lv_label_create(w[0]);
    if (!w[19]) { ui_objects_ok = false; return; }
    ui_style_apply(w[19], UI_STYLE_LABEL);
    lv_label_set_text(w[19], "13");
    lv_obj_set_pos(w[19], 274, 148);
    lv_obj_set_size(w[19], 23, 18);
    ui_style_font(w[19], 14);
    lv_obj_set_style_text_color(w[19], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[20] = lv_label_create(w[0]);
    if (!w[20]) { ui_objects_ok = false; return; }
    ui_style_apply(w[20], UI_STYLE_LABEL);
    lv_label_set_text(w[20], "14");
    lv_obj_set_pos(w[20], 274, 171);
    lv_obj_set_size(w[20], 23, 18);
    ui_style_font(w[20], 14);
    lv_obj_set_style_text_color(w[20], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[21] = lv_label_create(w[0]);
    if (!w[21]) { ui_objects_ok = false; return; }
    ui_style_apply(w[21], UI_STYLE_LABEL);
    lv_label_set_text(w[21], "15");
    lv_obj_set_pos(w[21], 274, 194);
    lv_obj_set_size(w[21], 23, 18);
    ui_style_font(w[21], 14);
    lv_obj_set_style_text_color(w[21], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[22] = lv_label_create(w[0]);
    if (!w[22]) { ui_objects_ok = false; return; }
    ui_style_apply(w[22], UI_STYLE_LABEL);
    lv_label_set_text(w[22], "16");
    lv_obj_set_pos(w[22], 274, 217);
    lv_obj_set_size(w[22], 23, 18);
    ui_style_font(w[22], 14);
    lv_obj_set_style_text_color(w[22], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[23] = lv_label_create(w[0]);
    if (!w[23]) { ui_objects_ok = false; return; }
    objects.cell_8_jk = w[23];
    ui_style_apply(w[23], UI_STYLE_LABEL);
    lv_label_set_text(w[23], "000");
    ui_style_apply(w[23], UI_STYLE_VALUE);
    lv_obj_set_pos(w[23], 201, 216);
    lv_obj_set_size(w[23], 50, 20);
    ui_style_font(w[23], 14);
    w[24] = lv_label_create(w[0]);
    if (!w[24]) { ui_objects_ok = false; return; }
    objects.cell_9_jk = w[24];
    ui_style_apply(w[24], UI_STYLE_LABEL);
    lv_label_set_text(w[24], "000");
    ui_style_apply(w[24], UI_STYLE_VALUE);
    lv_obj_set_pos(w[24], 299, 55);
    lv_obj_set_size(w[24], 50, 20);
    ui_style_font(w[24], 14);
    w[25] = lv_label_create(w[0]);
    if (!w[25]) { ui_objects_ok = false; return; }
    objects.cell_10_jk = w[25];
    ui_style_apply(w[25], UI_STYLE_LABEL);
    lv_label_set_text(w[25], "000");
    ui_style_apply(w[25], UI_STYLE_VALUE);
    lv_obj_set_pos(w[25], 299, 78);
    lv_obj_set_size(w[25], 50, 20);
    ui_style_font(w[25], 14);
    w[26] = lv_label_create(w[0]);
    if (!w[26]) { ui_objects_ok = false; return; }
    objects.cell_11_jk = w[26];
    ui_style_apply(w[26], UI_STYLE_LABEL);
    lv_label_set_text(w[26], "000");
    ui_style_apply(w[26], UI_STYLE_VALUE);
    lv_obj_set_pos(w[26], 299, 101);
    lv_obj_set_size(w[26], 50, 20);
    ui_style_font(w[26], 14);
    w[27] = lv_label_create(w[0]);
    if (!w[27]) { ui_objects_ok = false; return; }
    objects.cell_12_jk = w[27];
    ui_style_apply(w[27], UI_STYLE_LABEL);
    lv_label_set_text(w[27], "000");
    ui_style_apply(w[27], UI_STYLE_VALUE);
    lv_obj_set_pos(w[27], 299, 124);
    lv_obj_set_size(w[27], 50, 20);
    ui_style_font(w[27], 14);
    w[28] = lv_label_create(w[0]);
    if (!w[28]) { ui_objects_ok = false; return; }
    objects.cell_13_jk = w[28];
    ui_style_apply(w[28], UI_STYLE_LABEL);
    lv_label_set_text(w[28], "000");
    ui_style_apply(w[28], UI_STYLE_VALUE);
    lv_obj_set_pos(w[28], 299, 147);
    lv_obj_set_size(w[28], 50, 20);
    ui_style_font(w[28], 14);
    w[29] = lv_label_create(w[0]);
    if (!w[29]) { ui_objects_ok = false; return; }
    objects.cell_14_jk = w[29];
    ui_style_apply(w[29], UI_STYLE_LABEL);
    lv_label_set_text(w[29], "000");
    ui_style_apply(w[29], UI_STYLE_VALUE);
    lv_obj_set_pos(w[29], 299, 170);
    lv_obj_set_size(w[29], 50, 20);
    ui_style_font(w[29], 14);
    w[30] = lv_label_create(w[0]);
    if (!w[30]) { ui_objects_ok = false; return; }
    ui_style_apply(w[30], UI_STYLE_LABEL);
    lv_label_set_text(w[30], "17");
    lv_obj_set_pos(w[30], 372, 56);
    lv_obj_set_size(w[30], 23, 18);
    ui_style_font(w[30], 14);
    lv_obj_set_style_text_color(w[30], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[31] = lv_label_create(w[0]);
    if (!w[31]) { ui_objects_ok = false; return; }
    ui_style_apply(w[31], UI_STYLE_LABEL);
    lv_label_set_text(w[31], "18");
    lv_obj_set_pos(w[31], 372, 79);
    lv_obj_set_size(w[31], 23, 18);
    ui_style_font(w[31], 14);
    lv_obj_set_style_text_color(w[31], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[32] = lv_label_create(w[0]);
    if (!w[32]) { ui_objects_ok = false; return; }
    ui_style_apply(w[32], UI_STYLE_LABEL);
    lv_label_set_text(w[32], "19");
    lv_obj_set_pos(w[32], 372, 102);
    lv_obj_set_size(w[32], 23, 18);
    ui_style_font(w[32], 14);
    lv_obj_set_style_text_color(w[32], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[33] = lv_label_create(w[0]);
    if (!w[33]) { ui_objects_ok = false; return; }
    ui_style_apply(w[33], UI_STYLE_LABEL);
    lv_label_set_text(w[33], "20");
    lv_obj_set_pos(w[33], 372, 125);
    lv_obj_set_size(w[33], 23, 18);
    ui_style_font(w[33], 14);
    lv_obj_set_style_text_color(w[33], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[34] = lv_label_create(w[0]);
    if (!w[34]) { ui_objects_ok = false; return; }
    ui_style_apply(w[34], UI_STYLE_LABEL);
    lv_label_set_text(w[34], "21");
    lv_obj_set_pos(w[34], 372, 148);
    lv_obj_set_size(w[34], 23, 18);
    ui_style_font(w[34], 14);
    lv_obj_set_style_text_color(w[34], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[35] = lv_label_create(w[0]);
    if (!w[35]) { ui_objects_ok = false; return; }
    objects.cell_15_jk = w[35];
    ui_style_apply(w[35], UI_STYLE_LABEL);
    lv_label_set_text(w[35], "000");
    ui_style_apply(w[35], UI_STYLE_VALUE);
    lv_obj_set_pos(w[35], 299, 193);
    lv_obj_set_size(w[35], 50, 20);
    ui_style_font(w[35], 14);
    w[36] = lv_label_create(w[0]);
    if (!w[36]) { ui_objects_ok = false; return; }
    objects.cell_16_jk = w[36];
    ui_style_apply(w[36], UI_STYLE_LABEL);
    lv_label_set_text(w[36], "000");
    ui_style_apply(w[36], UI_STYLE_VALUE);
    lv_obj_set_pos(w[36], 299, 216);
    lv_obj_set_size(w[36], 50, 20);
    ui_style_font(w[36], 14);
    w[37] = lv_label_create(w[0]);
    if (!w[37]) { ui_objects_ok = false; return; }
    objects.cell_17_jk = w[37];
    ui_style_apply(w[37], UI_STYLE_LABEL);
    lv_label_set_text(w[37], "000");
    ui_style_apply(w[37], UI_STYLE_VALUE);
    lv_obj_set_pos(w[37], 397, 55);
    lv_obj_set_size(w[37], 50, 20);
    ui_style_font(w[37], 14);
    w[38] = lv_label_create(w[0]);
    if (!w[38]) { ui_objects_ok = false; return; }
    objects.cell_18_jk = w[38];
    ui_style_apply(w[38], UI_STYLE_LABEL);
    lv_label_set_text(w[38], "000");
    ui_style_apply(w[38], UI_STYLE_VALUE);
    lv_obj_set_pos(w[38], 397, 78);
    lv_obj_set_size(w[38], 50, 20);
    ui_style_font(w[38], 14);
    w[39] = lv_label_create(w[0]);
    if (!w[39]) { ui_objects_ok = false; return; }
    objects.cell_19_jk = w[39];
    ui_style_apply(w[39], UI_STYLE_LABEL);
    lv_label_set_text(w[39], "000");
    ui_style_apply(w[39], UI_STYLE_VALUE);
    lv_obj_set_pos(w[39], 397, 101);
    lv_obj_set_size(w[39], 50, 20);
    ui_style_font(w[39], 14);
    w[40] = lv_label_create(w[0]);
    if (!w[40]) { ui_objects_ok = false; return; }
    objects.cell_20_jk = w[40];
    ui_style_apply(w[40], UI_STYLE_LABEL);
    lv_label_set_text(w[40], "000");
    ui_style_apply(w[40], UI_STYLE_VALUE);
    lv_obj_set_pos(w[40], 397, 124);
    lv_obj_set_size(w[40], 50, 20);
    ui_style_font(w[40], 14);
    w[41] = lv_label_create(w[0]);
    if (!w[41]) { ui_objects_ok = false; return; }
    objects.cell_21_jk = w[41];
    ui_style_apply(w[41], UI_STYLE_LABEL);
    lv_label_set_text(w[41], "000");
    ui_style_apply(w[41], UI_STYLE_VALUE);
    lv_obj_set_pos(w[41], 397, 147);
    lv_obj_set_size(w[41], 50, 20);
    ui_style_font(w[41], 14);
    w[42] = lv_label_create(w[0]);
    if (!w[42]) { ui_objects_ok = false; return; }
    ui_style_apply(w[42], UI_STYLE_LABEL);
    lv_label_set_text(w[42], "01");
    lv_obj_set_pos(w[42], 176, 56);
    lv_obj_set_size(w[42], 23, 18);
    ui_style_font(w[42], 14);
    lv_obj_set_style_text_color(w[42], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[43] = lv_label_create(w[0]);
    if (!w[43]) { ui_objects_ok = false; return; }
    ui_style_apply(w[43], UI_STYLE_LABEL);
    lv_label_set_text(w[43], "02");
    lv_obj_set_pos(w[43], 176, 79);
    lv_obj_set_size(w[43], 23, 18);
    ui_style_font(w[43], 14);
    lv_obj_set_style_text_color(w[43], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[44] = lv_label_create(w[0]);
    if (!w[44]) { ui_objects_ok = false; return; }
    ui_style_apply(w[44], UI_STYLE_LABEL);
    lv_label_set_text(w[44], "03");
    lv_obj_set_pos(w[44], 176, 102);
    lv_obj_set_size(w[44], 23, 18);
    ui_style_font(w[44], 14);
    lv_obj_set_style_text_color(w[44], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[45] = lv_label_create(w[0]);
    if (!w[45]) { ui_objects_ok = false; return; }
    ui_style_apply(w[45], UI_STYLE_LABEL);
    lv_label_set_text(w[45], "04");
    lv_obj_set_pos(w[45], 176, 125);
    lv_obj_set_size(w[45], 23, 18);
    ui_style_font(w[45], 14);
    lv_obj_set_style_text_color(w[45], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[46] = lv_label_create(w[0]);
    if (!w[46]) { ui_objects_ok = false; return; }
    ui_style_apply(w[46], UI_STYLE_LABEL);
    lv_label_set_text(w[46], "05");
    lv_obj_set_pos(w[46], 176, 148);
    lv_obj_set_size(w[46], 23, 18);
    ui_style_font(w[46], 14);
    lv_obj_set_style_text_color(w[46], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[47] = lv_label_create(w[0]);
    if (!w[47]) { ui_objects_ok = false; return; }
    ui_style_apply(w[47], UI_STYLE_LABEL);
    lv_label_set_text(w[47], "06");
    lv_obj_set_pos(w[47], 176, 171);
    lv_obj_set_size(w[47], 23, 18);
    ui_style_font(w[47], 14);
    lv_obj_set_style_text_color(w[47], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[48] = lv_label_create(w[0]);
    if (!w[48]) { ui_objects_ok = false; return; }
    ui_style_apply(w[48], UI_STYLE_LABEL);
    lv_label_set_text(w[48], "07");
    lv_obj_set_pos(w[48], 176, 194);
    lv_obj_set_size(w[48], 23, 18);
    ui_style_font(w[48], 14);
    lv_obj_set_style_text_color(w[48], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[49] = lv_label_create(w[0]);
    if (!w[49]) { ui_objects_ok = false; return; }
    objects.cell_1_jk = w[49];
    ui_style_apply(w[49], UI_STYLE_LABEL);
    lv_label_set_text(w[49], "000");
    ui_style_apply(w[49], UI_STYLE_VALUE);
    lv_obj_set_pos(w[49], 201, 55);
    lv_obj_set_size(w[49], 50, 20);
    ui_style_font(w[49], 14);
    w[50] = lv_label_create(w[0]);
    if (!w[50]) { ui_objects_ok = false; return; }
    objects.cell_2_jk = w[50];
    ui_style_apply(w[50], UI_STYLE_LABEL);
    lv_label_set_text(w[50], "000");
    ui_style_apply(w[50], UI_STYLE_VALUE);
    lv_obj_set_pos(w[50], 201, 78);
    lv_obj_set_size(w[50], 50, 20);
    ui_style_font(w[50], 14);
    w[51] = lv_label_create(w[0]);
    if (!w[51]) { ui_objects_ok = false; return; }
    objects.cell_3_jk = w[51];
    ui_style_apply(w[51], UI_STYLE_LABEL);
    lv_label_set_text(w[51], "000");
    ui_style_apply(w[51], UI_STYLE_VALUE);
    lv_obj_set_pos(w[51], 201, 101);
    lv_obj_set_size(w[51], 50, 20);
    ui_style_font(w[51], 14);
    w[52] = lv_label_create(w[0]);
    if (!w[52]) { ui_objects_ok = false; return; }
    objects.cell_4_jk = w[52];
    ui_style_apply(w[52], UI_STYLE_LABEL);
    lv_label_set_text(w[52], "000");
    ui_style_apply(w[52], UI_STYLE_VALUE);
    lv_obj_set_pos(w[52], 201, 124);
    lv_obj_set_size(w[52], 50, 20);
    ui_style_font(w[52], 14);
    w[53] = lv_label_create(w[0]);
    if (!w[53]) { ui_objects_ok = false; return; }
    objects.cell_5_jk = w[53];
    ui_style_apply(w[53], UI_STYLE_LABEL);
    lv_label_set_text(w[53], "000");
    ui_style_apply(w[53], UI_STYLE_VALUE);
    lv_obj_set_pos(w[53], 201, 147);
    lv_obj_set_size(w[53], 50, 20);
    ui_style_font(w[53], 14);
    w[54] = lv_label_create(w[0]);
    if (!w[54]) { ui_objects_ok = false; return; }
    objects.cell_6_jk = w[54];
    ui_style_apply(w[54], UI_STYLE_LABEL);
    lv_label_set_text(w[54], "000");
    ui_style_apply(w[54], UI_STYLE_VALUE);
    lv_obj_set_pos(w[54], 201, 170);
    lv_obj_set_size(w[54], 50, 20);
    ui_style_font(w[54], 14);
    w[55] = lv_label_create(w[0]);
    if (!w[55]) { ui_objects_ok = false; return; }
    objects.cell_7_jk = w[55];
    ui_style_apply(w[55], UI_STYLE_LABEL);
    lv_label_set_text(w[55], "000");
    ui_style_apply(w[55], UI_STYLE_VALUE);
    lv_obj_set_pos(w[55], 201, 193);
    lv_obj_set_size(w[55], 50, 20);
    ui_style_font(w[55], 14);
    w[56] = lv_label_create(w[0]);
    if (!w[56]) { ui_objects_ok = false; return; }
    objects.cell_22_jk = w[56];
    ui_style_apply(w[56], UI_STYLE_LABEL);
    lv_label_set_text(w[56], "000");
    ui_style_apply(w[56], UI_STYLE_VALUE);
    lv_obj_set_pos(w[56], 397, 170);
    lv_obj_set_size(w[56], 50, 20);
    ui_style_font(w[56], 14);
    w[57] = lv_label_create(w[0]);
    if (!w[57]) { ui_objects_ok = false; return; }
    ui_style_apply(w[57], UI_STYLE_LABEL);
    lv_label_set_text(w[57], "22");
    lv_obj_set_pos(w[57], 372, 171);
    lv_obj_set_size(w[57], 23, 18);
    ui_style_font(w[57], 14);
    lv_obj_set_style_text_color(w[57], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[58] = lv_label_create(w[0]);
    if (!w[58]) { ui_objects_ok = false; return; }
    ui_style_apply(w[58], UI_STYLE_LABEL);
    lv_label_set_text(w[58], "FET");
    lv_obj_set_pos(w[58], 170, 286);
    lv_obj_set_size(w[58], 29, 18);
    ui_style_font(w[58], 14);
    w[59] = lv_label_create(w[0]);
    if (!w[59]) { ui_objects_ok = false; return; }
    ui_style_apply(w[59], UI_STYLE_LABEL);
    lv_label_set_text(w[59], "AVG");
    lv_obj_set_pos(w[59], 22, 183);
    lv_obj_set_size(w[59], 56, 20);
    ui_style_font(w[59], 14);
    w[60] = lv_label_create(w[0]);
    if (!w[60]) { ui_objects_ok = false; return; }
    objects.tem_fet_jk = w[60];
    ui_style_apply(w[60], UI_STYLE_LABEL);
    lv_label_set_text(w[60], "00");
    ui_style_apply(w[60], UI_STYLE_VALUE);
    lv_obj_set_pos(w[60], 198, 285);
    lv_obj_set_size(w[60], 42, 20);
    ui_style_font(w[60], 16);
    w[61] = lv_label_create(w[0]);
    if (!w[61]) { ui_objects_ok = false; return; }
    objects.text_vol_jk = w[61];
    ui_style_apply(w[61], UI_STYLE_LABEL);
    lv_label_set_text(w[61], "00");
    ui_style_apply(w[61], UI_STYLE_VALUE);
    lv_obj_set_pos(w[61], 274, 284);
    lv_obj_set_size(w[61], 70, 24);
    ui_style_font(w[61], 18);
    w[62] = lv_label_create(w[0]);
    if (!w[62]) { ui_objects_ok = false; return; }
    objects.ampe_jk = w[62];
    ui_style_apply(w[62], UI_STYLE_LABEL);
    lv_label_set_text(w[62], "00");
    ui_style_apply(w[62], UI_STYLE_VALUE);
    lv_obj_set_pos(w[62], 382, 284);
    lv_obj_set_size(w[62], 76, 24);
    ui_style_font(w[62], 18);
    w[63] = lv_label_create(w[0]);
    if (!w[63]) { ui_objects_ok = false; return; }
    ui_style_apply(w[63], UI_STYLE_LABEL);
    lv_label_set_text(w[63], "T1");
    lv_obj_set_pos(w[63], 20, 286);
    lv_obj_set_size(w[63], 29, 18);
    ui_style_font(w[63], 14);
    w[64] = lv_label_create(w[0]);
    if (!w[64]) { ui_objects_ok = false; return; }
    ui_style_apply(w[64], UI_STYLE_LABEL);
    lv_label_set_text(w[64], "T2");
    lv_obj_set_pos(w[64], 95, 286);
    lv_obj_set_size(w[64], 29, 18);
    ui_style_font(w[64], 14);
    w[65] = lv_label_create(w[0]);
    if (!w[65]) { ui_objects_ok = false; return; }
    objects.t_1_jk = w[65];
    ui_style_apply(w[65], UI_STYLE_LABEL);
    lv_label_set_text(w[65], "00");
    ui_style_apply(w[65], UI_STYLE_VALUE);
    lv_obj_set_pos(w[65], 48, 285);
    lv_obj_set_size(w[65], 42, 20);
    ui_style_font(w[65], 16);
    w[66] = lv_label_create(w[0]);
    if (!w[66]) { ui_objects_ok = false; return; }
    objects.t_2_jk = w[66];
    ui_style_apply(w[66], UI_STYLE_LABEL);
    lv_label_set_text(w[66], "00");
    ui_style_apply(w[66], UI_STYLE_VALUE);
    lv_obj_set_pos(w[66], 123, 285);
    lv_obj_set_size(w[66], 42, 20);
    ui_style_font(w[66], 16);
    w[67] = lv_label_create(w[0]);
    if (!w[67]) { ui_objects_ok = false; return; }
    ui_style_apply(w[67], UI_STYLE_LABEL);
    lv_label_set_text(w[67], "23");
    lv_obj_set_pos(w[67], 372, 194);
    lv_obj_set_size(w[67], 23, 18);
    ui_style_font(w[67], 14);
    lv_obj_set_style_text_color(w[67], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[68] = lv_label_create(w[0]);
    if (!w[68]) { ui_objects_ok = false; return; }
    objects.cell_23_jk = w[68];
    ui_style_apply(w[68], UI_STYLE_LABEL);
    lv_label_set_text(w[68], "000");
    ui_style_apply(w[68], UI_STYLE_VALUE);
    lv_obj_set_pos(w[68], 397, 193);
    lv_obj_set_size(w[68], 50, 20);
    ui_style_font(w[68], 14);
    w[69] = lv_label_create(w[0]);
    if (!w[69]) { ui_objects_ok = false; return; }
    objects.cell_24_jk = w[69];
    ui_style_apply(w[69], UI_STYLE_LABEL);
    lv_label_set_text(w[69], "000");
    ui_style_apply(w[69], UI_STYLE_VALUE);
    lv_obj_set_pos(w[69], 397, 216);
    lv_obj_set_size(w[69], 50, 20);
    ui_style_font(w[69], 14);
    w[70] = lv_label_create(w[0]);
    if (!w[70]) { ui_objects_ok = false; return; }
    ui_style_apply(w[70], UI_STYLE_LABEL);
    lv_label_set_text(w[70], "24");
    lv_obj_set_pos(w[70], 372, 217);
    lv_obj_set_size(w[70], 23, 18);
    ui_style_font(w[70], 14);
    lv_obj_set_style_text_color(w[70], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[71] = lv_label_create(w[0]);
    if (!w[71]) { ui_objects_ok = false; return; }
    ui_style_apply(w[71], UI_STYLE_LABEL);
    lv_label_set_text(w[71], "CAP");
    lv_obj_set_pos(w[71], 22, 78);
    lv_obj_set_size(w[71], 56, 20);
    ui_style_font(w[71], 14);
    w[72] = lv_label_create(w[0]);
    if (!w[72]) { ui_objects_ok = false; return; }
    objects.cap_jk = w[72];
    ui_style_apply(w[72], UI_STYLE_LABEL);
    lv_label_set_text(w[72], "00");
    ui_style_apply(w[72], UI_STYLE_VALUE);
    lv_obj_set_pos(w[72], 81, 76);
    lv_obj_set_size(w[72], 68, 22);
    ui_style_font(w[72], 16);
    w[73] = lv_btn_create(w[0]);
    if (!w[73]) { ui_objects_ok = false; return; }
    objects.scan_pass_jk = w[73];
    ui_style_apply(w[73], UI_STYLE_BTN);
    lv_obj_add_event_cb(w[73], action_su_kien_tong, LV_EVENT_PRESSED, (void *)0);
    lv_obj_set_pos(w[73], 12, 214);
    lv_obj_set_size(w[73], 144, 28);
    w[74] = lv_label_create(w[73]);
    if (!w[74]) { ui_objects_ok = false; return; }
    ui_style_apply(w[74], UI_STYLE_LABEL);
    lv_obj_set_pos(w[74], 0, 0);
    lv_obj_set_size(w[74], LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_style_align(w[74], LV_ALIGN_CENTER, LV_PART_MAIN);
    lv_label_set_text(w[74], "Scan Pass");
    ui_style_font(w[74], 14);
    w[75] = lv_label_create(w[0]);
    if (!w[75]) { ui_objects_ok = false; return; }
    objects.text_pass_jk_1 = w[75];
    ui_style_apply(w[75], UI_STYLE_LABEL);
    lv_label_set_text(w[75], "0");
    lv_obj_set_pos(w[75], 84, 251);
    lv_obj_set_size(w[75], 28, 20);
    ui_style_font(w[75], 14);
    w[76] = lv_label_create(w[0]);
    if (!w[76]) { ui_objects_ok = false; return; }
    objects.text_mac_adress = w[76];
    ui_style_apply(w[76], UI_STYLE_LABEL);
    lv_label_set_long_mode(w[76], LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_label_set_text(w[76], "0");
    lv_obj_set_pos(w[76], 135, 16);
    lv_obj_set_size(w[76], 240, 22);
    ui_style_font(w[76], 14);
    lv_label_set_long_mode(w[76], LV_LABEL_LONG_SCROLL_CIRCULAR);
    w[77] = lv_label_create(w[0]);
    if (!w[77]) { ui_objects_ok = false; return; }
    objects.text_pass_jk_2 = w[77];
    ui_style_apply(w[77], UI_STYLE_LABEL);
    lv_label_set_text(w[77], "0");
    lv_obj_set_pos(w[77], 114, 251);
    lv_obj_set_size(w[77], 28, 20);
    ui_style_font(w[77], 14);
    w[78] = lv_label_create(w[0]);
    if (!w[78]) { ui_objects_ok = false; return; }
    objects.text_pass_jk_3 = w[78];
    ui_style_apply(w[78], UI_STYLE_LABEL);
    lv_label_set_text(w[78], "0");
    lv_obj_set_pos(w[78], 144, 251);
    lv_obj_set_size(w[78], 28, 20);
    ui_style_font(w[78], 14);
    w[79] = lv_label_create(w[0]);
    if (!w[79]) { ui_objects_ok = false; return; }
    objects.text_pass_jk_4 = w[79];
    ui_style_apply(w[79], UI_STYLE_LABEL);
    lv_label_set_text(w[79], "0");
    lv_obj_set_pos(w[79], 174, 251);
    lv_obj_set_size(w[79], 28, 20);
    ui_style_font(w[79], 14);
    w[80] = lv_label_create(w[0]);
    if (!w[80]) { ui_objects_ok = false; return; }
    objects.text_pass_jk_5 = w[80];
    ui_style_apply(w[80], UI_STYLE_LABEL);
    lv_label_set_text(w[80], "0");
    lv_obj_set_pos(w[80], 204, 251);
    lv_obj_set_size(w[80], 28, 20);
    ui_style_font(w[80], 14);
    w[81] = lv_label_create(w[0]);
    if (!w[81]) { ui_objects_ok = false; return; }
    objects.text_pass_jk_6 = w[81];
    ui_style_apply(w[81], UI_STYLE_LABEL);
    lv_label_set_text(w[81], "0");
    lv_obj_set_pos(w[81], 234, 251);
    lv_obj_set_size(w[81], 28, 20);
    ui_style_font(w[81], 14);
    w[82] = lv_label_create(w[0]);
    if (!w[82]) { ui_objects_ok = false; return; }
    objects.text_pass_jk_7 = w[82];
    ui_style_apply(w[82], UI_STYLE_LABEL);
    lv_label_set_text(w[82], "0");
    lv_obj_set_pos(w[82], 264, 251);
    lv_obj_set_size(w[82], 28, 20);
    ui_style_font(w[82], 14);
    w[83] = lv_label_create(w[0]);
    if (!w[83]) { ui_objects_ok = false; return; }
    objects.text_pass_jk_8 = w[83];
    ui_style_apply(w[83], UI_STYLE_LABEL);
    lv_label_set_text(w[83], "0");
    lv_obj_set_pos(w[83], 294, 251);
    lv_obj_set_size(w[83], 28, 20);
    ui_style_font(w[83], 14);
    w[84] = lv_label_create(w[0]);
    if (!w[84]) { ui_objects_ok = false; return; }
    objects.text_pass_jk_9 = w[84];
    ui_style_apply(w[84], UI_STYLE_LABEL);
    lv_label_set_text(w[84], "0");
    lv_obj_set_pos(w[84], 324, 251);
    lv_obj_set_size(w[84], 28, 20);
    ui_style_font(w[84], 14);
    w[85] = lv_label_create(w[0]);
    if (!w[85]) { ui_objects_ok = false; return; }
    objects.text_pass_jk_10 = w[85];
    ui_style_apply(w[85], UI_STYLE_LABEL);
    lv_label_set_text(w[85], "0");
    lv_obj_set_pos(w[85], 354, 251);
    lv_obj_set_size(w[85], 28, 20);
    ui_style_font(w[85], 14);
    w[86] = lv_label_create(w[0]);
    if (!w[86]) { ui_objects_ok = false; return; }
    objects.text_pass_jk_11 = w[86];
    ui_style_apply(w[86], UI_STYLE_LABEL);
    lv_label_set_text(w[86], "0");
    lv_obj_set_pos(w[86], 384, 251);
    lv_obj_set_size(w[86], 28, 20);
    ui_style_font(w[86], 14);
    w[87] = lv_label_create(w[0]);
    if (!w[87]) { ui_objects_ok = false; return; }
    objects.text_pass_jk_12 = w[87];
    ui_style_apply(w[87], UI_STYLE_LABEL);
    lv_label_set_text(w[87], "0");
    lv_obj_set_pos(w[87], 414, 251);
    lv_obj_set_size(w[87], 28, 20);
    ui_style_font(w[87], 14);
}
void tick_screen_bms_jk(void) {}
void create_screen_pin_1k2_main(void) {
    lv_obj_t *w[69];
    w[0] = lv_obj_create(0);
    if (!w[0]) { ui_objects_ok = false; return; }
    objects.pin_1k2_main = w[0];
    ui_style_apply(w[0], UI_STYLE_SCREEN);
    lv_obj_set_pos(w[0], 0, 0);
    lv_obj_set_size(w[0], 480, 320);
    w[1] = lv_btn_create(w[0]);
    if (!w[1]) { ui_objects_ok = false; return; }
    objects.nut_back_1k2 = w[1];
    ui_style_apply(w[1], UI_STYLE_BTN);
    lv_obj_add_event_cb(w[1], action_su_kien_tong, LV_EVENT_PRESSED, (void *)0);
    lv_obj_set_pos(w[1], 388, 8);
    lv_obj_set_size(w[1], 76, 32);
    w[2] = lv_label_create(w[1]);
    if (!w[2]) { ui_objects_ok = false; return; }
    ui_style_apply(w[2], UI_STYLE_LABEL);
    lv_obj_set_pos(w[2], 0, 0);
    lv_obj_set_size(w[2], LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_style_align(w[2], LV_ALIGN_CENTER, LV_PART_MAIN);
    lv_label_set_text(w[2], "BACK");
    ui_style_font(w[2], 16);
    w[3] = lv_label_create(w[0]);
    if (!w[3]) { ui_objects_ok = false; return; }
    ui_style_apply(w[3], UI_STYLE_LABEL);
    lv_label_set_text(w[3], "SOC");
    lv_obj_set_pos(w[3], 22, 58);
    lv_obj_set_size(w[3], 56, 20);
    ui_style_font(w[3], 14);
    w[4] = lv_label_create(w[0]);
    if (!w[4]) { ui_objects_ok = false; return; }
    ui_style_apply(w[4], UI_STYLE_LABEL);
    lv_label_set_text(w[4], "Cycle");
    lv_obj_set_pos(w[4], 22, 79);
    lv_obj_set_size(w[4], 56, 20);
    ui_style_font(w[4], 14);
    w[5] = lv_label_create(w[0]);
    if (!w[5]) { ui_objects_ok = false; return; }
    ui_style_apply(w[5], UI_STYLE_LABEL);
    lv_label_set_text(w[5], "Delvol");
    lv_obj_set_pos(w[5], 22, 100);
    lv_obj_set_size(w[5], 56, 20);
    ui_style_font(w[5], 14);
    w[6] = lv_label_create(w[0]);
    if (!w[6]) { ui_objects_ok = false; return; }
    ui_style_apply(w[6], UI_STYLE_LABEL);
    lv_label_set_text(w[6], "Vmax");
    lv_obj_set_pos(w[6], 22, 121);
    lv_obj_set_size(w[6], 56, 20);
    ui_style_font(w[6], 14);
    w[7] = lv_label_create(w[0]);
    if (!w[7]) { ui_objects_ok = false; return; }
    ui_style_apply(w[7], UI_STYLE_LABEL);
    lv_label_set_text(w[7], "Vmin");
    lv_obj_set_pos(w[7], 22, 142);
    lv_obj_set_size(w[7], 56, 20);
    ui_style_font(w[7], 14);
    w[8] = lv_label_create(w[0]);
    if (!w[8]) { ui_objects_ok = false; return; }
    ui_style_apply(w[8], UI_STYLE_LABEL);
    lv_label_set_text(w[8], "RCAP");
    lv_obj_set_pos(w[8], 22, 163);
    lv_obj_set_size(w[8], 56, 20);
    ui_style_font(w[8], 14);
    w[9] = lv_label_create(w[0]);
    if (!w[9]) { ui_objects_ok = false; return; }
    ui_style_apply(w[9], UI_STYLE_LABEL);
    lv_label_set_text(w[9], "SOH");
    lv_obj_set_pos(w[9], 22, 184);
    lv_obj_set_size(w[9], 56, 20);
    ui_style_font(w[9], 14);
    w[10] = lv_label_create(w[0]);
    if (!w[10]) { ui_objects_ok = false; return; }
    objects.soc_1k2 = w[10];
    ui_style_apply(w[10], UI_STYLE_LABEL);
    lv_label_set_text(w[10], "00");
    ui_style_apply(w[10], UI_STYLE_VALUE);
    lv_obj_set_pos(w[10], 81, 56);
    lv_obj_set_size(w[10], 68, 22);
    ui_style_font(w[10], 16);
    w[11] = lv_label_create(w[0]);
    if (!w[11]) { ui_objects_ok = false; return; }
    objects.cycle_1k2 = w[11];
    ui_style_apply(w[11], UI_STYLE_LABEL);
    lv_label_set_text(w[11], "00");
    ui_style_apply(w[11], UI_STYLE_VALUE);
    lv_obj_set_pos(w[11], 81, 77);
    lv_obj_set_size(w[11], 68, 22);
    ui_style_font(w[11], 16);
    w[12] = lv_label_create(w[0]);
    if (!w[12]) { ui_objects_ok = false; return; }
    objects.del_vol_1k2 = w[12];
    ui_style_apply(w[12], UI_STYLE_LABEL);
    lv_label_set_text(w[12], "00");
    ui_style_apply(w[12], UI_STYLE_VALUE);
    lv_obj_set_pos(w[12], 81, 98);
    lv_obj_set_size(w[12], 68, 22);
    ui_style_font(w[12], 16);
    w[13] = lv_label_create(w[0]);
    if (!w[13]) { ui_objects_ok = false; return; }
    objects.v_max_lfp_1k2 = w[13];
    ui_style_apply(w[13], UI_STYLE_LABEL);
    lv_label_set_text(w[13], "00");
    ui_style_apply(w[13], UI_STYLE_VALUE);
    lv_obj_set_pos(w[13], 81, 119);
    lv_obj_set_size(w[13], 68, 22);
    ui_style_font(w[13], 16);
    w[14] = lv_label_create(w[0]);
    if (!w[14]) { ui_objects_ok = false; return; }
    objects.v_min_lfp_1k2 = w[14];
    ui_style_apply(w[14], UI_STYLE_LABEL);
    lv_label_set_text(w[14], "00");
    ui_style_apply(w[14], UI_STYLE_VALUE);
    lv_obj_set_pos(w[14], 81, 140);
    lv_obj_set_size(w[14], 68, 22);
    ui_style_font(w[14], 16);
    w[15] = lv_label_create(w[0]);
    if (!w[15]) { ui_objects_ok = false; return; }
    objects.soh_lfp_1k2 = w[15];
    ui_style_apply(w[15], UI_STYLE_LABEL);
    lv_label_set_text(w[15], "00");
    ui_style_apply(w[15], UI_STYLE_VALUE);
    lv_obj_set_pos(w[15], 81, 182);
    lv_obj_set_size(w[15], 68, 22);
    ui_style_font(w[15], 16);
    w[16] = lv_label_create(w[0]);
    if (!w[16]) { ui_objects_ok = false; return; }
    objects.rcap_lfp_1k2 = w[16];
    ui_style_apply(w[16], UI_STYLE_LABEL);
    lv_label_set_text(w[16], "00");
    ui_style_apply(w[16], UI_STYLE_VALUE);
    lv_obj_set_pos(w[16], 81, 161);
    lv_obj_set_size(w[16], 68, 22);
    ui_style_font(w[16], 16);
    w[17] = lv_label_create(w[0]);
    if (!w[17]) { ui_objects_ok = false; return; }
    objects.avg_lfp_1k2 = w[17];
    ui_style_apply(w[17], UI_STYLE_LABEL);
    lv_label_set_text(w[17], "00");
    ui_style_apply(w[17], UI_STYLE_VALUE);
    lv_obj_set_pos(w[17], 81, 203);
    lv_obj_set_size(w[17], 68, 22);
    ui_style_font(w[17], 16);
    w[18] = lv_label_create(w[0]);
    if (!w[18]) { ui_objects_ok = false; return; }
    ui_style_apply(w[18], UI_STYLE_LABEL);
    lv_label_set_text(w[18], "08");
    lv_obj_set_pos(w[18], 274, 56);
    lv_obj_set_size(w[18], 23, 18);
    ui_style_font(w[18], 14);
    lv_obj_set_style_text_color(w[18], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[19] = lv_label_create(w[0]);
    if (!w[19]) { ui_objects_ok = false; return; }
    ui_style_apply(w[19], UI_STYLE_LABEL);
    lv_label_set_text(w[19], "09");
    lv_obj_set_pos(w[19], 274, 77);
    lv_obj_set_size(w[19], 23, 18);
    ui_style_font(w[19], 14);
    lv_obj_set_style_text_color(w[19], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[20] = lv_label_create(w[0]);
    if (!w[20]) { ui_objects_ok = false; return; }
    ui_style_apply(w[20], UI_STYLE_LABEL);
    lv_label_set_text(w[20], "10");
    lv_obj_set_pos(w[20], 274, 98);
    lv_obj_set_size(w[20], 23, 18);
    ui_style_font(w[20], 14);
    lv_obj_set_style_text_color(w[20], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[21] = lv_label_create(w[0]);
    if (!w[21]) { ui_objects_ok = false; return; }
    ui_style_apply(w[21], UI_STYLE_LABEL);
    lv_label_set_text(w[21], "11");
    lv_obj_set_pos(w[21], 274, 119);
    lv_obj_set_size(w[21], 23, 18);
    ui_style_font(w[21], 14);
    lv_obj_set_style_text_color(w[21], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[22] = lv_label_create(w[0]);
    if (!w[22]) { ui_objects_ok = false; return; }
    ui_style_apply(w[22], UI_STYLE_LABEL);
    lv_label_set_text(w[22], "12");
    lv_obj_set_pos(w[22], 274, 140);
    lv_obj_set_size(w[22], 23, 18);
    ui_style_font(w[22], 14);
    lv_obj_set_style_text_color(w[22], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[23] = lv_label_create(w[0]);
    if (!w[23]) { ui_objects_ok = false; return; }
    ui_style_apply(w[23], UI_STYLE_LABEL);
    lv_label_set_text(w[23], "13");
    lv_obj_set_pos(w[23], 274, 161);
    lv_obj_set_size(w[23], 23, 18);
    ui_style_font(w[23], 14);
    lv_obj_set_style_text_color(w[23], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[24] = lv_label_create(w[0]);
    if (!w[24]) { ui_objects_ok = false; return; }
    ui_style_apply(w[24], UI_STYLE_LABEL);
    lv_label_set_text(w[24], "14");
    lv_obj_set_pos(w[24], 274, 182);
    lv_obj_set_size(w[24], 23, 18);
    ui_style_font(w[24], 14);
    lv_obj_set_style_text_color(w[24], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[25] = lv_label_create(w[0]);
    if (!w[25]) { ui_objects_ok = false; return; }
    ui_style_apply(w[25], UI_STYLE_LABEL);
    lv_label_set_text(w[25], "15");
    lv_obj_set_pos(w[25], 372, 56);
    lv_obj_set_size(w[25], 23, 18);
    ui_style_font(w[25], 14);
    lv_obj_set_style_text_color(w[25], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[26] = lv_label_create(w[0]);
    if (!w[26]) { ui_objects_ok = false; return; }
    ui_style_apply(w[26], UI_STYLE_LABEL);
    lv_label_set_text(w[26], "16");
    lv_obj_set_pos(w[26], 372, 77);
    lv_obj_set_size(w[26], 23, 18);
    ui_style_font(w[26], 14);
    lv_obj_set_style_text_color(w[26], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[27] = lv_label_create(w[0]);
    if (!w[27]) { ui_objects_ok = false; return; }
    objects.cell_8_1k2 = w[27];
    ui_style_apply(w[27], UI_STYLE_LABEL);
    lv_label_set_text(w[27], "000");
    ui_style_apply(w[27], UI_STYLE_VALUE);
    lv_obj_set_pos(w[27], 299, 55);
    lv_obj_set_size(w[27], 50, 20);
    ui_style_font(w[27], 14);
    w[28] = lv_label_create(w[0]);
    if (!w[28]) { ui_objects_ok = false; return; }
    objects.cell_9_1k2 = w[28];
    ui_style_apply(w[28], UI_STYLE_LABEL);
    lv_label_set_text(w[28], "000");
    ui_style_apply(w[28], UI_STYLE_VALUE);
    lv_obj_set_pos(w[28], 299, 76);
    lv_obj_set_size(w[28], 50, 20);
    ui_style_font(w[28], 14);
    w[29] = lv_label_create(w[0]);
    if (!w[29]) { ui_objects_ok = false; return; }
    objects.cell_10_1k2 = w[29];
    ui_style_apply(w[29], UI_STYLE_LABEL);
    lv_label_set_text(w[29], "000");
    ui_style_apply(w[29], UI_STYLE_VALUE);
    lv_obj_set_pos(w[29], 299, 97);
    lv_obj_set_size(w[29], 50, 20);
    ui_style_font(w[29], 14);
    w[30] = lv_label_create(w[0]);
    if (!w[30]) { ui_objects_ok = false; return; }
    objects.cell_11_1k2 = w[30];
    ui_style_apply(w[30], UI_STYLE_LABEL);
    lv_label_set_text(w[30], "000");
    ui_style_apply(w[30], UI_STYLE_VALUE);
    lv_obj_set_pos(w[30], 299, 118);
    lv_obj_set_size(w[30], 50, 20);
    ui_style_font(w[30], 14);
    w[31] = lv_label_create(w[0]);
    if (!w[31]) { ui_objects_ok = false; return; }
    objects.cell_12_1k2 = w[31];
    ui_style_apply(w[31], UI_STYLE_LABEL);
    lv_label_set_text(w[31], "000");
    ui_style_apply(w[31], UI_STYLE_VALUE);
    lv_obj_set_pos(w[31], 299, 139);
    lv_obj_set_size(w[31], 50, 20);
    ui_style_font(w[31], 14);
    w[32] = lv_label_create(w[0]);
    if (!w[32]) { ui_objects_ok = false; return; }
    objects.cell_13_1k2 = w[32];
    ui_style_apply(w[32], UI_STYLE_LABEL);
    lv_label_set_text(w[32], "000");
    ui_style_apply(w[32], UI_STYLE_VALUE);
    lv_obj_set_pos(w[32], 299, 160);
    lv_obj_set_size(w[32], 50, 20);
    ui_style_font(w[32], 14);
    w[33] = lv_label_create(w[0]);
    if (!w[33]) { ui_objects_ok = false; return; }
    objects.cell_14_1k2 = w[33];
    ui_style_apply(w[33], UI_STYLE_LABEL);
    lv_label_set_text(w[33], "000");
    ui_style_apply(w[33], UI_STYLE_VALUE);
    lv_obj_set_pos(w[33], 299, 181);
    lv_obj_set_size(w[33], 50, 20);
    ui_style_font(w[33], 14);
    w[34] = lv_label_create(w[0]);
    if (!w[34]) { ui_objects_ok = false; return; }
    ui_style_apply(w[34], UI_STYLE_LABEL);
    lv_label_set_text(w[34], "17");
    lv_obj_set_pos(w[34], 372, 98);
    lv_obj_set_size(w[34], 23, 18);
    ui_style_font(w[34], 14);
    lv_obj_set_style_text_color(w[34], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[35] = lv_label_create(w[0]);
    if (!w[35]) { ui_objects_ok = false; return; }
    ui_style_apply(w[35], UI_STYLE_LABEL);
    lv_label_set_text(w[35], "18");
    lv_obj_set_pos(w[35], 372, 119);
    lv_obj_set_size(w[35], 23, 18);
    ui_style_font(w[35], 14);
    lv_obj_set_style_text_color(w[35], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[36] = lv_label_create(w[0]);
    if (!w[36]) { ui_objects_ok = false; return; }
    ui_style_apply(w[36], UI_STYLE_LABEL);
    lv_label_set_text(w[36], "19");
    lv_obj_set_pos(w[36], 372, 140);
    lv_obj_set_size(w[36], 23, 18);
    ui_style_font(w[36], 14);
    lv_obj_set_style_text_color(w[36], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[37] = lv_label_create(w[0]);
    if (!w[37]) { ui_objects_ok = false; return; }
    objects.cell_15_1k2 = w[37];
    ui_style_apply(w[37], UI_STYLE_LABEL);
    lv_label_set_text(w[37], "000");
    ui_style_apply(w[37], UI_STYLE_VALUE);
    lv_obj_set_pos(w[37], 397, 55);
    lv_obj_set_size(w[37], 50, 20);
    ui_style_font(w[37], 14);
    w[38] = lv_label_create(w[0]);
    if (!w[38]) { ui_objects_ok = false; return; }
    objects.cell_16_1k2 = w[38];
    ui_style_apply(w[38], UI_STYLE_LABEL);
    lv_label_set_text(w[38], "000");
    ui_style_apply(w[38], UI_STYLE_VALUE);
    lv_obj_set_pos(w[38], 397, 76);
    lv_obj_set_size(w[38], 50, 20);
    ui_style_font(w[38], 14);
    w[39] = lv_label_create(w[0]);
    if (!w[39]) { ui_objects_ok = false; return; }
    objects.cell_17_1k2 = w[39];
    ui_style_apply(w[39], UI_STYLE_LABEL);
    lv_label_set_text(w[39], "000");
    ui_style_apply(w[39], UI_STYLE_VALUE);
    lv_obj_set_pos(w[39], 397, 97);
    lv_obj_set_size(w[39], 50, 20);
    ui_style_font(w[39], 14);
    w[40] = lv_label_create(w[0]);
    if (!w[40]) { ui_objects_ok = false; return; }
    objects.cell_18_1k2 = w[40];
    ui_style_apply(w[40], UI_STYLE_LABEL);
    lv_label_set_text(w[40], "000");
    ui_style_apply(w[40], UI_STYLE_VALUE);
    lv_obj_set_pos(w[40], 397, 118);
    lv_obj_set_size(w[40], 50, 20);
    ui_style_font(w[40], 14);
    w[41] = lv_label_create(w[0]);
    if (!w[41]) { ui_objects_ok = false; return; }
    objects.cell_19_1k2 = w[41];
    ui_style_apply(w[41], UI_STYLE_LABEL);
    lv_label_set_text(w[41], "000");
    ui_style_apply(w[41], UI_STYLE_VALUE);
    lv_obj_set_pos(w[41], 397, 139);
    lv_obj_set_size(w[41], 50, 20);
    ui_style_font(w[41], 14);
    w[42] = lv_label_create(w[0]);
    if (!w[42]) { ui_objects_ok = false; return; }
    ui_style_apply(w[42], UI_STYLE_LABEL);
    lv_label_set_text(w[42], "01");
    lv_obj_set_pos(w[42], 176, 56);
    lv_obj_set_size(w[42], 23, 18);
    ui_style_font(w[42], 14);
    lv_obj_set_style_text_color(w[42], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[43] = lv_label_create(w[0]);
    if (!w[43]) { ui_objects_ok = false; return; }
    ui_style_apply(w[43], UI_STYLE_LABEL);
    lv_label_set_text(w[43], "02");
    lv_obj_set_pos(w[43], 176, 77);
    lv_obj_set_size(w[43], 23, 18);
    ui_style_font(w[43], 14);
    lv_obj_set_style_text_color(w[43], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[44] = lv_label_create(w[0]);
    if (!w[44]) { ui_objects_ok = false; return; }
    ui_style_apply(w[44], UI_STYLE_LABEL);
    lv_label_set_text(w[44], "03");
    lv_obj_set_pos(w[44], 176, 98);
    lv_obj_set_size(w[44], 23, 18);
    ui_style_font(w[44], 14);
    lv_obj_set_style_text_color(w[44], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[45] = lv_label_create(w[0]);
    if (!w[45]) { ui_objects_ok = false; return; }
    ui_style_apply(w[45], UI_STYLE_LABEL);
    lv_label_set_text(w[45], "04");
    lv_obj_set_pos(w[45], 176, 119);
    lv_obj_set_size(w[45], 23, 18);
    ui_style_font(w[45], 14);
    lv_obj_set_style_text_color(w[45], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[46] = lv_label_create(w[0]);
    if (!w[46]) { ui_objects_ok = false; return; }
    ui_style_apply(w[46], UI_STYLE_LABEL);
    lv_label_set_text(w[46], "05");
    lv_obj_set_pos(w[46], 176, 140);
    lv_obj_set_size(w[46], 23, 18);
    ui_style_font(w[46], 14);
    lv_obj_set_style_text_color(w[46], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[47] = lv_label_create(w[0]);
    if (!w[47]) { ui_objects_ok = false; return; }
    ui_style_apply(w[47], UI_STYLE_LABEL);
    lv_label_set_text(w[47], "06");
    lv_obj_set_pos(w[47], 176, 161);
    lv_obj_set_size(w[47], 23, 18);
    ui_style_font(w[47], 14);
    lv_obj_set_style_text_color(w[47], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[48] = lv_label_create(w[0]);
    if (!w[48]) { ui_objects_ok = false; return; }
    ui_style_apply(w[48], UI_STYLE_LABEL);
    lv_label_set_text(w[48], "07");
    lv_obj_set_pos(w[48], 176, 182);
    lv_obj_set_size(w[48], 23, 18);
    ui_style_font(w[48], 14);
    lv_obj_set_style_text_color(w[48], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[49] = lv_label_create(w[0]);
    if (!w[49]) { ui_objects_ok = false; return; }
    objects.cell_1_1k2 = w[49];
    ui_style_apply(w[49], UI_STYLE_LABEL);
    lv_label_set_text(w[49], "000");
    ui_style_apply(w[49], UI_STYLE_VALUE);
    lv_obj_set_pos(w[49], 201, 55);
    lv_obj_set_size(w[49], 50, 20);
    ui_style_font(w[49], 14);
    w[50] = lv_label_create(w[0]);
    if (!w[50]) { ui_objects_ok = false; return; }
    objects.cell_2_1k2 = w[50];
    ui_style_apply(w[50], UI_STYLE_LABEL);
    lv_label_set_text(w[50], "000");
    ui_style_apply(w[50], UI_STYLE_VALUE);
    lv_obj_set_pos(w[50], 201, 76);
    lv_obj_set_size(w[50], 50, 20);
    ui_style_font(w[50], 14);
    w[51] = lv_label_create(w[0]);
    if (!w[51]) { ui_objects_ok = false; return; }
    objects.cell_3_1k2 = w[51];
    ui_style_apply(w[51], UI_STYLE_LABEL);
    lv_label_set_text(w[51], "000");
    ui_style_apply(w[51], UI_STYLE_VALUE);
    lv_obj_set_pos(w[51], 201, 97);
    lv_obj_set_size(w[51], 50, 20);
    ui_style_font(w[51], 14);
    w[52] = lv_label_create(w[0]);
    if (!w[52]) { ui_objects_ok = false; return; }
    objects.cell_4_1k2 = w[52];
    ui_style_apply(w[52], UI_STYLE_LABEL);
    lv_label_set_text(w[52], "000");
    ui_style_apply(w[52], UI_STYLE_VALUE);
    lv_obj_set_pos(w[52], 201, 118);
    lv_obj_set_size(w[52], 50, 20);
    ui_style_font(w[52], 14);
    w[53] = lv_label_create(w[0]);
    if (!w[53]) { ui_objects_ok = false; return; }
    objects.cell_5_1k2 = w[53];
    ui_style_apply(w[53], UI_STYLE_LABEL);
    lv_label_set_text(w[53], "000");
    ui_style_apply(w[53], UI_STYLE_VALUE);
    lv_obj_set_pos(w[53], 201, 139);
    lv_obj_set_size(w[53], 50, 20);
    ui_style_font(w[53], 14);
    w[54] = lv_label_create(w[0]);
    if (!w[54]) { ui_objects_ok = false; return; }
    objects.cell_6_1k2 = w[54];
    ui_style_apply(w[54], UI_STYLE_LABEL);
    lv_label_set_text(w[54], "000");
    ui_style_apply(w[54], UI_STYLE_VALUE);
    lv_obj_set_pos(w[54], 201, 160);
    lv_obj_set_size(w[54], 50, 20);
    ui_style_font(w[54], 14);
    w[55] = lv_label_create(w[0]);
    if (!w[55]) { ui_objects_ok = false; return; }
    objects.cell_7_1k2 = w[55];
    ui_style_apply(w[55], UI_STYLE_LABEL);
    lv_label_set_text(w[55], "000");
    ui_style_apply(w[55], UI_STYLE_VALUE);
    lv_obj_set_pos(w[55], 201, 181);
    lv_obj_set_size(w[55], 50, 20);
    ui_style_font(w[55], 14);
    w[56] = lv_label_create(w[0]);
    if (!w[56]) { ui_objects_ok = false; return; }
    ui_style_apply(w[56], UI_STYLE_LABEL);
    lv_label_set_text(w[56], "T_3:");
    lv_obj_set_pos(w[56], 318, 243);
    lv_obj_set_size(w[56], 39, 18);
    ui_style_font(w[56], 14);
    w[57] = lv_label_create(w[0]);
    if (!w[57]) { ui_objects_ok = false; return; }
    ui_style_apply(w[57], UI_STYLE_LABEL);
    lv_label_set_text(w[57], "AVG");
    lv_obj_set_pos(w[57], 22, 205);
    lv_obj_set_size(w[57], 56, 20);
    ui_style_font(w[57], 14);
    w[58] = lv_label_create(w[0]);
    if (!w[58]) { ui_objects_ok = false; return; }
    objects.t_3_1k2 = w[58];
    ui_style_apply(w[58], UI_STYLE_LABEL);
    lv_label_set_text(w[58], "00");
    ui_style_apply(w[58], UI_STYLE_VALUE);
    lv_obj_set_pos(w[58], 356, 242);
    lv_obj_set_size(w[58], 33, 20);
    ui_style_font(w[58], 14);
    w[59] = lv_label_create(w[0]);
    if (!w[59]) { ui_objects_ok = false; return; }
    objects.text_vol_1k2 = w[59];
    ui_style_apply(w[59], UI_STYLE_LABEL);
    lv_label_set_text(w[59], "00");
    ui_style_apply(w[59], UI_STYLE_VALUE);
    lv_obj_set_pos(w[59], 114, 279);
    lv_obj_set_size(w[59], 112, 28);
    ui_style_font(w[59], 22);
    w[60] = lv_label_create(w[0]);
    if (!w[60]) { ui_objects_ok = false; return; }
    objects.ampe_lfp_1k2 = w[60];
    ui_style_apply(w[60], UI_STYLE_LABEL);
    lv_label_set_text(w[60], "00");
    ui_style_apply(w[60], UI_STYLE_VALUE);
    lv_obj_set_pos(w[60], 348, 279);
    lv_obj_set_size(w[60], 112, 28);
    ui_style_font(w[60], 22);
    w[61] = lv_label_create(w[0]);
    if (!w[61]) { ui_objects_ok = false; return; }
    ui_style_apply(w[61], UI_STYLE_LABEL);
    lv_label_set_text(w[61], "T_1:");
    lv_obj_set_pos(w[61], 20, 243);
    lv_obj_set_size(w[61], 39, 18);
    ui_style_font(w[61], 14);
    w[62] = lv_label_create(w[0]);
    if (!w[62]) { ui_objects_ok = false; return; }
    ui_style_apply(w[62], UI_STYLE_LABEL);
    lv_label_set_text(w[62], "T_2:");
    lv_obj_set_pos(w[62], 169, 243);
    lv_obj_set_size(w[62], 39, 18);
    ui_style_font(w[62], 14);
    w[63] = lv_label_create(w[0]);
    if (!w[63]) { ui_objects_ok = false; return; }
    objects.t_1_1k2 = w[63];
    ui_style_apply(w[63], UI_STYLE_LABEL);
    lv_label_set_text(w[63], "00");
    ui_style_apply(w[63], UI_STYLE_VALUE);
    lv_obj_set_pos(w[63], 58, 242);
    lv_obj_set_size(w[63], 33, 20);
    ui_style_font(w[63], 14);
    w[64] = lv_label_create(w[0]);
    if (!w[64]) { ui_objects_ok = false; return; }
    objects.t_2_1k2 = w[64];
    ui_style_apply(w[64], UI_STYLE_LABEL);
    lv_label_set_text(w[64], "00");
    ui_style_apply(w[64], UI_STYLE_VALUE);
    lv_obj_set_pos(w[64], 207, 242);
    lv_obj_set_size(w[64], 33, 20);
    ui_style_font(w[64], 14);
    w[65] = lv_label_create(w[0]);
    if (!w[65]) { ui_objects_ok = false; return; }
    ui_style_apply(w[65], UI_STYLE_LABEL);
    lv_label_set_text(w[65], "%");
    lv_obj_set_pos(w[65], 133, 58);
    lv_obj_set_size(w[65], 16, 20);
    ui_style_font(w[65], 14);
    w[66] = lv_label_create(w[0]);
    if (!w[66]) { ui_objects_ok = false; return; }
    ui_style_apply(w[66], UI_STYLE_LABEL);
    lv_label_set_text(w[66], "20");
    lv_obj_set_pos(w[66], 372, 161);
    lv_obj_set_size(w[66], 23, 18);
    ui_style_font(w[66], 14);
    lv_obj_set_style_text_color(w[66], lv_color_hex(0x7F99B4), LV_PART_MAIN);
    w[67] = lv_label_create(w[0]);
    if (!w[67]) { ui_objects_ok = false; return; }
    objects.cell_20_1k2 = w[67];
    ui_style_apply(w[67], UI_STYLE_LABEL);
    lv_label_set_text(w[67], "000");
    ui_style_apply(w[67], UI_STYLE_VALUE);
    lv_obj_set_pos(w[67], 397, 160);
    lv_obj_set_size(w[67], 50, 20);
    ui_style_font(w[67], 14);
    w[68] = lv_label_create(w[0]);
    if (!w[68]) { ui_objects_ok = false; return; }
    ui_style_apply(w[68], UI_STYLE_LABEL);
    lv_label_set_long_mode(w[68], LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_label_set_text(w[68], "LFP 1.2 kW");
    ui_style_apply(w[68], UI_STYLE_VALUE);
    lv_obj_set_pos(w[68], 16, 10);
    lv_obj_set_size(w[68], 350, 28);
    ui_style_font(w[68], 22);
}
void tick_screen_pin_1k2_main(void) {}
void create_screen_screen_can_scanner(void) {
    lv_obj_t *w[6];
    w[0] = lv_obj_create(0);
    if (!w[0]) { ui_objects_ok = false; return; }
    objects.screen_can_scanner = w[0];
    ui_style_apply(w[0], UI_STYLE_SCREEN);
    lv_obj_set_pos(w[0], 0, 0);
    lv_obj_set_size(w[0], 480, 320);
    w[1] = lv_btn_create(w[0]);
    if (!w[1]) { ui_objects_ok = false; return; }
    objects.back_home_1 = w[1];
    ui_style_apply(w[1], UI_STYLE_BTN);
    lv_obj_set_pos(w[1], 4, 264);
    lv_obj_set_size(w[1], 88, 48);
    lv_obj_add_event_cb(w[1], action_su_kien_tong, LV_EVENT_PRESSED, (void *)0);
    w[2] = lv_label_create(w[0]);
    if (!w[2]) { ui_objects_ok = false; return; }
    ui_style_apply(w[2], UI_STYLE_LABEL);
    lv_obj_set_pos(w[2], 8, 278);
    lv_obj_set_size(w[2], 80, 22);
    lv_label_set_text(w[2], "Back");
    ui_style_font(w[2], 16);
    ui_style_apply(w[2], UI_STYLE_CENTER);
    w[3] = lv_btn_create(w[0]);
    if (!w[3]) { ui_objects_ok = false; return; }
    objects.back_home_2 = w[3];
    ui_style_apply(w[3], UI_STYLE_BTN);
    lv_obj_set_pos(w[3], 4, 200);
    lv_obj_set_size(w[3], 88, 56);
    lv_obj_add_event_cb(w[3], action_su_kien_tong, LV_EVENT_PRESSED, (void *)0);
    w[4] = lv_label_create(w[0]);
    if (!w[4]) { ui_objects_ok = false; return; }
    ui_style_apply(w[4], UI_STYLE_LABEL);
    lv_obj_set_pos(w[4], 8, 204);
    lv_obj_set_size(w[4], 80, 22);
    lv_label_set_text(w[4], "Total");
    ui_style_font(w[4], 16);
    ui_style_apply(w[4], UI_STYLE_CENTER);
    w[5] = lv_label_create(w[0]);
    if (!w[5]) { ui_objects_ok = false; return; }
    objects.total_id_can_read = w[5];
    ui_style_apply(w[5], UI_STYLE_LABEL);
    lv_obj_set_pos(w[5], 8, 230);
    lv_obj_set_size(w[5], 80, 22);
    lv_label_set_text(w[5], "0");
    ui_style_font(w[5], 18);
    ui_style_apply(w[5], UI_STYLE_CENTER);
    lv_obj_clear_flag(w[0], LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_add_event_cb(w[0], can_scanner_draw_event, LV_EVENT_DRAW_MAIN, NULL);
}
void tick_screen_screen_can_scanner(void) {}
void create_screen_test_tool(void) {
    lv_obj_t *w[27];
    w[0] = lv_obj_create(0);
    if (!w[0]) { ui_objects_ok = false; return; }
    objects.test_tool = w[0];
    ui_style_apply(w[0], UI_STYLE_SCREEN);
    lv_obj_set_pos(w[0], 0, 0);
    lv_obj_set_size(w[0], 480, 320);
    w[1] = lv_btn_create(w[0]);
    if (!w[1]) { ui_objects_ok = false; return; }
    objects.btn_signal_left = w[1];
    ui_style_apply(w[1], UI_STYLE_BTN);
    lv_obj_set_pos(w[1], 17, 10);
    lv_obj_set_size(w[1], 76, 40);
    lv_obj_add_event_cb(w[1], action_su_kien_tong, LV_EVENT_PRESSED, (void *)0);
    w[2] = lv_label_create(w[1]);
    if (!w[2]) { ui_objects_ok = false; return; }
    ui_style_apply(w[2], UI_STYLE_LABEL);
    lv_obj_set_pos(w[2], 0, 0);
    lv_obj_set_size(w[2], LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_style_align(w[2], LV_ALIGN_CENTER, LV_PART_MAIN);
    lv_label_set_recolor(w[2], true);
    lv_label_set_text(w[2], "<");
    ui_style_font(w[2], 18);
    w[3] = lv_btn_create(w[0]);
    if (!w[3]) { ui_objects_ok = false; return; }
    objects.btn_signal_right = w[3];
    ui_style_apply(w[3], UI_STYLE_BTN);
    lv_obj_set_pos(w[3], 111, 10);
    lv_obj_set_size(w[3], 76, 40);
    lv_obj_add_event_cb(w[3], action_su_kien_tong, LV_EVENT_PRESSED, (void *)0);
    w[4] = lv_label_create(w[3]);
    if (!w[4]) { ui_objects_ok = false; return; }
    ui_style_apply(w[4], UI_STYLE_LABEL);
    lv_obj_set_pos(w[4], 0, 0);
    lv_obj_set_size(w[4], LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_style_align(w[4], LV_ALIGN_CENTER, LV_PART_MAIN);
    lv_label_set_recolor(w[4], true);
    lv_label_set_text(w[4], ">");
    ui_style_font(w[4], 18);
    w[5] = lv_btn_create(w[0]);
    if (!w[5]) { ui_objects_ok = false; return; }
    objects.btn_on1 = w[5];
    ui_style_apply(w[5], UI_STYLE_BTN);
    lv_obj_set_pos(w[5], 251, 10);
    lv_obj_set_size(w[5], 90, 43);
    lv_obj_add_event_cb(w[5], action_su_kien_tong, LV_EVENT_PRESSED, (void *)0);
    w[6] = lv_label_create(w[5]);
    if (!w[6]) { ui_objects_ok = false; return; }
    ui_style_apply(w[6], UI_STYLE_LABEL);
    lv_obj_set_pos(w[6], 0, 0);
    lv_obj_set_size(w[6], LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_style_align(w[6], LV_ALIGN_CENTER, LV_PART_MAIN);
    lv_label_set_text(w[6], "On");
    ui_style_font(w[6], 18);
    w[7] = lv_btn_create(w[0]);
    if (!w[7]) { ui_objects_ok = false; return; }
    objects.btn_off = w[7];
    ui_style_apply(w[7], UI_STYLE_BTN);
    lv_obj_set_pos(w[7], 367, 11);
    lv_obj_set_size(w[7], 90, 43);
    lv_obj_add_event_cb(w[7], action_su_kien_tong, LV_EVENT_PRESSED, (void *)0);
    w[8] = lv_label_create(w[7]);
    if (!w[8]) { ui_objects_ok = false; return; }
    ui_style_apply(w[8], UI_STYLE_LABEL);
    lv_obj_set_pos(w[8], 0, 0);
    lv_obj_set_size(w[8], LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_style_align(w[8], LV_ALIGN_CENTER, LV_PART_MAIN);
    lv_label_set_text(w[8], "Off");
    ui_style_font(w[8], 18);
    w[9] = lv_obj_create(w[0]);
    if (!w[9]) { ui_objects_ok = false; return; }
    ui_style_apply(w[9], UI_STYLE_OBJ);
    lv_obj_set_pos(w[9], 6, 66);
    lv_obj_set_size(w[9], 286, 82);
    w[10] = lv_btn_create(w[0]);
    if (!w[10]) { ui_objects_ok = false; return; }
    objects.obj0 = w[10];
    ui_style_apply(w[10], UI_STYLE_BTN);
    lv_obj_set_pos(w[10], 19, 82);
    lv_obj_set_size(w[10], 50, 50);
    lv_obj_add_event_cb(w[10], action_su_kien_tong, LV_EVENT_PRESSED, (void *)0);
    w[11] = lv_label_create(w[10]);
    if (!w[11]) { ui_objects_ok = false; return; }
    ui_style_apply(w[11], UI_STYLE_LABEL);
    lv_obj_set_pos(w[11], 0, 0);
    lv_obj_set_size(w[11], LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_style_align(w[11], LV_ALIGN_CENTER, LV_PART_MAIN);
    lv_label_set_text(w[11], "+");
    ui_style_font(w[11], 18);
    w[12] = lv_btn_create(w[0]);
    if (!w[12]) { ui_objects_ok = false; return; }
    objects.obj1 = w[12];
    ui_style_apply(w[12], UI_STYLE_BTN);
    lv_obj_set_pos(w[12], 234, 82);
    lv_obj_set_size(w[12], 50, 50);
    lv_obj_add_event_cb(w[12], action_su_kien_tong, LV_EVENT_PRESSED, (void *)0);
    w[13] = lv_label_create(w[12]);
    if (!w[13]) { ui_objects_ok = false; return; }
    ui_style_apply(w[13], UI_STYLE_LABEL);
    lv_obj_set_pos(w[13], 0, 0);
    lv_obj_set_size(w[13], LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_style_align(w[13], LV_ALIGN_CENTER, LV_PART_MAIN);
    lv_label_set_text(w[13], "-");
    ui_style_font(w[13], 18);
    w[14] = lv_label_create(w[0]);
    if (!w[14]) { ui_objects_ok = false; return; }
    objects.text_km = w[14];
    ui_style_apply(w[14], UI_STYLE_LABEL);
    lv_obj_set_pos(w[14], 91, 83);
    lv_obj_set_size(w[14], LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_label_set_text(w[14], "00");
    ui_style_font(w[14], 18);
    w[15] = lv_label_create(w[0]);
    if (!w[15]) { ui_objects_ok = false; return; }
    ui_style_apply(w[15], UI_STYLE_LABEL);
    lv_obj_set_pos(w[15], 158, 114);
    lv_obj_set_size(w[15], LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_label_set_text(w[15], "Km/h");
    ui_style_font(w[15], 16);
    w[16] = lv_btn_create(w[0]);
    if (!w[16]) { ui_objects_ok = false; return; }
    objects.btn_sport = w[16];
    ui_style_apply(w[16], UI_STYLE_BTN);
    lv_obj_set_pos(w[16], 213, 256);
    lv_obj_set_size(w[16], 100, 50);
    lv_obj_add_event_cb(w[16], action_su_kien_tong, LV_EVENT_PRESSED, (void *)0);
    w[17] = lv_label_create(w[16]);
    if (!w[17]) { ui_objects_ok = false; return; }
    ui_style_apply(w[17], UI_STYLE_LABEL);
    lv_obj_set_pos(w[17], 0, 0);
    lv_obj_set_size(w[17], LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_style_align(w[17], LV_ALIGN_CENTER, LV_PART_MAIN);
    lv_label_set_text(w[17], "Sport");
    ui_style_font(w[17], 18);
    w[18] = lv_btn_create(w[0]);
    if (!w[18]) { ui_objects_ok = false; return; }
    objects.btn_eco = w[18];
    ui_style_apply(w[18], UI_STYLE_BTN);
    lv_obj_set_pos(w[18], 364, 255);
    lv_obj_set_size(w[18], 100, 50);
    lv_obj_add_event_cb(w[18], action_su_kien_tong, LV_EVENT_PRESSED, (void *)0);
    w[19] = lv_label_create(w[18]);
    if (!w[19]) { ui_objects_ok = false; return; }
    ui_style_apply(w[19], UI_STYLE_LABEL);
    lv_obj_set_pos(w[19], 0, 0);
    lv_obj_set_size(w[19], LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_style_align(w[19], LV_ALIGN_CENTER, LV_PART_MAIN);
    lv_label_set_text(w[19], "Eco");
    ui_style_font(w[19], 18);
    w[20] = lv_obj_create(w[0]);
    if (!w[20]) { ui_objects_ok = false; return; }
    ui_style_apply(w[20], UI_STYLE_OBJ);
    lv_obj_set_pos(w[20], 6, 160);
    lv_obj_set_size(w[20], 286, 66);
    w[21] = lv_label_create(w[0]);
    if (!w[21]) { ui_objects_ok = false; return; }
    ui_style_apply(w[21], UI_STYLE_LABEL);
    lv_obj_set_pos(w[21], 25, 176);
    lv_obj_set_size(w[21], LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_label_set_text(w[21], "Time");
    ui_style_font(w[21], 16);
    w[22] = lv_label_create(w[0]);
    if (!w[22]) { ui_objects_ok = false; return; }
    ui_style_apply(w[22], UI_STYLE_LABEL);
    lv_obj_set_pos(w[22], 134, 177);
    lv_obj_set_size(w[22], LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_label_set_text(w[22], "00");
    ui_style_font(w[22], 16);
    w[23] = lv_label_create(w[0]);
    if (!w[23]) { ui_objects_ok = false; return; }
    ui_style_apply(w[23], UI_STYLE_LABEL);
    lv_obj_set_pos(w[23], 182, 177);
    lv_obj_set_size(w[23], LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_label_set_text(w[23], "00");
    ui_style_font(w[23], 16);
    w[24] = lv_label_create(w[0]);
    if (!w[24]) { ui_objects_ok = false; return; }
    ui_style_apply(w[24], UI_STYLE_LABEL);
    lv_obj_set_pos(w[24], 174, 173);
    lv_obj_set_size(w[24], LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_label_set_text(w[24], ":");
    ui_style_font(w[24], 16);
    w[25] = lv_btn_create(w[0]);
    if (!w[25]) { ui_objects_ok = false; return; }
    objects.btn_back_home = w[25];
    ui_style_apply(w[25], UI_STYLE_BTN);
    lv_obj_set_pos(w[25], 17, 257);
    lv_obj_set_size(w[25], 100, 50);
    lv_obj_add_event_cb(w[25], action_su_kien_tong, LV_EVENT_PRESSED, (void *)0);
    w[26] = lv_label_create(w[25]);
    if (!w[26]) { ui_objects_ok = false; return; }
    ui_style_apply(w[26], UI_STYLE_LABEL);
    lv_obj_set_pos(w[26], 0, 0);
    lv_obj_set_size(w[26], LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_style_align(w[26], LV_ALIGN_CENTER, LV_PART_MAIN);
    lv_label_set_text(w[26], "BACK");
    ui_style_font(w[26], 18);
}
void tick_screen_test_tool(void) {}
void create_screens(void) {
    ui_objects_ok = true;
    ui_styles_init();
    lv_disp_t *display = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(display, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), true, LV_FONT_DEFAULT);
    lv_disp_set_theme(display, theme);
    create_screen_main(); if (!ui_objects_ok) return;
    ui_decor_screen(objects.main, UI_DECOR_MAIN);
    create_screen_main_2(); if (!ui_objects_ok) return;
    if (!battery_tabs_attach(objects.main_2, BATTERY_LFP35)) { ui_objects_ok = false; return; }
    create_screen_main_thong_bao(); if (!ui_objects_ok) return;
    create_screen_main_read_b1(); if (!ui_objects_ok) return;
    if (!battery_tabs_attach(objects.main_read_b1, BATTERY_B1)) { ui_objects_ok = false; return; }
    create_screen_ban_phim(); if (!ui_objects_ok) return;
    create_screen_read_a1(); if (!ui_objects_ok) return;
    if (!battery_tabs_attach(objects.read_a1, BATTERY_A1)) { ui_objects_ok = false; return; }
    create_screen_thong_tin_bao_hanh(); if (!ui_objects_ok) return;
    create_screen_sceen_speed_up(); if (!ui_objects_ok) return;
    create_screen_update_speed_trang_thai(); if (!ui_objects_ok) return;
    create_screen_read_can_screen(); if (!ui_objects_ok) return;
    create_screen_main_24kw(); if (!ui_objects_ok) return;
    if (!battery_tabs_attach(objects.main_24kw, BATTERY_LFP24)) { ui_objects_ok = false; return; }
    // Native jk_ui owns this app; do not allocate the unused legacy JK widget tree.
    create_screen_pin_1k2_main(); if (!ui_objects_ok) return;
    if (!battery_tabs_attach(objects.pin_1k2_main, BATTERY_LFP12)) { ui_objects_ok = false; return; }
    create_screen_screen_can_scanner(); if (!ui_objects_ok) return;
    create_screen_test_tool(); if (!ui_objects_ok) return;
}
void tick_screen(int screen_index) { (void)screen_index; }
