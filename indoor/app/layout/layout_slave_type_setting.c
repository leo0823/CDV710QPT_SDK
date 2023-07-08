#include "layout_define.h"
#include "layout_setting_general.h"
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

        slave_type_setting_obj_id_list,

        slave_type_setting_obj_id_titile_id,

        slave_type_setting_obj_id_msgbox_confirm,

        slave_type_setting_obj_id_msgbox_cancel,
};

typedef enum
{
        slave_type_setting_obj_id_checkbox,
}slave_type_setting_list;

static void slave_type_setting_cancel_click(lv_event_t *e)
{
        sat_layout_goto(operating_structure, LV_SCR_LOAD_ANIM_MOVE_RIGHT, SAT_VOID);
}
static void slave_type_setting_master_indoor_click(lv_event_t *e)
{
        sat_layout_goto(setting_master_indoor_unit_ip, LV_SCR_LOAD_ANIM_MOVE_LEFT, SAT_VOID);
}

static void slave_type_setting_extension_number_display(void)
{
        lv_obj_t * extension_number = lv_obj_get_child_form_id(lv_obj_get_child_form_id(sat_cur_layout_screen_get(),slave_type_setting_obj_id_extension_number_cont),slave_type_setting_obj_id_extension_number_sub);
        if(user_data_get()->system_mode <= 1)
        {
                lv_label_set_text(extension_number,lang_str_get(LAYOUT_SLAVE_TYPE_SETTING_XLS_LANG_ID_NOT_SET));
        }else
        {
                lv_label_set_text_fmt(extension_number,"ID %d",user_data_get()->system_mode);
        }
}


static void  slave_type_setting_cancel_func(lv_event_t *ev)
{
        setting_msgdialog_msg_del(slave_type_setting_obj_id_msgbox_bg_cont);
        
}


static void  slave_type_setting_confirm_func(lv_event_t *ev)
{
        lv_obj_t *parent = lv_obj_get_parent(lv_event_get_current_target(ev));
        for(int i =0;i < 7; i++)
        {
                lv_obj_t * list = lv_obj_get_child_form_id(parent, slave_type_setting_obj_id_list);

                lv_obj_t * checkbox = lv_obj_get_child_form_id(lv_obj_get_child_form_id(list,i),1);

                if (!strncmp((const char *)checkbox->bg_img_src, resource_ui_src_get("btn_radio_s.png"), strlen(resource_ui_src_get("btn_radio_s.png"))))
                {
                        user_data_get()->system_mode = i + 2;
                        char number[32] = {0};
                        memset(number, 0, sizeof(number));
                        strncpy(number,network_data_get()->sip_user,11);
                        sprintf(&number[11],"%d",i+2);
                        memset(network_data_get()->sip_user, 0, sizeof(network_data_get()->sip_user));
                        strcpy(network_data_get()->sip_user, number);
                        setenv("SIP", network_data_get()->sip_user, 1);
                        network_data_save();
                        user_data_save();
                break;

                }
        }
        setting_msgdialog_msg_del(slave_type_setting_obj_id_msgbox_bg_cont);
        slave_type_setting_extension_number_display();
}

static void slave_type_setting_extension_number_list_display(lv_obj_t * parent)
{
        for(int i = 0; i < 7;i++)
        {
                lv_obj_t * obj = lv_obj_get_child_form_id(parent,i);
                lv_obj_t * numb = lv_obj_get_child_form_id(obj,0);
                lv_obj_t * checkbox = lv_obj_get_child_form_id(obj,1);
                if(numb != NULL)
                {
                        lv_label_set_text_fmt(numb,"ID %d",i + 2);
                }
                if(obj->id == user_data_get()->system_mode - 2)
                {
                        lv_obj_set_style_bg_img_src(checkbox, resource_ui_src_get("btn_radio_s.png"), LV_PART_MAIN);
                }else
                {
                        lv_obj_set_style_bg_img_src(checkbox, resource_ui_src_get("btn_radio_n.png"), LV_PART_MAIN);
                }
        }
        
}


static void setting_extension_number_list_click(lv_event_t *ev)
{
        lv_obj_t *item = lv_event_get_current_target(ev);
        if (item == NULL)
        {
                return;
        }
        lv_obj_t *parent = lv_obj_get_parent(item);
        if (parent == NULL)
        {
                return;
        }

        lv_obj_t *item_img_obj = lv_obj_get_child_form_id(item, 1);
        if (item_img_obj == NULL)
        {
                return;
        }
        if (strncmp(item_img_obj->bg_img_src, "btn_radio_s.png", strlen("btn_radio_s.png")))
        {
                lv_obj_set_style_bg_img_src(item_img_obj, resource_ui_src_get("btn_radio_s.png"), LV_PART_MAIN);

                for (int i = 0; i < 8; i++)
                {
                        lv_obj_t *n_item = lv_obj_get_child_form_id(parent, i);
                        if ((n_item == NULL) || (n_item == item))
                        {
                                continue;
                        }
                        item_img_obj = lv_obj_get_child_form_id(n_item, 1);
                        if (strncmp(item_img_obj->bg_img_src, "btn_radio_s.png", strlen("btn_radio_s.png")))
                        {
                                lv_obj_set_style_bg_img_src(item_img_obj, resource_ui_src_get("btn_radio_n.png"), LV_PART_MAIN);
                        }
                }
        }
}

static void slave_type_setting_extension_number_click(lv_event_t *e)
{
        lv_obj_t * msgbox = setting_msgdialog_msg_bg_create(slave_type_setting_obj_id_msgbox_bg_cont,slave_type_setting_obj_id_msgbox_cont, 282, 143, 460, 356);
        lv_obj_t *list = setting_list_create(msgbox, slave_type_setting_obj_id_list);
        lv_common_style_set_common(list, slave_type_setting_obj_id_list, 27, 10, 460 - 27, 273, LV_ALIGN_TOP_LEFT, LV_PART_MAIN);
        for(int i =0; i<7; i++)
        {
                lv_common_img_text_btn_create(list, i, 0, 0, 366, 55,
                                        setting_extension_number_list_click, LV_OPA_TRANSP, 0x00, LV_OPA_TRANSP, 0x101010,
                                        0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                        0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                        46, 8, 366 - 16, 32, 0,
                                        "501", 0xffffff, 0x00a8ff, LV_TEXT_ALIGN_LEFT, lv_font_normal,
                                        0, 8, 32, 32, 1,
                                        (const char *)resource_ui_src_get("btn_radio_n.png")
                                        , LV_OPA_TRANSP, 0x00a8ff, LV_ALIGN_CENTER);
        }
        slave_type_setting_extension_number_list_display(list);
        setting_msgdialog_msg_confirm_and_cancel_btn_create(msgbox,slave_type_setting_obj_id_msgbox_confirm,slave_type_setting_obj_id_msgbox_cancel ,slave_type_setting_confirm_func,slave_type_setting_cancel_func);
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
                                      lang_str_get(LAYOUT_SLAVE_TYPE_SETTING_XLS_LANG_ID_SLAVE_TYPE_SETTING), 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_CENTER, lv_font_large);
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
                                                                lang_str_get(LAYOUT_SLAVE_TYPE_SETTING_XLS_LANG_ID_MASTTER_INDOOR), 0xFFFFFF, 0x00a8ff, LV_TEXT_ALIGN_LEFT, lv_font_normal,
                                                                0, 45, 838, 50, slave_type_setting_obj_id_master_indoor_sub,
                                                                lang_str_get(LAYOUT_SLAVE_TYPE_SETTING_XLS_LANG_ID_NOT_SET), 0x6d6d79, 0x00484f, LV_TEXT_ALIGN_LEFT, lv_font_small,
                                                                0, 0, 0, 0, -1,
                                                                NULL, 0xFFFFFF, 0x0078Cf, LV_TEXT_ALIGN_LEFT, lv_font_normal,
                                                                880, 20, 48, 48, -1,
                                                                NULL, LV_OPA_COVER, 0x00a8ff, LV_ALIGN_CENTER);

                lv_common_setting_btn_title_sub_info_img_create(sat_cur_layout_screen_get(), slave_type_setting_obj_id_extension_number_cont, 48, 168, 928, 86,
                                                                slave_type_setting_extension_number_click, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                                                0, 1, LV_BORDER_SIDE_BOTTOM, LV_OPA_COVER, 0x323237,
                                                                0, 1, LV_BORDER_SIDE_BOTTOM, LV_OPA_COVER, 0x00a8ff,
                                                                0, 8, 838, 50, slave_type_setting_obj_id_extension_number_title,
                                                                lang_str_get(LAYOUT_SLAVE_TYPE_SETTING_XLS_LANG_ID_EXTENSION_NUMBER), 0xFFFFFF, 0x00a8ff, LV_TEXT_ALIGN_LEFT, lv_font_normal,
                                                                0, 45, 838, 50, slave_type_setting_obj_id_extension_number_sub,
                                                                lang_str_get(LAYOUT_SLAVE_TYPE_SETTING_XLS_LANG_ID_NOT_SET), 0x6d6d79, 0x00484f, LV_TEXT_ALIGN_LEFT, lv_font_small,
                                                                0, 0, 0, 0, -1,
                                                                NULL, 0xFFFFFF, 0x0078Cf, LV_TEXT_ALIGN_LEFT, lv_font_normal,
                                                                880, 20, 48, 48, -1,
                                                                NULL, LV_OPA_COVER, 0x00a8ff, LV_ALIGN_CENTER);
                slave_type_setting_extension_number_display();
        }
}
static void sat_layout_quit(slave_type_setting)
{
}

sat_layout_create(slave_type_setting);