#pragma once
#include <stdint.h>
// Only this file changes when adapting the same application to another TFT board.
static constexpr uint16_t JK_SCREEN_W = 480, JK_SCREEN_H = 320;
static constexpr uint8_t JK_TFT_ROTATION = 1;
static constexpr int JK_BACKLIGHT_PIN = 27; // Same HIGH level as the supplied project.
static constexpr uint16_t JK_TOUCH_THRESHOLD = 600;
static constexpr unsigned JK_MAX_DEVICES = 16;
static constexpr uint32_t JK_SCAN_MS = 5000;
static constexpr uint32_t JK_CONNECT_TIMEOUT_MS = 5000;
static constexpr uint32_t JK_REQUEST_INTERVAL_MS = 2000;
static constexpr uint32_t JK_STALE_MS = 10000;
static constexpr bool JK_DEFAULT_32S = true; // Frame layout; NOT the battery's cell count.
