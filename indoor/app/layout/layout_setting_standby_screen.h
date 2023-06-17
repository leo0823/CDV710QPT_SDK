#ifndef _SETTING_STANDBY_SCREEN_H_
#define _SETTING_STANDBY_SCREEN_H_
#include "common/language.h"

typedef enum
{
        SETTING_STANDBY_SCREEN_LANG_ID_NOT_USE,
        SETTING_STANDBY_SCREEN_LANG_ID_SCREEN_OFF,
        SETTING_STANDBY_SCREEN_LANG_ID_OPEN_FRAME,
        SETTING_STANDBY_SCREEN_LANG_ID_DISPLAY_TIME,
        SETTING_STANDBY_SCREEN_LANG_ID_ALWAYS,
        SETTING_STANDBY_SCREEN_LANG_ID_TIME_DESIGNATION,
        SETTING_STANDBY_SCREEN_LANG_ID_ITEM_DISPLAY,
        SETTING_STANDBY_SCREEN_LANG_ID_0_ITEM,
        SETTING_STANDBY_SCREEN_LANG_ID_1_ITEM,
        SETTING_STANDBY_SCREEN_LANG_ID_2_ITEM,
        SETTING_STANDBY_SCREEN_LANG_ID_3_ITEM,
        SETTING_STANDBY_SCREEN_LANG_ID_4_ITEM,
        SETTING_STANDBY_SCREEN_LANG_ID_5_ITEM,
        SETTING_STANDBY_SCREEN_LANG_ID_BACKROUND,
        SETTING_STANDBY_SCREEN_LANG_ID_RANDOM_IMAGE,
        SETTING_STANDBY_SCREEN_LANG_ID_BASIC,
        SETTING_STANDBY_SCREEN_LANG_ID_SCREEN_CLEANING_MODE,
        SETTING_STANDBY_SCREEN_LANG_ID_END_TIME,
        SETTING_STANDBY_SCREEN_LANG_ID_NIGHT_MODE,
        SETTING_STANDBY_SCREEN_LANG_ID_USER_NIGHT_MODE,
        SETTING_STANDBY_SCREEN_LANG_ID_ADJUSTS_THE_BRIGHTNESS,
        SETTING_STANDBY_SCREEN_LANG_ID_HOUR,
        SETTING_STANDBY_SCREEN_LANG_ID_CALENDAR,
        SETTING_STANDBY_SCREEN_LANG_ID_RECENTLY_SAVED_VIDEO,
        SETTING_STANDBY_SCREEN_LANG_ID_FRONT_DOOR_VIDEO,
        SETTING_STANDBY_SCREEN_LANG_ID_CCTV_FOOTAGE,
        SETTING_STANDBY_SCREEN_LANG_ID_TOTAL

} LAYOUT_SETTING_STANDBY_SCREEN_LANG_ID;

static const char *layout_setting_standby_screen_language[SETTING_STANDBY_SCREEN_LANG_ID_TOTAL][LANGUAGE_ID_TOTAL] =
    {
        {"Not use", "Not use", "Not use"},
        {"Screen off", "Screen off", "Screen off"},
        {"Open frame", "Open frame", "Open frame"},
        {"Display Time", "Display Time", "Display Time"},
        {"Always", "Always", "Always"},
        {"Time designation","Time designation","Time designation"},
        {"Display item", "Display item", "Display item"},
        {"0 item", "0 item", "0 item"},
        {"1 item", "1 item", "1 item"},
        {"2 item", "2 item", "2 item"},
        {"3 item", "3 item", "3 item"},
        {"4 item", "4 item", "4 item"},
        {"5 item", "5 item", "5 item"},
        {"Background", "Background", "Background"},
        {"Random image", "Random image", "Random image"},
        {"Basic ", "Basic ", "Basic "},
        {"Screen Cleaning mode", "Screen Cleaning mode", "Screen Cleaning mode"},
        {"End time", "End time", "End time"},
        {"Night mode", "Night mode", "Night mode"},
        {"Use night mode", "Use night mode", "Use night mode"},
        {"Adjusts the brightness of the screen to dim when there is no room light.",
         "Adjusts the brightness of the screen to dim when there is no room light.",
         "Adjusts the brightness of the screen to dim when there is no room light."},
        {"Hour", "Hour", "Hour"},
        {"Calendar", "Calendar", "Calendar"},
        {"Recently saved video", "Recently saved video", "Recently saved video"},
        {"Front door video", "Front door video", "Front door video"},
        {"CCTV footage", "CCTV footage", "CCTV footage"},
};

/***
** 日期: 2022-04-26 09:16
** 作者: leo.liu
** 函数作用：获取home页面的字符串资源
** 返回参数说明：年/년 !@
***/
static inline const char *layout_setting_standby_screen_language_get(int id)
{
        return layout_setting_standby_screen_language[id][language_id_get()];
}

#endif