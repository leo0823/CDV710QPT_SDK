#ifndef _LAYOUT_SETTING_INSTALLATION_H_
#define _LAYOUT_SETTING_INSTALLATION_H_
#include "common/language.h"

typedef enum
{
        INSTALLATION_LANG_ID_THE_MENU_IS_TO_OPERATE,
        INSTALLATION_LANG_ID_WE_ARE_NOT_RESPONSIBLE,
        INSTALLATION_LANG_ID_I_HAVE_READ_AND_UNDERSTOOD,

        INSTALLATION_LANG_ID_BUILDING_HOUSE_NO,
        INSTALLATION_LANG_ID_IP_ADDRES,
        INSTALLATION_LANG_ID_IP_ADDRES_GATEWAY_DNS_SETTING,
        INSTALLATION_LANG_ID_OPERATIONG_SERVER_IP_ADDRES,
        INSTALLATION_LANG_ID_LOCAL_SERVER_SIP_SERVER_UPDATE,

        INSTALLATION_LANG_ID_COMMON_ENTRANCE_IP,
        INSTALLATION_LANG_ID_COMMON_ENTRANCE_IP_FOR_INTERLOCKING,

        INSTALLATION_LANG_ID_GUARD_STATION_NUMBER,

        INSTALLATION_LANG_ID_SENSOR,

        INSTALLATION_LANG_ID_SENSOR_TEST,

        INSTALLATION_LANG_ID_FRONT_DOOR_CAMERA,
        INSTALLATION_LANG_ID_FRONT_CCTV,

        INSTALLATION_LANG_ID_FACTORY_RESET,

        INSTALLATION_LANG_ID_TOTAL
} LAYOUT_SETTING_INSTALLATION_LANG_ID;

static const char *layout_setting_installation_language[INSTALLATION_LANG_ID_TOTAL][LANGUAGE_ID_TOTAL] =
    {
        {"This menu is to operate the product normally. Please note\n you don't need to change setting arbitraily.",
         "This menu is to operate the product normally. Please note\n you don't need to change setting arbitraily.",
         "This menu is to operate the product normally. Please note\n you don't need to change setting arbitraily."},

        {"*We are not responsible for any situations caused by arbitrary settings.", "*We are not responsible for any situations caused by arbitrary settings.", "*We are not responsible for any situations caused by arbitrary settings."},

        {"I have read and understood with your notice.", "I have read and understood with your notice.", "I have read and understood with your notice."},

        {"Building - House No.", "Building - House No.", "Building - House No."},

        {"IP address", "IP address", "IP address"},

        {"IP address setting, default gateway, subnet mask, DNS setting", "IP address setting, default gateway, subnet mask, DNS setting", "IP address setting, default gateway, subnet mask, DNS setting"},

        {"Operation server IP address", "Operation server IP address", "Operation server IP address"},

        {"Local server, SIP server update server, CCTV server", "Local server, SIP server update server, CCTV server", "Local server, SIP server update server, CCTV server"},

        {"Common entrance IP", "Common entrance IP", "Common entrance IP"},

        {"Common entrance IP for interlocking elevator main device", "Common entrance IP for interlocking elevator main device", "Common entrance IP for interlocking elevator main device"},

        {"Guard station number", "Guard station number", "Guard station number"},

        {"Sensor", "Sensor", "Sensor"},
        {"Sensor test", "Sensor test", "Sensor test"},

        {"Front door camera", "Front door camera", "Front door camera"},
         {"Front CCTV", "Front CCTV", "Front CCTV"},

        {"Factory reset", "Factory reset", "Factory reset"}

};

/***
** 日期: 2022-04-26 09:16
** 作者: leo.liu
** 函数作用：获取home页面的字符串资源
** 返回参数说明：年/년 !@
***/
static inline const char *layout_setting_installation_language_get(int id)
{
        return layout_setting_installation_language[id][language_id_get()];
}

#endif