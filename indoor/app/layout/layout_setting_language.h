#ifndef _SETTING_LANGUAGE_H_
#define _SETTING_LANGUAGE_H_

typedef enum {

	LANGUAGE_ID_LANG_LANG, 
	LANGUAGE_ID_LANG_TOTAL
} LAYOUT_LANGUAGE_LANG_ID;


static const char * layout_language_language[LANGUAGE_ID_LANG_TOTAL][LANGUAGE_ID_TOTAL] =
{
	{
		"언어", "语言","Language",
	}
};


/***
** 日期: 2022-04-26 09:16
** 作者: leo.liu
** 函数作用：获取home页面的字符串资源
** 返回参数说明：年/년 !@
***/
static inline const char * layout_language_language_get(int id)
{
	return layout_language_language[id][language_id_get()];
}


#endif

