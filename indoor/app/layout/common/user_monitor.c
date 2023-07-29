
#include "user_monitor.h"
#include "user_data.h"
#include "common/sat_linphone_event.h"
#include "common/lv_common.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "common/sat_ipcamera.h"
static int monitor_channel = -1;
static MON_ENTER_FLAG monitor_enter_flag = MON_ENTER_MANUAL_DOOR_FLAG;

const char *monitor_channel_get_url(int index, bool update)
{
        if (index < 8)
        {
                return network_data_get()->door_device[index].sip_url;
        }
        static char rtsp_uri[128] = {0};
        sprintf(rtsp_uri, "%s %s %s",  network_data_get()->cctv_device[index - 8].rtsp[0].rtsp_url, network_data_get()->cctv_device[index - 8].username, network_data_get()->cctv_device[index - 8].password);
        return rtsp_uri;
}
/***
** 日期: 2022-05-12 11:33
** 作者: leo.liu
** 函数作用：依据房号获取通道
** 返回参数说明：
***/
int monitor_index_get_by_user(const char *user)
{
        for (int i = 0; i < DEVICE_MAX; i++)
        {
                //<sip:010193001011@172.16.0.110>
                if (strstr(user, network_data_get()->door_device[i].sip_url) != NULL)
                {
                        return i;
                }
        }
        return -1;
}
#if 0
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
                        return DEVICE_MAX - 1;
                }
                return monitor_channel - 1;
        }
        else
        {
                if (monitor_channel == 8)
                {
                        return DEVICE_MAX - 1 + 8;
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
                if (monitor_channel == (DEVICE_MAX - 1))
                {
                        return 0;
                }
                return monitor_channel + 1;
        }
        else
        {
                if ((monitor_channel - 8) == (DEVICE_MAX - 1))
                {
                        return 8;
                }
                return monitor_channel + 1;
        }
        return -1;
}
#endif
/***
** 日期: 2022-05-12 11:33
** 作者: leo.liu
** 函数作用：获取上一个有效通道
** 返回参数说明：
***/
int monitor_channel_prev_get(void)
{
        if (is_channel_ipc_camera(monitor_channel) == false)
        {
                for(int i = 1 ; i <= monitor_channel; i ++)
                {
                        int pre_ch = monitor_channel - i < 0? DEVICE_MAX - 1 : monitor_channel - i;
                        if(monitor_valid_channel_check(pre_ch))
                        {
                                return pre_ch;
                        }
                }
                return -1;
        }
        else
        {
                for(int i = 1 ; i <= monitor_channel; i ++)
                {
                        int pre_ch = monitor_channel - i < 8? DEVICE_MAX - 1 : monitor_channel - i;
                        if(monitor_valid_channel_check(pre_ch))
                        {
                                return pre_ch;
                        }
                }
                return -1;
        }
        return -1;
}

/***
** 日期: 2022-05-12 11:33
** 作者: leo.liu
** 函数作用：获取下一个有效通道
** 返回参数说明：
***/
int monitor_channel_next_get(void)
{
        if (is_channel_ipc_camera(monitor_channel) == false)
        {
                for(int i = 1 ; i <= monitor_channel; i ++)
                {
                        int next_ch = monitor_channel + i > 8? 0 : monitor_channel + i;
                        if(monitor_valid_channel_check(next_ch))
                        {
                                return next_ch;
                        }
                }
                return -1;
        }
        else
        {
                for(int i = 1 ; i <= monitor_channel; i ++)
                {
                        int next_ch = monitor_channel + i > 16?  8 : monitor_channel + i;
                        if(monitor_valid_channel_check(next_ch))
                        {
                                return next_ch;
                        }
                }
                return -1;
        }
        return -1;
}
/*获取第一个有效的通道*/
int monitor_door_first_valid_get(bool door_camera)
{
        if(door_camera)
        {
                for (int i = 0; i < DEVICE_MAX; i++)
                {

                        if (network_data_get()->door_device[i].sip_url[0] != '\0')
                        {
                                return i;
                        }
                }
        }
        else
        {
                for (int i = 0; i < DEVICE_MAX; i++)
                {
                        if (network_data_get()->cctv_device[i].rtsp[0].rtsp_url[0] != '\0')
                        {
                                return i + 8;
                        }
                }
        }
        return -1;
}

/*获取最后一个有效通道*/
int monitor_door_last_valid_get(bool door_camera)
{
        if(door_camera)
        {
                for (int i = DEVICE_MAX - 1; i >= 0; i--)
                {
                        if (network_data_get()->door_device[i].sip_url[0] != '\0')
                        {
                                return i;
                        }
                }
        }
        else
        {
                for (int i = DEVICE_MAX - 1; i >= 0; i--)
                {
                        if (network_data_get()->cctv_device[i].rtsp[0].rtsp_url[0] != '\0')
                        {
                                return i + 8;
                        }
                }
        }
        return -1;
}

//获取门口机和CCTV的注册状态
bool monitor_door_registered_status_get(void)
{
        if(monitor_door_first_valid_get(true) == -1 && monitor_door_first_valid_get(false) == -1 )
        {
                return false;
        }
        return true;
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
void monitor_open(bool refresh)
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
                        char uri[128] = {0};
                        sprintf(uri, "%s:5066", monitor_channel_get_url(monitor_channel, true));
                        sat_linphone_call(uri, true, true, NULL);
                }
        }
        //   char url[128] = {0};
        //  sprintf(url, "sip:%s", "172.16.0.131@172.16.0.131")       ;
        //  sat_linphone_call(url, true, true, NULL);
        lv_common_video_mode_enable(refresh);
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
/************************************************************
** 函数说明: 判断通道是否有效
** 作者: xiaoxiao
** 日期: 2023-05-26 08:28:22
** 参数说明:
** 注意事项:
************************************************************/
bool monitor_valid_channel_check(int channel)
{

        //  if (network_data_get()->door_device_count)
        {
                if ((channel == MON_CH_DOOR1) || (channel == MON_CH_DOOR2))
                {

                        if((network_data_get()->door_device[channel].sip_url[0] != 0))
                        {
                                return true;
                        }
                        
                        return false;
                }
        }
        //    if (network_data_get()->cctv_device_count)
        {
                if ((channel >= MON_CH_CCTV1) && (channel <= MON_CH_CCTV8))
                {
                                channel -= 8;
                                if(network_data_get()->cctv_device[channel].rtsp[0].rtsp_url[0] != 0)
                                {
                                        return true;
                                }
                        return false;
                }
        }
        return false;
}

