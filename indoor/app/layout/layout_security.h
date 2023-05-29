#include "common/language.h"
typedef enum
{

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
        {
            "Security area\nsensor 1",
            "Security area\nsensor 1",
            "Security area\nsensor 1",
        },
        {
            "Security area\nsensor 2",
            "Security area\nsensor 2",
            "Security area\nsensor 2",
        },
        {
            "Security area\nsensor 3",
            "Security area\nsensor 3",
            "Security area\nsensor 3",
        },
        {
            "Security area\nsensor 4",
            "Security area\nsensor 4",
            "Security area\nsensor 4",
        },
        {
            "Security area\nsensor 5",
            "Security area\nsensor 5",
            "Security area\nsensor 5",
        },
        {
            "Security area\nsensor 6",
            "Security area\nsensor 6",
            "Security area\nsensor 6",
        },
        {
            "Security area\nsensor 7",
            "Security area\nsensor 7",
            "Security area\nsensor 7",
        },
        {
            "Security area\nsensor 8",
            "Security area\nsensor 8",
            "Security area\nsensor 8",
        },

};


static inline const char *layout_security_language_get(int id)
{
    return layout_security_general_language[id][language_id_get()];
}