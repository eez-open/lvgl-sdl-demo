#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "styles.h"
#include "ui.h"

objects_t objects;
lv_obj_t *tick_value_change_obj;

static void event_handler_cb_main_watch(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_DRAW_PART_BEGIN) {
        lv_obj_draw_part_dsc_t *draw_part_dsc = lv_event_get_draw_part_dsc(e);
        if (draw_part_dsc->class_p != &lv_meter_class) return;
        if (draw_part_dsc->type != LV_METER_DRAW_PART_TICK) return;
        g_eezFlowLvlgMeterTickIndex = draw_part_dsc->id;
        const char *temp;
        temp = evalTextProperty(flowState, 0, 2, "Failed to evalute scale label in Meter widget");
        if (temp) {
            static char label[32];
            strncpy(label, temp, sizeof(label));
            label[sizeof(label) - 1] = 0;
            draw_part_dsc->text = label;
            draw_part_dsc->text_length = sizeof(label);
        }
    }
}

static void event_handler_cb_main_exit_btn(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 23, 0);
    }
}

void create_screen_main() {
    void *flowState = getFlowState(0, 0);
    lv_obj_t *obj = lv_obj_create(0);
    objects.main = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 800, 480);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    {
        lv_obj_t *parent_obj = obj;
        {
            // pie
            lv_obj_t *obj = lv_meter_create(parent_obj);
            objects.pie = obj;
            lv_obj_set_pos(obj, 290, 190);
            lv_obj_set_size(obj, 220, 220);
            {
                lv_meter_scale_t *scale = lv_meter_add_scale(obj);
                lv_meter_set_scale_ticks(obj, scale, 2, 0, 0, lv_color_hex(0xff000000));
                lv_meter_set_scale_major_ticks(obj, scale, 0, 0, 0, lv_color_hex(0xff000000), 10);
                lv_meter_set_scale_range(obj, scale, 0, 100, 360, 0);
                {
                    lv_meter_indicator_t *indicator = lv_meter_add_arc(obj, scale, 110, lv_color_hex(0xffffa305), 0);
                    lv_meter_set_indicator_start_value(obj, indicator, 0);
                    lv_meter_set_indicator_end_value(obj, indicator, 40);
                }
                {
                    lv_meter_indicator_t *indicator = lv_meter_add_arc(obj, scale, 110, lv_color_hex(0xfffbff00), 0);
                    lv_meter_set_indicator_start_value(obj, indicator, 40);
                    lv_meter_set_indicator_end_value(obj, indicator, 80);
                }
                {
                    lv_meter_indicator_t *indicator = lv_meter_add_arc(obj, scale, 110, lv_color_hex(0xffff7b00), 0);
                    lv_meter_set_indicator_start_value(obj, indicator, 80);
                    lv_meter_set_indicator_end_value(obj, indicator, 100);
                }
            }
            lv_obj_set_style_border_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_opa(obj, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
        }
        {
            // watch
            lv_obj_t *obj = lv_meter_create(parent_obj);
            objects.watch = obj;
            lv_obj_set_pos(obj, 120, 70);
            lv_obj_set_size(obj, 220, 220);
            {
                lv_meter_scale_t *scale = lv_meter_add_scale(obj);
                lv_meter_set_scale_ticks(obj, scale, 60, 1, 10, lv_color_hex(0xff797f1f));
                lv_meter_set_scale_major_ticks(obj, scale, 5, 2, 20, lv_color_hex(0xff000000), 20);
                lv_meter_set_scale_range(obj, scale, 0, 59, 354, 270);
                {
                    lv_meter_indicator_t *indicator = lv_meter_add_needle_img(obj, scale, &img_img_hand_hour, 5, 5);
                }
                {
                    lv_meter_indicator_t *indicator = lv_meter_add_needle_img(obj, scale, &img_img_hand_min, 5, 5);
                }
                {
                    lv_meter_indicator_t *indicator = lv_meter_add_needle_line(obj, scale, 1, lv_color_hex(0xffff0000), 0);
                }
            }
            lv_obj_add_event_cb(obj, event_handler_cb_main_watch, LV_EVENT_ALL, flowState);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffc63c3c), LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffe0ecff), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // arcs
            lv_obj_t *obj = lv_meter_create(parent_obj);
            objects.arcs = obj;
            lv_obj_set_pos(obj, 460, 70);
            lv_obj_set_size(obj, 220, 220);
            {
                lv_meter_scale_t *scale = lv_meter_add_scale(obj);
                lv_meter_set_scale_ticks(obj, scale, 11, 2, 10, lv_color_hex(0xffa0a0a0));
                lv_meter_set_scale_major_ticks(obj, scale, 1, 2, 30, lv_color_hex(0xfff0f0f0), 15);
                lv_meter_set_scale_range(obj, scale, 0, 100, 270, 90);
                {
                    lv_meter_indicator_t *indicator = lv_meter_add_arc(obj, scale, 10, lv_color_hex(0xffff0000), 0);
                    lv_meter_set_indicator_start_value(obj, indicator, 0);
                }
                {
                    lv_meter_indicator_t *indicator = lv_meter_add_arc(obj, scale, 10, lv_color_hex(0xff00ff00), -10);
                    lv_meter_set_indicator_start_value(obj, indicator, 0);
                }
                {
                    lv_meter_indicator_t *indicator = lv_meter_add_arc(obj, scale, 10, lv_color_hex(0xff0000ff), -20);
                    lv_meter_set_indicator_start_value(obj, indicator, 0);
                }
            }
            lv_obj_set_style_pad_top(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_opa(obj, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
        }
        {
            // needle
            lv_obj_t *obj = lv_meter_create(parent_obj);
            objects.needle = obj;
            lv_obj_set_pos(obj, 290, 70);
            lv_obj_set_size(obj, 220, 220);
            {
                lv_meter_scale_t *scale = lv_meter_add_scale(obj);
                lv_meter_set_scale_ticks(obj, scale, 41, 2, 10, lv_color_hex(0xffa0a0a0));
                lv_meter_set_scale_major_ticks(obj, scale, 8, 4, 15, lv_color_hex(0xff000000), 10);
                lv_meter_set_scale_range(obj, scale, 0, 100, 300, 120);
                {
                    lv_meter_indicator_t *indicator = lv_meter_add_arc(obj, scale, 3, lv_color_hex(0xff0000ff), 0);
                    lv_meter_set_indicator_start_value(obj, indicator, 0);
                    lv_meter_set_indicator_end_value(obj, indicator, 20);
                }
                {
                    lv_meter_indicator_t *indicator = lv_meter_add_scale_lines(obj, scale, lv_color_hex(0xff0000ff), lv_color_hex(0xff0000ff), false, 0);
                    lv_meter_set_indicator_start_value(obj, indicator, 0);
                    lv_meter_set_indicator_end_value(obj, indicator, 20);
                }
                {
                    lv_meter_indicator_t *indicator = lv_meter_add_arc(obj, scale, 3, lv_color_hex(0xffff0000), 0);
                    lv_meter_set_indicator_start_value(obj, indicator, 80);
                    lv_meter_set_indicator_end_value(obj, indicator, 100);
                }
                {
                    lv_meter_indicator_t *indicator = lv_meter_add_scale_lines(obj, scale, lv_color_hex(0xffff0000), lv_color_hex(0xffff0000), false, 0);
                    lv_meter_set_indicator_start_value(obj, indicator, 80);
                    lv_meter_set_indicator_end_value(obj, indicator, 100);
                }
                {
                    lv_meter_indicator_t *indicator = lv_meter_add_needle_line(obj, scale, 4, lv_color_hex(0xff808080), -15);
                }
            }
            lv_obj_set_style_pad_top(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // logo
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.logo = obj;
            lv_obj_set_pos(obj, -176, 408);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_logo);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_ADV_HITTEST);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
        }
        {
            // web site
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.web_site = obj;
            lv_obj_set_pos(obj, 839, 442);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_web_site);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_ADV_HITTEST);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
        }
        {
            // exit_btn
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.exit_btn = obj;
            lv_obj_set_pos(obj, 680, 311);
            lv_obj_set_size(obj, 100, 50);
            lv_obj_add_event_cb(obj, event_handler_cb_main_exit_btn, LV_EVENT_ALL, flowState);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS|LV_OBJ_FLAG_HIDDEN);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "Exit");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
    }
}

void tick_screen_main() {
    void *flowState = getFlowState(0, 0);
    {
        lv_meter_indicator_t *indicator;
        
        lv_ll_t *indicators = &((lv_meter_t *)objects.watch)->indicator_ll;
        int index = 0;
        for (indicator = _lv_ll_get_tail(indicators); index > 0 && indicator != NULL; indicator = _lv_ll_get_prev(indicators, indicator), index--);
        
        if (indicator) {
            int32_t new_val = evalIntegerProperty(flowState, 0, 3, "Failed to evaluate Value in Meter widget");
            int32_t cur_val = indicator->start_value;
            if (new_val != cur_val) {
                tick_value_change_obj = objects.watch;
                lv_meter_set_indicator_value(objects.watch, indicator, new_val);
                tick_value_change_obj = NULL;
            }
        }
    }
    {
        lv_meter_indicator_t *indicator;
        
        lv_ll_t *indicators = &((lv_meter_t *)objects.watch)->indicator_ll;
        int index = 1;
        for (indicator = _lv_ll_get_tail(indicators); index > 0 && indicator != NULL; indicator = _lv_ll_get_prev(indicators, indicator), index--);
        
        if (indicator) {
            int32_t new_val = evalIntegerProperty(flowState, 0, 4, "Failed to evaluate Value in Meter widget");
            int32_t cur_val = indicator->start_value;
            if (new_val != cur_val) {
                tick_value_change_obj = objects.watch;
                lv_meter_set_indicator_value(objects.watch, indicator, new_val);
                tick_value_change_obj = NULL;
            }
        }
    }
    {
        lv_meter_indicator_t *indicator;
        
        lv_ll_t *indicators = &((lv_meter_t *)objects.watch)->indicator_ll;
        int index = 2;
        for (indicator = _lv_ll_get_tail(indicators); index > 0 && indicator != NULL; indicator = _lv_ll_get_prev(indicators, indicator), index--);
        
        if (indicator) {
            int32_t new_val = evalIntegerProperty(flowState, 0, 5, "Failed to evaluate Value in Meter widget");
            int32_t cur_val = indicator->start_value;
            if (new_val != cur_val) {
                tick_value_change_obj = objects.watch;
                lv_meter_set_indicator_value(objects.watch, indicator, new_val);
                tick_value_change_obj = NULL;
            }
        }
    }
    {
        lv_meter_indicator_t *indicator;
        
        lv_ll_t *indicators = &((lv_meter_t *)objects.arcs)->indicator_ll;
        int index = 0;
        for (indicator = _lv_ll_get_tail(indicators); index > 0 && indicator != NULL; indicator = _lv_ll_get_prev(indicators, indicator), index--);
        
        if (indicator) {
            int32_t new_val = evalIntegerProperty(flowState, 9, 2, "Failed to evaluate End value in Meter widget");
            int32_t cur_val = indicator->end_value;
            if (new_val != cur_val) {
                tick_value_change_obj = objects.arcs;
                lv_meter_set_indicator_end_value(objects.arcs, indicator, new_val);
                tick_value_change_obj = NULL;
            }
        }
    }
    {
        lv_meter_indicator_t *indicator;
        
        lv_ll_t *indicators = &((lv_meter_t *)objects.arcs)->indicator_ll;
        int index = 1;
        for (indicator = _lv_ll_get_tail(indicators); index > 0 && indicator != NULL; indicator = _lv_ll_get_prev(indicators, indicator), index--);
        
        if (indicator) {
            int32_t new_val = evalIntegerProperty(flowState, 9, 3, "Failed to evaluate End value in Meter widget");
            int32_t cur_val = indicator->end_value;
            if (new_val != cur_val) {
                tick_value_change_obj = objects.arcs;
                lv_meter_set_indicator_end_value(objects.arcs, indicator, new_val);
                tick_value_change_obj = NULL;
            }
        }
    }
    {
        lv_meter_indicator_t *indicator;
        
        lv_ll_t *indicators = &((lv_meter_t *)objects.arcs)->indicator_ll;
        int index = 2;
        for (indicator = _lv_ll_get_tail(indicators); index > 0 && indicator != NULL; indicator = _lv_ll_get_prev(indicators, indicator), index--);
        
        if (indicator) {
            int32_t new_val = evalIntegerProperty(flowState, 9, 4, "Failed to evaluate End value in Meter widget");
            int32_t cur_val = indicator->end_value;
            if (new_val != cur_val) {
                tick_value_change_obj = objects.arcs;
                lv_meter_set_indicator_end_value(objects.arcs, indicator, new_val);
                tick_value_change_obj = NULL;
            }
        }
    }
    {
        lv_meter_indicator_t *indicator;
        
        lv_ll_t *indicators = &((lv_meter_t *)objects.needle)->indicator_ll;
        int index = 4;
        for (indicator = _lv_ll_get_tail(indicators); index > 0 && indicator != NULL; indicator = _lv_ll_get_prev(indicators, indicator), index--);
        
        if (indicator) {
            int32_t new_val = evalIntegerProperty(flowState, 10, 2, "Failed to evaluate Value in Meter widget");
            int32_t cur_val = indicator->start_value;
            if (new_val != cur_val) {
                tick_value_change_obj = objects.needle;
                lv_meter_set_indicator_value(objects.needle, indicator, new_val);
                tick_value_change_obj = NULL;
            }
        }
    }
    {
        float timeline_position = getTimelinePosition(flowState);
        
        static struct {
            float last_timeline_position;
            int32_t obj_pie_x_init_value;
            int32_t obj_pie_y_init_value;
            int32_t obj_watch_x_init_value;
            int32_t obj_watch_y_init_value;
            int32_t obj_arcs_x_init_value;
            int32_t obj_arcs_y_init_value;
            int32_t obj_needle_x_init_value;
            int32_t obj_needle_y_init_value;
            int32_t obj_logo_x_init_value;
            int32_t obj_logo_y_init_value;
            int32_t obj_web_site_x_init_value;
            int32_t obj_web_site_y_init_value;
            int32_t obj_exit_btn_opacity_init_value;
        } anim_state = { -1 };
        
        if (anim_state.last_timeline_position == -1) {
            anim_state.last_timeline_position = 0;
            anim_state.obj_pie_x_init_value = lv_obj_get_style_prop(objects.pie, LV_PART_MAIN, LV_STYLE_X).num;
            anim_state.obj_pie_y_init_value = lv_obj_get_style_prop(objects.pie, LV_PART_MAIN, LV_STYLE_Y).num;
            anim_state.obj_watch_x_init_value = lv_obj_get_style_prop(objects.watch, LV_PART_MAIN, LV_STYLE_X).num;
            anim_state.obj_watch_y_init_value = lv_obj_get_style_prop(objects.watch, LV_PART_MAIN, LV_STYLE_Y).num;
            anim_state.obj_arcs_x_init_value = lv_obj_get_style_prop(objects.arcs, LV_PART_MAIN, LV_STYLE_X).num;
            anim_state.obj_arcs_y_init_value = lv_obj_get_style_prop(objects.arcs, LV_PART_MAIN, LV_STYLE_Y).num;
            anim_state.obj_needle_x_init_value = lv_obj_get_style_prop(objects.needle, LV_PART_MAIN, LV_STYLE_X).num;
            anim_state.obj_needle_y_init_value = lv_obj_get_style_prop(objects.needle, LV_PART_MAIN, LV_STYLE_Y).num;
            anim_state.obj_logo_x_init_value = lv_obj_get_style_prop(objects.logo, LV_PART_MAIN, LV_STYLE_X).num;
            anim_state.obj_logo_y_init_value = lv_obj_get_style_prop(objects.logo, LV_PART_MAIN, LV_STYLE_Y).num;
            anim_state.obj_web_site_x_init_value = lv_obj_get_style_prop(objects.web_site, LV_PART_MAIN, LV_STYLE_X).num;
            anim_state.obj_web_site_y_init_value = lv_obj_get_style_prop(objects.web_site, LV_PART_MAIN, LV_STYLE_Y).num;
            anim_state.obj_exit_btn_opacity_init_value = lv_obj_get_style_prop(objects.exit_btn, LV_PART_MAIN, LV_STYLE_OPA).num / 255.0f;
        }
        
        if (timeline_position != anim_state.last_timeline_position) {
            anim_state.last_timeline_position = timeline_position;
            
            {
                lv_obj_t *obj = objects.pie;
                
                float x_value = anim_state.obj_pie_x_init_value;
                float y_value = anim_state.obj_pie_y_init_value;
                
                while (1) {
                    // keyframe #1
                    if (timeline_position < 0) {
                        break;
                    }
                    if (timeline_position >= 0 && timeline_position < 1) {
                        float t = (timeline_position - 0) / 1;
                        // x
                        {
                            float t2 = eez_easeOutElastic(t);
                            x_value = (1 - t2) * x_value + t2 * 290;
                        }
                        // y
                        {
                            float t2 = eez_easeOutElastic(t);
                            y_value = (1 - t2) * y_value + t2 * 252;
                        }
                        break;
                    }
                    x_value = 290;
                    y_value = 252;
                    
                    break;
                }
                
                lv_style_value_t value;
                
                value.num = (int32_t)roundf(x_value);
                lv_obj_set_local_style_prop(obj, LV_STYLE_X, value, LV_PART_MAIN);
                
                value.num = (int32_t)roundf(y_value);
                lv_obj_set_local_style_prop(obj, LV_STYLE_Y, value, LV_PART_MAIN);
            }
            {
                lv_obj_t *obj = objects.watch;
                
                float x_value = anim_state.obj_watch_x_init_value;
                float y_value = anim_state.obj_watch_y_init_value;
                
                while (1) {
                    // keyframe #1
                    if (timeline_position < 0) {
                        break;
                    }
                    if (timeline_position >= 0 && timeline_position < 1) {
                        float t = (timeline_position - 0) / 1;
                        // x
                        {
                            float t2 = eez_easeOutElastic(t);
                            x_value = (1 - t2) * x_value + t2 * 10;
                        }
                        // y
                        {
                            float t2 = eez_easeOutElastic(t);
                            y_value = (1 - t2) * y_value + t2 * 10;
                        }
                        break;
                    }
                    x_value = 10;
                    y_value = 10;
                    
                    break;
                }
                
                lv_style_value_t value;
                
                value.num = (int32_t)roundf(x_value);
                lv_obj_set_local_style_prop(obj, LV_STYLE_X, value, LV_PART_MAIN);
                
                value.num = (int32_t)roundf(y_value);
                lv_obj_set_local_style_prop(obj, LV_STYLE_Y, value, LV_PART_MAIN);
            }
            {
                lv_obj_t *obj = objects.arcs;
                
                float x_value = anim_state.obj_arcs_x_init_value;
                float y_value = anim_state.obj_arcs_y_init_value;
                
                while (1) {
                    // keyframe #1
                    if (timeline_position < 0) {
                        break;
                    }
                    if (timeline_position >= 0 && timeline_position < 1) {
                        float t = (timeline_position - 0) / 1;
                        // x
                        {
                            float t2 = eez_easeOutElastic(t);
                            x_value = (1 - t2) * x_value + t2 * 570;
                        }
                        // y
                        {
                            float t2 = eez_easeOutElastic(t);
                            y_value = (1 - t2) * y_value + t2 * 10;
                        }
                        break;
                    }
                    x_value = 570;
                    y_value = 10;
                    
                    break;
                }
                
                lv_style_value_t value;
                
                value.num = (int32_t)roundf(x_value);
                lv_obj_set_local_style_prop(obj, LV_STYLE_X, value, LV_PART_MAIN);
                
                value.num = (int32_t)roundf(y_value);
                lv_obj_set_local_style_prop(obj, LV_STYLE_Y, value, LV_PART_MAIN);
            }
            {
                lv_obj_t *obj = objects.needle;
                
                float x_value = anim_state.obj_needle_x_init_value;
                float y_value = anim_state.obj_needle_y_init_value;
                
                while (1) {
                    // keyframe #1
                    if (timeline_position < 0) {
                        break;
                    }
                    if (timeline_position >= 0 && timeline_position < 1) {
                        float t = (timeline_position - 0) / 1;
                        // x
                        {
                            float t2 = eez_easeOutElastic(t);
                            x_value = (1 - t2) * x_value + t2 * 290;
                        }
                        // y
                        {
                            float t2 = eez_easeOutElastic(t);
                            y_value = (1 - t2) * y_value + t2 * 10;
                        }
                        break;
                    }
                    x_value = 290;
                    y_value = 10;
                    
                    break;
                }
                
                lv_style_value_t value;
                
                value.num = (int32_t)roundf(x_value);
                lv_obj_set_local_style_prop(obj, LV_STYLE_X, value, LV_PART_MAIN);
                
                value.num = (int32_t)roundf(y_value);
                lv_obj_set_local_style_prop(obj, LV_STYLE_Y, value, LV_PART_MAIN);
            }
            {
                lv_obj_t *obj = objects.logo;
                
                float x_value = anim_state.obj_logo_x_init_value;
                float y_value = anim_state.obj_logo_y_init_value;
                
                while (1) {
                    // keyframe #1
                    if (timeline_position < 0) {
                        break;
                    }
                    if (timeline_position >= 0 && timeline_position < 1) {
                        float t = (timeline_position - 0) / 1;
                        // x
                        {
                            float t2 = eez_easeOutElastic(t);
                            x_value = (1 - t2) * x_value + t2 * 19;
                        }
                        // y
                        {
                            float t2 = eez_easeOutElastic(t);
                            y_value = (1 - t2) * y_value + t2 * 407;
                        }
                        break;
                    }
                    x_value = 19;
                    y_value = 407;
                    
                    break;
                }
                
                lv_style_value_t value;
                
                value.num = (int32_t)roundf(x_value);
                lv_obj_set_local_style_prop(obj, LV_STYLE_X, value, LV_PART_MAIN);
                
                value.num = (int32_t)roundf(y_value);
                lv_obj_set_local_style_prop(obj, LV_STYLE_Y, value, LV_PART_MAIN);
            }
            {
                lv_obj_t *obj = objects.web_site;
                
                float x_value = anim_state.obj_web_site_x_init_value;
                float y_value = anim_state.obj_web_site_y_init_value;
                
                while (1) {
                    // keyframe #1
                    if (timeline_position < 0) {
                        break;
                    }
                    if (timeline_position >= 0 && timeline_position < 1) {
                        float t = (timeline_position - 0) / 1;
                        // x
                        {
                            float t2 = eez_easeOutElastic(t);
                            x_value = (1 - t2) * x_value + t2 * 631;
                        }
                        // y
                        {
                            float t2 = eez_easeOutElastic(t);
                            y_value = (1 - t2) * y_value + t2 * 441;
                        }
                        break;
                    }
                    x_value = 631;
                    y_value = 441;
                    
                    break;
                }
                
                lv_style_value_t value;
                
                value.num = (int32_t)roundf(x_value);
                lv_obj_set_local_style_prop(obj, LV_STYLE_X, value, LV_PART_MAIN);
                
                value.num = (int32_t)roundf(y_value);
                lv_obj_set_local_style_prop(obj, LV_STYLE_Y, value, LV_PART_MAIN);
            }
            {
                lv_obj_t *obj = objects.exit_btn;
                
                float opacity_value = anim_state.obj_exit_btn_opacity_init_value;
                
                while (1) {
                    // keyframe #1
                    if (timeline_position < 0) {
                        break;
                    }
                    opacity_value = 0;
                    
                    // keyframe #2
                    if (timeline_position < 1) {
                        break;
                    }
                    if (timeline_position >= 1 && timeline_position < 2) {
                        float t = (timeline_position - 1) / 1;
                        // opacity
                        opacity_value += eez_linear(t) * (1 - opacity_value);
                        break;
                    }
                    opacity_value = 1;
                    
                    break;
                }
                
                lv_style_value_t value;
                
                value.num = (int32_t)roundf(opacity_value * 255.0f);
                lv_obj_set_local_style_prop(obj, LV_STYLE_OPA, value, LV_PART_MAIN);
            }
        }
        }
    }
    

void create_screens() {
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    
    create_screen_main();
}

typedef void (*tick_screen_func_t)();

tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_main,
};

void tick_screen(int screen_index) {
    tick_screen_funcs[screen_index]();
}
