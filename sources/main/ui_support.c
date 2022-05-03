#include "ui_support.h"

lv_obj_t *create_def_obj(lv_obj_t *parent, lv_coord_t width, lv_coord_t height, const char *text)
{
    lv_obj_t *_obj = lv_obj_create(parent, NULL);
    lv_obj_set_size(_obj, width, height);
    lv_obj_set_click(_obj, true);

    // STISK EFEKT

    lv_obj_set_style_local_border_width(_obj, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 0);
    lv_obj_set_style_local_border_color(_obj, LV_OBJ_PART_MAIN, LV_STATE_PRESSED, COLOR_DARK);
    lv_obj_set_style_local_border_width(_obj, LV_OBJ_PART_MAIN, LV_STATE_PRESSED, 5);
    lv_obj_set_style_local_radius(_obj, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 10);

    if (NULL != text)
    {
        lv_obj_set_style_local_value_str(_obj, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, text);
        lv_obj_set_style_local_value_font(_obj, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, &font_en_28);
        lv_obj_set_style_local_value_color(_obj, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLACK);
        lv_obj_set_style_local_value_color(_obj, LV_OBJ_PART_MAIN, LV_STATE_PRESSED, LV_COLOR_WHITE);
        lv_obj_set_style_local_value_align(_obj, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_ALIGN_IN_LEFT_MID);
        lv_obj_set_style_local_value_ofs_x(_obj, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, height);
    }

    return _obj;
}

/* --- ACTIVATE/DEACTIVATE ICON --- */
void uncolor_icon(lv_obj_t *img)
{
    lv_obj_set_style_local_image_recolor_opa(img, LV_IMG_PART_MAIN, LV_STATE_DEFAULT, 255);
    lv_obj_set_style_local_image_recolor(img, LV_IMG_PART_MAIN, LV_STATE_DEFAULT, COLOR_DARK);
}
void color_icon(lv_obj_t *img)
{
    lv_obj_set_style_local_image_recolor_opa(img, LV_IMG_PART_MAIN, LV_STATE_DEFAULT, 0);
    lv_obj_set_style_local_image_recolor(img, LV_IMG_PART_MAIN, LV_STATE_DEFAULT, COLOR_DARK);
}

//========= DRAW SUBFUNCTIONS =========
lv_obj_t *draw_panel(lv_obj_t *parent, int width, int height, int xpos, int ypos, void event(lv_obj_t *, lv_event_t))
{
    lv_obj_t *panel = create_def_obj(parent, width, height, NULL);
    lv_obj_set_click(panel, true);
    lv_obj_set_event_cb(panel, event);

    lv_obj_align(panel, NULL, LV_ALIGN_IN_TOP_LEFT, xpos, ypos);
    lv_obj_set_style_local_bg_color(panel, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, COLOR_LIGHT);
    return panel;
}

void draw_header(lv_obj_t *parent, lv_obj_t **header1, lv_obj_t **header_pom, const char *name, int font)
{
    int height = lv_obj_get_height(parent);
    int width = lv_obj_get_width(parent);

    *header_pom = create_def_obj(parent, width, (int)(height / 8) + 2, NULL);
    lv_obj_set_click(*header_pom, false);
    lv_obj_align(*header_pom, NULL, LV_ALIGN_IN_TOP_MID, 0, (int)(height / 8));
    lv_obj_set_style_local_bg_color(*header_pom, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, COLOR_THEME);
    lv_obj_set_style_local_radius(*header_pom, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 0);

    *header1 = create_def_obj(parent, width, (int)(height / 4), name);
    lv_obj_set_click(*header1, false);
    lv_obj_align(*header1, NULL, LV_ALIGN_IN_TOP_MID, 0, 0);
    lv_obj_set_style_local_bg_color(*header1, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, COLOR_THEME);
    lv_obj_set_style_local_value_color(*header1, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    lv_obj_set_style_local_value_align(*header1, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_ALIGN_CENTER);
    lv_obj_set_style_local_value_ofs_x(*header1, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 0);
    lv_obj_set_style_local_value_font(*header1, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, font);
}

void draw_box(lv_obj_t *parent, lv_obj_t **block, lv_obj_t **img, lv_obj_t **value_label, int *val, int img_source, int font, int align)
{
    int height = lv_obj_get_height(parent);
    int width = lv_obj_get_width(parent);
    int margin_x = 10;
    int margin_y = -10;
    if (val != NULL)
        val = 0;
    if (align == LV_ALIGN_CENTER)
    {
        height = height - (int)(height / 4);
        margin_x = 0;
        margin_y = 17;
    }
    else if (align == LV_ALIGN_IN_BOTTOM_LEFT)
    {
        width = width / 2 - 20;
        height = height - (int)(height / 4) - 20;
        margin_x = 10;
    }
    else
    {
        width = width / 2 - 20;
        height = height - (int)(height / 4) - 20;
        margin_x = -10;
    }

    *block = create_def_obj(parent, width, height, NULL);
    lv_obj_set_click(*block, false);
    lv_obj_align(*block, NULL, align, margin_x, margin_y);
    lv_obj_set_style_local_bg_color(*block, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, COLOR_LIGHT);

    *img = lv_img_create(*block, NULL);
    lv_img_set_src(*img, (const void *)img_source);
    lv_obj_align(*img, NULL, LV_ALIGN_IN_TOP_MID, 0, 4);
    if (val > 0)
        color_icon(*img);
    else
        uncolor_icon(*img);

    *value_label = lv_label_create(*block, NULL);
    lv_label_set_text(*value_label, (val > 0) ? "ON" : "OFF");
    lv_obj_set_style_local_text_font(*value_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, (const lv_font_t *)font);
    lv_obj_align(*value_label, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, -3);
    lv_obj_set_style_local_text_color(*value_label, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, COLOR_DARK);
}

void draw_middle_line(lv_obj_t *parent, lv_obj_t **line)
{
    int height = lv_obj_get_height(parent);
    *line = create_def_obj(parent, 3, height - (int)(height / 4), NULL);
    lv_obj_set_click(*line, false);
    lv_obj_align(*line, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, 0);
    lv_obj_set_style_local_bg_color(*line, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(255, 255, 255));
}

//========= INIT PANELS SUBFUNCTIONS =========
lv_obj_t *init_main_panel(lv_obj_t *parent)
{
    lv_obj_t *obj = create_def_obj(parent, 600, 460, NULL);
    lv_obj_set_click(obj, false);
    lv_obj_align(obj, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 10);
    return obj;
}

lv_obj_t *init_exit_btn(lv_obj_t *parent)
{
    lv_obj_t *obj = create_def_obj(parent, 140, 50, "< EXIT");
    lv_obj_set_click(obj, true);
    lv_obj_align(obj, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, -10);
    lv_obj_set_style_local_bg_color(obj, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, COLOR_LIGHT);
    lv_obj_set_style_local_value_font(obj, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, &font_en_bold_28);
    lv_obj_set_style_local_value_color(obj, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    lv_obj_set_style_local_value_align(obj, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_ALIGN_CENTER);
    lv_obj_set_style_local_value_ofs_x(obj, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 0);
    lv_obj_set_event_cb(obj, event_click_exit);

    return obj;
}

side_block *init_block(lv_obj_t *parent, int img, int index)
{
    side_block *newBlock = (side_block *)malloc(sizeof(side_block));

    newBlock->panel = create_def_obj(parent, 150, 150, NULL);
    lv_obj_set_click(newBlock->panel, true);
    lv_obj_align(newBlock->panel, NULL, LV_ALIGN_IN_TOP_MID, 0, 85 + (155 * index));
    lv_obj_set_style_local_bg_color(newBlock->panel, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    lv_obj_set_style_local_bg_color(newBlock->panel, LV_OBJ_PART_MAIN, LV_STATE_PRESSED, COLOR_LIGHT);
    lv_obj_set_style_local_border_color(newBlock->panel, LV_OBJ_PART_MAIN, LV_STATE_PRESSED, LV_COLOR_WHITE);
    lv_obj_set_event_cb(newBlock->panel, event_global_override);

    newBlock->img = lv_img_create(newBlock->panel, NULL);
    lv_img_set_src(newBlock->img, (const void *)img);
    lv_obj_align(newBlock->img, NULL, LV_ALIGN_IN_TOP_MID, 0, 10);

    newBlock->val = lv_label_create(newBlock->panel, NULL);
    lv_label_set_text(newBlock->val, "-/-");
    lv_obj_set_style_local_text_font(newBlock->val, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &font_en_bold_28);
    lv_obj_align(newBlock->val, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, -5);
    lv_obj_set_style_local_text_color(newBlock->val, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, COLOR_DARK);

    return newBlock;
}

lv_obj_t *init_side_panel(lv_obj_t *parent, side_panel *panel)
{
    lv_obj_t *obj = create_def_obj(parent, 160, 460, NULL);
    lv_obj_set_click(obj, false);
    lv_obj_align(obj, NULL, LV_ALIGN_IN_RIGHT_MID, -10, 0);

    panel->header2 = create_def_obj(obj, 160, 10, NULL);
    lv_obj_set_click(panel->header2, false);
    lv_obj_align(panel->header2, NULL, LV_ALIGN_IN_TOP_MID, 0, 60);
    lv_obj_set_style_local_bg_color(panel->header2, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, COLOR_THEME);
    lv_obj_set_style_local_radius(panel->header2, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 0);

    panel->header = create_def_obj(obj, 160, 70, NULL);
    lv_obj_set_click(panel->header, false);
    lv_obj_align(panel->header, NULL, LV_ALIGN_IN_TOP_MID, 0, 0);
    lv_obj_set_style_local_bg_color(panel->header, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, COLOR_THEME);

    panel->label = lv_label_create(obj, NULL);
    lv_label_set_text(panel->label, "HOUSE");
    lv_obj_set_style_local_text_font(panel->label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &font_en_bold_32);
    lv_obj_align(panel->label, NULL, LV_ALIGN_IN_TOP_MID, -1, 17);
    lv_obj_set_style_local_text_color(panel->label, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);

    panel->block_light = init_block(obj, (int)&Bulb_b, 0);
    panel->block_socket = init_block(obj, (int)&Socket_b, 1);
    panel->exit = init_exit_btn(obj);

    return obj;
}