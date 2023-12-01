#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl/lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _objects_t {
    lv_obj_t *main;
    lv_obj_t *arcs;
    lv_obj_t *exit_btn;
    lv_obj_t *logo;
    lv_obj_t *needle;
    lv_obj_t *pie;
    lv_obj_t *watch;
    lv_obj_t *web_site;
} objects_t;

extern objects_t objects;

void create_screen_main();
void tick_screen_main();

void create_screens();
void tick_screen(int screen_index);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/