#ifndef _LAYOUT_SETTING_PASSWORD_H_
#define _LAYOUT_SETTING_PASSWORD_H_
typedef enum
{
        SETTING_PASSWORD_LANG_ID_RESET_HOUSEHOLD_PASSWORD,
        SETTING_PASSWORD_LANG_ID_RESET_COMMON_ENTRANCE_PASSWORD,
        SETTING_PASSWORD_LANG_ID_PASSWORD_RESET,
        SETTING_PASSWORD_LANG_ID_NEW_PASSWORD,
        SETTING_PASSWORD_LANG_ID_VERIFY_PASSWORD,
        SETTING_PASSWORD_LANG_ID_APPLE,
        SETTING_PASSWORD_LANG_ID_PASSWORD_NOT_MATCH,
        SETTING_PASSWORD_LANG_ID_OLD_PASSWORD,
        SETTING_PASSWORD_LANG_ID_TOTAL
} LAYOUT_SETTING_PASSWORD_LANG_ID;

static const char *layout_setting_password_language[SETTING_PASSWORD_LANG_ID_TOTAL][LANGUAGE_ID_TOTAL] =
    {

        {
            "Reset household password",
            "Reset household password",
            "Reset household password",
        },
        {
            "Reset common entrance password",
            "Reset common entrance password",
            "Reset common entrance password",
        },
        {
            "Password reset",
            "Password reset",
            "Password reset",
        },
        {
            "New password",
            "New password",
            "New password",
        },
        {
            "Verify password",
            "Verify password",
            "Verify password",
        },
        {
            "Apply",
            "Apply",
            "Apply",
        },
        {
            "The password does not match.",
            "The password does not match.",
            "The password does not match.",
        },
        {
            "Old password",
            "Old password",
            "Old password",
        },
};

/***
** 日期: 2022-04-26 09:16
** 作者: leo.liu
** 函数作用：获取home页面的字符串资源
** 返回参数说明：年/년 !@
***/
static inline const char *layout_setting_password_language_get(int id)
{
        return layout_setting_password_language[id][language_id_get()];
}

#endif