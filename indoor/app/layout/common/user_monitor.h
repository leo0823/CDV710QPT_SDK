#ifndef _USER_MONITOR_H_
#define _USER_MONITOR_H_
#include "stdbool.h"
#include "user_network.h"
#define is_channel_ipc_camera(ch) (((ch) >= 8) ? true : false)

#define MON_CH_DOOR1 0
#define MON_CH_DOOR2 1

#define MON_CH_CCTV1 8
#define MON_CH_CCTV2 9
typedef enum
{
        MON_ENTER_CALL_FLAG,
        MON_ENTER_MANUAL_DOOR_FLAG,
        MON_ENTER_MANUAL_CCTV_FLAG
} MON_ENTER_FLAG;
/***
** 日期: 2022-05-12 11:33
** 作者: leo.liu
** 函数作用：获取监控通道的地址
** 返回参数说明：
***/
const char *monitor_channel_get_url(int index,bool update);
/***
** 日期: 2022-05-12 11:33
** 作者: leo.liu
** 函数作用：依据房号获取通道
** 返回参数说明：
***/
int monitor_index_get_by_user(const char *number);
/***
** 日期: 2022-05-12 11:33
** 作者: leo.liu
** 函数作用：获取监控通道对应的索引
** 返回参数说明：
***/
int monitor_channel_prev_get(void);
/***
** 日期: 2022-05-12 11:33
** 作者: leo.liu
** 函数作用：获取下一个通道
** 返回参数说明：
***/
int monitor_channel_next_get(void);
/***
** 日期: 2022-05-12 11:33
** 作者: leo.liu
** 函数作用：获取监控通道
** 返回参数说明：
***/
int monitor_channel_get(void);
/***********************************************
** 作者: leo.liu
** 日期: 2022-12-28 8:37:5
** 说明: 设置通道
***********************************************/
void monitor_channel_set(int ch);
/***********************************************
** 作者: leo.liu
** 日期: 2022-12-28 9:43:34
** 说明: 进入监控标志
***********************************************/
void monitor_enter_flag_set(MON_ENTER_FLAG flag);
/***********************************************
** 作者: leo.liu
** 日期: 2022-12-28 9:44:13
** 说明:关闭监控
***********************************************/
void monitor_close(void);
/***********************************************
** 作者: leo.liu
** 日期: 2022-12-28 9:44:13
** 说明: 开启监控
***********************************************/
void monitor_open(bool refresh);
/***********************************************
** 作者: leo.liu
** 日期: 2022-12-28 9:44:13
** 说明: 获取进入监控标志
***********************************************/
MON_ENTER_FLAG monitor_enter_flag_get(void);
/***********************************************
** 作者: leo.liu
** 日期: 2022-12-28 9:44:13
** 说明: 获取门口机信息
** 010.001.001.011
BYTE1. 010(固定部分).
                BYTE2. 001 -> 0x01
                                bit[7]=0:
                                bit[6:0] 栋号

                                bit[7]=1:
                                        分机(门口机/室内分机)
                                        bit[6:5]=00:室内分机
                                        bit[6:5]=10:户外机)

                BYTE3. 001 楼层号
                BYTE4. 001 百分位和十分位 - 房号
                           个位 -BYTE2 bit[7]=0
                                                1:室内机
                                                3:Gateway IP system
                                                7:Lobby IP system
                                                9:Guard Phone IP system
                                                5:KIOSK IP system
                                   -BYTE2 bit[7]=1
                                                个位分机ID号
***********************************************/
#endif