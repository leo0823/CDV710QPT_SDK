

#ifndef _SETTING_SIGNLE_OPERATION_NETWORK_H_
#define _SETTING_SIGNLE_OPERATION_NETWORK_H_
typedef enum {

	SIGNLE_OPERATION_NETWORK_ID_LANG_OPERATION_NETWORK, 
	SIGNLE_OPERATION_NETWORK_ID_LANG_OPERATION_STRCUUTRE, 
	SIGNLE_OPERATION_NETWORK_ID_LANG_SINGLE,
	SIGNLE_OPERATION_NETWORK_ID_LANG_IP,
	SIGNLE_OPERATION_NETWORK_ID_LANG_GATEWAY,
	SIGNLE_OPERATION_NETWORK_ID_LANG_MASK,
	SIGNLE_OPERATION_NETWORK_ID_LANG_DNS,
	SIGNLE_OPERATION_NETWORK_ID_LANG_TOTAL
} LAYOUT_SIGNLE_OPERATION_NETWORK_LANG_ID;


static const char * layout_single_operation_network_language[SIGNLE_OPERATION_NETWORK_ID_LANG_TOTAL][LANGUAGE_ID_TOTAL] =
{
	{
		"운영 네트워크", "操作网络", "Operating network", 
	},
	{
		"경영 구조", "经营结构", "Operating structure", 
	},
	{
		"하나뿐인", "单户型", "single", 
	},
	{
		"Product IP", "产品IP", "Product IP", 
	},
	{
		"Default gateway", "Default gateway", "Default gateway", 
	},
	{
		"Subnet mask", "Subnet mask", "Subnet mask", 
	},
	{
		"DNS", "DNS", "DNS", 
	}
};


/***
** 日期: 2022-04-26 09:16
** 作者: leo.liu
** 函数作用：获取home页面的字符串资源
** 返回参数说明：年/년 !@
***/
static inline const char * layout_single_operation_network_language_get(int id)
{
	return layout_single_operation_network_language[id][language_id_get()];
}


#endif

