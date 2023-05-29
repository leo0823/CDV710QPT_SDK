#include "common/language.h"
typedef enum
{

    LAYOUT_AWAY_LANG_ID_LANG_SEMSOR1,
    LAYOUT_AWAY_LANG_ID_LANG_SEMSOR2,
    LAYOUT_AWAY_LANG_ID_LANG_SEMSOR3,
    LAYOUT_AWAY_LANG_ID_LANG_SEMSOR4,
    
    LAYOUT_AWAY_LANG_ID_LANG_SEMSOR5,
    LAYOUT_AWAY_LANG_ID_LANG_SEMSOR6,
    LAYOUT_AWAY_LANG_ID_LANG_SEMSOR7,
    LAYOUT_AWAY_LANG_ID_LANG_SEMSOR8,

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

    

    LAYOUT_AWAY_LANG_ID_LANG_TOTAL
} LAYOUT_AWAY_LANG_ID;

static const char *layout_away_general_language[LAYOUT_AWAY_LANG_ID_LANG_TOTAL][LANGUAGE_ID_TOTAL] =
    {
        {
            "away area\nsensor 1",
            "away area\nsensor 1",
            "away area\nsensor 1",
        },
        {
            "away area\nsensor 2",
            "away area\nsensor 2",
            "away area\nsensor 2",
        },
        {
            "away area\nsensor 3",
            "away area\nsensor 3",
            "away area\nsensor 3",
        },
        {
            "away area\nsensor 4",
            "away area\nsensor 4",
            "away area\nsensor 4",
        },
        {
            "away area\nsensor 5",
            "away area\nsensor 5",
            "away area\nsensor 5",
        },
        {
            "away area\nsensor 6",
            "away area\nsensor 6",
            "away area\nsensor 6",
        },
        {
            "away area\nsensor 7",
            "away area\nsensor 7",
            "away area\nsensor 7",
        },
        {
            "away area\nsensor 8",
            "away area\nsensor 8",
            "away area\nsensor 8",
        },
        {
            "Away function setting time",
            "Away function setting time",
            "Away function setting time",
            "Away function setting time",
        },
        {
            "Away function release time",
            "Away function release time",
            "Away function release time"
        },
        {
            "Save visitor photos",
            "Save visitor photos",
            "Save visitor photos",
        },
        {
            "Bypass Call",
            "Bypass Call",
            "Bypass Call",
        },
        {
            "0 seconds","0 seconds","0 seconds",
        },
        {
            "10 seconds","10 seconds","10 seconds",
        },
        {
            "20 seconds","20 seconds","20 seconds",
        },
        {
            "30 seconds","30 seconds","30 seconds",
        },
        {
            "40 seconds","40 seconds","40 seconds",
        },
        {
            "50 seconds","50 seconds","50 seconds",
        },
        {
            "60 seconds","60 seconds","60 seconds",
        },
        {
            "70 seconds","70 seconds","70 seconds",
        },
        {
            "80 seconds","80 seconds","80 seconds",
        },
        {
            "90 seconds","90 seconds","90 seconds",
        },



};

static inline const char *layout_away_language_get(int id)
{
    return layout_away_general_language[id][language_id_get()];
}