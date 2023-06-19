

#ifndef _MAIN_EVENT_H_
#define _MAIN_EVENT_H_
#include <stdbool.h>
#include "lvgl.h"
#define SAT_VOID

enum
{
        MSG_EVENT_CMD_SD_CHANGE = 0X0000,

        /****************************************************************
        2022-09-21 author:leo.liu 说明:开始，0：拍照完成
        *****************************************************************/
        MSG_EVENT_CMD_SNAPSHORT,

        /****************************************************************
        2022-09-21 author:leo.liu 说明:arg1:开始录制，0：录制完成
        *****************************************************************/
        MSG_EVENT_CMD_RECORD,

        /****************************************************************
        2022-09-21 author:leo.liu 说明:arg1 1:online,arg2:online num
                                                                2:rtsp streadm,arg2:avlid num
        *****************************************************************/
        MSG_EVENT_CMD_IPCAMERA,

        /****************************************************************
        2022-09-21 author:leo.liu 说明:arg1 :0:空闲，1:播放，2:暂停s
        *****************************************************************/
        MSG_EVENT_CMD_VIDEO_PLAY_STATE,

        /****************************************************************
        2022-09-21 author:leo.liu 说明:arg1 :cur,arg2:total
        *****************************************************************/
        MSG_EVENT_CMD_VIDEO_PLAY_DURATION,

        /****************************************************************
        2022-09-21 author:leo.liu 说明:linphone sip 信息
        *****************************************************************/
        MSG_EVENT_CMD_SIP_CMD,
        /****************************************************************
        2022-09-21 author:leo.liu 缩略图显示
        *****************************************************************/
        MSG_EVENT_CMD_THUMB_REFRESH,
        /****************************************************************
       2022-09-21 author:leo.liu AO开启后者关闭
       *****************************************************************/
        MSG_EVENT_CMD_AUDIO_OUTPUT,
        /****************************************************************
         2022-09-21 author:leo.liu ALARM
        *****************************************************************/
        MSG_EVENT_CMD_ALARM,
        /****************************************************************
       2022-09-21 author:leo.liu tuya
      *****************************************************************/
        MSG_EVENT_CMD_TUYA,
        /****************************************************************
         2022-09-21 author:leo.liu motion detection
        *****************************************************************/
        MSG_EVENT_CMD_MOTION_DETECTION,
        /****************************************************************
       2022-09-21 author:leo.liu ring play:arg1:0,start,1:finish
      *****************************************************************/
        MSG_EVENT_CMD_AUDIO_RING_PLAY,
};
typedef enum
{
        TUYA_EVENT_CMD_VIDEO_START,
        TUYA_EVENT_CMD_VIDEO_STOP,
        TUYA_EVENT_CMD_AUDIO_START,
        TUYA_EVENT_CMD_ONLINE,
        TUYA_EVENT_CMD_CH_CHANGE,
        TUYA_EVENT_CMD_MOTION_ENBALE,
        TUYA_EVENT_CMD_DOOR_OPEN,
} TUYA_CMD;
typedef struct
{
        lv_obj_t *srceen;

        void (*enter)(void);

        void (*quit)(void);
} sat_layout_info;

/*
 * @日期: 2022-08-08
 * @作者: leo.liu
 * @功能: 主任务处理
 * @return:
 */
bool sat_mian_task_init(void);

/***
** 日期: 2022-04-25 16:14
** 作者: leo.liu
** 函数作用：创建一个页面
** 返回参数说明：
***/
#define sat_layout_create(x) sat_layout_info layout_##x = {   \
                                 .enter = layout_##x##_enter, \
                                 .quit = layout_##x##_quit};

/***
** 日期: 2022-04-25 16:14
** 作者: leo.liu
** 函数作用：进入此页面的第一个执行的函数
** 返回参数说明：
***/
#define sat_layout_enter(x) layout_##x##_enter(void)

/***
** 日期: 2022-04-25 16:14
** 作者: leo.liu
** 函数作用：退出此页面的最后一个函数
** 返回参数说明：
***/
#define sat_layout_quit(x) layout_##x##_quit(void)

/***
** 日期: 2022-04-25 16:15
** 作者: leo.liu
** 函数作用：页面地址
** 返回参数说明：
***/
#define sat_playout_get(x) (&layout_##x)

/***
** 日期: 2022-04-25 16:15
** 作者: leo.liu
** 函数作用：声明页面
** 返回参数说明：
***/
#define sat_layout_define(x) extern sat_layout_info layout_##x

/***
** 日期: 2022-04-25 16:31
** 作者: leo.liu
** 函数作用：页面跳转
** 返回参数说明：
***/
bool _sat_layout_goto(sat_layout_info *layout, lv_scr_load_anim_t anim);

/***
** 日期: 2022-04-25 16:31
** 作者: leo.liu
** 函数作用：页面跳转
** 返回参数说明：
***/
#define sat_layout_goto(x, a, r)                 \
        _sat_layout_goto(sat_playout_get(x), a); \
        return r;

/***
**	 日期:2022-05-23 13:41:22
**	 作者: leo.liu
**	 函数作用：获取当前页面
**	 参数说明:
***/
const sat_layout_info *sat_cur_layout_get(void);
const sat_layout_info *sat_pre_layout_get(void);
const sat_layout_info *sat_next_layout_get(void);
/***
**	 日期:2022-05-23 13:41:22
**	 作者: leo.liu
**	 函数作用：获取当前页面
**	 参数说明:
***/
lv_obj_t *sat_cur_layout_screen_get(void);
/***
** 日期: 2022-05-12 10:34
** 作者: leo.liu
** 函数作用：发送消息到主线程
** 返回参数说明：
***/
bool sat_msg_send_cmd(unsigned int cmd, unsigned int arg1, unsigned int arg2);

/***********************************************
** 作者: leo.liu
** 日期: 2023-1-5 9:41:41
** 说明: SIP相关信息命令
***********************************************/
bool sat_msg_send_cmd_str(unsigned int cmd, const char *str, int length);

/*
 * @日期: 2022-08-12
 * @作者: leo.liu
 * @功能: sd卡状态处理函数注册
 * @return:
 */
void sd_state_channge_callback_register(void (*callback)(void));

/*
 * @日期: 2022-09-08
 * @作者: leo.liu
 * @注释: bool ,true,开始，false 完成
 */
void snapshot_state_callback_register(void (*callback)(bool ready));

/*
 * @日期: 2022-09-15
 * @作者: leo.liu
 * @注释: bool,true,开始，false 完成
 */
void record_state_callback_register(void (*callback)(bool reday));

/****************************************************************
**@日期: 2022-09-21
**@作者: leo.liu
**@功能:ipcamera相关的注册
*****************************************************************/
void ipcamera_state_callback_register(void (*callback)(unsigned int type, unsigned int num));

/***********************************************
** 作者: leo.liu
** 日期: 2022-10-17 13:39:21
** 说明: 注册视频播放状态变化的事件
***********************************************/
void video_play_state_callback_register(void (*callback)(unsigned int state));

/***********************************************
** 作者: leo.liu
** 日期: 2022-10-17 13:39:55
** 说明: 注册视频播放时长获取变化的事件
***********************************************/
void video_play_duration_callback_register(void (*callback)(unsigned int cur, unsigned int total));

/***********************************************
** 作者: leo.liu
** 日期: 2023-1-5 9:53:56
** 说明: 注册sip信息相关的命令
***********************************************/
void sip_cmd_callback_register(void (*callback)(unsigned char *str));
/***********************************************
** 作者: leo.liu
** 日期: 2023-1-5 9:53:56
** 说明: 缩略图
***********************************************/
void thumb_display_refresh_register(void (*callback)(void));
/***********************************************
** 作者: leo.liu
** 日期: 2023-1-5 9:53:56
** 说明: 音频输出输入函数
***********************************************/
void audio_output_cmd_register(void (*callback)(int arg));
/***********************************************
** 作者: leo.liu
** 日期: 2023-1-5 9:53:56
** 说明: 警报触发输入函数,
** arg1:警报通道号
** arg2:警报触发的当前电压值x100,比如3.32V = 332
***********************************************/
void alarm_sensor_cmd_register(void (*callback)(int arg1, int arg2));
/***********************************************
** 作者: leo.liu
** 日期: 2023-1-5 9:53:56
** 说明: tuya事件注册
***********************************************/
void tuya_event_cmd_register(bool (*callback)(TUYA_CMD cmd, int arg1));
/***********************************************
** 作者: leo.liu
** 日期: 2023-1-5 9:53:56
** 说明: 移动侦测事件处理
***********************************************/
void moiton_detection_event_cmd_register(bool (*callback)(void));
/***********************************************
** 作者: leo.liu
** 日期: 2023-1-5 9:53:56
** 说明:铃声播放处理
***********************************************/
void ring_play_event_cmd_register(bool (*callback)(int arg));
#endif
