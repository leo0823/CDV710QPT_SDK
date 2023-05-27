#ifndef _OPERATING_STRUCTURE_H_
#define _OPERATING_STRUCTURE_H_
typedef enum
{

    SIGNLE_OPERATION_STRUCTURE_ID_LANG_STRUCTURE,
    SIGNLE_OPERATION_STRUCTURE_ID_LANG_SLAVE_SETTING,
    SIGNLE_OPERATION_STRUCTURE_ID_LANG_SLAVE_SETTING_INFO,
    SIGNLE_OPERATION_STRUCTURE_ID_LANG_SLAVE_SETTING_INFO_MSTAR,
    SIGNLE_OPERATION_STRUCTURE_ID_LANG_SINGLE,
    SIGNLE_OPERATION_STRUCTURE_ID_LANG_SERVER_SYSTEM,
    SIGNLE_OPERATION_STRUCTURE_ID_LANG_TOTAL
} LAYOUT_SIGNLE_OPERATION_STRUCTURE_LANG_ID;

static const char *layout_operation_structure_language[SIGNLE_OPERATION_STRUCTURE_ID_LANG_TOTAL][LANGUAGE_ID_TOTAL] =
    {
        {
            "Operating structure",
            "Operating structure",
            "Operating structure",
        },
        {
            "Slave settings",
            "Slave settings",
            "Slave settings",
        },

        {"This is the sub indoor unit setting linked with the master unit.",
         "This is the sub indoor unit setting linked with the master unit.",
         "This is the sub indoor unit setting linked with the master unit."},

        {"This is the sub indoor unit setting linked with the master indoor unit.",
         "This is the sub indoor unit setting linked with the master indoor unit.",
         "This is the sub indoor unit setting linked with the master indoor unit."},

        {"Single\n\nOperating with master indoor unit \nand door camera (Basic)",
         "Single\n\nOperating with master indoor unit \nand door camera (Basic)",
         "Single\n\nOperating with master indoor unit \nand door camera (Basic)"},

        {"Server system\n\nOperating with server-based guard station\nand common entrance",
         "Server system\n\nOperating with server-based guard station\nand common entrance",
         "Server system\n\nOperating with server-based guard station\nand common entrance"}};
/***
** 日期: 2022-04-26 09:16
** 作者: leo.liu
** 函数作用：获取home页面的字符串资源
** 返回参数说明：年/년 !@
***/
static inline const char *layout_operation_structure_language_get(LAYOUT_SIGNLE_OPERATION_STRUCTURE_LANG_ID id)
{
    return layout_operation_structure_language[id][language_id_get()];
}
#endif