#include "common/language.h"
typedef enum
{
    LAYOUT_EMERGENCY_LANG_ID_LANG_EMERGENCY,
    LAYOUT_EMERGENCY_LANG_ID_LANG_TIP,
    LAYOUT_EMERGENCY_LANG_ID_LANG_CONFIRM,

    LAYOUT_EMERGENCY_LANG_ID_LANG_TOTAL
} LAYOUT_EMERGENCY_LANG_ID;

static const char *layout_away_general_language[LAYOUT_EMERGENCY_LANG_ID_LANG_TOTAL][LANGUAGE_ID_TOTAL] =
{
 

};

static inline const char *layout_emergency_language_get(int id)
{
    return layout_emergency_general_language[id][language_id_get()];
}