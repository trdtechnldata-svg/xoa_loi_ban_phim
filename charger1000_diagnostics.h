#pragma once
#include <stdint.h>
namespace charger1000 {
enum DiagnosticReason : uint8_t {
    DIAG_NONE, DIAG_QUEUE, DIAG_TASK, DIAG_CAN_RELEASE,
    DIAG_CAN_INSTALL, DIAG_CAN_START, DIAG_CAN_TX, DIAG_CAN_RESTORE
};
struct Diagnostics { uint8_t reason; int32_t code; };
// Only the idle UI or the running worker writes this state. Live drawing uses
// the copied queue snapshot, never this shared state while a job is running.
inline Diagnostics &diagnosticState() { static Diagnostics value = {DIAG_NONE, 0}; return value; }
inline void setDiagnostic(uint8_t reason, int32_t code) { diagnosticState() = {reason, code}; }
inline Diagnostics getDiagnostic() { return diagnosticState(); }
inline void clearDiagnostic() { setDiagnostic(DIAG_NONE, 0); }
inline const char *diagnosticLabel(uint8_t reason) {
    switch(reason) {
        case DIAG_QUEUE: return "QUEUE / RAM";
        case DIAG_TASK: return "TASK / RAM";
        case DIAG_CAN_RELEASE: return "CAN RELEASE";
        case DIAG_CAN_INSTALL: return "CAN INSTALL";
        case DIAG_CAN_START: return "CAN START";
        case DIAG_CAN_TX: return "CAN TX";
        case DIAG_CAN_RESTORE: return "CAN RESTORE";
        default: return "";
    }
}
}
