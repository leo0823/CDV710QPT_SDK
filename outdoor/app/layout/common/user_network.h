

#ifndef _USER_NETWORK_H_
#define _USER_NETWORK_H_
#include <stdlib.h>
#include <stdbool.h>
#include "user_data.h"

/***********************************************
** 作者: leo.liu
** 日期: 2023-1-5 17:13:48
** 说明: 用户网络处理
***********************************************/
void user_network_init(void);

/***********************************************
** 作者: leo.liu
** 日期: 2023-1-5 15:21:6
** 说明: 获取组播IP地址
***********************************************/
char *user_linphone_local_multicast_get(void);
/***********************************************
** 作者: leo.liu
** 日期: 2023-1-7 14:46:50
** 说明: 查询当前IP下的房号是否在线
***********************************************/
int user_network_device_online(const unsigned char *loc_number, network_device_info *device_info, int timeout);
/***********************************************
** 作者: leo.liu
** 日期: 2023-1-7 14:46:50
** device_type:1 indoor,2 :outdoor
***********************************************/
bool user_network_device_query(unsigned char *user, int device_type, network_device_info *device_info, int max_device, int *device_count, bool force);
/***********************************************
** 作者: leo.liu
** 日期: 2023-1-7 14:46:50
** 说明: 更新房号的IP 返回0:无需更新，1,更新成功，-1,更新失败
***********************************************/
int user_network_user_update(const unsigned char *loc_number, network_device_info *device_info, int timeout);
#endif
