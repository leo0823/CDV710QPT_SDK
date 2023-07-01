typedef enum
{
    ALARM_LIST_DELETED_ALL,
    ALARM_LIST_EMERGENCY_LOG,
    ALARM_LIST_EMERGENCY_OCCURS,
    ALARM_LIST_EMERGENCY_STOP,
    ALARM_LIST_EMERGENCY_RETURN,
    ALARM_LIST_SECURITY_EMERGENCY,
    ALARM_LIST_SECURITY_EMERGENCY_STOP,
    ALARM_LIST_SECURITY_EMERGENCY_RETURN,
    ALARM_LIST_INDOOR_OPERATION,
    ALARM_LIST_USER_OPERATION,
    ALARM_LIST_SECURITY_SENSOR1,
    ALARM_LIST_SECURITY_SENSOR2,
    ALARM_LIST_SECURITY_SENSOR3,
    ALARM_LIST_SECURITY_SENSOR4,
    ALARM_LIST_SECURITY_SENSOR5,
    ALARM_LIST_SECURITY_SENSOR6,
    ALARM_LIST_SECURITY_SENSOR7,
    ALARM_LIST_SECURITY_SENSOR8,
    ALARM_LIST_LANG_ID_TOTAL

} LAYOUT_ALARM_LIST_LANG_ID;

static const char *layout_alarm_list_language[ALARM_LIST_LANG_ID_TOTAL][LANGUAGE_ID_TOTAL] =
    {
        {"Delete all?","Delete all?","Delete all?"},
        {"Emergency occurs", "Emergency occurs", "Emergency occurs"},
        {"Emergency stop", "Emergency stop", "Emergency stop"},
        {"Emergency return", "Emergency return", "Emergency return"},
        {"Security emergency", "Security emergency", "Security emergency"},
        {"Security emergency stop", "Security emergency stop", "Security emergency stop"},
        {"Security emergency return", "Security emergency return", "Security emergency return"},
        {"indoor unit operation", "indoor unit operation","indoor unit operation"},
        {"user operation","user operation","user operation"},
        {"Security sensor1", "Security sensor1","Security sensor1"},
        {"Security sensor1", "Security sensor1","Security sensor2"},
        {"Security sensor1", "Security sensor1","Security sensor3"},
        {"Security sensor1", "Security sensor1","Security sensor4"},
        {"Security sensor1", "Security sensor1","Security sensor5"},
        {"Security sensor1", "Security sensor1","Security sensor6"},
        {"Security sensor1", "Security sensor1","Security sensor7"},
        {"Security sensor1", "Security sensor1","Security sensor8"},


    };

/***
** 日期: 2022-04-26 09:16
** 作者: leo.liu
** 函数作用：获取home页面的字符串资源
** 返回参数说明：年/년 !@
***/
static inline const char *layout_alarm_language_get(LAYOUT_ALARM_LIST_LANG_ID id)
{
        return layout_alarm_list_language[id][language_id_get()];
}
