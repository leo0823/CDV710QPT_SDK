

#ifndef _USER_NETWORK_H_
#define _USER_NETWORK_H_
#include <stdlib.h>
#include <stdbool.h>
#include "common/user_data.h"

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
** 日期: 2022-12-9 13:53:54
** 说明: 先开启udhcpc获取IP,失败后通过保存的设置IP，
如果没有IP，通过设置的房号默认分配IP
***********************************************/
void automatic_number_setting_deault_ip_and_netmask(void);
/***********************************************
** 作者: leo.liu
** 日期: 2023-1-7 14:46:50
** 说明: 修改门口机的信息
***********************************************/
bool user_network_device_version_get(const char *number, const char *ip, char *recv_buf, int recv_len, int timeout);
/***********************************************
** 作者: leo.liu
** 日期: 2023-1-7 14:46:50
** 说明: 修改门口机设备密码
***********************************************/
int user_network_device_password_modiy(const char *ip, const char *old_password, const char *new_password, int timeout);
/***********************************************
** 作者: leo.liu
** 日期: 2023-1-7 14:46:50
** 说明: 修改门口机设备名称
***********************************************/
bool user_network_device_name_modiy(const char *ip, const char *password, const char *register_user, const char *new_name, int timeout);

#endif
