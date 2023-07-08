#ifndef _SETTING_SETTING_GENERAL_H_
#define _SETTING_SETTING_GENERAL_H_
typedef struct
{
        int x, y, w, h;
        int cont_id;
        int title_id;
        int sub_id;
        int title_language_id;
        const char *(*title_language_cb)(int id);
        int sub_language_id;
        const char *(*sub_language_cb)(int id);
        lv_event_cb_t click_cb;

        int img_id;
} setting_list_info_t;
typedef struct
{
    int x, y, w, h;
    int cont_id;
    lv_event_cb_t click_cb;
    int check_id;
    bool select;
    int main_language_id;
    const char *(*main_language_cb)(int id);

} security_list_info_t;

lv_obj_t *setting_main_list_create(int id);
lv_obj_t *setting_list_create(lv_obj_t *parent, int id);
#endif