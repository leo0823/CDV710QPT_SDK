#include "layout_define.h"
#include "layout_playback.h"

#define PLAYBACK_THUMB_WIDTH (336)
#define PLAYBACK_THUMB_HIGHT (256)

enum
{
        playback_obj_id_title,
        playback_obj_id_cancel,
        playback_obj_id_total,
        playback_obj_id_left,
        playback_obj_id_right,
        playback_obj_id_thumb_base,
};
/***********************************************
 ** 作者: leo.liu
 ** 日期: 2023-2-2 13:46:56
 ** 说明: 标题显示
 ***********************************************/
static int playback_media_item = 0;
static int playback_media_total = 0;
static int playback_media_top = 0;
static file_type playback_media_type = FILE_TYPE_FLASH_PHOTO;
static char *playback_media_path = NULL;
/***
**   日期:2022-05-23 18:35:40
**   作者: leo.liu
**   函数作用：获取当前选中文件的索引
**   参数说明:
***/
int playback_pview_item_get(void)
{
        return playback_media_item;
}
void playback_pview_item_set(int item)
{
        playback_media_item = item;
}
/***
**   日期:2022-05-24 09:56:58
**   作者: leo.liu
**   函数作用：获取预览的类型
**   参数说明:
***/
file_type playback_pview_type_get(void)
{
        return playback_media_type;
}
/***
**   日期:2022-05-24 10:23:22
**   作者: leo.liu
**   函数作用：获取媒体根路径
**   参数说明:
***/
const char *playback_pview_path_get(void)
{
        return playback_media_path;
}
/***
**   日期:2022-05-24 10:51:04
**   作者: leo.liu
**   函数作用：获取媒体总数
**   参数说明:
***/
int playback_media_total_get(void)
{
        return playback_media_total;
}
/***
**   日期:2022-05-24 10:52:06
**   作者: leo.liu
**   函数作用：设置媒体总数
**   参数说明:
***/
void playback_media_total_set(int total)
{
        playback_media_total = total;
}

/***
**   日期:2022-05-24 11:35:47
**   作者: leo.liu
**   函数作用：获取预览页面的第一个索引
**   参数说明:
***/
int playback_media_top_get(void)
{
        return playback_media_top;
}
/***
**   日期:2022-05-24 11:36:23
**   作者: leo.liu
**   函数作用：设置预览页面的第一个索引
**   参数说明:
***/
void playback_media_top_set(int val)
{
        playback_media_top = val;
}

/***
**   日期:2022-05-24 10:55:48
**   作者: leo.liu
**   函数作用：获取当前媒体信息
**   参数说明:
***/
const file_info *playback_media_info_get(void)
{
        return media_file_info_get(playback_media_type, playback_media_item);
}

static void playback_thumb_param_init(void)
{
        if ((media_sdcard_insert_check() == SD_STATE_INSERT) || (media_sdcard_insert_check() == SD_STATE_FULL))
        {
                playback_media_type = FILE_TYPE_VIDEO;
                playback_media_path = SD_MEDIA_PATH;
        }
        else
        {
                playback_media_type = FILE_TYPE_FLASH_PHOTO;
                playback_media_path = FLASH_PHOTO_PATH;
        }
        media_file_total_get(playback_media_type, &playback_media_total, NULL);
        playback_media_top = playback_media_total - 1;
        playback_media_item = 0;
}

static lv_img_dsc_t *media_thumb_img_dsc_group[6] = {NULL};
static lv_point_t *media_thumb_point_gorup[6] = {NULL};
static bool media_thumb_refresh_gorup[6] = {false};
static void media_thumb_img_dsc_alloc(void)
{
        lv_point_t area[6] = {{7, 80}, {344, 80}, {681, 80}, {7, 337}, {344, 337}, {681, 337}};
        for (int i = 0; i < 6; i++)
        {
                if (media_thumb_img_dsc_group[i] == NULL)
                {
                        media_thumb_img_dsc_group[i] = lv_img_buf_alloc(PLAYBACK_THUMB_WIDTH, PLAYBACK_THUMB_HIGHT, LV_IMG_CF_TRUE_COLOR);
                        media_thumb_img_dsc_group[i]->header.reserved = 0x03;
                }
                if (media_thumb_point_gorup[i] == NULL)
                {
                        media_thumb_point_gorup[i] = lv_mem_alloc(sizeof(lv_point_t));
                        lv_memcpy_small(media_thumb_point_gorup[i], &area[i], sizeof(lv_point_t));
                }
                media_thumb_refresh_gorup[i] = false;
        }
}
static void media_thumb_img_dse_destroy(void)
{
        for (int i = 0; i < 6; i++)
        {
                if (media_thumb_img_dsc_group[i] != NULL)
                {
                        lv_img_buf_free(media_thumb_img_dsc_group[i]);
                        media_thumb_img_dsc_group[i] = NULL;
                }
                if (media_thumb_point_gorup[i] != NULL)
                {
                        lv_mem_free(media_thumb_point_gorup[i]);
                        media_thumb_point_gorup[i] = NULL;
                }
        }
}

static void playback_obj_cancel_click(lv_event_t *e)
{
        sat_layout_goto(home, LV_SCR_LOAD_ANIM_FADE_IN, SAT_VOID);
}
static bool playback_thumb_media_display_callback(const char *data, int x, int y, int w, int h)
{
        for (int i = 0; i < 6; i++)
        {
                if ((media_thumb_img_dsc_group[i] != NULL) && (media_thumb_point_gorup[i] != NULL) && (media_thumb_point_gorup[i]->x == x) && (media_thumb_point_gorup[i]->y == y))
                {
                        lv_memcpy_small((uint8_t *)media_thumb_img_dsc_group[i]->data, data, w * h * 3);
                        media_thumb_refresh_gorup[i] = true;
                        return true;
                }
        }
        SAT_DEBUG("thumb display failed(%d,%d,%d,%d)\n", x, y, w, h);
        return false;
}
static void playback_thumb_total_display(void)
{
        lv_obj_t *obj = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), playback_obj_id_total);
        if (obj == NULL)
        {
                SAT_DEBUG("lv_obj_t* obj  = lv_obj_get_child_form_id(sat_cur_layout_screen_get(),playback_obj_id_total);");
                return;
        }

        lv_label_set_text_fmt(obj, "%04d/%04d", (playback_media_total - playback_media_top) / 6 + 1, (playback_media_total - 1) / 6 + 1);
}

static void playback_thumb_refresh_display_callback(void)
{
        for (int i = 0; i < 6; i++)
        {
                if (media_thumb_refresh_gorup[i] == false)
                {
                        continue;
                }
                lv_obj_t *parent = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), playback_obj_id_thumb_base + i);
                if (parent == NULL)
                {
                        SAT_DEBUG(" lv_obj_t *parent = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), home_obj_id_video_cont);");
                        return;
                }
                lv_obj_clear_flag(parent, LV_OBJ_FLAG_HIDDEN);
                lv_obj_set_style_bg_img_src(parent, media_thumb_img_dsc_group[i], LV_PART_MAIN);
                media_thumb_refresh_gorup[i] = false;
        }
        /*每次加载完后显示总数*/
        playback_thumb_total_display();
}
static void playback_sd_state_change_callback(void)
{
        if (((media_sdcard_insert_check() == SD_STATE_UNPLUG) || (media_sdcard_insert_check() == SD_STATE_ERROR)) && (playback_media_type != FILE_TYPE_FLASH_PHOTO))
        {
                sat_layout_goto(home, LV_SCR_LOAD_ANIM_FADE_IN, SAT_VOID);
        }
}
static void playback_media_thumb_obj_click(lv_event_t *e)
{
        lv_obj_t *obj = lv_event_get_current_target(e);
        if (obj == NULL)
        {
                SAT_DEBUG("lv_obj_t* obj = lv_event_get_current_target(e);");
                return;
        }
        for (int i = 0; i < 6; i++)
        {
                lv_obj_t *item = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), playback_obj_id_thumb_base + i);
                if (item == NULL)
                {
                        SAT_DEBUG(" lv_obj_t* item = lv_obj_get_child_form_id(sat_cur_layout_screen_get(),playback_obj_id_thumb_base+i);");
                        return;
                }
                if (item == obj)
                {
                        int index = playback_media_top - i;
                        if ((index < 0) || (index >= playback_media_total))
                        {
                                break;
                        }
                        playback_media_item = index;
                        const file_info *info = media_file_info_get(playback_media_type, index);
                        if (info == NULL)
                        {
                                break;
                        }
                        if (info->type == FILE_TYPE_VIDEO)
                        {
                                sat_layout_goto(video, LV_SCR_LOAD_ANIM_NONE, SAT_VOID);
                        }
                        else
                        {
                                sat_layout_goto(photo, LV_SCR_LOAD_ANIM_NONE, SAT_VOID);
                        }
                        return;
                }
        }
        SAT_DEBUG("not find");
}
static void playabck_media_new_obj_display(lv_obj_t *parent, bool new)
{
        lv_obj_t *obj = lv_obj_get_child_form_id(parent, 0);
        if (obj == NULL)
        {
                SAT_DEBUG("   lv_obj_t* obj = lv_obj_get_child_form_id(parent,0);");
                return;
        }

        if (new == true)
        {
                lv_obj_clear_flag(obj, LV_OBJ_FLAG_HIDDEN);
        }
        else
        {
                lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
        }
}
static void playback_media_mode_obj_display(lv_obj_t *parent, char mode)
{
        lv_obj_t *obj = lv_obj_get_child_form_id(parent, 1);
        if (obj == NULL)
        {
                SAT_DEBUG("   lv_obj_t* obj = lv_obj_get_child_form_id(parent,0);");
                return;
        }

        if (mode == REC_MODE_ALARM)
        {
                lv_obj_clear_flag(obj, LV_OBJ_FLAG_HIDDEN);
        }
        else
        {
                lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
        }
}
static void playback_media_play_obj_display(lv_obj_t *parent, file_type type)
{
        lv_obj_t *obj = lv_obj_get_child_form_id(parent, 2);
        if (obj == NULL)
        {
                SAT_DEBUG("   lv_obj_t* obj = lv_obj_get_child_form_id(parent,0);");
                return;
        }

        if (type == FILE_TYPE_VIDEO)
        {
                lv_obj_clear_flag(obj, LV_OBJ_FLAG_HIDDEN);
        }
        else
        {
                lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
        }
}
static void playback_media_type_obj_display(lv_obj_t *parent, file_type type)
{
        lv_obj_t *obj = lv_obj_get_child_form_id(parent, 3);
        if (obj == NULL)
        {
                SAT_DEBUG("   lv_obj_t* obj = lv_obj_get_child_form_id(parent,0);");
                return;
        }

        obj = lv_obj_get_child_form_id(obj, 0);
        if (obj == NULL)
        {
                SAT_DEBUG("   lv_obj_t* obj = lv_obj_get_child_form_id(parent,0);");
                return;
        }

        if (type == FILE_TYPE_VIDEO)
        {
                lv_obj_set_style_bg_img_src(obj, resource_ui_src_get("ic_list_visitor_video.png"), LV_PART_MAIN);
        }
        else
        {
                lv_obj_set_style_bg_img_src(obj, resource_ui_src_get("ic_list_visitor_img.png"), LV_PART_MAIN);
        }
}
static void playabck_media_filename_obj_display(lv_obj_t *parent, const char *filename)
{
        lv_obj_t *obj = lv_obj_get_child_form_id(parent, 3);
        if (obj == NULL)
        {
                SAT_DEBUG("   lv_obj_t* obj = lv_obj_get_child_form_id(parent,0);");
                return;
        }

        obj = lv_obj_get_child_form_id(obj, 1);
        if (obj == NULL)
        {
                SAT_DEBUG("   lv_obj_t* obj = lv_obj_get_child_form_id(parent,0);");
                return;
        }
        lv_label_set_text(obj, filename);
}
static void playback_media_channel_obj_display(lv_obj_t *parent, const char *ch_name)
{
        lv_obj_t *obj = lv_obj_get_child_form_id(parent, 3);
        if (obj == NULL)
        {
                SAT_DEBUG("   lv_obj_t* obj = lv_obj_get_child_form_id(parent,0);");
                return;
        }

        obj = lv_obj_get_child_form_id(obj, 2);
        if (obj == NULL)
        {
                SAT_DEBUG("   lv_obj_t* obj = lv_obj_get_child_form_id(parent,0);");
                return;
        }
        lv_label_set_text(obj, ch_name);
}
static void playback_thumb_decode_all_display(void)
{
        /*显示加载的图像*/
        int thumb_count = 0;
        char arry[6][128] = {0};
        for (int i = 0; i < 6; i++)
        {
                lv_obj_t *parent = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), playback_obj_id_thumb_base + i);
                int index = playback_media_top - i;
                lv_obj_add_flag(parent, LV_OBJ_FLAG_HIDDEN);
                if (index >= 0)
                {
                        const file_info *info = media_file_info_get(playback_media_type, index);
                        sprintf(arry[thumb_count++], "%s%s %d %d %d %d", playback_media_path, info->file_name, media_thumb_point_gorup[i]->x, media_thumb_point_gorup[i]->y, PLAYBACK_THUMB_WIDTH, PLAYBACK_THUMB_HIGHT);
                        playabck_media_new_obj_display(parent, info->is_new);
                        playback_media_mode_obj_display(parent, info->mode);
                        playback_media_play_obj_display(parent, info->type);
                        playback_media_type_obj_display(parent, info->type);
                        playabck_media_filename_obj_display(parent, info->file_name);
                        playback_media_channel_obj_display(parent, info->ch);
                }
        }

        sat_linphone_media_thumb_display(arry, thumb_count, playback_thumb_media_display_callback);
}

static void playback_obj_left_click(lv_event_t *e)
{
        if (playback_media_total <= 6)
        {
                return;
        }
        playback_media_top += 6;
        if (playback_media_top >= playback_media_total)
        {
                playback_media_top = playback_media_total % 6 - 1;
                if (playback_media_top == -1)
                {
                        playback_media_top = 5;
                }
        }
        playback_thumb_decode_all_display();
}
static void playback_obj_right_click(lv_event_t *e)
{
        if (playback_media_total <= 6)
        {
                return;
        }
        playback_media_top -= 6;
        if (playback_media_top < 0)
        {
                playback_media_top = playback_media_total - 1;
        }
        playback_thumb_decode_all_display();
}
static void sat_layout_enter(playback)
{
        if (sat_pre_layout_get() == sat_playout_get(home))
        {
                playback_thumb_param_init();
        }
        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-2-2 13:42:25
         ** 说明: 缩略图显示相关
         ***********************************************/
        {
                media_thumb_img_dsc_alloc();
                thumb_display_refresh_register(playback_thumb_refresh_display_callback);
                sd_state_channge_callback_register(playback_sd_state_change_callback);
        }
        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-2-2 13:46:56
        ** 说明: 标题显示
        ***********************************************/
        {
                lv_common_text_create(sat_cur_layout_screen_get(), playback_obj_id_title, 0, 20, 1024, 40,
                                      NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      lang_str_get(PLAYBACK_XLS_LANG_ID_PLAYBACK), 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_CENTER, lv_font_large);
        }
        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-2-2 13:42:25
         ** 说明: 上一步
         ***********************************************/
        {
                lv_common_img_btn_create(sat_cur_layout_screen_get(), playback_obj_id_cancel, 35, 15, 48, 48,
                                         playback_obj_cancel_click, true, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0x808080,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         resource_ui_src_get("btn_title_back.png"), LV_OPA_COVER, 0x00a8ff, LV_ALIGN_CENTER);
        }
        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-2-2 13:46:56
         ** 说明: 标题显示
         ***********************************************/
        {
                lv_common_text_create(sat_cur_layout_screen_get(), playback_obj_id_total, 892, 25, 100, 30,
                                      NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      " ", 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_CENTER, lv_font_normal);
        }
        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-2-2 13:42:25
        ** 说明: 缩略图显示
        ***********************************************/
        for (int i = 0; i < 6; i++)
        {
                lv_obj_t *parent = lv_common_img_btn_create(sat_cur_layout_screen_get(), playback_obj_id_thumb_base + i, (int)media_thumb_point_gorup[i]->x, (int)media_thumb_point_gorup[i]->y, PLAYBACK_THUMB_WIDTH, PLAYBACK_THUMB_HIGHT,
                                                            playback_media_thumb_obj_click, true, LV_OPA_TRANSP, 0x242526, LV_OPA_TRANSP, 0x242526,
                                                            0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                            0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                            NULL, LV_OPA_TRANSP, 0x00a8ff, LV_ALIGN_CENTER);

                lv_common_img_btn_create(parent, 0, 16, 16, 48, 24,
                                         NULL, false, LV_OPA_TRANSP, 0x242526, LV_OPA_TRANSP, 0x242526,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         resource_ui_src_get("ic_main_new.png"), LV_OPA_TRANSP, 0x00a8ff, LV_ALIGN_CENTER);

                lv_common_img_btn_create(parent, 1, 284, 8, 48, 48,
                                         NULL, false, LV_OPA_TRANSP, 0x242526, LV_OPA_TRANSP, 0x242526,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         resource_ui_src_get("ic_playback_emergency.png"), LV_OPA_TRANSP, 0x00a8ff, LV_ALIGN_CENTER);

                lv_common_img_btn_create(parent, 2, 114, 73, 112, 112,
                                         NULL, false, LV_OPA_TRANSP, 0x242526, LV_OPA_TRANSP, 0x242526,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         resource_ui_src_get("btn_thumbnail_play_s.png"), LV_OPA_TRANSP, 0x00a8ff, LV_ALIGN_CENTER);

                parent = lv_common_img_btn_create(parent, 3, 0, PLAYBACK_THUMB_HIGHT - 64, PLAYBACK_THUMB_WIDTH, 64,
                                                  NULL, false, LV_OPA_TRANSP, 0x00, LV_OPA_TRANSP, 0x00,
                                                  0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                  0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                  resource_ui_src_get("playback_back.png"), LV_OPA_TRANSP, 0x00a8ff, LV_ALIGN_CENTER);

                lv_common_img_btn_create(parent, 0, 4, 8, 48, 48,
                                         NULL, false, LV_OPA_TRANSP, 0x242526, LV_OPA_TRANSP, 0x242526,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         NULL, LV_OPA_COVER, 0x00a8ff, LV_ALIGN_CENTER);

                lv_common_text_create(parent, 1, 52, 18, 210, 28,
                                      NULL, LV_OPA_TRANSP, 0X303030, LV_OPA_TRANSP, 0X303030,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      " ", 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_LEFT, lv_font_small);

                lv_common_text_create(parent, 2, 254, 18, 70, 28,
                                      NULL, LV_OPA_TRANSP, 0X303030, LV_OPA_TRANSP, 0X303030,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      " ", 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_RIGHT, lv_font_small);
        }

        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-2-2 13:42:25
         ** 说明: 上一步
         ***********************************************/
        {
                lv_obj_t *obj1 = lv_common_img_btn_create(sat_cur_layout_screen_get(), playback_obj_id_left, 24, 300, 80, 80,
                                                          playback_obj_left_click, true, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0x808080,
                                                          0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                          0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                          resource_ui_src_get("btn_thumbnail_arrow_left_n.png"), LV_OPA_COVER, 0x00a8ff, LV_ALIGN_CENTER);
                if (playback_media_total < 7)
                {
                        lv_obj_add_flag(obj1, LV_OBJ_FLAG_HIDDEN);
                }

                lv_obj_t *obj2 = lv_common_img_btn_create(sat_cur_layout_screen_get(), playback_obj_id_right, 919, 300, 80, 80,
                                                          playback_obj_right_click, true, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0x808080,
                                                          0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                          0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                          resource_ui_src_get("btn_thumbnail_arrow_right_n.png"), LV_OPA_COVER, 0x00a8ff, LV_ALIGN_CENTER);
                if (playback_media_total < 7)
                {
                        lv_obj_add_flag(obj2, LV_OBJ_FLAG_HIDDEN);
                }
        }

        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-2-2 13:42:25
         ** 说明: 刷新缩略图
         ***********************************************/
        playback_thumb_decode_all_display();
}

static void sat_layout_quit(playback)
{
        sat_linphone_media_thumb_destroy();
        thumb_display_refresh_register(NULL);
        sd_state_channge_callback_register(NULL);
        media_thumb_img_dse_destroy();
}

sat_layout_create(playback);