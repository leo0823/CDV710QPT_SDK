
#ifndef _SETTING_SERVER_OPERATION_NETWORK_H_
#define _SETTING_SERVER_OPERATION_NETWORK_H_
typedef enum
{

        SERVER_OPERATION_NETWORK_ID_LANG_SERVER_SYSTEM,
        SERVER_OPERATION_NETWORK_ID_LANG_BUILD_HOUSE_NUMBER,
        SERVER_OPERATION_NETWORK_ID_LANG_BUILD_NUMBER,
        SERVER_OPERATION_NETWORK_ID_LANG_FOOLR_NUMBER,
        SERVER_OPERATION_NETWORK_ID_LANG_HOUSEHOLD_NUMBER,
        SERVER_OPERATION_NETWORK_ID_LANG_EXTENSION_NUMBER,
        SERVER_OPERATION_NETWORK_ID_LANG_OPERATING_SERVER,
        SERVER_OPERATION_NETWORK_ID_LANG_LOCAL_SERVER,
        SERVER_OPERATION_NETWORK_ID_LANG_SIP_SERVER,
        SERVER_OPERATION_NETWORK_ID_LANG_UPDATE_SERVER,
        SERVER_OPERATION_NETWORK_ID_LANG_CCTV_SERVER,
        SERVER_OPERATION_NETWORK_ID_LANG_GUARD_STATION,
        SERVER_OPERATION_NETWORK_ID_LANG_GUARD_STATION_NUMBER,
        SERVER_OPERATION_NETWORK_ID_LANG_TOTAL
} LAYOUT_SERVER_OPERATION_NETWORK_LANG_ID;

static const char *layout_server_operation_network_language[SERVER_OPERATION_NETWORK_ID_LANG_TOTAL][LANGUAGE_ID_TOTAL] =
    {
        {
            "server system",
            "server system",
            "server system",
        },
        {
            "Building-House number",
            "Building-House number",
            "Building-House number",
        },
        {
            "Building number",
            "Building number",
            "Building number",
        },
        {
            "Foolr number",
            "Foolr number",
            "Foolr number",
        },
        {
            "Household number",
            "Household number",
            "Household number",
        },
        {
            "Extension number",
            "Extension number",
            "Extension number",
        },
        {
            "Operating server",
            "Operating server",
            "Operating server",
        },
        {
            "Local server",
            "Local server",
            "Local server",
        },
        {
            "SIP server",
            "SIP server",
            "SIP server",
        },
        {
            "Update server",
            "Update server",
            "Update server",
        },
        {
            "CCTV server",
            "CCTV server",
            "CCTV server",
        },
        {
            "Guard station",
            "Guard station",
            "Guard station",
        },
        {
            "Guard station number",
            "Guard station number",
            "Guard station number",
        }};

/***
** 日期: 2022-04-26 09:16
** 作者: leo.liu
** 函数作用：获取home页面的字符串资源
** 返回参数说明：年/년 !@
***/
static inline const char *layout_server_operation_network_language_get(LAYOUT_SERVER_OPERATION_NETWORK_LANG_ID id)
{
        return layout_server_operation_network_language[id][language_id_get()];
}

#endif