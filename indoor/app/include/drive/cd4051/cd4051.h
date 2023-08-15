#ifndef _CD4051_H_
#define _CD4051_H_
#include <stdbool.h>
/*初始化cd4051驱动*/
bool cd4051_drive_init(
    void (*enable_func)(bool),
    float (*read_func)(void),
    void (*ctrl_a_func)(int val),
    void (*ctrl_b_func)(int val),
    void (*ctrl_c_func)(int val));

/*使能/失能cd4051驱动*/
bool cd4051_drive_enable_set(bool en);

/*读取通道的电压值。
返回0xFF，数值读取错误*/
float cd4051_drive_read(int ch);
#endif