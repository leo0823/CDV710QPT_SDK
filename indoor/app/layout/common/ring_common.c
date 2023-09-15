#include "ring_common.h"
#include "unistd.h"
#include "string.h"
#include "stdio.h"
#include "common/sat_linphone_event.h"
#include "common/user_data.h"

/***********************************************
** 作者: leo.liu
** 日期: 2022-12-26 16:48:12
** 说明: 触摸音效播放
***********************************************/
bool ring_touch_play(void)
{
        if(user_data_get()->audio.touch_notification_volume == 0)
        {
                return false;
        }
        sat_linphone_audio_play_volume_set(user_data_get()->audio.touch_notification_volume);
        sat_linphone_audio_play_start(RESOURCE_RING_PATH "keysound/touch.mp3", 1); // touch.wav

        return true;
}

/***********************************************
** 作者: leo.liu
** 日期: 2022-12-26 16:48:12
** 说明: 播放门口机的音效
***********************************************/
bool ring_door_call_play(int index)
{
        if(user_data_get()->audio.entracne_volume == 0)
        {
                return false;
        }
        char cmd[128] = {0};
        memset(cmd, 0, sizeof(cmd));
        sat_linphone_audio_play_volume_set(user_data_get()->audio.entracne_volume);
        sprintf(cmd, RESOURCE_RING_PATH "door_camera/call_door%d.mp3", index);
        return sat_linphone_audio_play_start(cmd, user_data_get()->audio.ring_repeat == 0? 1 : 0xfffff);
}


/***********************************************
** 作者: leo.liu
** 日期: 2022-12-26 16:48:12
** 说明: 开锁铃声
***********************************************/
bool ring_unlock_play(void)
{
        char cmd[128] = {0};
        memset(cmd, 0, sizeof(cmd));
        sat_linphone_audio_play_volume_set(100);
        sprintf(cmd, RESOURCE_RING_PATH "open/open.mp3");
        return sat_linphone_audio_play_start(cmd, 1);
}
/***********************************************
** 作者: leo.liu
** 日期: 2022-12-26 16:48:12
** 说明:intercom 铃声
***********************************************/
bool ring_intercom_play(int index)
{
        if(user_data_get()->audio.extension_volume == 0)
        {
                return false;
        }
        char cmd[128] = {0};
        memset(cmd, 0, sizeof(cmd));
        sat_linphone_audio_play_volume_set(user_data_get()->audio.extension_volume);
        sprintf(cmd, RESOURCE_RING_PATH "extension/extension_call_%d.mp3", index);
        printf("cmd is %s\n",cmd);
        return sat_linphone_audio_play_start(cmd, 1);
}

/************************************************************
** 函数说明: 警报ling
** 作者: xiaoxiao
** 日期: 2023-05-16 11:43:00
** 参数说明: 
** 注意事项: 
************************************************************/
bool ring_alarm_play(void)
{
        // sat_linphone_audio_play_volume_set(100);
        // sat_linphone_audio_play_start(RESOURCE_RING_PATH"alarm/alarm.mp3", 1);
        return true;

}

/************************************************************
** 函数说明: 播放蜂鸣器报警
** 作者: xiaoxiao
** 日期: 2023-07-05 11:19:41
** 参数说明: 
** 注意事项: 
************************************************************/
bool ring_buzzer_play(int index)
{
        if(user_data_get()->audio.buzzer_volume == 0)
        {
                return false;
        }
        char cmd[128] = {0};
        memset(cmd, 0, sizeof(cmd));
        sat_linphone_audio_play_volume_set(user_data_get()->audio.buzzer_volume);
        sprintf(cmd, RESOURCE_RING_PATH "buzzer/buzzer_%d.mp3", index);
        return sat_linphone_audio_play_start(cmd, 1);

}


/************************************************************
** 函数说明: 播放公共入口铃声
** 作者: xiaoxiao
** 日期: 2023-07-05 11:19:41
** 参数说明: 
** 注意事项: 
************************************************************/
bool ring_common_door_play(int index)
{
        if(user_data_get()->audio.common_entrance_volume == 0)
        {
                return false;
        }
        char cmd[128] = {0};
        memset(cmd, 0, sizeof(cmd));
        sat_linphone_audio_play_volume_set(user_data_get()->audio.common_entrance_volume);
        sprintf(cmd, RESOURCE_RING_PATH "common_entrance/Common entrance_%d.mp3", index);
        return sat_linphone_audio_play_start(cmd, 1);

}

/************************************************************
** 函数说明: 播放警卫室call机铃声
** 作者: xiaoxiao
** 日期: 2023-07-05 11:19:41
** 参数说明: 
** 注意事项: 
************************************************************/
bool ring_guard_play(int index)
{
        if(user_data_get()->audio.guard_station_volume == 0)
        {
                return false;
        }
        char cmd[128] = {0};
        memset(cmd, 0, sizeof(cmd));
        sat_linphone_audio_play_volume_set(user_data_get()->audio.guard_station_volume);
        sprintf(cmd, RESOURCE_RING_PATH "security_office/security office_%d.mp3",index );
        return sat_linphone_audio_play_start(cmd, 1);

}

/************************************************************
** 函数说明: 播放繁忙音
** 作者: xiaoxiao
** 日期: 2023-07-05 11:19:41
** 参数说明: 
** 注意事项: 
************************************************************/
bool ring_busy_play(int index)
{
        return false;

}