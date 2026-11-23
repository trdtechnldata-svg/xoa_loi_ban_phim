#include "battery_tabs.h"
#include "screens.h"
#include <stdio.h>
#include <string.h>
#define BG 0x0C1624
#define CARD 0x132238
#define EDGE 0x2A425C
#define MUTED 0x94ABC3
#define WHITE 0xF3F7FF
#define TEAL 0x51DFBD
typedef struct { const char *name; lv_obj_t *value; } metric_t;
typedef struct {
    lv_obj_t *screen, *panel[2], *button[2];
    metric_t metrics[16];
    lv_obj_t *cells[24], *stats[3];
    unsigned metric_count, cell_count, selected;
} battery_view_t;
static battery_view_t views[BATTERY_PAGE_COUNT];
static void frame(lv_draw_ctx_t *ctx, const lv_area_t *root, int x, int y, int w, int h) {
    lv_draw_rect_dsc_t d; lv_draw_rect_dsc_init(&d);
    d.bg_color = lv_color_hex(CARD); d.bg_opa = LV_OPA_COVER;
    d.border_color = lv_color_hex(EDGE); d.border_width = 1; d.radius = 6;
    lv_area_t area = {root->x1+x,root->y1+y,root->x1+x+w-1,root->y1+y+h-1};
    lv_draw_rect(ctx,&d,&area);
}
static void caption(lv_draw_ctx_t *ctx, const lv_area_t *root, int x, int y, int w, const char *text, bool center) {
    lv_draw_label_dsc_t d; lv_draw_label_dsc_init(&d);
    d.font=&lv_font_montserrat_14;d.color=lv_color_hex(MUTED);
    d.align=center?LV_TEXT_ALIGN_CENTER:LV_TEXT_ALIGN_LEFT;
    lv_area_t area={root->x1+x,root->y1+y,root->x1+x+w-1,root->y1+y+19};
    lv_draw_label(ctx,&d,&area,text,NULL);
}
static void select_tab(battery_view_t *view, unsigned tab) {
    view->selected=tab;
    for(unsigned i=0;i<2;i++) {
        if(i==tab) lv_obj_clear_flag(view->panel[i],LV_OBJ_FLAG_HIDDEN);
        else lv_obj_add_flag(view->panel[i],LV_OBJ_FLAG_HIDDEN);
        lv_obj_set_style_bg_color(view->button[i],lv_color_hex(i==tab?0x14615C:0x182B40),LV_PART_MAIN);
        lv_obj_invalidate(view->button[i]);
    }
}
static void button_event(lv_event_t *event) {
    battery_view_t *view=lv_event_get_user_data(event);
    lv_obj_t *target=lv_event_get_target(event);
    if(lv_event_get_code(event)==LV_EVENT_CLICKED) select_tab(view,target==view->button[1]);
    else if(lv_event_get_code(event)==LV_EVENT_DRAW_MAIN) {
        lv_area_t a;lv_obj_get_coords(target,&a);
        lv_draw_label_dsc_t d;lv_draw_label_dsc_init(&d);
        d.font=&lv_font_montserrat_16;d.color=lv_color_hex(WHITE);d.align=LV_TEXT_ALIGN_CENTER;
        a.y1+=9;
        lv_draw_label(lv_event_get_draw_ctx(event),&d,&a,target==view->button[0]?"TONG QUAN":"CELL PIN",NULL);
    }
}
static void screen_loaded(lv_event_t *event) { select_tab(lv_event_get_user_data(event),0); }
static void panel_draw(lv_event_t *event) {
    battery_view_t *view=lv_event_get_user_data(event);
    lv_draw_ctx_t *ctx=lv_event_get_draw_ctx(event);
    lv_area_t a;lv_obj_get_coords(lv_event_get_target(event),&a);
    if(lv_event_get_target(event)==view->panel[0]) {
        unsigned rows=(view->metric_count+2)/3;
        int step=rows<=4?54:42;
        for(unsigned i=0;i<view->metric_count;i++) {
            int x=12+(i%3)*156,y=4+(i/3)*step;
            frame(ctx,&a,x,y,144,step-4);
            caption(ctx,&a,x+8,y+2,128,view->metrics[i].name,false);
        }
    } else {
        const char *names[]={"VMIN (V)","VMAX (V)","DELTA (V)"};
        for(unsigned i=0;i<3;i++) {frame(ctx,&a,12+i*156,4,144,40);caption(ctx,&a,20+i*156,6,128,names[i],false);}
        if(!view->cell_count) {
            caption(ctx,&a,12,90,456,"CHUA CO DIEN AP TUNG CELL TRONG DU LIEU A1",true);
            caption(ctx,&a,12,120,456,"Van hien Vmin / Vmax / Delta tu du lieu pin.",true);
            return;
        }
        unsigned rows=(view->cell_count+3)/4;int step=164/rows;
        for(unsigned i=0;i<view->cell_count;i++) {
            int x=12+(i%4)*117,y=52+(i/4)*step;char n[12];snprintf(n,sizeof(n),"%02u",i+1);
            frame(ctx,&a,x,y,108,step-3);caption(ctx,&a,x+5,y+5,23,n,false);
        }
    }
}
static void value_style(lv_obj_t *value,lv_obj_t *parent,int x,int y,int w,const lv_font_t *font) {
    if(!value) return;
    lv_obj_set_parent(value,parent);lv_obj_clear_flag(value,LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_pos(value,x,y);lv_obj_set_size(value,w,22);
    lv_obj_set_style_text_font(value,font,LV_PART_MAIN);lv_obj_set_style_text_color(value,lv_color_hex(TEAL),LV_PART_MAIN);
    lv_obj_set_style_text_align(value,LV_TEXT_ALIGN_LEFT,LV_PART_MAIN);
    lv_label_set_long_mode(value,LV_LABEL_LONG_CLIP);
}
static void bind_metrics(battery_view_t *v,const metric_t *items,unsigned count) {
    v->metric_count=count;memcpy(v->metrics,items,count*sizeof(*items));
}
static void bind_cells(battery_view_t *v,lv_obj_t **items,unsigned count,lv_obj_t *min,lv_obj_t *max,lv_obj_t *delta) {
    v->cell_count=count;if(count)memcpy(v->cells,items,count*sizeof(*items));
    v->stats[0]=min;v->stats[1]=max;v->stats[2]=delta;
}
bool battery_tabs_attach(lv_obj_t *screen,battery_page_t page) {
    if(!screen || page>=BATTERY_PAGE_COUNT) return false;
    battery_view_t *v=&views[page];
    if(v->screen==screen) return true;
    memset(v,0,sizeof(*v));v->screen=screen;
    lv_obj_update_layout(screen);
    // Reuse the exact labels updated by the original CAN code; only the parent/layout changes.
    for(unsigned i=0;i<lv_obj_get_child_cnt(screen);i++) {
        lv_obj_t *child=lv_obj_get_child(screen,i);
        if(lv_obj_get_y(child)>=40) lv_obj_add_flag(child,LV_OBJ_FLAG_HIDDEN);
    }
    switch(page) {
    case BATTERY_LFP35: {
        const metric_t m[]={{"SOC (%)",objects.soc},{"DIEN AP (V)",objects.text_vol_lfp},{"DONG DIEN (A)",objects.ampe_lfp},
            {"CYCLE",objects.cycle},{"RCAP (Ah)",objects.rcap_lfp},{"SOH (%)",objects.soh_lfp},{"AVG CELL (V)",objects.avg_lfp},
            {"TEMP 1",objects.t_1},{"TEMP 2",objects.t_2},{"TEMP 3",objects.t_3},{"TEMP 4",objects.t_4},{"TEMP 5",objects.t_5},{"TEMP 6",objects.t_6}};
        lv_obj_t *c[]={objects.cell_1,objects.cell_2,objects.cell_3,objects.cell_4,objects.cell_5,objects.cell_6,objects.cell_7,objects.cell_8,objects.cell_9,objects.cell_10,objects.cell_11,objects.cell_12,objects.cell_13,objects.cell_14,objects.cell_15,objects.cell_16,objects.cell_17,objects.cell_18,objects.cell_19,objects.cell_20,objects.cell_21,objects.cell_22};
        bind_metrics(v,m,13);bind_cells(v,c,22,objects.v_min_lfp,objects.v_max_lfp,objects.del_vol);break;
    }
    case BATTERY_B1: {
        const metric_t m[]={{"SOC (%)",objects.soc_b1},{"DIEN AP (V)",objects.text_vol_b1},{"DONG DIEN (A)",objects.ampe_b1},
            {"CYCLE",objects.cycle_b1},{"RCAP (Ah)",objects.rcap_b1},{"SOH (%)",objects.soh_b1},{"AVG CELL (V)",objects.avg_b1},
            {"TEMP 1",objects.t_1_b1},{"TEMP 2",objects.t_2_b1},{"TEMP 3",objects.t_3_b1},{"TEMP 4",objects.t_4_b1},{"TEMP 5",objects.t_5_b1},{"TEMP 6",objects.t_6_b1}};
        lv_obj_t *c[]={objects.cell_1_b1,objects.cell_2_b1,objects.cell_3_b1,objects.cell_4_b1,objects.cell_5_b1,objects.cell_6_b1,objects.cell_7_b1,objects.cell_8_b1,objects.cell_9_b1,objects.cell_10_b1,objects.cell_11_b1,objects.cell_12_b1,objects.cell_13_b1,objects.cell_14_b1};
        bind_metrics(v,m,13);bind_cells(v,c,14,objects.v_min_b1,objects.v_max_b1,objects.del_vol_b1);break;
    }
    case BATTERY_A1: {
        const metric_t m[]={{"SOC (%)",objects.soc_a1},{"DIEN AP (V)",objects.text_vol_a1},{"DONG DIEN (A)",objects.ampe_a1},
            {"TEMP 1",objects.t_1_a1},{"TEMP 2",objects.t_2_a1},{"TEMP 3",objects.t_3_a1},{"TEMP 4",objects.t_4_a1},{"TEMP 5",objects.t_5_a1},{"TEMP 6",objects.t_6_a1},{"TEMP 7",objects.t_7_a1}};
        bind_metrics(v,m,10);bind_cells(v,NULL,0,objects.v_min_a1,objects.v_max_a1,objects.del_vol_a1);break;
    }
    case BATTERY_LFP24: {
        const metric_t m[]={{"SOC (%)",objects.soc_24},{"DIEN AP (V)",objects.text_vol_lfp_24},{"DONG DIEN (A)",objects.ampe_lfp_24},
            {"CYCLE",objects.cycle_24},{"RCAP (Ah)",objects.rcap_lfp_24},{"SOH (%)",objects.soh_lfp_24},{"AVG CELL (V)",objects.avg_lfp_24},
            {"TEMP 1",objects.t_1_24},{"TEMP 2",objects.t_2_24},{"MOS TEMP",objects.t_3_24}};
        lv_obj_t *c[]={objects.cell_24_1,objects.cell_24_2,objects.cell_24_3,objects.cell_24_4,objects.cell_24_5,objects.cell_24_6,objects.cell_24_7,objects.cell_24_8,objects.cell_24_9,objects.cell_24_10,objects.cell_24_11,objects.cell_24_12,objects.cell_24_13,objects.cell_24_14,objects.cell_24_15,objects.cell_24_16,objects.cell_24_17,objects.cell_24_18,objects.cell_24_19};
        bind_metrics(v,m,10);bind_cells(v,c,19,objects.v_min_lfp_24,objects.v_max_lfp_24,objects.del_vol_24);break;
    }
    case BATTERY_LFP12: {
        const metric_t m[]={{"SOC (%)",objects.soc_1k2},{"DIEN AP (V)",objects.text_vol_1k2},{"DONG DIEN (A)",objects.ampe_lfp_1k2},
            {"CYCLE",objects.cycle_1k2},{"RCAP (Ah)",objects.rcap_lfp_1k2},{"SOH (%)",objects.soh_lfp_1k2},{"AVG CELL (V)",objects.avg_lfp_1k2},
            {"TEMP 1",objects.t_1_1k2},{"TEMP 2",objects.t_2_1k2},{"TEMP 3",objects.t_3_1k2}};
        lv_obj_t *c[]={objects.cell_1_1k2,objects.cell_2_1k2,objects.cell_3_1k2,objects.cell_4_1k2,objects.cell_5_1k2,objects.cell_6_1k2,objects.cell_7_1k2,objects.cell_8_1k2,objects.cell_9_1k2,objects.cell_10_1k2,objects.cell_11_1k2,objects.cell_12_1k2,objects.cell_13_1k2,objects.cell_14_1k2,objects.cell_15_1k2,objects.cell_16_1k2,objects.cell_17_1k2,objects.cell_18_1k2,objects.cell_19_1k2,objects.cell_20_1k2};
        bind_metrics(v,m,10);bind_cells(v,c,20,objects.v_min_lfp_1k2,objects.v_max_lfp_1k2,objects.del_vol_1k2);break;
    }
    default:return false;
    }
    for(unsigned i=0;i<2;i++) {
        v->panel[i]=lv_obj_create(screen);if(!v->panel[i]) return false;
        lv_obj_set_pos(v->panel[i],0,46);lv_obj_set_size(v->panel[i],480,224);
        lv_obj_set_style_pad_all(v->panel[i],0,0);lv_obj_set_style_border_width(v->panel[i],0,0);
        lv_obj_set_style_bg_color(v->panel[i],lv_color_hex(BG),0);lv_obj_set_style_bg_opa(v->panel[i],LV_OPA_COVER,0);
        lv_obj_set_style_radius(v->panel[i],0,0);lv_obj_clear_flag(v->panel[i],LV_OBJ_FLAG_SCROLLABLE);
        lv_obj_add_event_cb(v->panel[i],panel_draw,LV_EVENT_DRAW_MAIN,v);
        v->button[i]=lv_btn_create(screen);if(!v->button[i]) return false;
        lv_obj_set_pos(v->button[i],12+i*234,276);lv_obj_set_size(v->button[i],222,36);
        lv_obj_set_style_radius(v->button[i],7,0);lv_obj_set_style_border_width(v->button[i],0,0);
        lv_obj_add_event_cb(v->button[i],button_event,LV_EVENT_CLICKED,v);
        lv_obj_add_event_cb(v->button[i],button_event,LV_EVENT_DRAW_MAIN,v);
    }
    unsigned rows=(v->metric_count+2)/3;int step=rows<=4?54:42;
    for(unsigned i=0;i<v->metric_count;i++)
        value_style(v->metrics[i].value,v->panel[0],20+(i%3)*156,22+(i/3)*step,128,&lv_font_montserrat_18);
    for(unsigned i=0;i<3;i++) value_style(v->stats[i],v->panel[1],20+i*156,23,128,&lv_font_montserrat_18);
    rows=(v->cell_count+3)/4;step=rows?164/rows:0;
    for(unsigned i=0;i<v->cell_count;i++)
        value_style(v->cells[i],v->panel[1],40+(i%4)*117,56+(i/4)*step,74,&lv_font_montserrat_16);
    lv_obj_add_event_cb(screen,screen_loaded,LV_EVENT_SCREEN_LOADED,v);select_tab(v,0);
    return true;
}
