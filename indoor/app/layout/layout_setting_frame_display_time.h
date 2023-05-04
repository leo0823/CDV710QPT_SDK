#ifndef _SETTING_FRAME_DISPLAY_TIME_H_
#define _SETTING_FRAME_DISPLAY_TIME_H_

#include "common/language.h"

typedef enum
{
        SETTING_FRAME_DISPLAY_TIME_LANG_ID_TIME_DESIGNATION,
        SETTING_FRAME_DISPLAY_TIME_LANG_ID_TOTAL

} LAYOUT_SETTING_FRAME_DISPLAY_TIME_LANG_ID;

static const char *layout_setting_frame_display_time_language[SETTING_FRAME_DISPLAY_TIME_LANG_ID_TOTAL][LANGUAGE_ID_TOTAL] =
    {
        {"Time designation", "Time designation", "Time designation"},
};

/***
** 日期: 2022-04-26 09:16
** 作者: leo.liu
** 函数作用：获取home页面的字符串资源
** 返回参数说明：年/년 !@
***/
static inline const char *layout_setting_frame_display_time_language_get(int id)
{
        return layout_setting_frame_display_time_language[id][language_id_get()];
}
#endif