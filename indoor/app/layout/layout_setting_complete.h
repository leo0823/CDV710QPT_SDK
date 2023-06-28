

#ifndef _SETTING_COMPLETE_H_
#define _SETTING_COMPLETE_H_

typedef enum
{
        SETTING_COMPLETE_LANG_ID_SETTING_COMPLETE,
        SETTING_COMPLETE_LANG_ID_START_SETTING_IS_COMPLETE,
        SETTING_COMPLETE_LANG_ID_CONFIRM,
        SETTING_COMPLETE_LANG_ID_TOTAL
} LAYOUT_SETTING_COMPLETE_LANG_ID;

static const char *layout_complete_language[SETTING_COMPLETE_LANG_ID_TOTAL][LANGUAGE_ID_TOTAL] =
    {
        {
            "시작 설정 종료 ",
            "设置完成",
            "Setting complete",
            "Настройка завершена",
            "Configuración completa",
            "Hoàn thành cài đặt ",
            "اكتمال الإعدادات",
        }, 
        {
            "시작 설정 값을 모두 적용했습니다. 설정값을 지정하지 않은 항목은 환경설정 메뉴에서 다시 지정할 수 있습니다.",
            "所有起始设置值已经开始应用，可以在环境设置菜单中再次指定未指定设置值的项目。",
            "Start setting is complete. \nItems whose values are not specified can be specified again in the setting menu.",
            "Начальная настройка завершена. Значения тех параметров, которые не были выполнены изначально, можно выполнить позднее в меню настроек.",
            "La configuración de inicio está completa. Los elementos cuyos valores no se han especificado se pueden especificar de nuevo en el menú de configuración.",
            "Cài đặt ban đầu hoàn tất. Các mục không chỉ định có thể được cài đặt trong phần tùy chọn cài đặt",
            "NULL"
        },
};

/***
** 日期: 2022-04-26 09:16
** 作者: leo.liu
** 函数作用：获取home页面的字符串资源
** 返回参数说明：年/년 !@
***/
static inline const char *layout_complete_language_get(LAYOUT_SETTING_COMPLETE_LANG_ID id)
{
        return layout_complete_language[id][language_id_get()];
}

#endif
