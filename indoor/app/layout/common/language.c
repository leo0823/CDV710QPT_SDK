#include "language.h"
#include <stdlib.h>

/***
**   日期:2022-07-07 10:36:31
**   作者: leo.liu
**   函数作用：其他没有显示的字体
**   参数说明:
***/
static LANGUAGE_ID language_cur_id = LANGUAGE_ID_ENGLISH;

/***
** 日期: 2022-04-26 08:55
** 作者: leo.liu
** 函数作用：设置当前语言
** 返回参数说明：
***/
void language_id_set(LANGUAGE_ID id)
{
        language_cur_id = id;
}

/***
** 日期: 2022-04-26 08:56
** 作者: leo.liu
** 函数作用：获取当前语言ID
** 返回参数说明：
***/
LANGUAGE_ID language_id_get(void)
{
        return language_cur_id;
}

/***** 公共字符串资源 *****/
static const char *lang_common_language[LANG_COMMON_ID_TOTAL][LANGUAGE_ID_TOTAL] =
    {
        /***** LANG_COMMON_ID_OFF *****/
        {"OFF", "OFF", "OFF", "Apagar", "关", "OFF", "Wył.", "OFF", "إيقاف"},
        /***** LANG_COMMON_ID_ON *****/
        {"ON", "ON", "ON", "Encender", "开", "ON", "Wł.", "ON", "تشغيل"},
        /***** LANG_COMMON_ID_VIDEO *****/
        {"Video", "Video", "Video", "Video", "视频", "Video", "Filmy", "Video", "فيديو"},
        /***** LANG_COMMON_ID_PHOTO *****/
        {"Photo", "Photo", "Photo", "Foto", "照片", "Fotograf", "Zdjęcia", "Fotka", "صورة"},
        /***** LANG_COMMON_ID_CANCEL *****/
        {"Cancel", "Cancel", "Cancel", "Cancelar", "取消", "İptal", "Anuluj", "Zrušit", "الغاء"},
        /***** LANG_COMMON_ID_CONFIRM *****/
        {"Confirm", "Confirm", "Confirm", "Confirmar", "确认", "OK", "Zatwierdź", "OK", "تأكيد"},
        /***** LANG_COMMON_ID_DOOR1 *****/
        {"Door1", "Door1", "Door1", "Entrada 1", "门口机 1", "Lobi 1", "Wejście 1", "Dveře 1", "الباب  1"},
        {"Door2", "Door2", "Door2", "Entrada 2", "门口机 2", "Lobi 2", "Wejście 2", "Dveře 2", "الباب  2"},
        {"Door3", "Door3", "Door3", "Entrada 3", "门口机 3", "Lobi 3", "Wejście 3", "Dveře 3", "الباب  3"},
        {"Door4", "Door4", "Door4", "Entrada 4", "门口机 4", "Lobi 4", "Wejście 4", "Dveře 4", "الباب  4"},
        {"Door5", "Door5", "Door5", "Entrada 5", "门口机 5", "Lobi 5", "Wejście 5", "Dveře 5", "الباب  5"},
        {"Door6", "Door6", "Door6", "Entrada 6", "门口机 6", "Lobi 6", "Wejście 6", "Dveře 6", "الباب  6"},
        {"Door7", "Door7", "Door7", "Entrada 7", "门口机 7", "Lobi 7", "Wejście 7", "Dveře 7", "الباب  7"},
        {"Door8", "Door8", "Door8", "Entrada 8", "门口机 8", "Lobi 8", "Wejście 8", "Dveře 8", "الباب  8"},
        {"CCTV1", "CCTV1", "CCTV1", "CCTV1", "CCTV1", "CCTV1", "CCTV1", "CCTV1", "كاميرا مرا 1"},
        {"CCTV2", "CCTV2", "CCTV2", "CCTV2", "CCTV2", "CCTV2", "CCTV2", "CCTV2", "كاميرات مراقبة 2"},
        {"CCTV3", "CCTV3", "CCTV3", "CCTV3", "CCTV3", "CCTV3", "CCTV3", "CCTV3", "كاميرا مرا 3"},
        {"CCTV4", "CCTV4", "CCTV4", "CCTV4", "CCTV4", "CCTV4", "CCTV4", "CCTV4", "كاميرات مراقبة 4"},
        {"CCTV5", "CCTV5", "CCTV5", "CCTV5", "CCTV5", "CCTV5", "CCTV5", "CCTV5", "كاميرا مرا 5"},
        {"CCTV6", "CCTV6", "CCTV6", "CCTV6", "CCTV6", "CCTV6", "CCTV6", "CCTV6", "كاميرات مراقبة 6"},
        {"CCTV7", "CCTV7", "CCTV7", "CCTV7", "CCTV7", "CCTV7", "CCTV7", "CCTV7", "كاميرا مرا 7"},
        {"CCTV8", "CCTV8", "CCTV8", "CCTV8", "CCTV8", "CCTV8", "CCTV8",},
        /***** LANG_COMMON_ID_LANG *****/
        {"한국어", "中文(简体)", "English", "Русский", "Español", "Tiếng Việt", "عربي",},
};
/***
** 日期: 2022-04-28 13:55
** 作者: leo.liu
** 函数作用：获取公共字符串的字符串资源
** 返回参数说明：
***/
const char *language_common_string_get(int id)
{
        return lang_common_language[id][language_cur_id];
}
/***
**   日期:2022-05-24 10:04:38
**   作者: leo.liu
**   函数作用：根据通道类型获取字符串
**   参数说明:
***/
const char *language_common_ch_string_get(int ch)
{
        int group[10][2] =
            {
                {MON_CH_DOOR1, LANG_COMMON_ID_DOOR1},
                {MON_CH_DOOR2, LANG_COMMON_ID_DOOR2},
                {MON_CH_CCTV1, LANG_COMMON_ID_CCTV1},
                {MON_CH_CCTV2, LANG_COMMON_ID_CCTV2},
                {MON_CH_CCTV3, LANG_COMMON_ID_CCTV3},
                {MON_CH_CCTV4, LANG_COMMON_ID_CCTV4},
                {MON_CH_CCTV5, LANG_COMMON_ID_CCTV5},
                {MON_CH_CCTV6, LANG_COMMON_ID_CCTV6},
                {MON_CH_CCTV7, LANG_COMMON_ID_CCTV7},
                {MON_CH_CCTV8, LANG_COMMON_ID_CCTV8},
            };
        for (int i = 0; i < sizeof(group) / sizeof(int); i++)
        {
                if (group[i][0] == ch)
                {
                        return language_common_string_get(group[i][1]);
                }
        }
        return NULL;
}
