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
        return sat_linphone_audio_play_start(RESOURCE_RING_PATH "touch.mp3", 100); // touch.wav
                                                                                   // sat_linphone_audio_play_start("/tmp/nfs/CDV810QPT/indoor/app/layout/resource/rings/sound6.mp3",100);
}

/***********************************************
** 作者: leo.liu
** 日期: 2022-12-26 16:48:12
** 说明: 播放门口机1的音效
***********************************************/
bool ring_door1_call_play(void)
{
        char cmd[128] = {0};
        memset(cmd, 0, sizeof(cmd));

        sprintf(cmd, RESOURCE_RING_PATH "sound%d.mp3", user_data_get()->audio.door1_tone);
        return sat_linphone_audio_play_start(cmd, user_data_get()->audio.door_ring_volume);
}

/***********************************************
** 作者: leo.liu
** 日期: 2022-12-26 16:48:12
** 说明: 播放门口机2的音效
***********************************************/
bool ring_door2_call_play(void)
{
        char cmd[128] = {0};
        memset(cmd, 0, sizeof(cmd));

        sprintf(cmd, RESOURCE_RING_PATH "sound%d.mp3", user_data_get()->audio.door2_tone);
        return sat_linphone_audio_play_start(cmd, user_data_get()->audio.door_ring_volume);
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

        sprintf(cmd, RESOURCE_RING_PATH "sound%d.mp3", user_data_get()->audio.inter_tone);
        return sat_linphone_audio_play_start(cmd, 100);
}