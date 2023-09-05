#include "layout_define.h"
#include "layout_ipc_camera.h"
#include "common/sat_ipcamera.h"
/*进入模式设置:door camera /ipc*/

enum
{
        ipc_camera_registered_obj_id_title,
        ipc_camera_registered_obj_id_cancel,
        ipc_camera_registered_obj_id_next,

        ipc_camera_registered_obj_id_ipc_camera_registered_cont,

        ipc_camera_registered_obj_id_door_camera_list,
        ipc_camera_registered_obj_id_registered_door_camera_title,

        ipc_camera_registered_obj_id_msgbox,
};


static void ipc_camera_registered_cancel_click(lv_event_t *ev)
{

    sat_layout_goto(setting_installation, LV_SCR_LOAD_ANIM_MOVE_RIGHT, SAT_VOID);
        
}



static lv_obj_t *ipc_camera_registered_list_create(void)
{
        lv_obj_t *list = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), ipc_camera_registered_obj_id_door_camera_list);
        if (list != NULL)
        {
                return list;
        }
        list = lv_list_create(sat_cur_layout_screen_get());
        lv_common_style_set_common(list, ipc_camera_registered_obj_id_door_camera_list, 48, 194, 928, (600 - 194), LV_ALIGN_TOP_LEFT, LV_PART_MAIN);
        return list;
}

static void sat_layout_enter(indoor_register)
{

        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-2-2 13:46:56
        ** 说明: 标题显示
        ***********************************************/
        {
                lv_common_text_create(sat_cur_layout_screen_get(), ipc_camera_registered_obj_id_title, 0, 20, 1024, 40,
                                      NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      "Slave",
                                      0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_CENTER, lv_font_large);
        }
        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-2-2 13:42:25
         ** 说明: 上一步下一步
         ***********************************************/
        {
                lv_common_img_btn_create(sat_cur_layout_screen_get(), ipc_camera_registered_obj_id_cancel, 35, 15, 48, 48,
                                         ipc_camera_registered_cancel_click, true, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0x808080,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         resource_ui_src_get("btn_title_back.png"), LV_OPA_COVER, 0x00a8ff, LV_ALIGN_CENTER);

        }


        {
                //   int camera_count = layout_ipc_cmeara_is_doorcamera_get() == false ? network_data_get()->cctv_device_count : network_data_get()->door_device_count;

                /***********************************************
                 ** 作者: leo.liu
                 ** 日期: 2023-2-2 13:42:50
                 ** 说明: 显示注册的设备
                 ***********************************************/
                // if (camera_count > 0)
                {
                        lv_obj_t *obj = lv_common_text_create(sat_cur_layout_screen_get(), ipc_camera_registered_obj_id_registered_door_camera_title, 0, 146, 584, 48,
                                                              NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                                              0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                              0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                              "Registered salve",
                                                              0X00A8ff, 0X00A8ff, LV_TEXT_ALIGN_LEFT, lv_font_small);

                        lv_obj_set_style_pad_left(obj, 16, LV_PART_MAIN);



                        lv_obj_t *list = ipc_camera_registered_list_create();
                        int item_y = 0;

                        const asterisk_register_info *p_register_info = asterisk_register_info_get();
                        for (int i = 0; i < 20; i++)
                        {
                                /*主机或者门口机过滤*/
                                if ((p_register_info[i].name[0] == '\0') || (p_register_info[i].timestamp == 0))
                                {
                                        continue;
                                }
                        

                                char * ip = strstr(p_register_info[i].ip,":");
                                if(ip != NULL)
                                {
                                        ip[0] = '\0';
                                }

                                        lv_obj_t *parent = lv_common_setting_btn_title_sub_info_img_create(list, i, 0, item_y, 928, 88,
                                                                                                        NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                                                                                        0, 1, LV_BORDER_SIDE_BOTTOM, LV_OPA_COVER, 0x323237,
                                                                                                        0, 1, LV_BORDER_SIDE_BOTTOM, LV_OPA_COVER, 0x00a8ff,
                                                                                                        10, 8, 838, 50, 0,
                                                                                                        p_register_info[i].name, 0xFFFFFF, 0x00a8ff, LV_TEXT_ALIGN_LEFT, lv_font_normal,
                                                                                                        10, 45, 838, 50, 1,
                                                                                                        p_register_info[i].ip, 0x6d6d79, 0x00484f, LV_TEXT_ALIGN_LEFT, lv_font_small,
                                                                                                        0, 0, 0, 0, -1,
                                                                                                        NULL, 0xFFFFFF, 0x0078Cf, LV_TEXT_ALIGN_LEFT, lv_font_normal,
                                                                                                        0, 20, 48, 48, 2,
                                                                                                        NULL, LV_OPA_TRANSP, 0, LV_ALIGN_CENTER);
                                        lv_obj_t *sub = lv_obj_get_child_form_id(parent, 1);
                                        if (sub != NULL)
                                        {
                                                lv_label_set_long_mode(sub, LV_LABEL_LONG_DOT);
                                        }

                                        item_y += 88;
                        }
                }
        }
}
static void sat_layout_quit(indoor_register)
{
}

sat_layout_create(indoor_register);