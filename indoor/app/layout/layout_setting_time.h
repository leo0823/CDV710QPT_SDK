#ifndef _LAYOUT_SETTING_TIME_H_
#define _LAYOUT_SETTING_TIME_H_

typedef enum
{

        SETTING_TIME_ID_DATE_TIME,
        SETTING_TIME_ID_SET_DATE_AND_TIME,
        SETTING_TIME_ID_THE_TIME_IS_SET_AUTOMATICALLY,
        SETTING_TIME_ID_LANG_TOTAL
} LAYOUT_SETTING_TIME_LANG_ID;

static const char *layout_setting_time_language[SETTING_TIME_ID_LANG_TOTAL][LANGUAGE_ID_TOTAL] =
    {
        {
            "Date/time",
            "Date/time",
            "Date/time",
        },
        {
            "Set date and time automatically",
            "Set date and time automatically",
            "Set date and time automatically",
        },
        {
            "The time is set automatically when connected to the network.",
            "The time is set automatically when connected to the network.",
            "The time is set automatically when connected to the network.",
        }};

/***
** 日期: 2022-04-26 09:16
** 作者: leo.liu
** 函数作用：获取home页面的字符串资源
** 返回参数说明：年/년 !@
***/
static inline const char *layout_setting_time_language_get(LAYOUT_SETTING_TIME_LANG_ID id)
{
        return layout_setting_time_language[id][language_id_get()];
}

void setting_time_first_enter_set_flag(char isfirst);
#endif
