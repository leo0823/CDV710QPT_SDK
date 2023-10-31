
#include "layout_define.h"

enum
{
	setting_single_operation_network_obj_id_titile_label,
	setting_single_operation_network_obj_id_cancel_btn,
	setting_single_operation_network_obj_id_next_btn,

	/***********************************************
	** 作者: leo.liu
	** 日期: 2023-1-31 16:0:12
	** 说明: operating structure
	***********************************************/
	setting_single_operation_network_obj_id_operating_structure_cont,
	setting_single_operation_network_obj_id_operating_structure_title_lable,
	setting_single_operation_network_obj_id_operating_structure_single_label,
	setting_single_operation_network_obj_id_operating_structure_img,

	/***********************************************
	** 作者: leo.liu
	** 日期: 2023-2-1 8:50:19
	** 说明: 数字键盘
	***********************************************/
	setting_single_operation_network_obj_id_number_keyboard_btn,

	/***********************************************
	** 作者: leo.liu
	** 日期: 2023-2-1 13:43:33
	** 说明: ip文本框
	***********************************************/
	setting_single_operation_network_obj_id_ip_textbox,
	setting_single_operation_network_obj_id_gateway_textbox,
	setting_single_operation_network_obj_id_mask_textbox,
	setting_single_operation_network_obj_id_dns_textbox,

	/***********************************************
	** 作者: leo.liu
	** 日期: 2023-2-1 13:43:33
	** 说明: ip文本显示
	***********************************************/
	setting_single_operation_network_obj_id_ip_label,
	setting_single_operation_network_obj_id_gateway_label,
	setting_single_operation_network_obj_id_mask_label,
	setting_single_operation_network_obj_id_dns_label,

	/***********************************************
	** 作者: leo.liu
	** 日期: 2023-2-2 9:14:54
	** 说明: 垂直线
	***********************************************/
	setting_single_operation_network_obj_id_ver_line,
};

static void setting_single_operation_network_cancel_btn_click(lv_event_t *ev)
{
	sat_layout_goto(power_setting, LV_SCR_LOAD_ANIM_MOVE_RIGHT, SAT_VOID);
}

static void setting_single_operation_network_next_btn_click(lv_event_t *ev)
{
	sat_layout_goto(setting_user_wifi, LV_SCR_LOAD_ANIM_MOVE_LEFT, SAT_VOID);
}

/***********************************************
** 作者: leo.liu
** 日期: 2023-1-31 16:3:29
** 说明: 创建operating structure
***********************************************/
static void setting_single_operating_btn_click(lv_event_t *ev)
{
	sat_layout_goto(operating_structure, LV_SCR_LOAD_ANIM_FADE_IN, SAT_VOID);
}

/***********************************************
** 作者: leo.liu
** 日期: 2023-2-1 8:51:49
** 说明: 输入数字键盘
***********************************************/
static lv_obj_t *setting_single_textarea_focused_get(void)
{

	int obj_id[] = {
	    setting_single_operation_network_obj_id_ip_textbox,
	    setting_single_operation_network_obj_id_gateway_textbox,
	    setting_single_operation_network_obj_id_mask_textbox,
	    setting_single_operation_network_obj_id_dns_textbox};

	lv_obj_t *textarea = NULL;

	for (int i = 0; i < sizeof(obj_id) / sizeof(int); i++)
	{

		textarea = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), obj_id[i]);

		if ((textarea != NULL) && (lv_obj_get_state(textarea) & LV_STATE_FOCUSED))
		{

			return textarea;
		}
	}

	return textarea;
}

static bool setting_single_textbox_del(void)
{
	lv_obj_t *textarea = setting_single_textarea_focused_get();

	if (textarea == NULL)
	{
		return false;
	}

	lv_textarea_del_char(textarea);

	return true;
}

static bool setting_signle_textbox_add(const char *string)
{
	lv_obj_t *textarea = setting_single_textarea_focused_get();

	if (textarea == NULL)
	{

		return false;
	}

	lv_textarea_add_text(textarea, string);
	return true;
}

static void setting_single_number_keyboard_btn_click(lv_event_t *e)
{

	lv_obj_t *obj = lv_event_get_target(e);
	uint32_t id = lv_btnmatrix_get_selected_btn(obj);

	if (id == 11)
	{

		setting_single_textbox_del();
	}
	else
	{
		const char *text = lv_btnmatrix_get_btn_text(obj, id);

		if (text != NULL)
		{

			setting_signle_textbox_add(text);
		}
	}
}

static void sat_layout_enter(single_operation_network)
{
	/***********************************************
	** 作者: leo.liu
	** 日期: 2023-2-2 13:46:56
	** 说明: 标题显示
	***********************************************/
	{
		lv_common_text_create(sat_cur_layout_screen_get(), setting_single_operation_network_obj_id_titile_label, 0, 20, 1024, 40,
				      NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
				      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
				      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
				      lang_str_get(SIGNLE_OPERATION_NETWORK_XLS_LANG_ID_OPERATION_NETWORK), 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_CENTER, lv_font_large);
	}

	/***********************************************
	** 作者: leo.liu
	** 日期: 2023-2-2 13:42:25
	** 说明: 上一步下一步
	***********************************************/
	{
		lv_common_img_btn_create(sat_cur_layout_screen_get(), setting_single_operation_network_obj_id_cancel_btn, 35, 15, 48, 48,
					 setting_single_operation_network_cancel_btn_click, true, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0x808080,
					 0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
					 0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
					 resource_ui_src_get("btn_title_back.png"), LV_OPA_COVER, 0x00a8ff, LV_ALIGN_CENTER);

		lv_common_img_btn_create(sat_cur_layout_screen_get(), setting_single_operation_network_obj_id_next_btn, 952, 15, 48, 48,
					 setting_single_operation_network_next_btn_click, true, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0x808080,
					 0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
					 0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
					 resource_ui_src_get("btn_title_next.png"), LV_OPA_COVER, 0x00a8ff, LV_ALIGN_CENTER);
	}

	/***********************************************
	** 作者: leo.liu
	** 日期: 2023-2-2 13:42:50
	** 说明: 设置按钮创建
	***********************************************/
	{
		lv_common_setting_btn_title_sub_info_img_create(sat_cur_layout_screen_get(), setting_single_operation_network_obj_id_operating_structure_cont, 48, 80, 928, 86,
								setting_single_operating_btn_click, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
								0, 1, LV_BORDER_SIDE_BOTTOM, LV_OPA_COVER, 0x323237,
								0, 1, LV_BORDER_SIDE_BOTTOM, LV_OPA_COVER, 0x00a8ff,
								0, 8, 838, 50, setting_single_operation_network_obj_id_operating_structure_title_lable,
								lang_str_get(SIGNLE_OPERATION_NETWORK_XLS_LANG_ID_OPERATION_STRCUUTRE), 0xFFFFFF, 0x00a8ff, LV_TEXT_ALIGN_LEFT, lv_font_normal,
								0, 45, 838, 50, setting_single_operation_network_obj_id_operating_structure_single_label,
								lang_str_get(SIGNLE_OPERATION_NETWORK_XLS_LANG_ID_SINGLE), 0x6d6d79, 0x00484f, LV_TEXT_ALIGN_LEFT, lv_font_small,
								0, 0, 0, 0, -1,
								NULL, 0xFFFFFF, 0x0078Cf, LV_TEXT_ALIGN_LEFT, lv_font_normal,
								880, 20, 48, 48, setting_single_operation_network_obj_id_operating_structure_img,
								resource_ui_src_get("ic_list_setting.png"), LV_OPA_COVER, 0x00a8ff, LV_ALIGN_CENTER);
	}

	/***********************************************
	** 作者: leo.liu
	** 日期: 2023-2-2 13:43:18
	** 说明: 数字键盘创建
	***********************************************/
	{
		lv_common_number_input_keyboard_create(sat_cur_layout_screen_get(), setting_single_operation_network_obj_id_number_keyboard_btn, 648, 184, 312, 402,
						       setting_single_number_keyboard_btn_click, LV_OPA_COVER, 0x808080, LV_OPA_COVER, 0x00a8ff,
						       360, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
						       360, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
						       0XFFFFFF, 0XFFFFFF, LV_TEXT_ALIGN_CENTER, lv_font_large,
						       18, 24);
	}

	/***********************************************
	** 作者: leo.liu
	** 日期: 2023-2-2 13:43:29
	** 说明: 文本输入框显示
	***********************************************/
	{
		lv_common_textarea_create(sat_cur_layout_screen_get(), setting_single_operation_network_obj_id_ip_textbox, 298, 227, 250, 50,
					  NULL, LV_OPA_TRANSP, 0, LV_OPA_COVER, 0X101010,
					  LV_OPA_TRANSP, 0Xffffff, LV_OPA_COVER, 0Xffffff,
					  9, 2, LV_BORDER_SIDE_FULL, LV_OPA_COVER, 0X101010,
					  9, 2, LV_BORDER_SIDE_FULL, LV_OPA_COVER, 0x00a8ff,
					  "192.168.0.2", 0Xffffff, 0x00a8ff, LV_TEXT_ALIGN_CENTER, lv_font_normal, 15,
					  5, 500, 0Xffffff);

		lv_common_textarea_create(sat_cur_layout_screen_get(), setting_single_operation_network_obj_id_gateway_textbox, 298, 287, 250, 50,
					  NULL, LV_OPA_TRANSP, 0, LV_OPA_COVER, 0X101010,
                                                           LV_OPA_TRANSP,0Xffffff,LV_OPA_COVER,0Xffffff,
					  9, 2, LV_BORDER_SIDE_FULL, LV_OPA_COVER, 0X101010,
					  9, 2, LV_BORDER_SIDE_FULL, LV_OPA_COVER, 0x00a8ff,
					  "192.168.0.1", 0Xffffff, 0x00a8ff, LV_TEXT_ALIGN_CENTER, lv_font_normal, 15,
					  5, 500, 0Xffffff);

		lv_common_textarea_create(sat_cur_layout_screen_get(), setting_single_operation_network_obj_id_mask_textbox, 298, 347, 250, 50,
					  NULL, LV_OPA_TRANSP, 0, LV_OPA_COVER, 0X101010,
                                                           LV_OPA_TRANSP,0Xffffff,LV_OPA_COVER,0Xffffff,
					  9, 2, LV_BORDER_SIDE_FULL, LV_OPA_COVER, 0X101010,
					  9, 2, LV_BORDER_SIDE_FULL, LV_OPA_COVER, 0x00a8ff,
					  "255.255.255.0", 0Xffffff, 0x00a8ff, LV_TEXT_ALIGN_CENTER, lv_font_normal, 15,
					  5, 500, 0Xffffff);

		lv_common_textarea_create(sat_cur_layout_screen_get(), setting_single_operation_network_obj_id_dns_textbox, 298, 407, 250, 50,
					  NULL, LV_OPA_TRANSP, 0, LV_OPA_COVER, 0X101010,
                                                           LV_OPA_TRANSP,0Xffffff,LV_OPA_COVER,0Xffffff,
					  9, 2, LV_BORDER_SIDE_FULL, LV_OPA_COVER, 0X101010,
					  9, 2, LV_BORDER_SIDE_FULL, LV_OPA_COVER, 0x00a8ff,
					  "114.114.114.114", 0Xffffff, 0x00a8ff, LV_TEXT_ALIGN_CENTER, lv_font_normal, 15,
					  5, 500, 0Xffffff);
	}

	/***********************************************
	** 作者: leo.liu
	** 日期: 2023-2-2 13:43:48
	** 说明: 文本显示
	***********************************************/
	{
		lv_common_text_create(sat_cur_layout_screen_get(), setting_single_operation_network_obj_id_ip_label, 32, 235, 200, 50,
				      NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
				      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
				      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
				      lang_str_get(SIGNLE_OPERATION_NETWORK_XLS_LANG_ID_IP), 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_LEFT, lv_font_normal);

		lv_common_text_create(sat_cur_layout_screen_get(), setting_single_operation_network_obj_id_gateway_label, 32, 295, 200, 50,
				      NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
				      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
				      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
				      lang_str_get(SIGNLE_OPERATION_NETWORK_XLS_LANG_ID_GATEWAY), 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_LEFT, lv_font_normal);

		lv_common_text_create(sat_cur_layout_screen_get(), setting_single_operation_network_obj_id_mask_label, 32, 355, 200, 50,
				      NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
				      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
				      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
				      lang_str_get(SIGNLE_OPERATION_NETWORK_XLS_LANG_ID_MASK), 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_LEFT, lv_font_normal);

		lv_common_text_create(sat_cur_layout_screen_get(), setting_single_operation_network_obj_id_dns_label, 32, 415, 200, 50,
				      NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
				      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
				      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
				      lang_str_get(SIGNLE_OPERATION_NETWORK_XLS_LANG_ID_DNS), 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_LEFT, lv_font_normal);
	}

	/***********************************************
	** 作者: leo.liu
	** 日期: 2023-2-2 13:44:0
	** 说明: 垂直线显示
	***********************************************/
	{
		lv_common_img_btn_create(sat_cur_layout_screen_get(), setting_single_operation_network_obj_id_ver_line, 584, 168, 1, 432,
					 NULL, false, LV_OPA_COVER, 0x323237, LV_OPA_TRANSP, 0,
					 0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
					 0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
					 NULL, LV_OPA_TRANSP, 0, LV_ALIGN_CENTER);
	}
}

static void sat_layout_quit(single_operation_network)
{
}

sat_layout_create(single_operation_network);
