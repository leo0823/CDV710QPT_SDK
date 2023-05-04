#include "layout_define.h"
#include "layout_door_camera_registed.h"
#include "layout_setting_general.h"
enum
{
        door_camera_edit_obj_id_title,
        door_camera_edit_obj_id_cancel,
        door_camera_edit_obj_id_list
};

/*
 * 编辑注册的设备索引号
 */
static int door_camera_edit_index = -1;
void device_edit_index_setting(int index)
{
        door_camera_edit_index = index;
}
int device_edit_index_get(void)
{
        return door_camera_edit_index;
}

/*返回按钮点击事件*/
static void door_camera_edit_cancel_obj_click(lv_event_t *e)
{
        sat_layout_goto(door_camera_registed, LV_SCR_LOAD_ANIM_MOVE_RIGHT, SAT_VOID);
}

static void door_camera_edit_channge_name_obj_click(lv_event_t *e)
{
         device_password_input_enter_mode_setting(0x01);
        sat_layout_goto(door_camera_password_input, LV_SCR_LOAD_ANIM_FADE_IN, SAT_VOID);
}
static void door_camera_edit_channge_password_obj_click(lv_event_t *e)
{
        device_password_input_enter_mode_setting(0);
        sat_layout_goto(door_camera_password_input, LV_SCR_LOAD_ANIM_FADE_IN, SAT_VOID);
}
static void sat_layout_enter(door_camera_edit)
{
        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-2-2 13:46:56
         ** 说明: 标题显示
         ***********************************************/
        {
                lv_common_text_create(sat_cur_layout_screen_get(), door_camera_edit_obj_id_title, 0, 20, 1024, 40,
                                      NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      layout_door_camera_search_language_get(DOOR_CAMERA_SEARCH_ID_CHANGE_DOOR_CAMERA_INFOMATION), 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_CENTER, lv_font_large);
        }
        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-2-2 13:42:25
         ** 说明: 上一步下一步
         ***********************************************/
        {
                lv_common_img_btn_create(sat_cur_layout_screen_get(), door_camera_edit_obj_id_cancel, 35, 15, 48, 48,
                                         door_camera_edit_cancel_obj_click, true, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0x808080,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         resource_ui_src_get("btn_title_back.png"), LV_OPA_COVER, 0x00a8ff, LV_ALIGN_CENTER);
        }

        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-2-3 14:13:25
         ** 说明: 列表创建
         ***********************************************/
        {
                setting_list_info_t main_list_group[] = {

                    {0, 0, 928, 88,
                     0, 0, -1,
                     DOOR_CAMERA_SEARCH_ID_CHANGE_NAME, layout_door_camera_search_language_get,
                     -1, NULL,
                     door_camera_edit_channge_name_obj_click, -1},
                    {0, 88, 928, 88,
                     1, 0, -1,
                     DOOR_CAMERA_SEARCH_ID_CHANGE_TH_CONNETION_PASSWORD, layout_door_camera_search_language_get,
                     -1, NULL,
                     door_camera_edit_channge_password_obj_click, -1}};

                lv_obj_t *list = setting_list_create(sat_cur_layout_screen_get(), door_camera_edit_obj_id_list);
                lv_common_style_set_common(list, door_camera_edit_obj_id_list, 48, 88, 928, 512, LV_ALIGN_TOP_LEFT, LV_PART_MAIN);

                for (int i = 0; i < sizeof(main_list_group) / sizeof(setting_list_info_t); i++)
                {
                        lv_common_setting_btn_title_sub_info_img_create(list, main_list_group[i].cont_id, main_list_group[i].x, main_list_group[i].y, main_list_group[i].w, main_list_group[i].h,
                                                                        main_list_group[i].click_cb, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                                                        0, 1, LV_BORDER_SIDE_BOTTOM, LV_OPA_COVER, 0x323237,
                                                                        0, 1, LV_BORDER_SIDE_BOTTOM, LV_OPA_COVER, 0x00a8ff,
                                                                        0, 30, 576, 43, main_list_group[i].title_id,
                                                                        main_list_group[i].title_language_id == -1 ? NULL : main_list_group[i].title_language_cb(main_list_group[i].title_language_id), 0xFFFFFF, 0x00a8ff, LV_TEXT_ALIGN_LEFT, lv_font_normal,
                                                                        0, 52, 576, 29, main_list_group[i].sub_id,
                                                                        main_list_group[i].sub_language_id == -1 ? NULL : main_list_group[i].sub_language_cb(main_list_group[i].sub_language_id), 0x6d6d79, 0x00484f, LV_TEXT_ALIGN_LEFT, lv_font_small,
                                                                        0, 0, 0, 0, -1,
                                                                        NULL, 0xFFFFFF, 0x0078Cf, LV_TEXT_ALIGN_LEFT, lv_font_normal,
                                                                        0, 28, 32, 32, main_list_group[i].img_id,
                                                                        NULL, LV_OPA_COVER, 0x00a8ff, LV_ALIGN_CENTER);
                }
        }
}

static void sat_layout_quit(door_camera_edit)
{
}

sat_layout_create(door_camera_edit);