
#include "layout_define.h"
#include "layout_power_setting.h"


enum {

	power_setting_obj_id_power_setting_label, 
	power_setting_obj_id_welcom_label, 
	power_setting_obj_id_languge_btn, 
	power_setting_obj_id_languge_label, 
	power_setting_obj_id_languge_icon, 
	power_setting_obj_id_right_btn, 
	power_setting_obj_id_run_btn, 
	power_setting_obj_id_skip_btn, 
};


static void power_setting_language_btn_client(lv_event_t * ev)
{
	 sat_layout_goto(setting_language, LV_SCR_LOAD_ANIM_FADE_OUT,SAT_VOID);
}


/***********************************************
** 作者: leo.liu
** 日期: 2023-1-13 15:23:33
** 说明: 运行按钮
***********************************************/
static void power_setting_run_btn_client(lv_event_t * ev)
{
	if(user_data_get()->system_mode == 0){
		
		sat_layout_goto(single_operation_network, LV_SCR_LOAD_ANIM_FADE_IN,SAT_VOID);
	}
	else{
		sat_layout_goto(server_operation_network, LV_SCR_LOAD_ANIM_FADE_IN,SAT_VOID);	
	}
}


/***********************************************
** 作者: leo.liu
** 日期: 2023-1-13 15:23:55
** 说明: 跳过按钮
***********************************************/
static void power_setting_skip_btn_client(lv_event_t * ev)
{
}


static void sat_layout_enter(power_setting)
{
	/***********************************************
	** 作者: leo.liu
	** 日期: 2023-2-2 13:46:56
	** 说明: 标题显示
	***********************************************/
	{
		lv_common_text_create(sat_cur_layout_screen_get(), power_setting_obj_id_power_setting_label, 0, 20, 1024, 40, 
			NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0, 
			0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0, 
			0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0, 
			layout_power_setting_language_get(POWER_SETTING_LANG_POWER_SET), 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_CENTER, lv_font_large);
	}

	/***********************************************
	** 作者: leo.liu
	** 日期: 2023-2-2 13:51:30
	** 说明: 欢迎开始使用
	***********************************************/
	{
		lv_common_text_create(sat_cur_layout_screen_get(), power_setting_obj_id_welcom_label, 53, 164, 918, 70, 
			NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0, 
			0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0, 
			0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0, 
			layout_power_setting_language_get(POWER_SETTING_LANG_WELCOM), 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_CENTER, lv_font_normal);
	}

	/***********************************************
	** 作者: leo.liu
	** 日期: 2023-2-2 14:16:18
	** 说明: 语言设置
	***********************************************/
	{
		lv_common_img_text_btn_create(sat_cur_layout_screen_get(), power_setting_obj_id_languge_btn, 418, 302, 188, 72, 
			power_setting_language_btn_client, LV_OPA_TRANSP, 0x00, LV_OPA_TRANSP, 0x101010, 
			0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0, 
			0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0, 
			0, 19, 107, 33, power_setting_obj_id_languge_label, 
			language_common_string_get(LANG_COMMON_ID_LANG), 0xffffff, 0x00a8ff, LV_TEXT_ALIGN_RIGHT, lv_font_normal, 
			108, 12, 48, 48, power_setting_obj_id_languge_icon, 
			(const char *) resource_ui_src_get("btn_list_right.png"), LV_OPA_COVER, 0x00a8ff, LV_ALIGN_CENTER);
	}

	/***********************************************
	** 作者: leo.liu
	** 日期: 2023-2-2 14:42:13
	** 说明: 运行和跳过
	***********************************************/
	{
		lv_obj_t *		obj = lv_common_text_create(sat_cur_layout_screen_get(), power_setting_obj_id_run_btn, 165, 450, 311, 72, 
			power_setting_run_btn_client, LV_OPA_COVER, 0x00a8ff, LV_OPA_COVER, 0x808080, 
			60, 		0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0, 
			60, 		0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0, 
			layout_power_setting_language_get(POWER_SETTING_LANG_RUN), 0XFFFFFFFF, 0xFFFFff, LV_TEXT_ALIGN_CENTER, lv_font_normal);

		lv_obj_set_style_pad_top(obj, 20, LV_PART_MAIN);

		obj 				= lv_common_text_create(sat_cur_layout_screen_get(), power_setting_obj_id_skip_btn, 548, 450, 311, 72, 
			power_setting_skip_btn_client, LV_OPA_COVER, 0x47494a, LV_OPA_COVER, 0x808080, 
			60, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0, 
			60, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0, 
			layout_power_setting_language_get(POWER_SETTING_LANG_SKIP), 0XFFFFFFFF, 0XFFFFFFFF, LV_TEXT_ALIGN_CENTER, lv_font_normal);

		lv_obj_set_style_pad_top(obj, 20, LV_PART_MAIN);
	}
}


static void sat_layout_quit(power_setting)
{
}


sat_layout_create(power_setting);
