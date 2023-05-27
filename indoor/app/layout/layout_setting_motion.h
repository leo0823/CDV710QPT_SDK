#ifndef _LAYOUT_SETTING_MOTION_H_
#define _LAYOUT_SETTING_MOTION_H_
#include "common/language.h"

typedef enum
{
        SETTING_MOTION_LANG_ID_USE_MOTION_DETECTION,
        SETTING_MOTION_LANG_ID_SELECT_CAMERA,
        SETTING_MOTION_LANG_ID_STORAGE_FORMAT,
        SETTING_MOTION_LANG_ID_SENSITIVTY_SETTING,
        SETTING_MOTION_LANG_ID_MOTION_DETECTING_SCHEDULE,
        SETTING_MOTION_LANG_ID_LCD_ON_WHEN_MOTION_DETECTED,
        SETTING_MOTION_LANG_ID_SCHEDULE_SETTING,
        SETTING_MOTION_LANG_ID_START,
        SETTING_MOTION_LANG_ID_END,
        SETTING_MOTION_LANG_ID_HIGH,
        SETTING_MOTION_LANG_ID_MIDDLE,
        SETTING_MOTION_LANG_ID_LOW,
        SETTING_MOTION_LANG_ID_TOTAL
} LAYOUT_SETTING_MOTION_LANG_ID;

static const char *layout_setting_motion_language[SETTING_MOTION_LANG_ID_TOTAL][LANGUAGE_ID_TOTAL] =
    {
        {"Use motion detection", "Use motion detection", "Use motion detection"},
        {"Select camera", "Select camera", "Select camera"},
        {"Storage format", "Storage format", "Storage format"},
        {"Sensitivity setting", "Sensitivity setting", "Sensitivity setting"},
        {"Motion detecting schedule", "Motion detecting schedule", "Motion detecting schedule"},
        {"LCD On when motion detected", "LCD On when motion detected", "LCD On when motion detected"},
        {"Schedule setting", "Schedule setting", "Schedule setting"},
        {"Start", "Start", "Start"},
        {"End", "End", "End"},
        {"High", "High", "High", "Sensible", "高", "Hasssiyet", "Duża", "Nejvyšší", "عالي"},
        {"Middle", "Middle", "Middle", "Normal", "中", "Normal", "Normalna", "Normání", "متوسط"},
        {"Low", "Low", "Low", "Insensible", "低", "Etkisiz", "Mała", "Citlivost", "منخفض"},
};

/***
** 日期: 2022-04-26 09:16
** 作者: leo.liu
** 函数作用：获取home页面的字符串资源
** 返回参数说明：年/년 !@
***/
static inline const char *layout_setting_motion_language_get(int id)
{
        return layout_setting_motion_language[id][language_id_get()];
}

#endif