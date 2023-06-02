#ifndef _LAYOUT_SETTING_SCREEN_H_
#define _LAYOUT_SETTING_SCREEN_H_
#include "common/language.h"

typedef enum
{
        SCREEN_LANG_ID_LCD_SCREEN_BRIGHNESS,
        SCREEN_LANG_ID_LCD_STANDBY_SCREEN,
        SCREEN_LANG_ID_LCD_SCREEN_AFTER_15SEC,
        SCREEN_LANG_ID_LCD_SCREEN_AFTER_30SEC,
        SCREEN_LANG_ID_LCD_SCREEN_AFTER_60SEC,
        SCREEN_LANG_ID_LCD_SCREEN_AFTER_180SEC,
        SCREEN_LANG_ID_LCD_SCREEN_OPEN_FRAME,
        SCREEN_LANG_ID_LCD_SCREEN_CLEANING_MODE,
        SCREEN_LANG_ID_TOTAL

} LAYOUT_SETTING_SCREEN_LANG_ID;

static const char *layout_setting_screen_language[SCREEN_LANG_ID_TOTAL][LANGUAGE_ID_TOTAL] =
    {
        {"LCD screen brightness", "LCD screen brightness", "LCD screen brightness"},
        {"Standby screen", "Standby screen", "Standby screen"},
        {"After 15 seconds", "After 15 seconds", "After 15 seconds"},
        {"After 30 seconds", "After 30 seconds", "After 30 seconds"},
        {"After 1 minutes", "After 1 minutes", "After 1 minutes"},
        {"After 1 minutes", "After 3 minutes", "After 3 minutes"},
        {"Open frame", "Open frame", "Open frame"},
        {"Screen Cleaning mode", "Screen Cleaning mode", "Screen Cleaning mode"},
};

/***
** 日期: 2022-04-26 09:16
** 作者: leo.liu
** 函数作用：获取home页面的字符串资源
** 返回参数说明：年/년 !@
***/
static inline const char *layout_setting_screen_language_get(int id)
{
        return layout_setting_screen_language[id][language_id_get()];
}

#endif