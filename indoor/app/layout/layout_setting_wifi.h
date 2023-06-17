#ifndef _SETTING_WIFI_H_
#define _SETTING_WIFI_H_

typedef enum {

	WIFI_SETTING_ID_LANG_WIFI_WIRELESS_NETWORK, 
        WIFI_SETTING_ID_LANG_WIFI,
        WIFI_SETTING_ID_LANG_ADD_NETWORKS,
        WIFI_SETTING_ID_LANG_DISCOVERED_NETWORKS,
	WIFI_SETTING_ID_LANG_TOTAL
} LAYOUT_SETTING_WIFI_LANG_ID;


static const char * layout_setting_wifi_language[WIFI_SETTING_ID_LANG_TOTAL][LANGUAGE_ID_TOTAL] =
{
	{
		"Wi-Fi (wireless network)", "Wi-Fi (wireless network)","Wi-Fi (wireless network)",
	},
        {
		"Wi-Fi", "Wi-Fi","Wi-Fi",
	},
        {
		"Connected network", "Connected network","Connected network",
	},
        {
		"Discovered networks", "Discovered networks","Discovered networks",
	}
};


/***
** 日期: 2022-04-26 09:16
** 作者: leo.liu
** 函数作用：获取home页面的字符串资源
** 返回参数说明：年/년 !@
***/
static inline const char * layout_setting_wifi_language_get(int id)
{
	return layout_setting_wifi_language[id][language_id_get()];
}


#endif

