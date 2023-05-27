#ifndef _LAYOUT_HOME_H_
#define _LAYOUT_HOME_H_
#include "common/language.h"
#include "common/sat_user_file.h"
typedef enum
{
        PLAYBACK_LANG_ID_PLAYBACK,
        PLAYBACK_LANG_ID_TOTAL

} LAYOUT_PLAYBACK_LANG_ID;

static const char *layout_playback_language[PLAYBACK_LANG_ID_TOTAL][LANGUAGE_ID_TOTAL] =
    {
        {"Playback", "Playback", "Playback"},
};
/***
**   日期:2022-05-23 18:35:40
**   作者: leo.liu
**   函数作用：获取当前选中文件的索引
**   参数说明:
***/
int playback_pview_item_get(void);
void playback_pview_item_set(int item);
/***
**   日期:2022-05-24 09:56:58
**   作者: leo.liu
**   函数作用：获取预览的类型
**   参数说明:
***/
file_type playback_pview_type_get(void);
/***
** 日期: 2022-04-26 09:16
** 作者: leo.liu
** 函数作用：获取home页面的字符串资源
** 返回参数说明：年/년 !@
***/
static inline const char *layout_playback_language_get(int id)
{
        return layout_playback_language[id][language_id_get()];
}
/***
**   日期:2022-05-24 10:23:22
**   作者: leo.liu
**   函数作用：获取媒体根路径
**   参数说明:
***/
const char *playback_pview_path_get(void);
/***
**   日期:2022-05-24 10:51:04
**   作者: leo.liu
**   函数作用：获取媒体总数
**   参数说明:
***/
int playback_media_total_get(void);
/***
**   日期:2022-05-24 10:52:06
**   作者: leo.liu
**   函数作用：设置媒体总数
**   参数说明:
***/
void playback_media_total_set(int total);
/***
**   日期:2022-05-24 11:35:47
**   作者: leo.liu
**   函数作用：获取预览页面的第一个索引
**   参数说明:
***/
int playback_media_top_get(void);
/***
**   日期:2022-05-24 11:36:23
**   作者: leo.liu
**   函数作用：设置预览页面的第一个索引
**   参数说明:
***/
void playback_media_top_set(int val);
/***
**   日期:2022-05-24 10:55:48
**   作者: leo.liu
**   函数作用：获取当前媒体信息
**   参数说明:
***/
const file_info *playback_media_info_get(void);
#endif