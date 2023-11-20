#ifndef _LAYOUT_MONITOR_H_
#define _LAYOUT_MONITOR_H_
#include <stdbool.h>
bool monitor_doorcamera_call_extern_func(char *arg);
bool monitor_doorcamera_call_inside_func(char *arg);
bool monitor_other_call_busy_inside_func(char *arg);
bool monitor_other_call_busy_extern_func(char *arg);
void layout_monitor_ch_name_set(char *doorname);
#endif
