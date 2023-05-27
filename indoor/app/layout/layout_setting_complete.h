

#ifndef _SETTING_COMPLETE_H_
#define _SETTING_COMPLETE_H_

typedef enum
{
        SETTING_COMPLETE_LANG_ID_SETTING_COMPLETE,
        SETTING_COMPLETE_LANG_ID_START_SETTING_IS_COMPLETE,
        SETTING_COMPLETE_LANG_ID_CONFIRM,
        SETTING_COMPLETE_LANG_ID_TOTAL
} LAYOUT_SETTING_COMPLETE_LANG_ID;

static const char *layout_complete_language[SETTING_COMPLETE_LANG_ID_TOTAL][LANGUAGE_ID_TOTAL] =
    {
        {
            "Setting complete",
            "Setting complete",
            "Setting complete",
        }, {
            "Start setting is complete. \nItems whose values are not specified can be specified again in the setting menu.",
            "Start setting is complete. \nItems whose values are not specified can be specified again in the setting menu.",
            "Start setting is complete. \nItems whose values are not specified can be specified again in the setting menu.",
        },
};

/***
** 日期: 2022-04-26 09:16
** 作者: leo.liu
** 函数作用：获取home页面的字符串资源
** 返回参数说明：年/년 !@
***/
static inline const char *layout_complete_language_get(LAYOUT_SETTING_COMPLETE_LANG_ID id)
{
        return layout_complete_language[id][language_id_get()];
}

#endif
