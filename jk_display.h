#pragma once
#include <TFT_eSPI.h>
TFT_eSPI &jk_display();
void jk_display_begin();
bool jk_display_touch(uint16_t &x, uint16_t &y);
