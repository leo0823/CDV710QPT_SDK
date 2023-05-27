

#ifndef _SETTING_INITIALIZE_H_
#define _SETTING_INITIALIZE_H_

typedef enum
{
        SETTING_INITIALIZE_LANG_ID_DATA_CANNOT_BE,
        SETTING_INITIALIZE_LANG_ID_INITIALZATION_LIST,
        SETTING_INITIALIZE_LANG_ID_CALL_LOG,
        SETTING_INITIALIZE_LANG_ID_SAVED_VIDEO,
        SETTING_INITIALIZE_LANG_ID_EMERGENCY_RECORD,
        SETTING_INITIALIZE_LANG_ID_INITIALZATION_IS_COMPLETE,
        SETTING_INITIALIZE_LANG_ID_COMPLETE,
        SETTING_INITIALIZE_LANG_ID_RESET,
        SETTING_INITIALIZE_LANG_ID_TOTAL
} LAYOUT_SETTING_INITIALIZE_LANG_ID;

static const char *layout_setting_initialize_language[SETTING_INITIALIZE_LANG_ID_TOTAL][LANGUAGE_ID_TOTAL] =
    {

        {
            "Data cannot be recovered after initialization.",
            "Data cannot be recovered after initialization.",
            "Data cannot be recovered after initialization.",
        },
        {
            "Initialization list",
            "Initialization list",
            "Initialization list",
        },
        {
            "Call log:",
            "Call log:",
            "Call log:",
        },
        {
            "Saved video:",
            "Saved video:",
            "Saved video:",
        },
        {
            "Emergency record:",
            "Emergency record:",
            "Emergency record:",
        },
        {
            "Initialization is complete.",
            "Initialization is complete.",
            "Initialization is complete.",
        },
        {
            "Complete",
            "Complete",
            "Complete",
        },
        {
            "Reset",
            "Reset",
            "Reset",
        },
};

/***
** 日期: 2022-04-26 09:16
** 作者: leo.liu
** 函数作用：获取home页面的字符串资源
** 返回参数说明：年/년 !@
***/
static inline const char *layout_setting_initialize_language_get(int id)
{
        return layout_setting_initialize_language[id][language_id_get()];
}

#endif
