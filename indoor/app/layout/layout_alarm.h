#include "common/language.h"
typedef enum
{
    LAYOUT_ALARM_LANG_ID_LANG_EMERHENCY,
    LAYOUT_ALARM_LANG_ID_LANG_SECURITY_EMERGENCY,
    LAYOUT_ALARM_LANG_ID_LANG_HOUSEHOLD_OPERATION,
    LAYOUT_ALARM_LANG_ID_LANG_SENSOR1,
    LAYOUT_ALARM_LANG_ID_LANG_SENSOR2,
    LAYOUT_ALARM_LANG_ID_LANG_SENSOR3,
    LAYOUT_ALARM_LANG_ID_LANG_SENSOR4,
    LAYOUT_ALARM_LANG_ID_LANG_SENSOR5,
    LAYOUT_ALARM_LANG_ID_LANG_SENSOR6,
    LAYOUT_ALARM_LANG_ID_LANG_SENSOR7,
    LAYOUT_ALARM_LANG_ID_LANG_STOP,
    LAYOUT_ALARM_LANG_ID_LANG_RETURN,
    LAYOUT_ALARM_LANG_ID_LANG_TOTAL
} LAYOUT_ALARM_LANG_ID;

static const char *layout_alarm_general_language[LAYOUT_ALARM_LANG_ID_LANG_TOTAL][LANGUAGE_ID_TOTAL] =
{
    {"emergency","emergency","emergency"}
};

static inline const char *layout_alarm_language_get(int id)
{
    return layout_alarm_general_language[id][language_id_get()];
}