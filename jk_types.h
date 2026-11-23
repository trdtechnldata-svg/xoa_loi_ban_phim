#pragma once
#include <stdint.h>
#include <stddef.h>
#include "jk_config.h"
enum class JkProfile : uint8_t { JK02_24S, JK02_32S };
enum class JkState : uint8_t {
    Starting,
    Idle,
    Scanning,
    Connecting,
    Discovering,
    Connected,
    Disconnected,
    Error
};
struct JkDevice {
    char name[33];
    char address[18];
    int16_t rssi;
    uint8_t addressType;
    bool likelyJk;
};
struct JkData {
    bool valid;
    uint32_t updatedMs, sequence;
    uint16_t cellMv[32];
    uint32_t enabledMask;
    uint8_t cellCount, soc, soh;
    float voltage, current, power, temp1, temp2, mosTemp, balanceCurrent, remainingAh, capacityAh;
    float minCell, maxCell, deltaCell;
    uint32_t cycles, uptime, errors;
    bool charge, discharge, balancing;
};
struct JkInfo {
    bool valid;
    char model[17], hardware[9], software[9], deviceName[17], serial[17], setupPass[17];
};
struct JkSnapshot {
    JkState state;
    JkProfile profile;
    bool linkUp;
    uint8_t deviceCount;
    JkDevice devices[JK_MAX_DEVICES], selected;
    JkData data;
    JkInfo info;
    char status[72];
    uint32_t revision, badFrames, rxDrops;
};
