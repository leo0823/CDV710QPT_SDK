

#ifndef _SETTING_USER_WIFI_H_
#define _SETTING_USER_WIFI_H_
#if 0
typedef enum
{

        SETTING_USER_WIFI_LANG_ID_TOTAL
} LAYOUT_SETTING_USER_WIFI_LANG_ID;

static const char *layout_setting_user_wifi_language[SETTING_USER_WIFI_LANG_ID_TOTAL][LANGUAGE_ID_TOTAL] =
    {
        {

        },
};

/***
** 日期: 2022-04-26 09:16
** 作者: leo.liu
** 函数作用：获取home页面的字符串资源
** 返回参数说明：年/년 !@
***/
static inline const char *layout_settign_user_wifi_language_get(int id)
{
        return layout_setting_user_wifi_language[id][language_id_get()];
}
#endif
#endif
