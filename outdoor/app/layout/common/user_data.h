#ifndef _USER_DATA_H_
#define _USER_DATA_H_
#include "stdbool.h"
#include <time.h>
#define DEVICE_MAX 8
typedef struct
{
        char ip[32];
        char mask[32];
} user_network_info;
typedef struct
{
        char number[128];
        char name[64];
        char password[10];
} network_device_info;

typedef struct
{
        user_network_info network;
        network_device_info device;

        int register_device_count;
        char register_device[DEVICE_MAX][64];
} user_data_info;
/***
** 日期: 2022-05-05 08:47
** 作者: leo.liu
** 函数作用：保存用户数据到flash
** 返回参数说明：
***/
bool user_data_save(void);
/***
** 日期: 2022-05-05 08:47
** 作者: leo.liu
** 函数作用：获取用户数据
** 返回参数说明：
***/
bool user_data_init(void);
/***
** 日期: 2022-05-05 08:47
** 作者: leo.liu
** 函数作用：获取用户数据
** 返回参数说明：
***/
user_data_info *user_data_get(void);
/***
** 日期: 2022-05-05 08:47
** 作者: leo.liu
** 函数作用：恢复默认数据
** 返回参数说明：
***/
void user_data_reset(void);
/***
** 日期: 2022-05-05 08:47
** 作者: leo.liu
** 函数作用：检验数据是否已经存在
** 返回参数说明：
***/
bool detemine_existence_of_the_sip_uri(const char *uri);
/***
** 日期: 2022-05-05 08:47
** 作者: leo.liu
** 函数作用：删除一个sip用户
** 返回参数说明：
***/
bool delete_a_sip_uri(const char *uri);
/***
** 日期: 2022-05-05 08:47
** 作者: leo.liu
** 函数作用：注册一个账号
** 返回参数说明：
***/
bool register_a_sip_uri(const char *uri);
#endif
