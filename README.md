## 2023/05/04:
## 增加涂鸦SDK的接入，相关的事件在layout_logo中注册
### 在layout_logo.c中执行tuya事件注册函数，注册相关的事件处理
>void tuya_event_cmd_register(bool (*callback)(TUYA_CMD cmd, int arg1));

### 修改内容:
        indoor/app/lib/common/libuser_common.a
        indoor/app/lib/share/libmediastreamer2.a
        indoor/app/lib/share/libtuya.a

        indoor/app/include/common/sat_main_event.h
        indoor/app/layout/layout_define.h
        indoor/app/layout/layout_logo.c

### 新增加的文件
        indoor/app/layout/common/tuya_common.c
        indoor/app/layout/common/tuya_common.h



