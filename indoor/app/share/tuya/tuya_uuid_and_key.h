#ifndef TUYA_UUID_AND_KEY_H_
#define TUYA_UUID_AND_KEY_H_
#include <stdbool.h>
/*****  文件名格式为:xxxx-xx-xx.conf *****/
#define TUYA_UUID_AND_KEY_CONF_PATH "/appconfigs/run/tuya_key/"
/***
**   日期:2022-05-27 08:11:56
**   作者: leo.liu
**   函数作用：判断是否右tuya文档
**   参数说明:
** 返回：
** 	true:可以进入系统，
** 	false:需要重新注册tuya key和uuid
**	在初始化之前先挂在sd到/mnt目录下，并且将xxxx-xx-xx.xls（excel97-2003格式）放在/mnt/tuya_key目录下面
***/
bool tuya_key_and_uuid_init(void);
/***
**   日期:2022-05-27 09:48:37
**   作者: leo.liu
**   函数作用：从xls中读取读取指定的文档
**   参数说明:
***/
bool tuya_key_and_key_xls_register(int index);
/***
**   日期:2022-05-27 16:51:54
**   作者: leo.liu
**   函数作用：读取tuya的uuid和key,读取路径在/etc/config/tuya_key/xxxx-xx-xx.conf
**   参数说明:
***/
bool tuya_uuid_and_key_read(unsigned char *uuid, unsigned char *key);
/***
**   日期:2022-06-16 15:41:19
**   作者: leo.liu
**   函数作用：读取tuya序列号
**   参数说明:
***/
bool tuya_serial_number_get(char *serial);
#endif