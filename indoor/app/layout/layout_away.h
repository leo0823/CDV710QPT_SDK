#include "common/language.h"
typedef enum
{
    LAYOUT_AWAY_LANG_ID_LANG_DETECTS_INSTRUDERS,
    LAYOUT_AWAY_LANG_ID_LANG_OUT_GOING,
    LAYOUT_AWAY_LANG_ID_LANG_RELEASE,
    LAYOUT_AWAY_LANG_ID_LANG_AWAY,
    LAYOUT_AWAY_LANG_ID_LANG_END,
    LAYOUT_AWAY_LANG_ID_LANG_EXECUTION,
    LAYOUT_AWAY_LANG_ID_LANG_RUNNING,
    LAYOUT_AWAY_FUNCRION_SETTING_TIME,
    LAYOUT_AWAY_FUNCRION_RELEASE_TIME,
    LAYOUT_AWAY_SAVE_VISITORS_PHORO,
    LAYOUT_AWAY_BYPASS_CALL,
    LAYOUT_AWAY_RELEASE_TIME_SECOND_0,
    LAYOUT_AWAY_RELEASE_TIME_SECOND_10,
    LAYOUT_AWAY_RELEASE_TIME_SECOND_20,
    LAYOUT_AWAY_RELEASE_TIME_SECOND_30,
    LAYOUT_AWAY_RELEASE_TIME_SECOND_40,
    LAYOUT_AWAY_RELEASE_TIME_SECOND_50,
    LAYOUT_AWAY_RELEASE_TIME_SECOND_60,
    LAYOUT_AWAY_RELEASE_TIME_SECOND_70,
    LAYOUT_AWAY_RELEASE_TIME_SECOND_80,
    LAYOUT_AWAY_RELEASE_TIME_SECOND_90,
    LAYOUT_AWAY_SETTING_TIME_1_MINUTE,
    LAYOUT_AWAY_SETTING_TIME_2_MINUTE,
    LAYOUT_AWAY_SETTING_TIME_3_MINUTE,
    

    LAYOUT_AWAY_LANG_ID_LANG_TOTAL
} LAYOUT_AWAY_LANG_ID;

static const char *layout_away_general_language[LAYOUT_AWAY_LANG_ID_LANG_TOTAL][LANGUAGE_ID_TOTAL] =
    {
        {"Detects intruders inside and outside \nour house in away mode","Detects intruders inside and outside \nour house in away mode","Detects intruders inside and outside \nour house in away mode"},
        {"Outgoing time setting","Outgoing time setting","Outgoing time setting"},
        {"release time Setting","release time Setting","release time Setting"},

        {"외출", "外出", "Away","Отсутствие","Salida","Vắng nhà","بعيد"},

        {"종료", "结束", "End","thúc","Fin","Kết","إنهاء"},
        
        {"실행", "执行", "Execution","Выполнение","Ejecución","Thực hiện","تنفيذ"},

        {"외출기능이 실행중입니다.", "外出功能正在运行", "Away mode is running","Режим отсуствия активирован","El modo Salida está funcionando","Chế độ vắng nhà đang hoạt động","وضع الخروج قيد التشغيل "},

        {
            "외출기능 설정 시간",
            "外出功能设置时间",
            "Away function setting time",
            "Настройка периода задержки активации функции отсутствия",
            "Ajuste de hora de la función Salida",
            "Cài đặt thời gian vắng nhà",
            "التحكم بوقت وضعية الخروج"
        },
        {
            "외출기능 해제 시간",
            "外出功能解除时间",
            "Away function release time"
            "Время срабатыния сигнализации при использовании функции отсутствия",
            "Desactivación de tiempo de la función Salida",
            "Thời gian bắt đầu chế độ vắng nhà",
            "التحكم بإنهاء وقت وضعية الخروج "
        },
        {
            "방문자 사진 저장",
            "保存访客照片",
            "Save visitor photos",
            "Сохранить фото посетителя",
            "Guardar fotos de visitantes",
            "Lưu hình ảnh người đến thăm",
            "حفظ صور الزوار"
        },
        
        {
            "우회통화",
            "路旁呼叫",
            "Bypass Call",
            "Переадресация вызова",
            "Omitir llamada",
            "Bỏ qua cuộc gọi",
            "تجاوز المكالمة"
        },
        {
            "0 초","0 秒","0 seconds","0 секунд","0 segundos","0 giây","0 ثانية "
        },
        {
            "10 초","0 秒","10 seconds","10 секунд","10 segundos","10 giây","10 ثانية "
        },
        {
            "20 초","20 秒","20 seconds","20 секунд","20 segundos","20 giây","20 ثانية "
        },
        {
            "30 초","30 秒","30 seconds","30 секунд","30 segundos","30 giây","30 ثانية "
        },
        {
            "40 초","40 秒","40 seconds","40 секунд","40 segundos","40 giây","40 ثانية "
        },
        {
            "50 초","50 秒","50 seconds","50 секунд","50 segundos","50 giây","50 ثانية "
        },
        {
            "60 초","60 秒","60 seconds","60 секунд","60 segundos","60 giây","60 ثانية "
        },
        {
            "70 초","70 秒","70 seconds","70 секунд","70 segundos","70 giây","70 ثانية "
        },
        {
            "80 초","80 秒","80 seconds","80 секунд","80 segundos","80 giây","80 ثانية "
        },
        {
            "90 초","90 秒","90 seconds","90 секунд","90 segundos","90 giây","90 ثانية "
        },

};

static inline const char *layout_away_language_get(int id)
{
    return layout_away_general_language[id][language_id_get()];
}