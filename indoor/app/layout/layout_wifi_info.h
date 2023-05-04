

#ifndef _WIFI_INFO_H_
#define _WIFI_INFO_H_

typedef enum {

	WIFI_INFO_ID_LANG_SECURITY,
        WIFI_INFO_ID_LANG_IP_ADDRES,
	WIFI_INFO_ID_LANG_TOTAL
} LAYOUT_WIFI_INFO_LANG_ID;


static const char * layout_wifi_info_language[WIFI_INFO_ID_LANG_TOTAL][LANGUAGE_ID_TOTAL] =
{
	{
		"Security", "Security","Security",
	},
        {
		"IP address", "IP address","IP address",
	}
};


/***
** 日期: 2022-04-26 09:16
** 作者: leo.liu
** 函数作用：获取home页面的字符串资源
** 返回参数说明：年/년 !@
***/
static inline const char * layout_wifi_info_language_get(LAYOUT_WIFI_INFO_LANG_ID id)
{
	return layout_wifi_info_language[id][language_id_get()];
}

/***********************************************
 ** 作者: leo.liu
 ** 日期: 2023-2-2 13:46:56
 ** 说明: 设置连接wifi的信息
 ***********************************************/
void connected_wifi_info_setting(const void *info);
#endif

