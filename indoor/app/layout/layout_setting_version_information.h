

#ifndef _SETTING_DOWNLOAD_H_
#define _SETTING_DOWNLOAD_H_

typedef enum
{
        SETTING_VERSION_INFORMATION_LANG_ID_CURRENT_VERSION,
        SETTING_VERSION_INFORMATION_LANG_ID_UPDATE_VERSION,
        SETTING_VERSION_INFORMATION_LANG_ID_UPDATE,
        SETTING_VERSION_INFORMATION_LANG_ID_UPDATE_ING,
        SETTING_VERSION_INFORMATION_LANG_ID_TOTAL
} LAYOUT_SETTING_VERSION_INFORMATION_LANG_ID;

static const char *layout_setting_version_information_language[SETTING_VERSION_INFORMATION_LANG_ID_TOTAL][LANGUAGE_ID_TOTAL] =
    {

        {
            "Current version",
            "Current version",
            "Current version",
        },
        {
            "Update version",
            "Update version",
            "Update version",
        },
        {
            "Update",
            "Update",
            "Update",
        },
        {
            "Upgrading...",
            "Upgrading...",
            "Upgrading...",
        },
};

/***
** 日期: 2022-04-26 09:16
** 作者: leo.liu
** 函数作用：获取home页面的字符串资源
** 返回参数说明：年/년 !@
***/
static inline const char *layout_setting_version_information_language_get(int id)
{
        return layout_setting_version_information_language[id][language_id_get()];
}

#endif
