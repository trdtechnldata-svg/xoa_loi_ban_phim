#pragma once
#include "jk_types.h"
void jk_ui_begin();
void jk_ui_tick(const JkSnapshot &snapshot);
void jk_ui_touch(uint16_t x, uint16_t y, bool pressed, const JkSnapshot &snapshot);

bool jk_ui_exit_requested();
