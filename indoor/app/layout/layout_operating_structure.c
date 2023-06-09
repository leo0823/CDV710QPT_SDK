
#include "layout_define.h"
enum
{
        layout_operating_structure_obj_id_title,
        layout_operating_structure_obj_id_cancel,
        layout_operating_structure_obj_id_next,

        layout_operating_structure_obj_id_slave_setting_cont,
        layout_operating_structure_obj_id_slave_setting_title,
        layout_operating_structure_obj_id_slave_setting_sub,
        layout_operating_structure_obj_id_slave_setting_img,

        layout_operating_structure_obj_id_single_check,
        layout_operating_structure_obj_id_single_text,
        layout_operating_structure_obj_id_single_sub_text,

        layout_operating_structure_obj_id_server_check,
        layout_operating_structure_obj_id_server_text,
        layout_operating_structure_obj_id_server_sub_text,

        layout_operating_structure_obj_id_ver_line,
};
static void operating_structure_goto_layout_process(lv_scr_load_anim_t anim)
{
        if (user_data_get()->is_device_init == 0)
        {
                if (user_data_get()->system_mode == 0)
                {
                        sat_layout_goto(single_operation_network, anim, SAT_VOID);
                }
                else
                {
                        sat_layout_goto(server_operation_network, anim, SAT_VOID);
                }
        }
        else
        {
                sat_layout_goto(setting_installation, anim, SAT_VOID);
        }
}

static void operating_structure_cancel_btn_click(lv_event_t *e)
{
        operating_structure_goto_layout_process(LV_SCR_LOAD_ANIM_MOVE_RIGHT);
}
static void operating_structure_save_btn_click(lv_event_t *e)
{
        lv_obj_t *obj = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), layout_operating_structure_obj_id_single_check);
        if (obj == NULL)
        {
                return;
        }
        if (strstr((const char *)lv_obj_get_img_src(obj), "btn_radio_s.png"))
        {
                user_data_get()->system_mode = 0;
        }
        else
        {
                user_data_get()->system_mode = 1;
        }
        char number[32] = {0};
        memset(number, 0, sizeof(number));
        strncpy(number,network_data_get()->sip_user,11);
        sprintf(&number[11],"%d",1);
        memset(network_data_get()->sip_user, 0, sizeof(network_data_get()->sip_user));
        strcpy(network_data_get()->sip_user, number);
        setenv("SIP", network_data_get()->sip_user, 1);
        network_data_save();
        user_data_save();
        operating_structure_goto_layout_process(LV_SCR_LOAD_ANIM_FADE_IN);
}
static void operating_structure_slave_seting_click(lv_event_t *e)
{
        sat_layout_goto(slave_type_setting, LV_SCR_LOAD_ANIM_FADE_IN, SAT_VOID);
}

static void opearting_strutrue_single_server_obj_display(lv_obj_t *obj_s, int dst_obj_id)
{
        lv_obj_t *obj_n = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), dst_obj_id);
        if (obj_n == NULL)
        {
                return;
        }

        lv_obj_set_style_bg_img_src(obj_s, resource_ui_src_get("btn_radio_s.png"), LV_PART_MAIN);
        lv_obj_set_style_bg_img_src(obj_n, resource_ui_src_get("btn_radio_n.png"), LV_PART_MAIN);
}
static void operating_structrue_next_obj_display(void)
{
        lv_obj_t *obj = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), layout_operating_structure_obj_id_next);
        if (obj == NULL)
        {

                return;
        }
        if (lv_obj_has_flag(obj, LV_OBJ_FLAG_HIDDEN) == true)
        {

                lv_obj_clear_flag(obj, LV_OBJ_FLAG_HIDDEN);
        }
}
static void operating_structure_sub_info_display(int is_single)
{
        lv_obj_t *item = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), layout_operating_structure_obj_id_slave_setting_cont);
        lv_obj_t *sub_label = lv_obj_get_child_form_id(item, layout_operating_structure_obj_id_slave_setting_sub);
        lv_label_set_text(sub_label, lang_str_get(is_single == 0 ? SIGNLE_OPERATION_STRUCTURE_XLS_LANG_ID_SLAVE_SETTING_INFO : is_single == 1?SIGNLE_OPERATION_STRUCTURE_XLS_LANG_ID_SLAVE_SETTING_INFO_MSTAR : SIGNLE_OPERATION_STRUCTURE_XLS_LANG_ID_SLAVE_SETTING_ENABLE));
}

static void operating_structure_single_check_click(lv_event_t *e)
{
        lv_obj_t *obj_s = lv_event_get_current_target(e);
        if (obj_s == NULL)
        {
                return;
        }
        opearting_strutrue_single_server_obj_display(obj_s, layout_operating_structure_obj_id_server_check);
        operating_structure_sub_info_display(0);
        operating_structrue_next_obj_display();
}
static void operating_structure_server_check_click(lv_event_t *e)
{
        lv_obj_t *obj_s = lv_event_get_current_target(e);
        if (obj_s == NULL)
        {
                return;
        }
        opearting_strutrue_single_server_obj_display(obj_s, layout_operating_structure_obj_id_single_check);
        operating_structure_sub_info_display(1);
        operating_structrue_next_obj_display();
}


static void opearting_strutrue_single_server_init_display(void)
{
        lv_obj_t *obj_single = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), layout_operating_structure_obj_id_single_check);
        lv_obj_t *obj_server = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), layout_operating_structure_obj_id_server_check);
        
        if(user_data_get()->system_mode == 0)
        {
                lv_obj_set_style_bg_img_src(obj_single, resource_ui_src_get("btn_radio_s.png"), LV_PART_MAIN);
                lv_obj_set_style_bg_img_src(obj_server, resource_ui_src_get("btn_radio_n.png"), LV_PART_MAIN);
        }else if(user_data_get()->system_mode == 1)
        {
                lv_obj_set_style_bg_img_src(obj_server, resource_ui_src_get("btn_radio_s.png"), LV_PART_MAIN);
                lv_obj_set_style_bg_img_src(obj_single, resource_ui_src_get("btn_radio_n.png"), LV_PART_MAIN);    
        }else
        {
                lv_obj_set_style_bg_img_src(obj_server, resource_ui_src_get("btn_radio_n.png"), LV_PART_MAIN);
                lv_obj_set_style_bg_img_src(obj_single, resource_ui_src_get("btn_radio_n.png"), LV_PART_MAIN);    
        }

       
}

static void sat_layout_enter(operating_structure)
{

        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-2-2 13:46:56
        ** 说明: 标题显示
        ***********************************************/
        {
                lv_common_text_create(sat_cur_layout_screen_get(), layout_operating_structure_obj_id_title, 0, 20, 1024, 40,
                                      NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      lang_str_get(SIGNLE_OPERATION_STRUCTURE_XLS_LANG_ID_STRUCTURE), 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_CENTER, lv_font_large);
        }

        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-2-2 13:42:25
        ** 说明: 上一步下一步
        ***********************************************/
        {
                lv_common_img_btn_create(sat_cur_layout_screen_get(), layout_operating_structure_obj_id_cancel, 35, 15, 48, 48,
                                         operating_structure_cancel_btn_click, true, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0x808080,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         resource_ui_src_get("btn_title_back.png"), LV_OPA_COVER, 0x00a8ff, LV_ALIGN_CENTER);

                lv_obj_t *obj = lv_common_img_btn_create(sat_cur_layout_screen_get(), layout_operating_structure_obj_id_next, 912, 15, 80, 48,
                                                         operating_structure_save_btn_click, true, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0x808080,
                                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                         resource_ui_src_get("btn_title_check.png"), LV_OPA_COVER, 0x00a8ff, LV_ALIGN_CENTER);
                lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
        }
        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-2-2 13:42:50
        ** 说明: 设置按钮创建
        ***********************************************/
        {
                lv_common_setting_btn_title_sub_info_img_create(sat_cur_layout_screen_get(), layout_operating_structure_obj_id_slave_setting_cont, 48, 80, 928, 86,
                                                                operating_structure_slave_seting_click, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                                                0, 1, LV_BORDER_SIDE_BOTTOM, LV_OPA_COVER, 0x323237,
                                                                0, 1, LV_BORDER_SIDE_BOTTOM, LV_OPA_COVER, 0x00a8ff,
                                                                0, 8, 838, 50, layout_operating_structure_obj_id_slave_setting_title,
                                                                lang_str_get(SIGNLE_OPERATION_STRUCTURE_XLS_LANG_ID_SLAVE_SETTING), 0xFFFFFF, 0x00a8ff, LV_TEXT_ALIGN_LEFT, lv_font_normal,
                                                                0, 45, 838, 50, layout_operating_structure_obj_id_slave_setting_sub,
                                                                lang_str_get(SIGNLE_OPERATION_STRUCTURE_XLS_LANG_ID_SLAVE_SETTING_INFO), 0x6d6d79, 0x00484f, LV_TEXT_ALIGN_LEFT, lv_font_small,
                                                                0, 0, 0, 0, -1,
                                                                NULL, 0xFFFFFF, 0x0078Cf, LV_TEXT_ALIGN_LEFT, lv_font_normal,
                                                                880, 20, 48, 48, layout_operating_structure_obj_id_slave_setting_img,
                                                                resource_ui_src_get("ic_list_setting.png"), LV_OPA_COVER, 0x00a8ff, LV_ALIGN_CENTER);

                operating_structure_sub_info_display(user_data_get()->system_mode);
        }
        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-2-2 13:42:50
        ** 说明: single setting
        ***********************************************/
        {
                lv_common_img_btn_create(sat_cur_layout_screen_get(), layout_operating_structure_obj_id_single_check, 240, 243, 32, 32,
                                                                operating_structure_single_check_click, true, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0x808080,
                                                                0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                                0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                                resource_ui_src_get("btn_radio_s.png"), LV_OPA_TRANSP, 0x00a8ff, LV_ALIGN_CENTER);

                lv_common_img_btn_create(sat_cur_layout_screen_get(), layout_operating_structure_obj_id_server_check, 753, 243, 32, 32,
                                                                operating_structure_server_check_click, true, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0x808080,
                                                                0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                                0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                                resource_ui_src_get("btn_radio_s.png"), LV_OPA_TRANSP, 0x00a8ff, LV_ALIGN_CENTER);

                opearting_strutrue_single_server_init_display();
        }

        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-2-2 13:46:56
         ** 说明: 系统显示
         ***********************************************/
        {
                lv_common_text_create(sat_cur_layout_screen_get(), layout_operating_structure_obj_id_single_text, 0, 295, 511, 60,
                                      NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      lang_str_get(SIGNLE_OPERATION_NETWORK_XLS_LANG_ID_SINGLE), 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_CENTER, lv_font_small);

                lv_common_text_create(sat_cur_layout_screen_get(), layout_operating_structure_obj_id_single_sub_text, 100, 355, 311, 60,
                                      NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      lang_str_get(SIGNLE_OPERATION_STRUCTURE_XLS_LANG_ID_SINGLE), 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_CENTER, lv_font_small);

                lv_common_text_create(sat_cur_layout_screen_get(), layout_operating_structure_obj_id_server_text, 513, 295, 511, 60,
                                      NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      lang_str_get(SIGNLE_OPERATION_NETWORK_XLS_LANG_ID_SERVER_SYSTEM), 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_CENTER, lv_font_small);
                lv_common_text_create(sat_cur_layout_screen_get(), layout_operating_structure_obj_id_server_sub_text, 613, 355, 311, 60,
                                      NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      lang_str_get(SIGNLE_OPERATION_STRUCTURE_XLS_LANG_ID_SERVER_SYSTEM), 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_CENTER, lv_font_small);
        }
        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-2-2 13:44:0
        ** 说明: 垂直线显示
        ***********************************************/
        {
                lv_common_img_btn_create(sat_cur_layout_screen_get(), layout_operating_structure_obj_id_ver_line, 511, 168, 1, 432,
                                         NULL, false, LV_OPA_COVER, 0x323237, LV_OPA_TRANSP, 0,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         NULL, LV_OPA_TRANSP, 0, LV_ALIGN_CENTER);
        }
}
static void sat_layout_quit(operating_structure)
{
}

sat_layout_create(operating_structure);