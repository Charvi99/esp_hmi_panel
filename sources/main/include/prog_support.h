#pragma once

#include "ui_main.h"


int search_for_room(lv_obj_t *obj);
int search_for_item(lv_obj_t *obj, int type);

void set_item_value_1(int room_index, int item_index, int val);

void change_main_panel_vals(lv_obj_t **light_label, lv_obj_t **socket_label);
void change_main_panel_vals_all(lv_obj_t **light_label, lv_obj_t **socket_label);

void create_room(room_block *newRoom, int width, int height, int xpos, int ypos, size_t size, cJSON *json);
void set_room_dimension(int room_count, int *width,int *height,int *space_x,int *space_y,int *row,int *culomn,int *size);

void generate_rooms(size_t count, cJSON *json);
void house_init(cJSON *json);
void house_destroy();