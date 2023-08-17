// typedef enum
// {
//         layout_alarm_obj_id_number_keyboard_btn,
//         layout_alarm_password_input_obj_id_tips,
//         layout_alarm_password_input_obj_id_cancel,
//         layout_alarm_obj_id_passwd_input_tx1,
//         layout_alarm_obj_id_passwd_input_tx2,
//         layout_alarm_obj_id_passwd_input_tx3,
//         layout_alarm_obj_id_passwd_input_tx4,

// }passwd_cont_obj_id;

// static int parent_id = 0;
// /***********************************************
// ** 作者: leo.liu
// ** 日期: 2023-2-1 8:51:49
// ** 说明: 输入数字键盘
// ***********************************************/
// static lv_obj_t * layout_alarm_password_input_textarea_focused_get(void)
// {
//         lv_obj_t *textarea = NULL;

//         lv_obj_t *parent = lv_obj_get_child_form_id(sat_cur_layout_screen_get(),  parent_id);
//         for (int i = 0; i < 2; i++)
//         {
               
//                 for (int j = 0; j < 4; j++)
//                 {
//                         textarea = lv_obj_get_child_form_id(parent,  layout_alarm_obj_id_passwd_input_tx1 + j);
//                         if (lv_obj_get_state(textarea) == LV_STATE_FOCUSED)
//                         {
//                             return textarea;
//                         }
//                 }
//         }
//         return textarea;
// }


// static void passwd_incorrect_timer(lv_timer_t *ptimer)
// {
//         lv_obj_t *parent = lv_obj_get_child_form_id(sat_cur_layout_screen_get(),  parent_id);
//         lv_obj_set_style_bg_color(parent, lv_color_hex(0x0), LV_PART_MAIN);
//         lv_timer_del(ptimer);

// }

// static void  layout_alarm_passwd_input_text_next_foucued(void)
// {
//         lv_obj_t *textarea = NULL;

//         lv_obj_t *parent = lv_obj_get_child_form_id(sat_cur_layout_screen_get(),  parent_id);
   
//         for (int j = 0; j < 4; j++)
//         {
//                 textarea = lv_obj_get_child_form_id(parent,  layout_alarm_obj_id_passwd_input_tx1 + j);
//                 if (lv_obj_get_state(textarea) == LV_STATE_FOCUSED)
//                 {
//                         if(j == 3)
//                         {
//                         char buffer[4];
//                         memset(buffer,0,sizeof(buffer));
                        
//                         for(int k =0;k<4;k++)
//                         {
//                                 strcat(buffer,lv_textarea_get_text(lv_obj_get_child_form_id(parent,  layout_alarm_obj_id_passwd_input_tx1 + k)));
//                         }
//                         if(strncmp(user_data_get()->etc.password,buffer,4) == 0)
//                         {
//                                 // lv_obj_add_flag(lv_obj_get_child_form_id(sat_cur_layout_screen_get(), parent_id), LV_OBJ_FLAG_HIDDEN);
//                                 user_data_get()->alarm.security_alarm_enable = false;
//                                 user_data_get()->alarm.security_alarm_enable_list = 0x00;
//                                 user_data_save();
//                                 sat_layout_goto(security,LV_SCR_LOAD_ANIM_FADE_IN, SAT_VOID);
//                         }
                        
//                         lv_obj_set_style_bg_color(parent, lv_color_hex(0x5E0000), LV_PART_MAIN);
//                         lv_sat_timer_create(passwd_incorrect_timer, 500, NULL);
//                         for(int k = 0;k < 4;k++)
//                         {
//                                 textarea = lv_obj_get_child_form_id(parent,  layout_alarm_obj_id_passwd_input_tx1 + k);
//                                 lv_textarea_del_char(textarea);
//                                 lv_obj_clear_state(textarea, LV_STATE_FOCUSED);
//                         }
//                         textarea = lv_obj_get_child_form_id(parent,  layout_alarm_obj_id_passwd_input_tx1);
//                         lv_obj_add_state(textarea, LV_STATE_FOCUSED);
//                         return ;                              
//                         }
//                         lv_obj_clear_state(textarea, LV_STATE_FOCUSED);
//                         textarea = lv_obj_get_child_form_id(parent,  layout_alarm_obj_id_passwd_input_tx1 + j + 1);
//                         lv_obj_add_state(textarea, LV_STATE_FOCUSED);
//                         return;
//                 }
                
//         }
        
// }
// static void  layout_alarm_passwd_input_text_prev_foucued(void)
// {
//         lv_obj_t *textarea = NULL;

//         lv_obj_t *parent = lv_obj_get_child_form_id(sat_cur_layout_screen_get(),  parent_id);

//         for (int j = 0; j < 4; j++)
//         {
//                 textarea = lv_obj_get_child_form_id(parent,  layout_alarm_obj_id_passwd_input_tx1 + j);
//                 if ((lv_obj_get_state(textarea) == LV_STATE_FOCUSED) && (j != 0))
//                 {
//                     lv_obj_clear_state(textarea, LV_STATE_FOCUSED);
//                     textarea = lv_obj_get_child_form_id(parent,  layout_alarm_obj_id_passwd_input_tx1 + j - 1);
//                     lv_obj_add_state(textarea, LV_STATE_FOCUSED);
//                     return;
//                 }
//         }
        
// }

// static bool  layout_alarm_password_input_textbox_del(void)
// {
//          layout_alarm_passwd_input_text_prev_foucued();
//         lv_obj_t *textarea =  layout_alarm_password_input_textarea_focused_get();

//         if (textarea == NULL)
//         {
//                 return false;
//         }
//         lv_textarea_del_char(textarea);

//         return true;
// }

// static bool  layout_alarm_passwd_inpu_textbox_add(const char *string)
// {
//         lv_obj_t *textarea =  layout_alarm_password_input_textarea_focused_get();

//         if (textarea == NULL)
//         {
//                 return false;
//         }

//         lv_textarea_add_text(textarea, string);
//          layout_alarm_passwd_input_text_next_foucued();
//         return true;
// }

// static void  layout_alarm_password_input_keyboard_click(lv_event_t *ev)
// {
//         lv_obj_t *obj = lv_event_get_target(ev);
//         uint32_t id = lv_btnmatrix_get_selected_btn(obj);

//         if (id == 11)
//         {
//                  layout_alarm_password_input_textbox_del();
//         }
//         else
//         {
//                 const char *text = lv_btnmatrix_get_btn_text(obj, id);

//                 if (text != NULL)
//                 {

//                          layout_alarm_passwd_inpu_textbox_add(text);
//                 }
//         }
// }

// void layout_alarm_passwd_input(int id)
// {
//             parent_id = parent_id;
//             lv_obj_t * parent = lv_common_img_btn_create(sat_cur_layout_screen_get(), parent_id, 0, 0, 1024, 600,
//                                         NULL, false, LV_OPA_90, 0, LV_OPA_90, 0,
//                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
//                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
//                                         NULL, LV_OPA_TRANSP, 0x00a8ff, LV_ALIGN_CENTER);
            
//             lv_obj_add_flag(parent, LV_OBJ_FLAG_HIDDEN);

//             /************************************************************
//             ** 函数说明: 数字键盘创建
//             ** 作者: xiaoxiao
//             ** 日期: 2023-04-27 16:40:03
//             ** 参数说明: 
//             ** 注意事项: 
//             ************************************************************/
//             {
//                 lv_obj_t *obj = lv_common_number_input_keyboard_create(parent, layout_alarm_obj_id_number_keyboard_btn, 128, 90, 312, 500,
//                                                      layout_alarm_password_input_keyboard_click, LV_OPA_COVER, 0X101010, LV_OPA_COVER, 0x00a8ff,
//                                                     360, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
//                                                     360, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
//                                                     0XFFFFFF, 0XFFFFFF, LV_TEXT_ALIGN_CENTER, lv_font_large,
//                                                     18, 24);
//                 lv_btnmatrix_set_btn_ctrl(obj, 9, LV_BTNMATRIX_CTRL_HIDDEN);
//             }

//             /************************************************************
//             ** 函数说明: 密码提示
//             ** 作者: xiaoxiao
//             ** 日期: 2023-04-27 17:50:33
//             ** 参数说明: 
//             ** 注意事项: 
//             ************************************************************/
//             {
//                     lv_common_text_create(parent, layout_alarm_password_input_obj_id_tips, 644, 198, 217, 43,
//                                         NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
//                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
//                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
//                                        "Enter Password", 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_CENTER, lv_font_normal);
//             }

//             /************************************************************
//             ** 函数说明: 密码文本输入框创建
//             ** 作者: xiaoxiao
//             ** 日期: 2023-04-27 17:30:01
//             ** 参数说明: 
//             ** 注意事项: 
//             ************************************************************/
//             for (int j = 0; j < 4; j++)
//             {

//                 lv_obj_t *obj = lv_common_textarea_create(parent, layout_alarm_obj_id_passwd_input_tx1+j, 596 + 84 * j, 262, 60, 76,
//                                                             NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0X101010,
//                                                             LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0X101010,
//                                                             0, 4, LV_BORDER_SIDE_BOTTOM, LV_OPA_COVER, 0Xffffff,
//                                                             0, 4, LV_BORDER_SIDE_BOTTOM, LV_OPA_COVER, 0x00a8ff,
//                                                             NULL, 0Xffffff, 0Xffffff, LV_TEXT_ALIGN_CENTER, lv_font_large, 1,
//                                                             20, 500, 0Xffffff);

//                 lv_textarea_set_password_mode(obj, true);
//                 lv_textarea_set_password_show_time(obj, 500);
//                 lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
//                 if (j == 0)
//                 {
//                         lv_obj_add_state(obj, LV_STATE_FOCUSED);
//                 }
//             }

//             /***********************************************
//             ** 作者: leo.liu
//             ** 日期: 2023-2-3 14:13:25
//             ** 说明: 返回按钮
//             ***********************************************/
//             {
//                     lv_common_img_btn_create(parent, layout_alarm_password_input_obj_id_cancel, 35, 15, 48, 48,
//                                                         NULL, true, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0x808080,
//                                             0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
//                                             0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
//                                             resource_ui_src_get("btn_close.png"), LV_OPA_COVER, 0x00a8ff, LV_ALIGN_CENTER);
//             }
// }            
