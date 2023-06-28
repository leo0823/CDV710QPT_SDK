

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
        SETTING_SENSOR_USAGE_LANG_ID_SENSOR_FOR_SECURITY,
        SETTING_SENSOR_USAGE_LANG_ID_NOT_USED,
        SETTING_SENSOR_USAGE_LANG_ID_NO,
        SETTING_SENSOR_USAGE_LANG_ID_NC,
        SETTING_SENSOR_USAGE_LANG_ID_ALWAYS,
        SETTING_SENSOR_USAGE_LANG_ID_RUNNNG_TIPS,
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
            "센서 접점 1",
            "传感器触点 1",
            "Sensor contact 1",
            "Контакт датчика 1",
            "Sensor de contacto 1",
            "Cảm biến tiếp xúc 1",
            "Контакт датчика 1",
            "الإتصال بالمستشعر 1",
        },
        {
            "센서 접점 2",
            "传感器触点 2",
            "Sensor contact 2",
            "Контакт датчика 2",
            "Sensor de contacto 2",
            "Cảm biến tiếp xúc 2",
            "Контакт датчика 2",
            "لإتصال بالمستشعر 2",
        },
        {
            "센서 접점 3",
            "传感器触点 3",
            "Sensor contact 3",
            "Контакт датчика 3",
            "Sensor de contacto 3",
            "Cảm biến tiếp xúc 3",
            "Контакт датчика 3",
            "لإتصال بالمستشعر 3",
        },
        {
            "센서 접점 4",
            "传感器触点 4",
            "Sensor contact 4",
            "Контакт датчика 4",
            "Sensor de contacto 4",
            "Cảm biến tiếp xúc 4",
            "Контакт датчика 4",
            "لإتصال بالمستشعر 4",
        },
        {
            "센서 접점 5",
            "传感器触点 5",
            "Sensor contact 5",
            "Контакт датчика 5",
            "Sensor de contacto 5",
            "Cảm biến tiếp xúc 5",
            "Контакт датчика 5",
            "لإتصال بالمستشعر 5",
        },
        {
            "센서 접점 6",
            "传感器触点 6",
            "Sensor contact 6",
            "Контакт датчика 6",
            "Sensor de contacto 6",
            "Cảm biến tiếp xúc 6",
            "Контакт датчика 6",
            "لإتصال بالمستشعر 6",
        },
        {
            "센서 접점 7",
            "传感器触点 7",
            "Sensor contact 7",
            "Контакт датчика 7",
            "Sensor de contacto 7",
            "Cảm biến tiếp xúc 7",
            "Контакт датчика 6",
            "لإتصال بالمستشعر 7",
        },
        {
            "Not used",
            "Not used",
            "Not used",
        },
        {
            "NO",
            "NO",
            "NO",
        },
        {
            "NC",
            "NC",
            "NC",
        },
        {
            "Always detect",
            "Always detect",
            "Always detect",
        },
        {
            "NULL",
            "NULL",
            "The outing is currently running.The 'Not used' setting is applied after the end of the outing.",
            "NULL",
            "NULL",
            "NULL",
            "NULL",

        }
        
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
