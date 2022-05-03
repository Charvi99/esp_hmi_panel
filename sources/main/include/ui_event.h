#pragma once

#include "ui_main.h"

void event_click_item(lv_obj_t *obj, lv_event_t event);
void event_click_room(lv_obj_t *obj, lv_event_t event);
void event_click_exit(lv_obj_t *obj, lv_event_t event);
void event_global_override(lv_obj_t *obj, lv_event_t event);
void event_light_override(int room_index);

