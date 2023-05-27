#ifndef _LAYOUT_SETTING_MASTER_INDOOR_UINT_IP_H_
#define _LAYOUT_SETTING_MASTER_INDOOR_UINT_IP_H_
typedef enum
{
        _SETTING_MASTER_INDOOR_UNIT_IP_LANG_ID_MASTER_WALLPAD_IP,
        _SETTING_MASTER_INDOOR_UNIT_IP_LANG_ID_TOTAL
} LAYOUT_SETTING_MASTER_INDOOR_UNIT_IP_LANG_ID;

static const char *layout_setting_master_indoor_unit_ip_language[_SETTING_MASTER_INDOOR_UNIT_IP_LANG_ID_TOTAL][LANGUAGE_ID_TOTAL] =
    {
        {"Master Wallpad IP", "Master Wallpad IP", "Master Wallpad IP"},
};

/***
** 日期: 2022-04-26 09:16
** 作者: leo.liu
** 函数作用：获取home页面的字符串资源
** 返回参数说明：年/년 !@
***/
static inline const char *layout_setting_master_indoor_unit_ip_language_get(int id)
{
        return layout_setting_master_indoor_unit_ip_language[id][language_id_get()];
}

#endif