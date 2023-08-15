#ifndef _SSD20X_SARAD_H_
#define _SSD20X_SARAD_H_
#include <stdbool.h>
/*开启sarad*/
bool sarad_open(void);
/*device 关闭*/
bool sarad_close(void);
/*
device:设备号：
0-2，sarad0~sarad2
*/
float sarad_read(int dev);
#endif