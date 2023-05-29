#ifndef _LAYOUT_INTERCOM_CALL_H_
#define _LAYOUT_INTERCOM_CALL_H_

#include "common/language.h"

typedef enum
{
        INTERCOM_LANG_ID_CAll_CHANNEL,
        INTERCOM_LANG_ID_CAll_LOG,
        INTERCOM_LANG_ID_EXTENSION,
        INTERCOM_LANG_ID_GUARD,
        INTERCOM_LANG_ID_INCOMMING_CALL,
        INTERCOM_LANG_ID_OUTCOMING_CALL,
        INTERCOM_LANG_ID_CONNECTED_CALL,
        INTERCOM_LANG_ID_DOOR_CAMERA,
        INTERCOM_LANG_ID_COMMON_TRANCE, 
        INTERCOM_LANG_ID_GUARD_STATION, 
        INTERCOM_LANG_ID_TOTAL,

} LAYOUT_INTERCOM_LANG_ID;

static const char *layout_intercom_language[INTERCOM_LANG_ID_TOTAL][LANGUAGE_ID_TOTAL] =
    {
        {"Call channel", "Call channel", "Call channel"},
        {"Call log", "Call log", "Call log"},
        {"Extension", "Extension", "Extension"},
        {"Guard", "Guard", "Guard"},
        {"Incomming call", "Incomming call", "Incomming call"},
        {"Calling.", "Calling.", "Calling."},
        {"Call connected.", "Call connected.", "Call connected."},
        {"Door camera", "Doro camera", "Door camara"},
        {"Common trance", "Common trance", "Common trance"},
        {"Guard station", "Guard station", "Guard station"},
};

/***
** 日期: 2022-04-26 09:16
** 作者: leo.liu
** 函数作用：获取home页面的字符串资源
** 返回参数说明：年/년 !@
***/
static inline const char *layout_intercom_language_get(int id)
{
        return layout_intercom_language[id][language_id_get()];
}
/*0:空闲，1：call outgoing 2:incomming 3:talk*/
void intercom_call_status_setting(int state);
bool intercom_call_username_setting(const char *user);
#endif