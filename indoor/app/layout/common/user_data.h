#ifndef _USER_DATA_H_
#define _USER_DATA_H_
#include "stdbool.h"
#include <time.h>
#define DEVICE_MAX 8
#include "common/sat_ipcamera.h"
typedef struct
{
        bool enable;
        /***** 0:door1 ,1:door2 --- 3:cctv2 *****/
        char select_camera;
        /***** 0:photo 1:video *****/
        char saving_fmt;
        /***** 灵敏度 2：low,1:middle,0:height *****/
        char sensivity;
        /***** 定时器 *****/
        bool timer_en;
        /***** lcd *****/
        bool lcd_en;

        struct tm start;
        struct tm end;
} user_motion_info;

typedef struct
{
        bool key_sound;
        bool ring_mute;
        /***** 1-6 rings *****/
        int door_tone;
        int inter_tone;

        int door_ring_volume;
        int door_talk_volume;
        int inter_ring_volume;
        int inter_talk_volume;

        int buzzer_tone;
        int buzzer_volume;
        int common_entrance_tone;
        int common_entrance_volume;
        int common_entrance_voice;
        int securirty_office_tone;
        int entracne_volume;
        int entrancr_voice;
        int guard_station_volume;
        int guard_station_voice;
        int extension_volume;
        int extension_voice;
        int touch_notification_volume;
        int touch_notification_voice;
} user_audio_info;

typedef struct
{
        int bright;
        int cont;
        int color;
} isp_info;

typedef struct
{
        /***** 0:lcd off 1:open frame *****/
        char standby_mode;
        /**屏幕待机时间设置***/
        int screen_off_time;
        /***** lcd的亮度 *****/
        int lcd_brigtness;

        /***** open frame time:0:always 1:时间段*****/
        char frame_time_en;
        /***** 转换为分钟 （hh：mm）*****/
        int frame_time_start;
        int frame_time_end;

        int wait_display_time;

        /***** 夜间模式 *****/
        bool night_mode;
        int night_time_start;
        int night_time_end;
        /***** 显示列表 0b 11111 低五位表示显示位*****/
        int frame_list;
        /***** 帧背景显示 *****/
        bool frame_background;

        isp_info door1;
        isp_info door2;
        isp_info cctv1;
        isp_info cctv2;
} user_display_info;

typedef struct
{
        /***** 0:english *****/
        char language;
        /***** 0：id1  1：id2 *****/
        char deive_id;
        /***** 0:标准模式，1快速模式 *****/
        char open_the_door;

        /***** door1开锁模式 0:camera locak ,1：digital door lock*****/
        char door1_open_door_mode;
        /***** 1:1lock 2:2lock *****/
        char door2_lock_num;
        /*****  house hold password *****/
        char password[4];
        /*****  common entrance password *****/
        char comm_ent_password[4];
        

} user_etc_info;

typedef struct
{
        bool auto_record;

        int away_alarm_enable_list;//离家警报模式：被监测的传感器列表
        int security_alarm_enable_list;//安全警报模式：被监测的传感器列表

        bool security_alarm_enable;//安全警报模式；0：关闭；1：开启

        bool away_alarm_enable;//离家警报模式；0：关闭；1：开启

        int emergency_mode;//0:手动触发警报 1:安防系统自动触发警报

        int alarm_enable[8];//0不使能，1：NO高电平触发 2：NC低电平触发

        int away_sensor_enable[8];//离家模式下传感器使能状态：只有被使能的传感器才能设置监测状态

        int security_sensor_enable[8];//安全模式下传感器使能状态：只有被使能的传感器才能设置监测状态

        int alarm_trigger[8];//传感器触发列表

        bool alarm_enable_always[2][8];//传感器总是使能：设置了总是使能，对应模式下的传感器总是能被检测（即使没有开启警报检测）


        int away_release_time;//离家释放时间；在点击离家检测使能的按键后，在此期间内，并不会真正的使能离家警报检测

        int away_setting_time;//离家设置时间；在进入离家警报检测以后（离家释放时间过后），在此期间内，检测无效

        bool away_save_photo;//离家模式报警是否拍照

        bool away_auto_record;//离家模式报警是否启动CCTV录像

        bool security_auto_record;//安全模式报警是否启动CCTV录像

} user_alarm_info;

typedef struct
{
        char is_device_init;
        char time_automatically;

        char auto_record_mode; // 0:off,1:video,2:photo;

        bool wifi_enable;

        user_motion_info motion;

        user_audio_info audio;

        user_display_info display;

        user_etc_info etc;

        user_alarm_info alarm;

        char system_mode; // 0xFF 高4位 0：单系统，1:服务型。低4位表示ID号
        char mastar_wallpad_ip[16];//sip server 的IP

        int call_time;

        int always_monitoring;
        bool last_call_new;
} user_data_info;

bool user_data_save(void);
bool user_data_init(void);
user_data_info *user_data_get(void);
void user_data_reset(void);

/*************************************************************************************************************************************************
*******************************											                                                                                              *******************************
*******************************					                                                        楚河汉界					                             *******************************
*******************************											                                                                                              *******************************
*************************************************************************************************************************************************/

typedef struct
{
        char sip_user[32];
        char ip[32];
        char mask[32];


        struct ipcamera_info door_device[DEVICE_MAX];

        struct ipcamera_info cctv_device[DEVICE_MAX];

} user_network_info;

bool network_data_save(void);
bool network_data_init(void);
user_network_info *network_data_get(void);
void network_data_reset(void);
bool network_device_sort(void);

#endif
