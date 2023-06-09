
#include <stdbool.h>
#include <assert.h>
#include <time.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "user_record.h"
#include "user_monitor.h"
#include "common/sat_user_file.h"
#include "common/sat_linphone_event.h"
#include "tuya/tuya_api.h"
/***
** 日期: 2022-05-19 10:37
** 作者: leo.liu
** 函数作用：接收编码后的流
** 返回参数说明：
***/
static bool jpeg_write_callback(unsigned char *data, int size, int ch, int mode)
{
        printf("=====>>>write size:%d %d\n", size, mode);
        if ((mode & 0x1F))
        {
                file_type type = FILE_TYPE_FLASH_PHOTO;
                if ((media_sdcard_insert_check() == SD_STATE_INSERT) || (media_sdcard_insert_check() == SD_STATE_FULL))
                {
                        type = FILE_TYPE_PHOTO;
                }
                char file_path[128] = {0};

                char *name = NULL;
                if (is_channel_ipc_camera(ch) == true)
                {
                        name = network_data_get()->cctv_device[ch - 8].door_name;
                }
                else
                {
                        name = network_data_get()->door_device[ch].door_name;
                }

                media_file_create(type, name, mode & 0x1F, file_path);
                int fd = open(file_path, O_CREAT | O_WRONLY);
                if (fd >= 0)
                {
                        printf("\n\n snap jpg:%s %dkb \n\n", file_path, size / 1024);
                        write(fd, data, size);
                        close(fd);
                }
                else
                {
                        printf("\n\n snap jpg: %s open failed \n\n", file_path);
                }
                media_file_bad_check(file_path);
        }
        if (mode & REC_MODE_TUYA_CALL)
        {
                printf("======tuya_api_call_event=====\n");
                printf("ch is %d\n",ch);
                tuya_api_call_event(1,(const char *)data, size);
        }
        if (mode & REC_MODE_TUYA_ALARM)
        {
                printf("======tuya_api_alarm_event=====\n");
                printf("ch is %d\n",ch);
                tuya_api_alarm_event(0, (const char *)data, size);
        }
        if (mode & REC_MODE_TUYA_MOTION)
        {
                printf("ch is %d\n",ch);
                printf("======tuya_api_motion_event=====\n");
                tuya_api_motion_event(0, (const char *)data, size);
        }
        system("sync");
        return true;
}
/***
** 日期: 2022-05-19 10:37
** 作者: leo.liu
** 函数作用：抓拍一张照片
** 返回参数说明：
***/
bool record_jpeg_start(REC_MODE mode)
{
        printf("record_jpeg_start \n");
        return sat_linphone_snap(monitor_channel_get(), mode, jpeg_write_callback);
}
/*
 * @日期: 2022-09-15
 * @作者: leo.liu
 * @注释: 视频录制完成的回调函数
 */
static bool record_video_callback(const char *path, int ch, int mode)
{
        if((media_sdcard_insert_check() == SD_STATE_UNPLUG) || (media_sdcard_insert_check() == SD_STATE_ERROR))
        {
                return false;
        }
        char file_path[64] = {0};
        char *name = NULL;
        if (is_channel_ipc_camera(ch) == true)
        {
                name = network_data_get()->cctv_device[ch - 8].door_name;
        }
        else
        {
                name = network_data_get()->door_device[ch].door_name;
        }
        media_file_create(FILE_TYPE_VIDEO, name, mode, file_path);

        char cmd[128] = {0};
        sprintf(cmd, "mv %s %s", path, file_path);
        system(cmd);
        media_file_bad_check(file_path);
        printf("record video:%s \n", file_path);
        return true;
}
/*
 * @日期: 2022-09-15
 * @作者: leo.liu
 * @注释: 视频录制
 */
bool record_video_start(int has_audio, REC_MODE mode)
{
        return sat_linphone_start_record_video(has_audio, monitor_channel_get(), mode, record_video_callback);
}
/*
 * @日期: 2022-09-15
 * @作者: leo.liu
 * @注释: 停止录制
 */
bool record_video_stop(void)
{
        return sat_linphone_stop_record_video();
}
