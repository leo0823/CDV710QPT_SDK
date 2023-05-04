#ifndef _LAYOUT_SETTING_SOUND_H_
#define _LAYOUT_SETTING_SOUND_H_
#include "common/language.h"

typedef enum
{
        SOUND_LANG_ID_VOLUME,
        SOUND_LANG_ID_THE_VOLUME_OF_THE_CALLING,
        SOUND_LANG_ID_BUZZER,
        SOUND_LANG_ID_FRONT_DOOR,
        SOUND_LANG_ID_RINGTONE1,
        SOUND_LANG_ID_RINGTONE2,
        SOUND_LANG_ID_RINGTONE3,
        SOUND_LANG_ID_RINGTONE4,
        SOUND_LANG_ID_RINGTONE5,
        SOUND_LANG_ID_RINGTONE6,
        SOUND_LANG_ID_COMMON_ENTRANCE,
        SOUND_LANG_ID_SECURITY_OFFICE,
        SOUND_LANG_ID_EXTENSION,
        SOUND_LANG_ID_ENTRANCE,
        SOUND_LANG_ID_GUARD_STATION,
        SOUND_LANG_ID_TOUCH_NOTIFICATION,
        SOUND_LANG_ID_TOTAL

} LAYOUT_SETTING_HOME_LANG_ID;

static const char *layout_setting_sound_language[SOUND_LANG_ID_TOTAL][LANGUAGE_ID_TOTAL] =
    {
        {"Volume", "Volume", "Volume"},
        {"The volume of the calling and receiving tone", "The volume of the calling and receiving tone", "The volume of the calling and receiving tone"},
        {"Buzzer", "Buzzer", "Buzzer"},
        {"Front door", "Front door", "Front door"},
        {"Ringtone 1", "Ringtone 1", "Ringtone 1"},
        {"Ringtone 2", "Ringtone 2", "Ringtone 2"},
        {"Ringtone 3", "Ringtone 3", "Ringtone 3"},
        {"Ringtone 4", "Ringtone 4", "Ringtone 4"},
        {"Ringtone 5", "Ringtone 5", "Ringtone 5"},
        {"Ringtone 6", "Ringtone 6", "Ringtone 6"},
        {"Common entrance", "Common entrance", "Common entrance"},
        {"Security office", "Security office", "Security office"},
        {"Extension", "Extension", "Extension"},
        {"Entrance", "Entrance", "Entrance"},
        {"Guard station", "Guard station", "Guard station"},
        {"Touch/notification", "Touch/notification", "Touch/notification"},
};

/***
** 日期: 2022-04-26 09:16
** 作者: leo.liu
** 函数作用：获取home页面的字符串资源
** 返回参数说明：年/년 !@
***/
static inline const char *layout_setting_sound_language_get(int id)
{
        return layout_setting_sound_language[id][language_id_get()];
}

#endif