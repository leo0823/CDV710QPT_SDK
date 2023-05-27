#ifndef _SLAVE_TYPE_SETTING_H_
#define _SLAVE_TYPE_SETTING_H_
typedef enum
{
        LAYOUT_SLAVE_TYPE_SETTING_LANG_ID_SLAVE_TYPE_SETTING,
        LAYOUT_SLAVE_TYPE_SETTING_LANG_ID_MASTTER_INDOOR,
        LAYOUT_SLAVE_TYPE_SETTING_LANG_ID_EXTENSION_NUMBER,
        LAYOUT_SLAVE_TYPE_SETTING_LANG_ID_NOT_SET,

        LAYOUT_SLAVE_TYPE_SETTING_LANG_ID_TOTAL,
} LAYOUT_SLAVE_TYPE_SETTING_LANG_ID;

static const char *layout_slave_type_setting_language[LAYOUT_SLAVE_TYPE_SETTING_LANG_ID_TOTAL][LANGUAGE_ID_TOTAL] =
    {
        {"Slave type setting", "Slave type setting", "Slave type setting"},
        {"Master indoor unit IP setting", "Master indoor unit IP setting", "Master indoor unit IP setting"},
        {"Extension number setting", "Extension number setting", "Extension number setting"},
        {"Not set", "Not set", "Not set"},
};
/***
** 日期: 2022-04-26 09:16
** 作者: leo.liu
** 函数作用：获取home页面的字符串资源
** 返回参数说明：年/년 !@
***/
static inline const char *layout_slave_type_setting_language_get(LAYOUT_SLAVE_TYPE_SETTING_LANG_ID id)
{
        return layout_slave_type_setting_language[id][language_id_get()];
}
#endif