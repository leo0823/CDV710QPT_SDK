
#include "user_monitor.h"
#include "user_data.h"
#include "common/sat_linphone_event.h"
#include "common/lv_common.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
static int monitor_channel = -1;
static MON_ENTER_FLAG monitor_enter_flag = MON_ENTER_MANUAL_DOOR_FLAG;

/***
** 日期: 2022-05-12 11:33
** 作者: leo.liu
** 函数作用：获取监控通道的地址
** 返回参数说明：index < 8门口机，>= 8 CCTV
***/
const char *monitor_channel_get_url(int index, bool update)
{
        if (index < 8)
        {
                if (index >= network_data_get()->door_device_count)
                {
                        return NULL;
                }

                static char url[128] = {0};
                memset(url, 0, sizeof(url));
                if (update == true)
                {
                        int reslut = user_network_user_update((unsigned char *)network_data_get()->sip_user, &(network_data_get()->door_device[index]), 300);
                        if (reslut == 1)
                        {
                                network_data_save();
                        }
                }
                sprintf(url, "%s/%s", network_data_get()->door_device[index].user, network_data_get()->door_device[index].password);
                return url;
        }

        index -= 8;
        if (index < network_data_get()->cctv_device_count)
        {
                return network_data_get()->cctv_device[index].user;
        }

        return NULL;
}
/***
** 日期: 2022-05-12 11:33
** 作者: leo.liu
** 函数作用：依据房号获取通道
** 返回参数说明：
***/
int monitor_index_get_by_user(const char *user)
{
        for (int i = 0; i < network_data_get()->door_device_count; i++)
        {
                //<sip:010193001011@172.16.0.110>
                if (strncmp(network_data_get()->door_device[i].user, user, 12) == 0)
                {
                        if (strcmp(network_data_get()->door_device[i].user, user))
                        {
                                int reslut = user_network_user_update((unsigned char *)network_data_get()->sip_user, &(network_data_get()->door_device[i]), 300);
                                if (reslut == 1)
                                {
                                        network_data_save();
                                }
                        }
                        //   SAT_DEBUG("user:%s====%s ====index:%d  ====>>channel:%d",user,user_data_get()->door_device[i].user,i,door_channel_group[i]);
                        return i;
                }
        }
        return -1;
}

/***
** 日期: 2022-05-12 11:33
** 作者: leo.liu
** 函数作用：获取上一个通道
** 返回参数说明：
***/
int monitor_channel_prev_get(void)
{
        if (is_channel_ipc_camera(monitor_channel) == false)
        {
                if (monitor_channel == 0)
                {
                        return network_data_get()->door_device_count - 1;
                }
                return monitor_channel - 1;
        }
        else
        {
                if (monitor_channel == 8)
                {
                        return network_data_get()->cctv_device_count - 1 + 8;
                }
                return monitor_channel - 1;
        }
        return -1;
}
/***
** 日期: 2022-05-12 11:33
** 作者: leo.liu
** 函数作用：获取下一个通道
** 返回参数说明：
***/
int monitor_channel_next_get(void)
{
        if (is_channel_ipc_camera(monitor_channel) == false)
        {
                if (monitor_channel == (network_data_get()->door_device_count - 1))
                {
                        return 0;
                }
                return monitor_channel + 1;
        }
        else
        {
                if ((monitor_channel - 8) == (network_data_get()->cctv_device_count - 1))
                {
                        return 8;
                }
                return monitor_channel + 1;
        }
        return -1;
}
/***
** 日期: 2022-05-12 11:33
** 作者: leo.liu
** 函数作用：获取监控通道
** 返回参数说明：
***/
int monitor_channel_get(void)
{
        return monitor_channel;
}

/***********************************************
** 作者: leo.liu
** 日期: 2022-12-28 8:37:5
** 说明: 设置通道
***********************************************/
void monitor_channel_set(int ch)
{
        monitor_channel = ch;
}

/***********************************************
** 作者: leo.liu
** 日期: 2022-12-28 9:43:34
** 说明: 进入监控标志
***********************************************/
void monitor_enter_flag_set(MON_ENTER_FLAG flag)
{
        monitor_enter_flag = flag;
}

/***********************************************
** 作者: leo.liu
** 日期: 2022-12-28 9:44:13
** 说明: 获取进入监控标志
***********************************************/
MON_ENTER_FLAG monitor_enter_flag_get(void)
{
        return monitor_enter_flag;
}
/***********************************************
** 作者: leo.liu
** 日期: 2022-12-28 9:44:13
** 说明: 开启监控
***********************************************/
static void monitor_reset(void)
{
        sat_linphone_ipcamera_stop();
        sat_linphone_handup(0xFF);
}
void monitor_open(void)
{
        if ((monitor_enter_flag == MON_ENTER_MANUAL_DOOR_FLAG) || (monitor_enter_flag == MON_ENTER_MANUAL_CCTV_FLAG))
        {
                monitor_reset();
                usleep(10 * 1000);
                if (is_channel_ipc_camera(monitor_channel_get()) == true)
                {
                        sat_linphone_ipcamera_start(monitor_channel_get_url(monitor_channel, true));
                }
                else
                {
                        char url[128] = {0};
                        sprintf(url, "sip:%s", monitor_channel_get_url(monitor_channel, true));
                        sat_linphone_call(url, true, true, user_linphone_local_multicast_get());
                }
        }
        //   char url[128] = {0};
        //  sprintf(url, "sip:%s", "172.16.0.131@172.16.0.131")       ;
        //  sat_linphone_call(url, true, true, NULL);
        lv_common_video_mode_enable(true);
}
/***********************************************
** 作者: leo.liu
** 日期: 2022-12-28 9:44:13
** 说明:关闭监控
***********************************************/
void monitor_close(void)
{
        monitor_reset();
        lv_common_video_mode_enable(false);
}
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
