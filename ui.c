#include "ui.h"
#include "screens.h"
extern bool ui_objects_ready(void);
static int16_t currentScreen = -1;
void loadScreen(enum ScreensEnum screenId) {
    int index = (int)screenId - 1;
    if (index < 0 || index >= 15) return;
    lv_obj_t *screen = ((lv_obj_t **)&objects)[index];
    if (!screen) return;
    currentScreen = index;
    lv_scr_load(screen);
}
void ui_init(void) {
    create_screens();
    if (!ui_objects_ready()) return;
    loadScreen(SCREEN_ID_MAIN);
    lv_refr_now(NULL);
}
void ui_tick(void) {
    if (currentScreen >= 0) tick_screen(currentScreen);
}
