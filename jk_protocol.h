#pragma once
#include "jk_types.h"
// Portable C++: no Arduino/BLE/display dependency. Safe for arbitrary notification sizes.
class JkProtocol {
    uint8_t buffer_[300]{};
    size_t used_ = 0;

  public:
    uint32_t badFrames = 0, goodFrames = 0;
    void reset();
    bool push(uint8_t byte, uint8_t out[300]);
    static bool decodeData(const uint8_t *p, size_t n, JkProfile profile, JkData &out);
    static bool decodeInfo(const uint8_t *p, size_t n, JkInfo &out);
    static void command(uint8_t reg, uint8_t out[20]);
};
