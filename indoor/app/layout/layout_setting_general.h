
#ifndef _SETTING_SETTING_GENERAL_H_
#define _SETTING_SETTING_GENERAL_H_
typedef enum
{

        SETTING_GENERAL_LANG_ID_LANG_SETTINGS,
        SETTING_GENERAL_LANG_ID_LANG_GENERAL,
        SETTING_GENERAL_LANG_ID_LANG_SOUND,
        SETTING_GENERAL_LANG_ID_LANG_SCREEN,
        SETTING_GENERAL_LANG_ID_LANG_RECORD_MONITORING,
        SETTING_GENERAL_LANG_ID_LANG_INSTALLATION_CONFIGURATION,

        SETTING_GENERAL_LANG_ID_LANG_DATA_AND_TIME,
        SETTING_GENERAL_LANG_ID_LANG_AUTO_SETUP_ON,
        SETTING_GENERAL_LANG_ID_LANG_AUTO_SETUP_OFF,

        SETTING_GENERAL_LANG_ID_LANG_PASSWORD,
        SETTING_GENERAL_LANG_ID_LANG_CHANNGE_PASSWORD_FOR_SECURITY,

        SETTING_GENERAL_LANG_ID_LANG_STORAGE_SPACE,

        SETTING_GENERAL_LANG_ID_LANG_DOOR_OPENING_METHOD,
        SETTING_GENERAL_LANG_ID_LANG_OPEN_AFTER_CALL,
        SETTING_GENERAL_LANG_ID_LANG_OPEN_WHEN_CALL,

        SETTING_GENERAL_LANG_ID_LANG_DOOR_OPENER_MODULE,
        SETTING_GENERAL_LANG_ID_LANG_DIGITAL_DOOR_CAMERA,
        SETTING_GENERAL_LANG_ID_LANG_DIGITAL_DOOR_LOCK,

        SETTING_GENERAL_LANG_ID_LANG_DOOR_OPEN_NUM,
        SETTING_GENERAL_LANG_ID_LANG_DOOR_OPEN_NUM1,
        SETTING_GENERAL_LANG_ID_LANG_DOOR_OPEN_NUM2,

        SETTING_GENERAL_LANG_ID_LANG_CALL_TIMER,
        SETTING_GENERAL_LANG_ID_LANG_1_MINUTE,
        SETTING_GENERAL_LANG_ID_LANG_3_MINUTE,
        SETTING_GENERAL_LANG_ID_LANG_5_MINUTE,

        SETTING_GENERAL_LANG_ID_LANG_SENSOR_SETTING,
        SETTING_GENERAL_LANG_ID_LANG_SENSOR_TEST,
        SETTING_GENERAL_LANG_ID_LANG_DOWNLOAD_MOBILE_APP,
        SETTING_GENERAL_LANG_ID_LANG_INITIALIZATION_USER_DATA,
        SETTING_GENERAL_LANG_ID_LANG_VERSION_INFORMATION,

        SETTING_GENERAL_LANG_ID_LANG_TOTAL
} LAYOUT_SETTING_GENERAL_LANG_ID;

static const char *layout_setting_general_language[SETTING_GENERAL_LANG_ID_LANG_TOTAL][LANGUAGE_ID_TOTAL] =
    {
        {
            "환경설정",
            "环境设置",
            "Settings",
            "Ajustes",
            "Cài đặt",
            "Настройки",
            "الإعدادات",

        },
        {
            "General",
            "General",
            "General",
        },
        {
            "Sound",
            "Sound",
            "Sound",
        },
        {
            "Screen",
            "Screen",
            "Screen",
        },
        {
            "Recording/Monitoring",
            "Recording/Monitoring",
            "Recording/Monitoring",
        },
        {
            "Installation configuration",
            "Installation configuration",
            "Installation configuration",
        },
        {
            "Date and time",
            "Date and time",
            "Date and time",
        },
        {
            "Auto setup on",
            "Auto setup on",
            "Auto setup on",
        },
        {
            "Auto setup off",
            "Auto setup off",
            "Auto setup off",
        },
        {
            "Password",
            "Password",
            "Password",
        },
        {
            "Change password for security",
            "Change password for security",
            "Change password for security",
        },
        {
            "Storage space",
            "Storage space",
            "Storage space",
        },
        {
            "Door opening method",
            "Door opening method",
            "Door opening method",
        },
        {
            "Open the door after calling",
            "Open the door after calling",
            "Open the door after calling",
        },
        {
            "Open the door when called",
            "Open the door when called",
            "Open the door when called",
        },
        {
            "Door opener module",
            "Door opener module",
            "Door opener module",
        },
        {
            "Door camera",
            "Door camera",
            "Door camera",
        },
        {
            "Digital door lock",
            "Digital door lock",
            "Digital door lock",
        },
        {
            "Door camera #2 : Number of door openings",
            "Door camera #2 : Number of door openings",
            "Door camera #2 : Number of door openings",
        },
        {
            "1Door",
            "1Door",
            "1Door",
        },
        {
            "2Door",
            "2Door",
            "2Door",
        },
        {
            "call time",
            "call time",
            "call time",
        },
        {
            "1 minute",
            "1 minute",
            "1 minute",
        },
        {
            "3 minute",
            "3 minute",
            "3 minute",
        },
        {
            "5 minute",
            "5 minute",
            "5 minute",
        },
        {
            "Sensor  setting",
            "Sensor  setting",
            "Sensor  setting",
        },
        {
            "Sensor  test",
            "Sensor  test",
            "Sensor  test",
        },
        {
            "Download mobile app",
            "Download mobile app",
            "Download mobile app",
        },
        {
            "Initialization user data",
            "Initialization user data",
            "Initialization user data",
        },
        {
            "Version information",
            "Version information",
            "Version information",
        },
};
typedef struct
{
        int x, y, w, h;
        int cont_id;
        int title_id;
        int sub_id;
        int title_language_id;
        const char *(*title_language_cb)(int id);
        int sub_language_id;
        const char *(*sub_language_cb)(int id);
        lv_event_cb_t click_cb;

        int img_id;
} setting_list_info_t;
typedef struct
{
    int x, y, w, h;
    int cont_id;
    lv_event_cb_t click_cb;
    int check_id;
    bool select;
    int main_language_id;
    const char *(*main_language_cb)(int id);

} security_list_info_t;
/***
** 日期: 2022-04-26 09:16
** 作者: leo.liu
** 函数作用：获取home页面的字符串资源
** 返回参数说明：年/년 !@
***/
static inline const char *layout_setting_general_language_get(int id)
{
        return layout_setting_general_language[id][language_id_get()];
}

lv_obj_t *setting_main_list_create(int id);
lv_obj_t *setting_list_create(lv_obj_t *parent, int id);
#endif