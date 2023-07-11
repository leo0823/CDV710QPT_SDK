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
        sat_linphone_audio_play_volume_set(100);
        sat_linphone_audio_play_start(RESOURCE_RING_PATH "touch.mp3", 100); // touch.wav
        return true;
        }

/***********************************************
** 作者: leo.liu
** 日期: 2022-12-26 16:48:12
** 说明: 播放门口机的音效
***********************************************/
bool ring_door_call_play(void)
{
        
        char cmd[128] = {0};
        memset(cmd, 0, sizeof(cmd));
        sat_linphone_audio_play_volume_set(user_data_get()->audio.door_ring_volume);
        sprintf(cmd, RESOURCE_RING_PATH "sound%d.mp3", user_data_get()->audio.door_tone);
        return sat_linphone_audio_play_start(cmd, 100);
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
        sprintf(cmd, RESOURCE_RING_PATH "open.mp3");
        return sat_linphone_audio_play_start(cmd, 100);
}
/***********************************************
** 作者: leo.liu
** 日期: 2022-12-26 16:48:12
** 说明:intercom 铃声
***********************************************/
bool ring_intercom_play(void)
{
        char cmd[128] = {0};
        memset(cmd, 0, sizeof(cmd));
        sat_linphone_audio_play_volume_set(user_data_get()->audio.inter_tone);
        sprintf(cmd, RESOURCE_RING_PATH "sound%d.mp3", user_data_get()->audio.inter_tone);
        return sat_linphone_audio_play_start(cmd, 100);
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
        sat_linphone_audio_play_volume_set(100);
        sat_linphone_audio_play_start(RESOURCE_RING_PATH"alarm.mp3", 100);
        return true;

}

/************************************************************
** 函数说明: 播放蜂鸣器报警
** 作者: xiaoxiao
** 日期: 2023-07-05 11:19:41
** 参数说明: 
** 注意事项: 
************************************************************/
bool ring_buzzer_play(void)
{
        char cmd[128] = {0};
        memset(cmd, 0, sizeof(cmd));
        sat_linphone_audio_play_volume_set(user_data_get()->audio.buzzer_volume);
        sprintf(cmd, RESOURCE_RING_PATH "sound%d.mp3", user_data_get()->audio.buzzer_tone);
        return sat_linphone_audio_play_start(cmd, 100);
        // sat_linphone_audio_play_start(RESOURCE_RING_PATH "touch.mp3", 100); // touch.wav
        // return true;
}