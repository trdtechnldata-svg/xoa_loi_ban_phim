#pragma once
#include "jk_types.h"
bool jk_ble_begin();
void jk_ble_snapshot(JkSnapshot &out);
bool jk_ble_scan();
bool jk_ble_connect(const JkDevice &device);
bool jk_ble_disconnect();
bool jk_ble_profile(JkProfile profile);

void jk_ble_suspend();
