#ifndef _LAYOUT_POWER_SETTING_H_
#define _LAYOUT_POWER_SETTING_H_
#include "common/language.h"

 typedef enum{

	POWER_SETTING_LANG_POWER_SET,//启动设置
	POWER_SETTING_LANG_WELCOM,
	POWER_SETTING_LANG_RUN,
	POWER_SETTING_LANG_SKIP,
	POWER_SETTING_LANG_ID_TOTAL
	
}LAYOUT_POWER_SETTING_LANG_ID;

static const char * layout_power_setting_language[POWER_SETTING_LANG_ID_TOTAL][LANGUAGE_ID_TOTAL] =
{
	{
		"시작설정","启动设置","Startup settings"
	},
	{
		"시작설정.\n이 설정은 제품을 정상적으로 운영하기 위한 필수 요소를 진행합니다.","欢迎新的开始\n此设置是使产品正常运行所必需的","Welcome to a new start.\nThis setting is necessary for the normal operation of the product."
	},
	{
		"실행","运行","Run",
	},
	{
		"건너뛰기","跳过","Skip",
	},
};

/***
** 日期: 2022-04-26 09:16
** 作者: leo.liu
** 函数作用：获取home页面的字符串资源
** 返回参数说明：年/년 !@
***/
static inline const char * layout_power_setting_language_get(LAYOUT_POWER_SETTING_LANG_ID id)
{
	return layout_power_setting_language[id][language_id_get()];
}

#endif

