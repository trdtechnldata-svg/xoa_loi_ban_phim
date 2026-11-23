#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _objects_t {
    lv_obj_t *main;
    lv_obj_t *main_2;
    lv_obj_t *main_thong_bao;
    lv_obj_t *main_read_b1;
    lv_obj_t *ban_phim;
    lv_obj_t *read_a1;
    lv_obj_t *thong_tin_bao_hanh;
    lv_obj_t *sceen_speed_up;
    lv_obj_t *update_speed_trang_thai;
    lv_obj_t *read_can_screen;
    lv_obj_t *main_24kw;
    lv_obj_t *bms_jk;
    lv_obj_t *pin_1k2_main;
    lv_obj_t *screen_can_scanner;
    lv_obj_t *test_tool;
    lv_obj_t *ampe_a1;
    lv_obj_t *ampe_b1;
    lv_obj_t *ampe_jk;
    lv_obj_t *ampe_lfp;
    lv_obj_t *ampe_lfp_1k2;
    lv_obj_t *ampe_lfp_24;
    lv_obj_t *avg_b1;
    lv_obj_t *avg_jk;
    lv_obj_t *avg_lfp;
    lv_obj_t *avg_lfp_1k2;
    lv_obj_t *avg_lfp_24;
    lv_obj_t *back_home;
    lv_obj_t *back_home_1;
    lv_obj_t *back_home_2;
    lv_obj_t *back_main_speed_up_7;
    lv_obj_t *back_mo_toc_4;
    lv_obj_t *bar_speed_up;
    lv_obj_t *batt_bar;
    lv_obj_t *batt_text;
    lv_obj_t *btn_add_option;
    lv_obj_t *btn_back_home;
    lv_obj_t *btn_eco;
    lv_obj_t *btn_off;
    lv_obj_t *btn_on1;
    lv_obj_t *btn_signal_left;
    lv_obj_t *btn_signal_right;
    lv_obj_t *btn_sport;
    lv_obj_t *btn_test_hmi;
    lv_obj_t *but_reset;
    lv_obj_t *butt_1_2kw;
    lv_obj_t *butt_24;
    lv_obj_t *butt_bms_jk;
    lv_obj_t *can_read_butt;
    lv_obj_t *cap_jk;
    lv_obj_t *cell_1;
    lv_obj_t *cell_1_1k2;
    lv_obj_t *cell_1_b1;
    lv_obj_t *cell_1_jk;
    lv_obj_t *cell_10;
    lv_obj_t *cell_10_1k2;
    lv_obj_t *cell_10_b1;
    lv_obj_t *cell_10_jk;
    lv_obj_t *cell_11;
    lv_obj_t *cell_11_1k2;
    lv_obj_t *cell_11_b1;
    lv_obj_t *cell_11_jk;
    lv_obj_t *cell_12;
    lv_obj_t *cell_12_1k2;
    lv_obj_t *cell_12_b1;
    lv_obj_t *cell_12_jk;
    lv_obj_t *cell_13;
    lv_obj_t *cell_13_1k2;
    lv_obj_t *cell_13_b1;
    lv_obj_t *cell_13_jk;
    lv_obj_t *cell_14;
    lv_obj_t *cell_14_1k2;
    lv_obj_t *cell_14_b1;
    lv_obj_t *cell_14_jk;
    lv_obj_t *cell_15;
    lv_obj_t *cell_15_1k2;
    lv_obj_t *cell_15_jk;
    lv_obj_t *cell_16;
    lv_obj_t *cell_16_1k2;
    lv_obj_t *cell_16_jk;
    lv_obj_t *cell_17;
    lv_obj_t *cell_17_1k2;
    lv_obj_t *cell_17_jk;
    lv_obj_t *cell_18;
    lv_obj_t *cell_18_1k2;
    lv_obj_t *cell_18_jk;
    lv_obj_t *cell_19;
    lv_obj_t *cell_19_1k2;
    lv_obj_t *cell_19_jk;
    lv_obj_t *cell_2;
    lv_obj_t *cell_2_1k2;
    lv_obj_t *cell_2_b1;
    lv_obj_t *cell_2_jk;
    lv_obj_t *cell_20;
    lv_obj_t *cell_20_1k2;
    lv_obj_t *cell_20_jk;
    lv_obj_t *cell_21;
    lv_obj_t *cell_21_jk;
    lv_obj_t *cell_22;
    lv_obj_t *cell_22_jk;
    lv_obj_t *cell_23_jk;
    lv_obj_t *cell_24_1;
    lv_obj_t *cell_24_10;
    lv_obj_t *cell_24_11;
    lv_obj_t *cell_24_12;
    lv_obj_t *cell_24_13;
    lv_obj_t *cell_24_14;
    lv_obj_t *cell_24_15;
    lv_obj_t *cell_24_16;
    lv_obj_t *cell_24_17;
    lv_obj_t *cell_24_18;
    lv_obj_t *cell_24_19;
    lv_obj_t *cell_24_2;
    lv_obj_t *cell_24_3;
    lv_obj_t *cell_24_4;
    lv_obj_t *cell_24_5;
    lv_obj_t *cell_24_6;
    lv_obj_t *cell_24_7;
    lv_obj_t *cell_24_8;
    lv_obj_t *cell_24_9;
    lv_obj_t *cell_24_jk;
    lv_obj_t *cell_3;
    lv_obj_t *cell_3_1k2;
    lv_obj_t *cell_3_b1;
    lv_obj_t *cell_3_jk;
    lv_obj_t *cell_4;
    lv_obj_t *cell_4_1k2;
    lv_obj_t *cell_4_b1;
    lv_obj_t *cell_4_jk;
    lv_obj_t *cell_5;
    lv_obj_t *cell_5_1k2;
    lv_obj_t *cell_5_b1;
    lv_obj_t *cell_5_jk;
    lv_obj_t *cell_6;
    lv_obj_t *cell_6_1k2;
    lv_obj_t *cell_6_b1;
    lv_obj_t *cell_6_jk;
    lv_obj_t *cell_7;
    lv_obj_t *cell_7_1k2;
    lv_obj_t *cell_7_b1;
    lv_obj_t *cell_7_jk;
    lv_obj_t *cell_8;
    lv_obj_t *cell_8_1k2;
    lv_obj_t *cell_8_b1;
    lv_obj_t *cell_8_jk;
    lv_obj_t *cell_9;
    lv_obj_t *cell_9_1k2;
    lv_obj_t *cell_9_b1;
    lv_obj_t *cell_9_jk;
    lv_obj_t *cycle;
    lv_obj_t *cycle_1k2;
    lv_obj_t *cycle_24;
    lv_obj_t *cycle_b1;
    lv_obj_t *cycle_jk;
    lv_obj_t *dd_cars;
    lv_obj_t *del_vol;
    lv_obj_t *del_vol_1k2;
    lv_obj_t *del_vol_24;
    lv_obj_t *del_vol_a1;
    lv_obj_t *del_vol_b1;
    lv_obj_t *del_vol_jk;
    lv_obj_t *impes_48v;
    lv_obj_t *impes_48v_backup;
    lv_obj_t *impes_zin;
    lv_obj_t *kb_input;
    lv_obj_t *klara_a1_48v;
    lv_obj_t *klara_a1_60v;
    lv_obj_t *klara_a1_60v_backup;
    lv_obj_t *klara_a1_72v;
    lv_obj_t *klara_a1_zin_speed;
    lv_obj_t *klara_s1_48v;
    lv_obj_t *klara_s1_48v_backup;
    lv_obj_t *klara_s1_60v;
    lv_obj_t *klara_s1_61;
    lv_obj_t *klara_s1_72v;
    lv_obj_t *klara_s1_zin_speed;
    lv_obj_t *label_show_selection;
    lv_obj_t *load_ban_phim;
    lv_obj_t *nut_back;
    lv_obj_t *nut_back_1;
    lv_obj_t *nut_back_1k2;
    lv_obj_t *nut_back_2;
    lv_obj_t *nut_back_24;
    lv_obj_t *nut_back_3;
    lv_obj_t *nut_back_4;
    lv_obj_t *nut_back_jk;
    lv_obj_t *nut_bao_hanh;
    lv_obj_t *obj0;
    lv_obj_t *obj1;
    lv_obj_t *rcap_b1;
    lv_obj_t *rcap_jk;
    lv_obj_t *rcap_lfp;
    lv_obj_t *rcap_lfp_1k2;
    lv_obj_t *rcap_lfp_24;
    lv_obj_t *read_pin_a1;
    lv_obj_t *read_pin_b1;
    lv_obj_t *read_pin_lfp;
    lv_obj_t *scan_pass_jk;
    lv_obj_t *soc;
    lv_obj_t *soc_1k2;
    lv_obj_t *soc_24;
    lv_obj_t *soc_a1;
    lv_obj_t *soc_b1;
    lv_obj_t *soc_jk;
    lv_obj_t *soh_b1;
    lv_obj_t *soh_jk;
    lv_obj_t *soh_lfp;
    lv_obj_t *soh_lfp_1k2;
    lv_obj_t *soh_lfp_24;
    lv_obj_t *speed_up;
    lv_obj_t *t_1;
    lv_obj_t *t_1_1k2;
    lv_obj_t *t_1_24;
    lv_obj_t *t_1_a1;
    lv_obj_t *t_1_b1;
    lv_obj_t *t_1_jk;
    lv_obj_t *t_2;
    lv_obj_t *t_2_1k2;
    lv_obj_t *t_2_24;
    lv_obj_t *t_2_a1;
    lv_obj_t *t_2_b1;
    lv_obj_t *t_2_jk;
    lv_obj_t *t_3;
    lv_obj_t *t_3_1k2;
    lv_obj_t *t_3_24;
    lv_obj_t *t_3_a1;
    lv_obj_t *t_3_b1;
    lv_obj_t *t_4;
    lv_obj_t *t_4_a1;
    lv_obj_t *t_4_b1;
    lv_obj_t *t_5;
    lv_obj_t *t_5_a1;
    lv_obj_t *t_5_b1;
    lv_obj_t *t_6;
    lv_obj_t *t_6_a1;
    lv_obj_t *t_6_b1;
    lv_obj_t *t_7_a1;
    lv_obj_t *ta_new_options;
    lv_obj_t *tem_fet_jk;
    lv_obj_t *text_bao_hanh;
    lv_obj_t *text_data_can;
    lv_obj_t *text_gioi_thieu;
    lv_obj_t *text_id_can;
    lv_obj_t *text_km;
    lv_obj_t *text_loai_xe;
    lv_obj_t *text_mac_adress;
    lv_obj_t *text_pass_jk_1;
    lv_obj_t *text_pass_jk_10;
    lv_obj_t *text_pass_jk_11;
    lv_obj_t *text_pass_jk_12;
    lv_obj_t *text_pass_jk_2;
    lv_obj_t *text_pass_jk_3;
    lv_obj_t *text_pass_jk_4;
    lv_obj_t *text_pass_jk_5;
    lv_obj_t *text_pass_jk_6;
    lv_obj_t *text_pass_jk_7;
    lv_obj_t *text_pass_jk_8;
    lv_obj_t *text_pass_jk_9;
    lv_obj_t *text_speed_up;
    lv_obj_t *text_vol_1k2;
    lv_obj_t *text_vol_a1;
    lv_obj_t *text_vol_b1;
    lv_obj_t *text_vol_jk;
    lv_obj_t *text_vol_lfp;
    lv_obj_t *text_vol_lfp_24;
    lv_obj_t *total_id_can_read;
    lv_obj_t *v_max_a1;
    lv_obj_t *v_max_b1;
    lv_obj_t *v_max_lfp;
    lv_obj_t *v_max_lfp_1k2;
    lv_obj_t *v_max_lfp_24;
    lv_obj_t *v_min_a1;
    lv_obj_t *v_min_b1;
    lv_obj_t *v_min_lfp;
    lv_obj_t *v_min_lfp_1k2;
    lv_obj_t *v_min_lfp_24;
} objects_t;

extern objects_t objects;

enum ScreensEnum {
    SCREEN_ID_MAIN = 1,
    SCREEN_ID_MAIN_2 = 2,
    SCREEN_ID_MAIN_THONG_BAO = 3,
    SCREEN_ID_MAIN_READ_B1 = 4,
    SCREEN_ID_BAN_PHIM = 5,
    SCREEN_ID_READ_A1 = 6,
    SCREEN_ID_THONG_TIN_BAO_HANH = 7,
    SCREEN_ID_SCEEN_SPEED_UP = 8,
    SCREEN_ID_UPDATE_SPEED_TRANG_THAI = 9,
    SCREEN_ID_READ_CAN_SCREEN = 10,
    SCREEN_ID_MAIN_24KW = 11,
    SCREEN_ID_BMS_JK = 12,
    SCREEN_ID_PIN_1K2_MAIN = 13,
    SCREEN_ID_SCREEN_CAN_SCANNER = 14,
    SCREEN_ID_TEST_TOOL = 15,
};

void create_screen_main();
void tick_screen_main();

void create_screen_main_2();
void tick_screen_main_2();

void create_screen_main_thong_bao();
void tick_screen_main_thong_bao();

void create_screen_main_read_b1();
void tick_screen_main_read_b1();

void create_screen_ban_phim();
void tick_screen_ban_phim();

void create_screen_read_a1();
void tick_screen_read_a1();

void create_screen_thong_tin_bao_hanh();
void tick_screen_thong_tin_bao_hanh();

void create_screen_sceen_speed_up();
void tick_screen_sceen_speed_up();

void create_screen_update_speed_trang_thai();
void tick_screen_update_speed_trang_thai();

void create_screen_read_can_screen();
void tick_screen_read_can_screen();

void create_screen_main_24kw();
void tick_screen_main_24kw();

void create_screen_bms_jk();
void tick_screen_bms_jk();

void create_screen_pin_1k2_main();
void tick_screen_pin_1k2_main();

void create_screen_screen_can_scanner();
void tick_screen_screen_can_scanner();

void create_screen_test_tool();
void tick_screen_test_tool();

void create_screens();
void tick_screen(int screen_index);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/