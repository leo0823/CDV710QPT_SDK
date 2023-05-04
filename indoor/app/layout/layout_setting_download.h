

#ifndef _SETTING_DOWNLOAD_H_
#define _SETTING_DOWNLOAD_H_

typedef enum
{
        SETTING_DOWNLOAD_LANG_ID_GOOGLE_PLAY_STORE,
        SETTING_DOWNLOAD_LANG_ID_GOOGLE_APP_STORE,
        SETTING_DOWNLOAD_LANG_ID_VIDEO_CALL_WITH_MOBILE_APP,
        SETTING_DOWNLOAD_LANG_ID_TOTAL
} LAYOUT_SETTING_DOWNLOAD_LANG_ID;

static const char *layout_setting_download_language[SETTING_DOWNLOAD_LANG_ID_TOTAL][LANGUAGE_ID_TOTAL] =
    {
      
        {
            "Google Play Store",
            "Google Play Store",
            "Google Play Store",
        },
        {
            "Apple App Store",
            "Apple App Store",
            "Apple App Store",
        },
        {
            "Video call with mobile app, front door,\nCCTV monitoring is available.",
            "Video call with mobile app, front door,\nCCTV monitoring is available.",
            "Video call with mobile app, front door,\nCCTV monitoring is available.",
        },
};

/***
** 日期: 2022-04-26 09:16
** 作者: leo.liu
** 函数作用：获取home页面的字符串资源
** 返回参数说明：年/년 !@
***/
static inline const char *layout_setting_download_language_get(int id)
{
        return layout_setting_download_language[id][language_id_get()];
}

#endif
