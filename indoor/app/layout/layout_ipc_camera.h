#ifndef _LAYOUT_DOOR_CAMERA_SEARCH_H_
#define _LAYOUT_DOOR_CAMERA_SEARCH_H_
#include <stdbool.h>
#define IPC_CAMERA_FLAG_PWD_ERROR 0X01
#define IPC_CAMERA_FLAG_REGISTER 0X02
#define IPC_CAMERA_FLAG_INPUT_USER 0X04
#define IPC_CAMERA_FLAG_INPUT_PWD 0X08
#define IPC_CAMERA_FLAG_CHANGE_NAME 0X10
#define IPC_CAMERA_FLAG_CHANGE_PWD 0X20
#define IPC_CAMERA_FLAG_SEARCH 0X40

void layout_ipc_camera_input_flag_set(int flg);
int layout_ipc_camera_input_flag_get(void);
/*进入模式设置:door camera /ipc*/
bool layout_ipc_cmeara_is_doorcamera_get(void);
void layout_ipc_cmeara_is_doorcamera_set(bool yeno);

/*当前编辑的索引号*/
void layout_ipc_camera_edit_index_set(int index);
int layout_ipc_camera_edit_index_get(void);
void ipc_camera_password_state_set(int flg);
#endif
