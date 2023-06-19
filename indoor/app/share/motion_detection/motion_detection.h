#ifndef _MOTION_DETECTION_H_
#define _MOTION_DETECTION_H_
#include <stdbool.h>
#include <stdlib.h>
/*初始化移动侦测资源*/
bool motion_detection_init(void **handle, void *(*malloc_callback)(size_t), void (*free_callback)(void *));
/*移动侦测预处理*/
bool motion_detection_preprocess(void *handle, int motion_width, int motion_hight, int motion_threshold, int motion_sensivity, int skip_frame);
/*移动侦测处理*/
bool motion_detection_process(void *handle, unsigned char *frame, int frame_x, int frame_y, int frame_width, int frame_hight, int *is_move);
/*返初始化移动侦测资源*/
bool motion_detection_uninit(void *handle);
#endif