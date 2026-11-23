#include <stdbool.h>
#include "actions.h"

lv_event_t g_eez_event = {};
bool g_eez_event_is_available = false;

void action_su_kien_tong(lv_event_t *e)
{
    g_eez_event = *e;
    g_eez_event_is_available = true;
}
void action_mo_toc_main(lv_event_t *e)
{
    g_eez_event = *e;
    g_eez_event_is_available = true;
}
void action_mo_toc_tung_xe(lv_event_t *e)
{
    g_eez_event = *e;
    g_eez_event_is_available = true;
}