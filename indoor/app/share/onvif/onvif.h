#ifndef _ONVIF_H_
#define _ONVIF_H_
#include <stdbool.h>
#include <stdlib.h>
#define XML_FILE_MAX (1024 * 1024)
/****************************************************************
**@日期: 2022-09-16
**@作者: leo.liu
**@功能: 设备发现
**@参数：
*****************************************************************/
bool ipc_camera_search(char ipc_addr[8][32], int *num);
/****************************************************************
**@日期: 2022-09-21
**@作者: leo.liu
**@功能:获取media profile token
*****************************************************************/
bool ipc_profile_token_get(const char *ip, int port, const char *user, const char *password, char profile[8][64], int *profile_num);
/****************************************************************
**@日期: 2022-09-20
**@作者: leo.liu
**@功能:获取设备的rtsp
*****************************************************************/
bool ipc_camera_rtsp_get(const char *ip, int port, const char *user, const char *password, const char *profile_token, char *rstp, int len);
#endif