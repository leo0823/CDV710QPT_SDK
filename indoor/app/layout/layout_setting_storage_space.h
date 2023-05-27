#ifndef _LAYOUT_SETTING_STORAGE_SPACE_H_
#define _LAYOUT_SETTING_STORAGE_SPACE_H_
#include "common/language.h"

typedef enum
{
        SETTING_STORAGE_LANG_ID_INTERNAL_STORAGE,
        SETTING_STORAGE_LANG_ID_EXTERNAL_STORAGE,
        SETTING_STORAGE_LANG_ID_REMAINING_DATA,
        SETTING_STORAGE_LANG_ID_SD_FORMAT,
        SETTING_STORAGE_LANG_ID_WOULD_YOU_LIKE_FORMAT,
        SETTING_STORAGE_LANG_ID_WOULD_YOU_LIKE_DEL,
        SETTING_STORAGE_LANG_ID_DELETE,
        SETTING_STORAGE_LANG_ID_TOTAL
} LAYOUT_SETTING_STORAGE_SPACE_LANG_ID;

static const char *layout_setting_storage_space_language[SETTING_STORAGE_LANG_ID_TOTAL][LANGUAGE_ID_TOTAL] =
    {
        {"Internal storage", "Internal storage", "Internal storage"},
        {"External storage", "External storage", "External storage"},
        {"Remaining\ndata", "Remaining\ndata", "Remaining\ndata"},
        {"SD card format", "SD card format", "SD card format"},
        {"Would you like to format it?", "Would you like to format it?", "Would you like to format it?"},
        {"Would you like to delete it?", "Would you like to delete it?", "Would you like to delete it?"},
        {"Delete", "Delete", "Delete"},
};

/***
** 日期: 2022-04-26 09:16
** 作者: leo.liu
** 函数作用：获取home页面的字符串资源
** 返回参数说明：年/년 !@
***/
static inline const char *layout_setting_storage_space_language_get(int id)
{
        return layout_setting_storage_space_language[id][language_id_get()];
}

#endif