

#ifndef _LV_COMMON_H_
#define _LV_COMMON_H_
#include "layout_define.h"

/***********************************************
** 作者: leo.liu
** 日期: 2023-2-2 16:1:42
** 说明: 设置控件基本属性
***********************************************/
#define lv_common_style_set_common(obj, id, x, y, w, h, align, selector) \
	{                                                                \
		lv_obj_set_id(obj, id);                                  \
		lv_obj_set_style_x(obj, x, selector);                    \
		lv_obj_set_style_y(obj, y, selector);                    \
		lv_obj_set_style_width(obj, w, selector);                \
		lv_obj_set_style_height(obj, h, selector);               \
		lv_obj_set_style_align(obj, align, selector);            \
	}

/***********************************************
** 作者: leo.liu
** 日期: 2023-2-2 16:1:42
** 说明: 设置按下基本属性
***********************************************/
#define lv_common_style_set_event(obj, cb, click, default_bg_opa, default_bg_color, default_selector, press_bg_opa, press_bg_color, press_selector) \
	{                                                                                                                                           \
		lv_obj_set_style_bg_opa(obj, default_bg_opa, default_selector);                                                                     \
		if (default_bg_opa > LV_OPA_MIN)                                                                                                    \
		{                                                                                                                                   \
			lv_obj_set_style_bg_color(obj, lv_color_hex(default_bg_color), default_selector);                                           \
		}                                                                                                                                   \
		lv_obj_set_style_bg_opa(obj, press_bg_opa, press_selector);                                                                         \
		if (press_bg_opa > LV_OPA_MIN)                                                                                                      \
		{                                                                                                                                   \
			lv_obj_set_style_bg_color(obj, lv_color_hex(press_bg_color), press_selector);                                               \
		}                                                                                                                                   \
		if (click)                                                                                                                          \
		{                                                                                                                                   \
			lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);                                                                                \
		}                                                                                                                                   \
		else                                                                                                                                \
		{                                                                                                                                   \
			lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);                                                                              \
		}                                                                                                                                   \
		if (cb != NULL)                                                                                                                     \
		{                                                                                                                                   \
			lv_obj_add_event_cb(obj, cb, LV_EVENT_CLICKED, NULL);                                                                       \
		}                                                                                                                                   \
	}

/***********************************************
** 作者: leo.liu
** 日期: 2023-2-2 16:1:42
** 说明: 设置文本基本属性
***********************************************/
#define lv_common_style_set_text(obj, string, font_default_color, font_press_color, align, font, press_part, defalut_part) \
	{                                                                                                                  \
		if (font != NULL)                                                                                          \
		{                                                                                                          \
			lv_obj_set_style_text_font(obj, font, defalut_part);                                               \
		}                                                                                                          \
		lv_obj_set_style_text_align(obj, align, defalut_part);                                                     \
		lv_obj_set_style_text_color(obj, lv_color_hex(font_default_color), defalut_part);                          \
		lv_obj_set_style_text_color(obj, lv_color_hex(font_press_color), press_part);                              \
		if (string != NULL)                                                                                        \
		{                                                                                                          \
			lv_label_set_text(obj, string);                                                                    \
		}                                                                                                          \
	}

/***********************************************
** 作者: leo.liu
** 日期: 2023-2-2 16:1:42
** 说明: 设置文本框基本属性
***********************************************/
#define lv_common_style_set_textarea(obj, string, font_default_color, font_focused_color, align, font, press_part, defalut_part, max_char) \
	{                                                                                                                                  \
		lv_common_style_set_text(obj, NULL, font_default_color, font_focused_color, align, font, press_part, defalut_part);        \
		if (string != NULL)                                                                                                        \
		{                                                                                                                          \
			lv_textarea_set_text(obj, string);                                                                                 \
		}                                                                                                                          \
		lv_textarea_set_one_line(obj, false);                                                                                      \
		lv_textarea_set_max_length(obj, max_char);                                                                                 \
	}

/***********************************************
** 作者: leo.liu
** 日期: 2023-2-2 16:1:42
** 说明: 设置图片基本属性
***********************************************/
#define lv_common_style_set_img(obj, img_src, press_img_recolor_opa, press_img_recolor, align, default_part, press_part) \
	{                                                                                                                \
		if (img_src != NULL)                                                                                     \
		{                                                                                                        \
			lv_obj_set_style_bg_img_src(obj, img_src, default_part);                                         \
			lv_obj_set_style_bg_img_align(obj, align, default_part);                                         \
			lv_obj_set_style_bg_img_recolor_opa(obj, press_img_recolor_opa, press_part);                     \
			lv_obj_set_style_bg_img_recolor(obj, lv_color_hex(press_img_recolor), press_part);               \
		}                                                                                                        \
	}
/***********************************************
** 作者: leo.liu
** 日期: 2023-2-2 16:1:42
** 说明: 设置填充属性
***********************************************/
#define lv_common_style_set_pad(obj, top, left, buttom, right, column, row, part) \
	{                                                                         \
		lv_obj_set_style_pad_top(obj, top, part);                         \
		lv_obj_set_style_pad_left(obj, left, part);                       \
		lv_obj_set_style_pad_bottom(obj, buttom, part);                   \
		lv_obj_set_style_pad_right(obj, right, part);                     \
		lv_obj_set_style_pad_column(obj, column, part);                   \
		lv_obj_set_style_pad_row(obj, row, part);                         \
	}
/***********************************************
** 作者: leo.liu
** 日期: 2023-2-2 16:1:42
** 说明: 设置边框属性
***********************************************/
#define lv_common_style_set_boader(obj, radius, boarder_opa, boarder_width, boarder_side, boarder_color, part) \
	{                                                                                                      \
		if (radius > 0)                                                                                \
		{                                                                                              \
			lv_obj_set_style_radius(obj, radius, part);                                            \
		}                                                                                              \
		lv_obj_set_style_border_opa(obj, boarder_opa, part);                                           \
		if (boarder_opa > LV_OPA_MIN)                                                                  \
		{                                                                                              \
			lv_obj_set_style_border_width(obj, boarder_width, part);                               \
			lv_obj_set_style_border_side(obj, boarder_side, part);                                 \
			lv_obj_set_style_border_color(obj, lv_color_hex(boarder_color), part);                 \
		}                                                                                              \
	}

lv_obj_t *lv_common_img_btn_create(lv_obj_t *parent, int id, int x, int y, int w, int h,
				   lv_event_cb_t cb, bool click, lv_opa_t default_bg_opa, uint32_t default_bg_color, lv_opa_t press_bg_opa, uint32_t press_bg_color,
				   int defalut_radius, int defalut_boarder_width, lv_border_side_t default_boarder_side, int boarder_default_opa, uint32_t boarder_default_color,
				   int press_radius, int press_boarder_width, lv_border_side_t press_boarder_side, int boarder_press_opa, uint32_t boarder_press_color,
				   const char *img_src, lv_opa_t press_img_recolor_opa, uint32_t press_img_recolor, lv_align_t align);

/***********************************************
** 作者: leo.liu
** 日期: 2023-1-30 8:31:26
** 说明: 通用标题文本显示
***********************************************/
lv_obj_t *lv_common_text_create(lv_obj_t *parent, int id, int x, int y, int w, int h,
				lv_event_cb_t cb, lv_opa_t default_bg_opa, uint32_t default_bg_color, lv_opa_t press_bg_opa, uint32_t press_bg_color,
				int defalut_radius, int defalut_boarder_width, lv_border_side_t default_boarder_side, int boarder_default_opa, uint32_t boarder_default_color,
				int press_radius, int press_boarder_width, lv_border_side_t press_boarder_side, int boarder_press_opa, uint32_t boarder_press_color,
				const char *string, uint32_t font_default_color, uint32_t font_press_color, lv_text_align_t align, const lv_font_t *font);

/***********************************************
** 作者: leo.liu
** 日期: 2023-2-2 14:8:52
** 说明: 图片按钮创建
***********************************************/
lv_obj_t *lv_common_img_text_btn_create(lv_obj_t *parent, int id, int x, int y, int w, int h,
					lv_event_cb_t cb, lv_opa_t default_bg_opa, uint32_t default_bg_color, lv_opa_t press_bg_opa, uint32_t press_bg_color,
					int defalut_radius, int defalut_boarder_width, lv_border_side_t default_boarder_side, int boarder_default_opa, uint32_t boarder_default_color,
					int press_radius, int press_boarder_width, lv_border_side_t press_boarder_side, int boarder_press_opa, uint32_t boarder_press_color,
					int title_x, int title_y, int title_w, int title_h, int title_id,
					const char *title_string, uint32_t title_default_color, uint32_t title_press_color, lv_text_align_t title_align, lv_font_t *title_font,
					int img_x, int img_y, int img_w, int img_h, int img_id,
					const char *img_src, lv_opa_t press_img_recolor_opa, uint32_t press_img_recolor, lv_align_t img_align);

/***********************************************
** 作者: leo.liu
** 日期: 2023-2-1 8:19:24
** 说明: 数字输入键盘键盘创建
***********************************************/
lv_obj_t *lv_common_number_input_keyboard_create(lv_obj_t *parent, int id, int x, int y, int w, int h,
						 lv_event_cb_t cb, lv_opa_t default_bg_opa, uint32_t default_bg_color, lv_opa_t press_bg_opa, uint32_t press_bg_color,
						 int defalut_radius, int defalut_boarder_width, lv_border_side_t default_boarder_side, int boarder_default_opa, uint32_t boarder_default_color,
						 int press_radius, int press_boarder_width, lv_border_side_t press_boarder_side, int boarder_press_opa, uint32_t boarder_press_color,
						 uint32_t font_default_color, uint32_t font_press_color, lv_text_align_t align, const lv_font_t *font,
						 int row, int column);

/***********************************************
** 作者: leo.liu
** 日期: 2023-2-1 11:43:3
** 说明: 文本输入框
***********************************************/
lv_obj_t *lv_common_textarea_create(lv_obj_t *parent, int id, int x, int y, int w, int h,
				    lv_event_cb_t cb, lv_opa_t default_bg_opa, uint32_t default_bg_color, lv_opa_t press_bg_opa, uint32_t press_bg_color,
				    lv_opa_t default_cursor_opa, uint32_t default_cursor_color, lv_opa_t press_cursor_opa, uint32_t press_cursor_color,
				    int defalut_radius, int defalut_boarder_width, lv_border_side_t default_boarder_side, int boarder_default_opa, uint32_t boarder_default_color,
				    int press_radius, int press_boarder_width, lv_border_side_t press_boarder_side, int boarder_press_opa, uint32_t boarder_press_color,
				    const char *string, uint32_t font_default_color, uint32_t font_focused_color, lv_text_align_t align, const lv_font_t *font, int max_char,
				    int text_offset_y, int anim_time, uint32_t cursor_color);

/***********************************************
** 作者: leo.liu
** 日期: 2023-2-1 11:43:3
** 说明: 按钮显示
***********************************************/
lv_obj_t *lv_common_setting_btn_title_sub_info_img_create(lv_obj_t *parent, int id, int x, int y, int w, int h,
							  lv_event_cb_t cb, lv_opa_t default_bg_opa, uint32_t default_bg_color, lv_opa_t press_bg_opa, uint32_t press_bg_color,
							  int defalut_radius, int defalut_boarder_width, lv_border_side_t default_boarder_side, int boarder_default_opa, uint32_t boarder_default_color,
							  int press_radius, int press_boarder_width, lv_border_side_t press_boarder_side, int boarder_press_opa, uint32_t boarder_press_color,
							  int title_x, int title_y, int title_w, int title_h, int title_id,
							  const char *title_string, uint32_t title_default_color, uint32_t title_press_color, lv_text_align_t title_align, lv_font_t *title_font,
							  int sub_x, int sub_y, int sub_w, int sub_h, int sub_id,
							  const char *sub_string, uint32_t sub_default_color, uint32_t sub_press_color, lv_text_align_t sub_align, lv_font_t *sub_font,
							  int info_x, int info_y, int info_w, int info_h, int info_id,
							  const char *info_string, uint32_t info_default_color, uint32_t info_press_color, lv_text_align_t info_align, lv_font_t *info_font,
							  int img_x, int img_y, int img_w, int img_h, int img_id,
							  const char *img_src, lv_opa_t press_img_recolor_opa, uint32_t press_img_recolor, lv_align_t img_align);
/***********************************************
** 作者: leo.liu
** 日期: 2023-2-1 11:43:3
** 说明: 键盘创建
***********************************************/
lv_obj_t *lv_common_keyboard_create(lv_obj_t *parent, int id, int x, int y, int w, int h,
				    lv_event_cb_t cb, lv_opa_t default_bg_opa, uint32_t default_bg_color, lv_opa_t press_bg_opa, uint32_t press_bg_color,
				    int defalut_radius, int defalut_boarder_width, lv_border_side_t default_boarder_side, int boarder_default_opa, uint32_t boarder_default_color,
				    int press_radius, int press_boarder_width, lv_border_side_t press_boarder_side, int boarder_press_opa, uint32_t boarder_press_color,
				    int defalut_item_radius, int defalut_item_boarder_width, lv_border_side_t default_item_boarder_side, int boarder_item_default_opa, uint32_t boarde_item_default_color,
				    int press_item_radius, int press_item_boarder_width, lv_border_side_t press_item_boarder_side, int boarder_item_press_opa, uint32_t boarder_item_press_color,
				    uint32_t font_default_color, uint32_t font_press_color, lv_text_align_t align, const lv_font_t *font,
				    int pad_top, int pad_left, int pad_right, int pad_bottom, int pad_column, int pad_row,
				    lv_opa_t default_parent_bg_opa, uint32_t default_parent_bg_color, lv_opa_t press_parent_bg_opa, uint32_t press_parent_bg_color);

/***********************************************
** 作者: leo.liu
** 日期: 2023-2-1 11:43:3
** 说明: 滚筒
***********************************************/
lv_obj_t *lv_common_roller_create(lv_obj_t *parent, int id, int x, int y, int w, int h,
				  lv_event_cb_t cb, lv_opa_t default_bg_opa, uint32_t default_bg_color, lv_opa_t press_bg_opa, uint32_t press_bg_color,
				  int defalut_radius, int defalut_boarder_width, lv_border_side_t default_boarder_side, int boarder_default_opa, uint32_t boarder_default_color,
				  int press_radius, int press_boarder_width, lv_border_side_t press_boarder_side, int boarder_press_opa, uint32_t boarder_press_color,
				  int row_cont, int line_space, int min, int max, uint32_t default_text_color, uint32_t select_text_color, lv_text_align_t text_align, lv_font_t *text_font,
				  const char *img_src);

/***********************************************
** 作者: leo.liu
** 日期: 2023-2-1 11:43:3
** 说明: 按钮显示
***********************************************/
lv_obj_t *lv_common_slider_create(lv_obj_t *parent, int id, int x, int y, int w, int h,
				  lv_event_cb_t cb, lv_opa_t default_bg_opa, uint32_t default_bg_color,
				  int bg_radius, int bg_boarder_width, lv_border_side_t bg_boarder_side, int bg_boarder_opa, uint32_t bg_boarder_color,
				  int slider_radius, int slider_boarder_width, lv_border_side_t slider_boarder_side, int slider_boarder_opa, uint32_t slider_boarder_color,

				  int text_x, int text_y, int text_w, int text_h, int text_id,
				  const char *text_string, uint32_t text_font_color, lv_text_align_t text_align, lv_font_t *text_font,

				  int slider_x, int slider_y, int slider_w, int slider_h, int slider_id,
				  lv_opa_t slider_bg_opa, uint32_t slider_bg_color, lv_opa_t slider_foure_opa, uint32_t slider_foure_color,

				  int left_btn_x, int left_btn_y, int left_btn_w, int left_btn_h, int left_btn_id,
				  const char *left_btn_img_src, lv_opa_t left_btn_press_img_recolor_opa, uint32_t left_btn_press_img_recolor, lv_align_t left_btn_img_align,

				  int right_btn_x, int right_btn_y, int right_btn_w, int right_btn_h, int right_btn_id,
				  const char *right_btn_img_src, lv_opa_t right_btn_press_img_recolor_opa, uint32_t right_btn_press_img_recolor, lv_align_t right_btn_img_align,
				  int knob_radius, int knob_size, uint32_t knob_bg_color, lv_opa_t knob_opa, const char *knob_img_src,
				  int min, int max, int cur_value);
/***********************************************
 ** 作者: leo.liu
 ** 日期: 2023-2-1 11:43:3
 ** 说明: 视频模式选择
 ***********************************************/
void lv_common_video_mode_enable(bool en);

/************************************************************
** 函数说明: 消息框的背景创建
** 作者: xiaoxiao
** 日期: 2023-05-13 09:04:12
** 参数说明: 
** 注意事项: 
************************************************************/
lv_obj_t *setting_msgdialog_msg_bg_create(int parent_id,int id,int x,int y,int w,int h);

/************************************************************
** 函数说明: 消息框标语创建
** 作者: xiaoxiao
** 日期: 2023-05-13 09:04:12
** 参数说明: 
** 注意事项: 
************************************************************/
lv_obj_t * setting_msgdialog_msg_create(lv_obj_t *parent,  int id,const char *msg_string,int x, int y, int w, int h);

/************************************************************
** 函数说明: 消息框的确认按键创建
** 作者: xiaoxiao
** 日期: 2023-05-13 09:06:35
** 参数说明: 
** 注意事项: 
************************************************************/
void setting_msgdialog_msg_confirm_btn_create(lv_obj_t *parent, int id,lv_event_cb_t cb);
/************************************************************
** 函数说明: 消息框的取消确认按键创建
** 作者: xiaoxiao
** 日期: 2023-05-18 11:59:41
** 参数说明: 
** 注意事项: 
************************************************************/
void setting_msgdialog_msg_confirm_and_cancel_btn_create(lv_obj_t *parent, int confirm_id, int cancel_id,lv_event_cb_t con_cb,lv_event_cb_t can_cb);
/************************************************************
** 函数说明: 消息框删除
** 作者: xiaoxiao
** 日期: 2023-05-13 09:04:12
** 参数说明: 
** 注意事项: 
************************************************************/
void setting_msgdialog_msg_del(int id);
#endif
