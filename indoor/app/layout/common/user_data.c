
#include "user_data.h"

#include <stdbool.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include "stdio.h"
#include "stdlib.h"

#include "common/sat_user_common.h"

#define USER_DATA_PATH "/app/data/user_data.cfg"
#define NETWORK_DATA_PATH "/app/data/network_data.cfg"

static user_data_info user_data =
    {
        0
    };

static const user_data_info user_data_default =
    {
        .is_device_init = 0,
        .auto_record_mode = 0,
        .wifi_enable = true,
        .motion = {
            .enable = false,
            .select_camera = 1,
            .saving_fmt = 0,
            .sensivity = 1,
            .timer_en = false,
            .lcd_en = false,
            .start = {
                .tm_year = 2023,
                .tm_mon = 1,
                .tm_mday = 1,
                .tm_hour = 0,
                .tm_min = 0,
                .tm_sec = 0},
            .end = {.tm_year = 2023, .tm_mon = 1, .tm_mday = 1, .tm_hour = 0, .tm_min = 0, .tm_sec = 0}},
        .audio = {
            .key_sound = true,
            .ring_mute = false,
            .door1_tone = 1,
            .door2_tone = 2,
            .inter_tone = 3,
            .door_ring_volume = 2,
            .door_talk_volume = 2,
            .inter_ring_volume = 2,
            .inter_talk_volume = 2,
            
            .buzzer = 1,
            .front_door = 1,
            .common_entrance = 1,
            .securirty_office = 1,
            .securirty_office = 1,

            .entracne_volume = 1,
            .entrancr_voice = 1,
            .common_entrance_volume = 1,
            .common_entrance_voice = 1,
            .guard_station_volume = 1,
            .guard_station_voice = 1,
            .extension_volume = 1,
            .extension_voice = 1,
            .touch_notification_volume = 1,
            .touch_notification_voice = 1,
        },

        .display = {
            .standby_mode = 0,
            .screen_off_time = 30,
            .lcd_brigtness = 100,
            .frame_time_en = 0,
            .frame_time_start = 0,
            .frame_time_end = 0,
            .night_mode = false,
            .night_time_start = 0,
            .night_time_end = 0,
            .frame_list = 0x00,
            .frame_background = false,
            .door1 = {.bright = 10, .cont = 10, .color = 10},
            .door2 = {.bright = 10, .cont = 10, .color = 10},
            .cctv1 = {.bright = 10, .cont = 10, .color = 10},
            .cctv2 = {.bright = 10, .cont = 10, .color = 10},

        },
        .etc = {
            .language = 0,
            .deive_id = 0,
            .open_the_door = 0,
            .door1_open_door_mode = 0,
            .door2_lock_num = 1,
            .password = {"1234"},
            .comm_ent_password = {"1234"},
        },
        .alarm = {
        .auto_record = false,
        .away_alarm_enable_list = 0x00,//离家设防列表
        .security_alarm_enable_list = 0x00,//安全设防列表
        .away_alarm_enable = false,//离家设防使能状态
        .security_alarm_enable = false,//安全设防状态显示
        .emergency_mode = 0,//0:手动触发警报 1:安防系统自动触发警报

        .alarm_enable[0] = 0,//0不使能，1：NC低电平触发2：NO高电平触发
        .alarm_enable[1] = 0,
        .alarm_enable[2] = 0,
        .alarm_enable[3] = 0,
        .alarm_enable[4] = 0,
        .alarm_enable[5] = 0,
        .alarm_enable[6] = 0,
        .alarm_enable[7] = 0,

        .alarm_trigger[0] = 0,//0非触发状态，1触发状态
        .alarm_trigger[1] = 0,
        .alarm_trigger[2] = 0,
        .alarm_trigger[3] = 0,
        .alarm_trigger[4] = 0,
        .alarm_trigger[5] = 0,
        .alarm_trigger[6] = 0,
        .alarm_trigger[7] = 0,
        .alarm_enable_always[0][0] = false,
        .alarm_enable_always[0][1] = false,
        .alarm_enable_always[0][2] = false,
        .alarm_enable_always[0][3] = false,
        .alarm_enable_always[0][4] = false,
        .alarm_enable_always[0][5] = false,
        .alarm_enable_always[0][6] = false,
        .alarm_enable_always[0][7] = false,
        .alarm_enable_always[1][0] = false,
        .alarm_enable_always[1][1] = false,
        .alarm_enable_always[1][2] = false,
        .alarm_enable_always[1][3] = false,
        .alarm_enable_always[1][4] = false,
        .alarm_enable_always[1][5] = false,
        .alarm_enable_always[1][6] = false,
        .alarm_enable_always[1][7] = false,
        .away_setting_time = 1,
        .away_release_time = 30,
        
        .away_auto_record = false,
        .security_auto_record = false,
        
        },
        .system_mode = 0,
        .time_automatically = 1,
        .call_time = 1,
        .always_monitoring = 0,
        .last_call_new = false,

};
// {"010193001012@172.16.0.104", "010193001013@172.16.0.104", "010193001014@172.16.0.185", "010193001015@172.16.0.104", "010193001016@172.16.0.104", "010193001017@172.16.0.104", "010193001018@172.16.0.104"},

bool user_data_save(void)
{
        int fd = open(USER_DATA_PATH, O_WRONLY | O_CREAT);

        if (fd < 0)
        {
                printf("write open %s fail \n", USER_DATA_PATH);
                return false;
        }

        write(fd, &user_data, sizeof(user_data_info));

        close(fd);
        system("sync");
        return true;
}

#define user_data_check_range_out(cur, min, max)                                   \
        if ((user_##data.cur < min) || (user_##data.cur > max))                    \
        {                                                                          \
                printf("user data error %d(%d,%d) \n", user_##data.cur, min, max); \
                user_##data.cur = user_##data##_default.cur;                       \
        }

#define user_data_motion_check_range_out(x, min, max) user_data_check_range_out(motion.x, min, max)

#define user_data_audio_check_range_out(x, min, max) user_data_check_range_out(audio.x, min, max)

#define user_data_display_check_range_out(x, min, max) user_data_check_range_out(display.x, min, max)

#define user_data_etc_check_range_out(x, min, max) user_data_check_range_out(etc.x, min, max)

#define user_data_alarm_check_range_out(x, min, max) user_data_check_range_out(alarm.x, min, max)

/***
** 日期: 2022-05-05 08:47
** 作者: leo.liu
** 函数作用：检验数据是否合法
** 返回参数说明：
***/
static void user_data_check_valid(void)
{
        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-1-12 14:35:9
        ** 说明: 初始值设置
        ***********************************************/
        user_data_check_range_out(is_device_init, 0, 1);

        /***** 自动记录模式 *****/
        user_data_check_range_out(auto_record_mode, 0, 2);
        user_data_check_range_out(wifi_enable, 0, 1);

        /***** 移动侦测 *****/
        user_data_motion_check_range_out(enable, 0, 1);
        user_data_motion_check_range_out(select_camera, 0, 15);
        user_data_motion_check_range_out(saving_fmt, 0, 1);
        user_data_motion_check_range_out(sensivity, 0, 2);
        user_data_motion_check_range_out(timer_en, 0, 1);
        user_data_motion_check_range_out(lcd_en, 0, 1);

        user_data_motion_check_range_out(start.tm_year, 2021, 2037);
        user_data_motion_check_range_out(start.tm_mon, 1, 12);
        user_data_motion_check_range_out(start.tm_mday, 1, 31);
        user_data_motion_check_range_out(start.tm_hour, 0, 23);
        user_data_motion_check_range_out(start.tm_min, 0, 59);
        user_data_motion_check_range_out(start.tm_sec, 0, 59);

        user_data_motion_check_range_out(end.tm_year, 2021, 2037);
        user_data_motion_check_range_out(end.tm_mon, 1, 12);
        user_data_motion_check_range_out(end.tm_mday, 1, 31);
        user_data_motion_check_range_out(end.tm_hour, 0, 23);
        user_data_motion_check_range_out(end.tm_min, 0, 59);
        user_data_motion_check_range_out(end.tm_sec, 0, 59);

        /***** audio *****/
        user_data_audio_check_range_out(key_sound, 0, 1);
        user_data_audio_check_range_out(ring_mute, 0, 1);
        user_data_audio_check_range_out(door1_tone, 1, 6);
        user_data_audio_check_range_out(door2_tone, 1, 6);
        user_data_audio_check_range_out(inter_tone, 1, 6);

         user_data_audio_check_range_out(buzzer, 1, 6);
         user_data_audio_check_range_out(front_door, 1, 6);
         user_data_audio_check_range_out(common_entrance, 1, 6);
         user_data_audio_check_range_out(securirty_office, 1, 6);
         user_data_audio_check_range_out(extension, 1, 6);

        user_data_audio_check_range_out(door_ring_volume, 0, 3);
        user_data_audio_check_range_out(inter_ring_volume, 0, 3);

        user_data_audio_check_range_out(door_talk_volume, 1, 3);
        user_data_audio_check_range_out(inter_talk_volume, 1, 3);

       

        /***** display *****/
        user_data_display_check_range_out(standby_mode, 0, 1);
        user_data_display_check_range_out(lcd_brigtness, 1, 100);
        user_data_display_check_range_out(frame_time_en, 0, 1);
        user_data_display_check_range_out(frame_time_start, 0, 1440);
        user_data_display_check_range_out(screen_off_time, 15, 180);
        user_data_display_check_range_out(frame_time_end, 0, 1440);
        user_data_display_check_range_out(night_mode, 0, 1);
        user_data_display_check_range_out(night_time_start, 0, 1440);
        user_data_display_check_range_out(night_time_end, 0, 1440);

        user_data_display_check_range_out(frame_list, 0, 0x1F);
        user_data_display_check_range_out(frame_background, 0, 1);

        user_data_display_check_range_out(door1.bright, 0, 20);
        user_data_display_check_range_out(door1.cont, 0, 20);
        user_data_display_check_range_out(door1.color, 0, 20);

        user_data_display_check_range_out(door2.bright, 0, 20);
        user_data_display_check_range_out(door2.cont, 0, 20);
        user_data_display_check_range_out(door2.color, 0, 20);

        user_data_display_check_range_out(cctv1.bright, 0, 20);
        user_data_display_check_range_out(cctv1.cont, 0, 20);
        user_data_display_check_range_out(cctv1.color, 0, 20);

        user_data_display_check_range_out(cctv2.bright, 0, 20);
        user_data_display_check_range_out(cctv2.cont, 0, 20);
        user_data_display_check_range_out(cctv2.color, 0, 20);

        /***** etc *****/
        user_data_etc_check_range_out(language, 0, 9);
        user_data_etc_check_range_out(deive_id, 0, 3);
        user_data_etc_check_range_out(open_the_door, 0, 1);
        user_data_etc_check_range_out(door1_open_door_mode, 0, 1);
        user_data_etc_check_range_out(door2_lock_num, 1, 2);
        user_data_etc_check_range_out(password[0], '0', '9');
        user_data_etc_check_range_out(password[1], '0', '9');
        user_data_etc_check_range_out(password[2], '0', '9');
        user_data_etc_check_range_out(password[3], '0', '9');

        /*****	alarm *****/
        user_data_alarm_check_range_out(auto_record, 0, 1);
        user_data_alarm_check_range_out(away_alarm_enable, 0, 1);
        user_data_alarm_check_range_out(security_alarm_enable, 0, 1);
        user_data_alarm_check_range_out(emergency_mode, 0, 1);

        user_data_alarm_check_range_out(away_alarm_enable_list, 0, 0x7f);
        user_data_alarm_check_range_out(security_alarm_enable_list, 0,0x7f);
        user_data_alarm_check_range_out(alarm_enable[0], 0, 2);
        user_data_alarm_check_range_out(alarm_trigger[0], 0, 1);
        user_data_alarm_check_range_out(alarm_enable[1], 0, 2);
        user_data_alarm_check_range_out(alarm_trigger[1], 0, 1);
        user_data_alarm_check_range_out(alarm_enable[2], 0, 2);
        user_data_alarm_check_range_out(alarm_trigger[2], 0, 1);
        user_data_alarm_check_range_out(alarm_enable[3], 0, 2);
        user_data_alarm_check_range_out(alarm_trigger[3], 0, 1);
        user_data_alarm_check_range_out(alarm_enable[4], 0, 2);
        user_data_alarm_check_range_out(alarm_trigger[4], 0, 1);
        user_data_alarm_check_range_out(alarm_enable[5], 0, 2);
        user_data_alarm_check_range_out(alarm_trigger[5], 0, 1);
        user_data_alarm_check_range_out(alarm_enable[6], 0, 2);
        user_data_alarm_check_range_out(alarm_trigger[6], 0, 1);
        user_data_alarm_check_range_out(alarm_enable[7], 0, 2);
        user_data_alarm_check_range_out(alarm_trigger[7], 0, 1);
        user_data_alarm_check_range_out(alarm_enable_always[0][0], 0, 1);
        user_data_alarm_check_range_out(alarm_enable_always[0][1], 0, 1);
        user_data_alarm_check_range_out(alarm_enable_always[0][2], 0, 1);
        user_data_alarm_check_range_out(alarm_enable_always[0][3], 0, 1);
        user_data_alarm_check_range_out(alarm_enable_always[0][4], 0, 1);
        user_data_alarm_check_range_out(alarm_enable_always[0][5], 0, 1);
        user_data_alarm_check_range_out(alarm_enable_always[0][6], 0, 1);
        user_data_alarm_check_range_out(alarm_enable_always[0][7], 0, 1);
        user_data_alarm_check_range_out(alarm_enable_always[1][0], 0, 1);
        user_data_alarm_check_range_out(alarm_enable_always[1][1], 0, 1);
        user_data_alarm_check_range_out(alarm_enable_always[1][2], 0, 1);
        user_data_alarm_check_range_out(alarm_enable_always[1][3], 0, 1);
        user_data_alarm_check_range_out(alarm_enable_always[1][4], 0, 1);
        user_data_alarm_check_range_out(alarm_enable_always[1][5], 0, 1);
        user_data_alarm_check_range_out(alarm_enable_always[1][6], 0, 1);
        user_data_alarm_check_range_out(alarm_enable_always[1][7], 0, 1);

        user_data_alarm_check_range_out(away_setting_time, 1, 3);
        user_data_alarm_check_range_out(away_release_time, 30, 90);
        user_data_alarm_check_range_out(away_auto_record, 0, 1);
        user_data_alarm_check_range_out(security_auto_record, 0, 1);
        user_data_check_range_out(system_mode, 0, 1);
        user_data_check_range_out(time_automatically, 0, 1);
        user_data_check_range_out(call_time, 1, 3);
}

bool user_data_init(void)
{
        int fd = open(USER_DATA_PATH, O_RDONLY);

        if (fd < 0)
        {
                printf("read open %s fail \n", USER_DATA_PATH);
                user_data = user_data_default;
                return false;
        }

        read(fd, &user_data, sizeof(user_data_info));

        close(fd);
        user_data_check_valid();
        return true;
}

user_data_info *user_data_get(void)
{
        return &user_data;
}

void user_data_reset(void)
{
        char language = user_data.etc.language;

        user_data = user_data_default;
        user_data.etc.language = language;
        user_data_save();
        system("sync");
}
/*************************************************************************************************************************************************
*******************************											                                                                                              *******************************
*******************************					                                                        楚河汉界					                             *******************************
*******************************											                                                                                              *******************************
*************************************************************************************************************************************************/
static user_network_info network_data = {0};

static const user_network_info network_data_default = {
    .sip_user = {"010129001011"},
    .ip = {0},
    .mask = {"255.0.0.0"},
    .door_device_count = 0,
    .cctv_device_count = 0,
};

#define network_data_check_range_out(cur, min, max)                                      \
        if ((network_##data.cur < min) || (network_##data.cur > max))                    \
        {                                                                                \
                printf("network data error %d(%d,%d) \n", network_##data.cur, min, max); \
                network_##data.cur = network_##data##_default.cur;                       \
        }

bool network_data_save(void)
{
        int fd = open(NETWORK_DATA_PATH, O_WRONLY | O_CREAT);

        if (fd < 0)
        {
                printf("write open %s fail \n", NETWORK_DATA_PATH);
                return false;
        }

        write(fd, &network_data, sizeof(user_network_info));

        close(fd);
        system("sync");
        return true;
}

static void printf_register_device(void)
{
        SAT_DEBUG("register cont:%d", network_data.door_device_count);
        printf("\n\n#############################################\n");
        for (int i = 0; i < network_data.door_device_count; i++)
        {
                printf("door camera :%d\n", i);
                printf("accout:%s\n", network_data.door_device[i].username);
                printf("password:%s\n", network_data.door_device[i].password);
                printf("ipaddr:%s\n", network_data.door_device[i].ipaddr);
                printf("port:%d\n", network_data.door_device[i].port);
                printf("sip_url:%s\n", network_data.door_device[i].sip_url);
                printf("name:%s\n", network_data.door_device[i].door_name);
                printf("door camera rtsp profile token num%d\n", network_data.door_device[i].profile_token_num);
                for (int j = 0; j < network_data.door_device[i].profile_token_num; j++)
                {
                        printf("---profile token:%s\n", network_data.door_device[i].rtsp[j].profile_token);
                        printf("---rtsp url:%s\n", network_data.door_device[i].rtsp[j].rtsp_url);
                }
        }
        printf("\n");
        for (int i = 0; i < network_data.cctv_device_count; i++)
        {
                printf("CCTV  :%d\n", i);
                printf("accout:%s\n", network_data.cctv_device[i].username);
                printf("password:%s\n", network_data.cctv_device[i].password);
                printf("ipaddr:%s\n", network_data.cctv_device[i].ipaddr);
                printf("port:%d\n", network_data.cctv_device[i].port);
                printf("sip_url:%s\n", network_data.cctv_device[i].sip_url);
                printf("name:%s\n", network_data.cctv_device[i].door_name);
                printf("door camera rtsp profile token num%d\n", network_data.cctv_device[i].profile_token_num);
                for (int j = 0; j < network_data.cctv_device[i].profile_token_num; j++)
                {
                        printf("---profile token:%s\n", network_data.cctv_device[i].rtsp[j].profile_token);
                        printf("---rtsp url:%s\n", network_data.cctv_device[i].rtsp[j].rtsp_url);
                }
        }
        printf("#############################################\n\n");
}
/***
** 日期: 2022-05-05 08:47
** 作者: leo.liu
** 函数作用：检验数据是否合法
** 返回参数说明：
***/
static void network_data_check_valid(void)
{
        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-1-5 14:33:3
         ** 说明: sip
         ***********************************************/
        for (int i = 0; i < strlen(network_data.sip_user); i++)
        {

                network_data_check_range_out(sip_user[i], '0', '9');
        }
        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-1-5 14:33:3
        ** 说明: 本机IP,和掩码
        ***********************************************/
        for (int i = 0; i < strlen(network_data.ip); i++)
        {
                if (network_data.ip[i] != '.')
                {
                        network_data_check_range_out(ip[i], '0', '9');
                        break;
                }
        }
        for (int i = 0; i < strlen(network_data.mask); i++)
        {
                if (network_data.mask[i] != '.')
                {
                        network_data_check_range_out(mask[i], '0', '9');
                        break;
                }
        }
        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-1-10 9:40:52
        ** 说明:	 检测分机IP组
        ***********************************************/
        network_data_check_range_out(door_device_count, 0, DEVICE_MAX);

        network_data_check_range_out(cctv_device_count, 0, DEVICE_MAX);
        printf_register_device();
}

bool network_data_init(void)
{
        int fd = open(NETWORK_DATA_PATH, O_RDONLY);

        if (fd < 0)
        {
                printf("read open %s fail \n", NETWORK_DATA_PATH);
                network_data = network_data_default;
                return false;
        }

        read(fd, &network_data, sizeof(user_network_info));

        close(fd);
        network_data_check_valid();
        network_data_save();
        return true;
}

user_network_info *network_data_get(void)
{
        return &network_data;
}

void network_data_reset(void)
{
        network_data = network_data_default;
        network_data_save();
        system("sync");
}