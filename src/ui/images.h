#ifndef EEZ_LVGL_UI_IMAGES_H
#define EEZ_LVGL_UI_IMAGES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <lvgl/lvgl.h>

extern const lv_img_dsc_t img_img_hand_hour;
extern const lv_img_dsc_t img_img_hand_min;
extern const lv_img_dsc_t img_logo;
extern const lv_img_dsc_t img_web_site;

#ifndef EXT_IMG_DESC_T
#define EXT_IMG_DESC_T
typedef struct _ext_img_desc_t {
    const char *name;
    const lv_img_dsc_t *img_dsc;
} ext_img_desc_t;
#endif

extern const ext_img_desc_t images[4];


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_IMAGES_H*/