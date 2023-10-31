#ifndef LAYOUT_IO_SETTING
#define LAYOUT_IO_SETTING
#include "common/sat_ipcamera.h"
typedef struct
{
  char ip_setting_flag;
  struct ipcamera_network network;
  struct ipcamera_info pinfo;

} layout_setting_ipaddress_info;

layout_setting_ipaddress_info *layout_setting_ipaddress_info_get(void);
#endif