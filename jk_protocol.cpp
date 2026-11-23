#include "jk_protocol.h"
#include <string.h>
static const uint8_t HEADER[] = {0x55, 0xAA, 0xEB, 0x90};
static uint16_t le16(const uint8_t *p) {
    return uint16_t(p[0]) | uint16_t(p[1]) << 8;
}
static uint32_t le32(const uint8_t *p) {
    return uint32_t(p[0]) | uint32_t(p[1]) << 8 | uint32_t(p[2]) << 16 | uint32_t(p[3]) << 24;
}
static bool valid(const uint8_t *p, size_t n) {
    if (!p || n != 300 || memcmp(p, HEADER, 4))
        return false;
    uint8_t sum = 0;
    for (size_t i = 0; i < 299; i++)
        sum += p[i];
    return sum == p[299];
}
void JkProtocol::reset() {
    used_ = 0;
    badFrames = goodFrames = 0;
}
bool JkProtocol::push(uint8_t byte, uint8_t out[300]) {
    if (used_ < 4) {
        if (byte == HEADER[used_])
            buffer_[used_++] = byte;
        else {
            used_ = byte == HEADER[0] ? 1 : 0;
            if (used_)
                buffer_[0] = byte;
        }
        return false;
    }
    buffer_[used_++] = byte;
    if (used_ < 300)
        return false;
    if (valid(buffer_, 300)) {
        memcpy(out, buffer_, 300);
        used_ = 0;
        goodFrames++;
        return true;
    }
    badFrames++;
    // Retain an inner header or partial suffix so a damaged packet cannot desynchronize forever.
    for (size_t i = 1; i < 300; i++) {
        size_t n = 300 - i;
        if (n > 4)
            n = 4;
        if (!memcmp(buffer_ + i, HEADER, n)) {
            used_ = 300 - i;
            memmove(buffer_, buffer_ + i, used_);
            return false;
        }
    }
    used_ = 0;
    return false;
}
bool JkProtocol::decodeData(const uint8_t *p, size_t n, JkProfile profile, JkData &out) {
    if (!valid(p, n) || p[4] != 2)
        return false;
    JkData d{};
    unsigned cells = profile == JkProfile::JK02_32S ? 32 : 24, off = cells == 32 ? 32 : 0;
    d.enabledMask = le32(p + (cells == 32 ? 70 : 54));
    uint16_t min = 0xFFFF, max = 0;
    for (unsigned i = 0; i < cells; i++) {
        uint16_t mv = le16(p + 6 + i * 2);
        d.cellMv[i] = mv;
        bool active = d.enabledMask ? ((d.enabledMask >> i) & 1u) : mv != 0;
        if (active && mv) {
            d.cellCount++;
            if (mv < min)
                min = mv;
            if (mv > max)
                max = mv;
        }
    }
    d.minCell = d.cellCount ? min * 0.001f : 0;
    d.maxCell = max * 0.001f;
    d.deltaCell = d.cellCount ? (max - min) * 0.001f : 0;
    d.voltage = le32(p + 118 + off) * 0.001f;
    d.current = int32_t(le32(p + 126 + off)) * 0.001f;
    d.power = d.voltage * d.current;
    d.temp1 = int16_t(le16(p + 130 + off)) * 0.1f;
    d.temp2 = int16_t(le16(p + 132 + off)) * 0.1f;
    d.mosTemp = int16_t(le16(p + (cells == 32 ? 144 : 134))) * 0.1f;
    d.errors = cells == 32 ? le32(p + 134 + off) : le16(p + 136);
    d.balanceCurrent = int16_t(le16(p + 138 + off)) * 0.001f;
    d.balancing = p[140 + off] != 0;
    d.soc = p[141 + off];
    d.soh = p[158 + off];
    d.remainingAh = le32(p + 142 + off) * 0.001f;
    d.capacityAh = le32(p + 146 + off) * 0.001f;
    d.cycles = le32(p + 150 + off);
    d.uptime = le32(p + 162 + off);
    d.charge = p[166 + off] != 0;
    d.discharge = p[167 + off] != 0;
    // The caller picks a frame layout explicitly; do not silently reinterpret another layout.
    if (d.soc > 100 || d.soh > 100)
        return false;
    d.valid = true;
    out = d;
    return true;
}
bool JkProtocol::decodeInfo(const uint8_t *p, size_t n, JkInfo &out) {
    if (!valid(p, n) || p[4] != 3)
        return false;
    JkInfo info{};
    char *fields[] = {info.model, info.hardware, info.software, info.deviceName, info.serial, info.setupPass};
    const unsigned offsets[] = {6, 22, 30, 46, 86, 118}, sizes[] = {16, 8, 8, 16, 16, 16};
    for (unsigned f = 0; f < 6; f++)
        for (unsigned i = 0; i < sizes[f] && p[offsets[f] + i]; i++) {
            uint8_t c = p[offsets[f] + i];
            fields[f][i] = c >= 32 && c < 127 ? char(c) : '?';
        }
    info.valid = true;
    out = info;
    return true;
}
void JkProtocol::command(uint8_t reg, uint8_t out[20]) {
    memset(out, 0, 20);
    out[0] = 0xAA;
    out[1] = 0x55;
    out[2] = 0x90;
    out[3] = 0xEB;
    out[4] = reg;
    for (unsigned i = 0; i < 19; i++)
        out[19] += out[i];
}
