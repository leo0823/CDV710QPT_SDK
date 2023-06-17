#ifndef _LAYOUT_SETTING_RECORDING_H_
#define _LAYOUT_SETTING_RECORDING_H_
#include "common/language.h"

typedef enum
{
        RECORDING_LANG_ID_AUTO_RECORIDNG_CALLS,
        RECORDING_LANG_ID_MOTION_DETECTION,
        RECORDING_LANG_ID_ALWAYS_MONITORING,
        RECORDING_LANG_ID_10_SEC_PER_CAMERA,
        RECORDING_LANG_ID_30_SEC_PER_CAMERA,
        RECORDING_LANG_ID_60_SEC_PER_CAMERA,
        RECORDING_LANG_ID_TOTAL
} LAYOUT_SETTING_RECORDING_LANG_ID;

static const char *layout_setting_recording_language[RECORDING_LANG_ID_TOTAL][LANGUAGE_ID_TOTAL] =
    {
        {"Automatic recording during calls", "Automatic recording during calls", "Automatic recording during calls"},
        {"Motion detection", "Motion detection", "Motion detection"},
        {"Always monitoring", "Always monitoring", "Always monitoring"},
        /***** SETTING_RECORD_LANG_ID_ALWAYS_10SEC *****/
        {"10 seconds per camera", "10 seconds per camera", "10 seconds per camera", "10 segundos por cámara", "每个摄像头10秒", "Her kamera icin 10 saniye", "Czas zapisu 10 sek.", "10 sekund na kameru", "10 ثواني"},
        /***** SETTING_RECORD_LANG_ID_ALWAYS_30SEC *****/
        {"30 seconds per camera", "30 seconds per camera", "30 seconds per camera", "30 segundos por cámara", "每个摄像头30秒", "Her kamera icin 30 saniye", "Czas zapisu 30 sek.", "30 sekund na kameru", "30 ثواني"},
        /***** SETTING_RECORD_LANG_ID_ALWAYS_60SEC *****/
        {"60 seconds per camera", "60 seconds per camera", "60 seconds per camera", "60 segundos por cámara", "每个摄像头60秒", "Her kamera icin 60 saniye", "Czas zapisu 60 sek.", "60 sekund na kameru", "60 ثواني"},
};

/***
** 日期: 2022-04-26 09:16
** 作者: leo.liu
** 函数作用：获取home页面的字符串资源
** 返回参数说明：年/년 !@
***/
static inline const char *layout_setting_recording_language_get(int id)
{
        return layout_setting_recording_language[id][language_id_get()];
}

#endif