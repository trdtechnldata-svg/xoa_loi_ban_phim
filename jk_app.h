#pragma once
#include <stdint.h>
void jk_app_open();
bool jk_app_is_open();
void jk_app_poll();
bool jk_app_capture_touch(uint16_t x, uint16_t y, bool pressed);
