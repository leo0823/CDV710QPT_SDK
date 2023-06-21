#include "layout_define.h"
#include "layout_slave_type_setting.h"
enum
{
        slave_type_setting_obj_id_title,
        slave_type_setting_obj_id_cancel,

        slave_type_setting_obj_id_master_indor_cont,
        slave_type_setting_obj_id_master_indoor_tile,
        slave_type_setting_obj_id_master_indoor_sub,

        slave_type_setting_obj_id_extension_number_cont,
        slave_type_setting_obj_id_extension_number_title,
        slave_type_setting_obj_id_extension_number_sub,

        slave_type_setting_obj_id_msgbox_bg_cont,

        slave_type_setting_obj_id_msgbox_cont,

        slave_type_setting_obj_id_titile_id,

        slave_type_setting_obj_id_msgbox_confirm,

        slave_type_setting_obj_id_msgbox_cancel,
};

static void slave_type_setting_cancel_click(lv_event_t *e)
{
        sat_layout_goto(operating_structure, LV_SCR_LOAD_ANIM_MOVE_RIGHT, SAT_VOID);
}
static void slave_type_setting_master_indoor_click(lv_event_t *e)
{
        sat_layout_goto(setting_master_indoor_unit_ip, LV_SCR_LOAD_ANIM_MOVE_LEFT, SAT_VOID);
}
static void slave_type_setting_extension_number_click(lv_event_t *e)
{
        lv_obj_t * masgbox = setting_msgdialog_msg_bg_create(slave_type_setting_obj_id_msgbox_bg_cont,slave_type_setting_obj_id_msgbox_cont, 282, 143, 460, 283);
        setting_msgdialog_msg_create(masgbox,slave_type_setting_obj_id_titile_id,"The outing is currently running.The 'Not used' setting is applied after the end of the outing.", 0, 90, 460, 80);
        setting_msgdialog_msg_confirm_and_cancel_btn_create(masgbox,slave_type_setting_obj_id_msgbox_confirm,slave_type_setting_obj_id_msgbox_cancel ,"Confirm","Cancel", NULL,NULL);
}

static void sat_layout_enter(slave_type_setting)
{
        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-2-2 13:46:56
         ** 说明: 标题显示
         ***********************************************/
        {
                lv_common_text_create(sat_cur_layout_screen_get(), slave_type_setting_obj_id_title, 0, 20, 1024, 40,
                                      NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      layout_slave_type_setting_language_get(LAYOUT_SLAVE_TYPE_SETTING_LANG_ID_SLAVE_TYPE_SETTING), 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_CENTER, lv_font_large);
        }

        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-2-2 13:42:25
        ** 说明: 上一步
        ***********************************************/
        {
                lv_common_img_btn_create(sat_cur_layout_screen_get(), slave_type_setting_obj_id_cancel, 35, 15, 48, 48,
                                         slave_type_setting_cancel_click, true, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0x808080,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         resource_ui_src_get("btn_title_back.png"), LV_OPA_COVER, 0x00a8ff, LV_ALIGN_CENTER);
        }

        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-2-2 13:42:50
        ** 说明: 设置master创建
        ***********************************************/
        {
                lv_common_setting_btn_title_sub_info_img_create(sat_cur_layout_screen_get(), slave_type_setting_obj_id_master_indor_cont, 48, 80, 928, 86,
                                                                slave_type_setting_master_indoor_click, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                                                0, 1, LV_BORDER_SIDE_BOTTOM, LV_OPA_COVER, 0x323237,
                                                                0, 1, LV_BORDER_SIDE_BOTTOM, LV_OPA_COVER, 0x00a8ff,
                                                                0, 8, 838, 50, slave_type_setting_obj_id_master_indoor_tile,
                                                                layout_slave_type_setting_language_get(LAYOUT_SLAVE_TYPE_SETTING_LANG_ID_MASTTER_INDOOR), 0xFFFFFF, 0x00a8ff, LV_TEXT_ALIGN_LEFT, lv_font_normal,
                                                                0, 45, 838, 50, slave_type_setting_obj_id_master_indoor_sub,
                                                                layout_slave_type_setting_language_get(LAYOUT_SLAVE_TYPE_SETTING_LANG_ID_NOT_SET), 0x6d6d79, 0x00484f, LV_TEXT_ALIGN_LEFT, lv_font_small,
                                                                0, 0, 0, 0, -1,
                                                                NULL, 0xFFFFFF, 0x0078Cf, LV_TEXT_ALIGN_LEFT, lv_font_normal,
                                                                880, 20, 48, 48, -1,
                                                                NULL, LV_OPA_COVER, 0x00a8ff, LV_ALIGN_CENTER);

                lv_common_setting_btn_title_sub_info_img_create(sat_cur_layout_screen_get(), slave_type_setting_obj_id_extension_number_cont, 48, 168, 928, 86,
                                                                slave_type_setting_extension_number_click, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                                                0, 1, LV_BORDER_SIDE_BOTTOM, LV_OPA_COVER, 0x323237,
                                                                0, 1, LV_BORDER_SIDE_BOTTOM, LV_OPA_COVER, 0x00a8ff,
                                                                0, 8, 838, 50, slave_type_setting_obj_id_extension_number_title,
                                                                layout_slave_type_setting_language_get(LAYOUT_SLAVE_TYPE_SETTING_LANG_ID_EXTENSION_NUMBER), 0xFFFFFF, 0x00a8ff, LV_TEXT_ALIGN_LEFT, lv_font_normal,
                                                                0, 45, 838, 50, slave_type_setting_obj_id_extension_number_sub,
                                                                layout_slave_type_setting_language_get(LAYOUT_SLAVE_TYPE_SETTING_LANG_ID_NOT_SET), 0x6d6d79, 0x00484f, LV_TEXT_ALIGN_LEFT, lv_font_small,
                                                                0, 0, 0, 0, -1,
                                                                NULL, 0xFFFFFF, 0x0078Cf, LV_TEXT_ALIGN_LEFT, lv_font_normal,
                                                                880, 20, 48, 48, -1,
                                                                NULL, LV_OPA_COVER, 0x00a8ff, LV_ALIGN_CENTER);
        }
}
static void sat_layout_quit(slave_type_setting)
{
}

sat_layout_create(slave_type_setting);