#ifndef _LAYOUT_MONITOR_H_
#define _LAYOUT_MONITOR_H_
#include <stdbool.h>
 bool monitor_doorcamera_call_extern_func(char* arg);
 bool monitor_doorcamera_call_inside_func(char* arg);
typedef enum
{
    MONITOR_LANG_ID_MONITOR_MOBILE_APP,
    MONITOR_LANG_ID_TALK_MOBILE_APP,
    MONITOR_LANG_ID_TOTAL,
  

}LAYOUT_MONITOR_LANG_ID;
static const char *layout_monitor_language[MONITOR_LANG_ID_TOTAL][LANGUAGE_ID_TOTAL] =
    {
        {"Currently in use in mobile app.", 
        "正在移动应用程序中使用",
        "Currently in use in mobile app.",
        "Сейчас используется в мобильном приложении.",
        "Actualmente en uso en la aplicación móvil.",
        "Hiện đang được sữ dụng trong ứng dụng di động",
        "قيد الاستخدام حاليًا في تطبيق الجوّال."},
        {"Currently in talk in mobile app.", "Currently in talk in mobile app.", "Currently in talk in mobile app."},

    };

 /***
** 日期: 2022-04-26 09:16
** 作者: leo.liu
** 函数作用：获取monitor页面的字符串资源
** 返回参数说明：年/년 !@
***/
static inline const char *layout_monitor_language_get(LAYOUT_MONITOR_LANG_ID id)
{
        return layout_monitor_language[id][language_id_get()];
}

#endif
