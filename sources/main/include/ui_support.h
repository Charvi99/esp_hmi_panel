#pragma once

#include "ui_main.h"



lv_obj_t *create_def_obj(lv_obj_t *parent, lv_coord_t width, lv_coord_t height, const char *text);

void uncolor_icon(lv_obj_t *img);
void color_icon(lv_obj_t *img);

lv_obj_t *draw_panel(lv_obj_t *parent, int width, int height, int xpos, int ypos, void event(lv_obj_t *, lv_event_t));
void draw_header(lv_obj_t *parent, lv_obj_t **header1, lv_obj_t **header_pom, const char *name, int font);
void draw_box(lv_obj_t *parent, lv_obj_t **block, lv_obj_t **img, lv_obj_t **value_label, int *val, int img_source, int font, int align);
void draw_middle_line(lv_obj_t *parent, lv_obj_t **line);

lv_obj_t *init_main_panel(lv_obj_t *parent);
lv_obj_t *init_exit_btn(lv_obj_t *parent);
side_block *init_block(lv_obj_t *parent, int img, int index);
lv_obj_t *init_side_panel(lv_obj_t *parent, side_panel *panel);
