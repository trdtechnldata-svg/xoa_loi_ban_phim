#include "jk_display.h"
#include "jk_config.h"
// The multi-app sketch initializes the physical TFT once. Never create/reinitialize a second driver.
extern TFT_eSPI tft;
TFT_eSPI &jk_display() { return tft; }
void jk_display_begin() { /* Display setup belongs to xoa_loi_ban_phim.ino. */ }
bool jk_display_touch(uint16_t &x, uint16_t &y) {
    return tft.getTouch(&x, &y, JK_TOUCH_THRESHOLD);
}
