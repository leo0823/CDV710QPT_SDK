#ifndef _LAYOUT_WIFI_INPUT_H_
#define _LAYOUT_WIFI_INPUT_H_

 typedef enum{

    WIFI_INPUT_LANG_ID_INPUT_USER,
	WIFI_INPUT_LANG_ID_INPUT_PASSWORD,//启动设置
	WIFI_INPUT_LANG_ID_CONNECTING,
	WIFI_INPUT_LANG_ID_CONNECT_FAILED,
	WIFI_INPUT_LANG_ID_CONFIRM,
	POWER_SETTING_LANG_ID_TOTAL
	
}LAYOUT_WIFI_INPUT_LANG_ID;


static const char * layout_wifi_input_language[POWER_SETTING_LANG_ID_TOTAL][LANGUAGE_ID_TOTAL] =
{
    {
		"Please enter the account number","Please enter the account number","Please enter the account number"
	},
	{
		"Please enter a password","Please enter a password","Please enter a password"
	},
	{
		"connrcting","connrcting","connrcting"
	},
	{
		"connect failed","connect failed","connect failed"
	},
	{
		"Confirm","Confirm","Confirm"
	}
};

/***
** 日期: 2022-04-26 09:16
** 作者: leo.liu
** 函数作用：获取home页面的字符串资源
** 返回参数说明：年/년 !@
***/
static inline const char * layout_wifi_input_language_get(LAYOUT_WIFI_INPUT_LANG_ID id)
{
	return layout_wifi_input_language[id][language_id_get()];
}
/***
** 日期: 2022-04-26 09:16
** 作者: leo.liu
** 函数作用：设置wifi输入账号
** 返回参数说明：
***/
void wifi_input_user_setting(const char* user);

#endif

