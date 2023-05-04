

#ifndef _SETTING_SENSOR_USAGE_SETTING_H_
#define _SETTING_SENSOR_USAGE_SETTING_H_

typedef enum
{
        SETTING_SENSOR_USAGE_LANG_ID_SENSOR_SETTINGS_WHEN_GOING_OUT,
        SETTING_SENSOR_USAGE_LANG_ID_SENSOR_SETTING_WHEN_SECURITY_MODE,
        SETTING_SENSOR_USAGE_LANG_ID_SENSOR_CONTACT_1,
        SETTING_SENSOR_USAGE_LANG_ID_SENSOR_CONTACT_2,
        SETTING_SENSOR_USAGE_LANG_ID_SENSOR_CONTACT_3,
        SETTING_SENSOR_USAGE_LANG_ID_SENSOR_CONTACT_4,
        SETTING_SENSOR_USAGE_LANG_ID_SENSOR_CONTACT_5,
        SETTING_SENSOR_USAGE_LANG_ID_SENSOR_CONTACT_6,
        SETTING_SENSOR_USAGE_LANG_ID_SENSOR_CONTACT_7,
        SETTING_SENSOR_USAGE_LANG_ID_NOT_USED,
        SETTING_SENSOR_USAGE_LANG_ID_SENSOR_FOR_SECURITY,
        SETTING_SENSOR_USAGE_LANG_ID_TOTAL
} LAYOUT_SETTING_SENSOR_USAGE_LANG_ID;

static const char *layout_setting_sensor_usage_language[SETTING_SENSOR_USAGE_LANG_ID_TOTAL][LANGUAGE_ID_TOTAL] =
    {
        {
            "Sensor settings when going out",
            "Sensor settings when going out",
            "Sensor settings when going out",
        },
        {
            "Sensor settings for security mode",
            "Sensor settings for security mode",
            "Sensor settings for security mode",
        },
        {
            "Sensor contact 1",
            "Sensor contact 1",
            "Sensor contact 1",
        },
        {
            "Sensor contact 2",
            "Sensor contact 2",
            "Sensor contact 2",
        },
        {
            "Sensor contact 3",
            "Sensor contact 3",
            "Sensor contact 3",
        },
        {
            "Sensor contact 4",
            "Sensor contact 4",
            "Sensor contact 4",
        },
        {
            "Sensor contact 5",
            "Sensor contact 5",
            "Sensor contact 5",
        },
        {
            "Sensor contact 6",
            "Sensor contact 6",
            "Sensor contact 6",
        },
        {
            "Sensor contact 7",
            "Sensor contact 7",
            "Sensor contact 7",
        },
        {
            "Not used",
            "Not used",
            "Not used",
        },
        {
            "Sensor for security",
            "Sensor for security",
            "Sensor for security",
        },
};

/***
** 日期: 2022-04-26 09:16
** 作者: leo.liu
** 函数作用：获取home页面的字符串资源
** 返回参数说明：年/년 !@
***/
static inline const char *layout_setting_sensor_usage_language_get(int id)
{
        return layout_setting_sensor_usage_language[id][language_id_get()];
}

#endif
