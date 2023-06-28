#include "common/language.h"
typedef enum
{
    SETTING_SENSOR_USAGE_LANG_ID_ALWAYS
    LAYOUT_SECURITY_LANG_ID_LANG_SEMSOR1,
    LAYOUT_SECURITY_LANG_ID_LANG_SEMSOR2,
    LAYOUT_SECURITY_LANG_ID_LANG_SEMSOR3,
    LAYOUT_SECURITY_LANG_ID_LANG_SEMSOR4,
    LAYOUT_SECURITY_LANG_ID_LANG_SEMSOR5,
    LAYOUT_SECURITY_LANG_ID_LANG_SEMSOR6,
    LAYOUT_SECURITY_LANG_ID_LANG_SEMSOR7,
    LAYOUT_SECURITY_LANG_ID_LANG_SEMSOR8,
    LAYOUT_SECURITY_LANG_ID_LANG_TOTAL
} LAYOUT_SECURITY_LANG_ID;

static const char *layout_security_general_language[LAYOUT_SECURITY_LANG_ID_LANG_TOTAL][LANGUAGE_ID_TOTAL] =
{
        {"Not used","Not used","Not used","Not used","Not used","Not used","Not used"},
        {"NO","NO","NO","NO","NO","NO","NO",},
        {"NC","NC","NC","NC","NC","NC","NC",},
        {"Always detect","Always detect","Always detect","Always detect","Always detect","Always detect","Always detect"}

};


static inline const char *layout_security_language_get(int id)
{
    return layout_security_general_language[id][language_id_get()];
}