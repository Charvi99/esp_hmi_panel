#include "prog_support.h"

#define TAG ((const char *)"prog_support")

int search_for_room(lv_obj_t *obj)
{
    for (size_t i = 0; i < room_count; i++)
    {
        if (obj == room_array[i].panel)
            return i;
    }
    return -1;
}

int search_for_item(lv_obj_t *obj, int type)
{
    if (active_room_index > -1)
    {
        for (size_t i = 0; i < room_array[active_room_index].items_count; i++)
        {
            if (obj == room_array[active_room_index].items[i].panel)
                return i;
        }
    }
    return -1;
}

void set_item_value_1(int room_index, int item_index, int val)
{
    ESP_LOGI(TAG, "type is %d ", room_array[room_index].items[item_index].type);
    ESP_LOGI(TAG, "val is %d ", val);
    room_array[room_index].items[item_index].val = val;

    if (room_array[room_index].items[item_index].type == 0) // LIGHT
    {
        ESP_LOGI(TAG, "Nastavuji svetla: ");
        if (room_array[room_index].items[item_index].val > 0)
        {
            lv_label_set_text(room_array[room_index].items[item_index].value_label, "ON");
            color_icon(room_array[room_index].items[item_index].img);
            ESP_LOGI(TAG, "ON");
        }
        else
        {
            lv_label_set_text(room_array[room_index].items[item_index].value_label, "OFF");
            uncolor_icon(room_array[room_index].items[item_index].img);
            ESP_LOGI(TAG, "OFF");
        }
    }
    else if (room_array[room_index].items[item_index].type == 1) // SOCKET
    {
        if (room_array[room_index].items[item_index].val > 0)
        {
            lv_label_set_text(room_array[room_index].items[item_index].value_label, "ON");
            color_icon(room_array[room_index].items[item_index].img);
        }
        else
        {
            lv_label_set_text(room_array[room_index].items[item_index].value_label, "OFF");
            uncolor_icon(room_array[room_index].items[item_index].img);
        }
    }
    else if (room_array[room_index].items[item_index].type == 2) // TEMP
    {
        if (room_array[room_index].items[item_index].val > 0)
        {
            lv_label_set_text(room_array[room_index].items[item_index].value_label, "ON");
            color_icon(room_array[room_index].items[item_index].img);
        }
        else
        {
            lv_label_set_text(room_array[room_index].items[item_index].value_label, "OFF");
            uncolor_icon(room_array[room_index].items[item_index].img);
        }
    }
    else if (room_array[room_index].items[item_index].type == 3) // HUMI
    {
        if (room_array[room_index].items[item_index].val > 0)
        {
            lv_label_set_text(room_array[room_index].items[item_index].value_label, "ON");
            color_icon(room_array[room_index].items[item_index].img);
        }
        else
        {
            lv_label_set_text(room_array[room_index].items[item_index].value_label, "OFF");
            uncolor_icon(room_array[room_index].items[item_index].img);
        }
    }
    else if (room_array[room_index].items[item_index].type == 4) // CO2
    {
        if (room_array[room_index].items[item_index].val > 0)
        {
            lv_label_set_text(room_array[room_index].items[item_index].value_label, "ON");
            color_icon(room_array[room_index].items[item_index].img);
        }
        else
        {
            lv_label_set_text(room_array[room_index].items[item_index].value_label, "OFF");
            uncolor_icon(room_array[room_index].items[item_index].img);
        }
    }
    else if (room_array[room_index].items[item_index].type == 5) // UNKNOW
    {
        if (room_array[room_index].items[item_index].val > 0)
        {
            lv_label_set_text(room_array[room_index].items[item_index].value_label, "ON");
            color_icon(room_array[room_index].items[item_index].img);
        }
        else
        {
            lv_label_set_text(room_array[room_index].items[item_index].value_label, "OFF");
            uncolor_icon(room_array[room_index].items[item_index].img);
        }
    }
    else if (room_array[room_index].items[item_index].type == 2) // EXTRA
    {
        if (room_array[room_index].items[item_index].val > 0)
        {
            lv_label_set_text(room_array[room_index].items[item_index].value_label, "ON");
            color_icon(room_array[room_index].items[item_index].img);
        }
        else
        {
            lv_label_set_text(room_array[room_index].items[item_index].value_label, "OFF");
            uncolor_icon(room_array[room_index].items[item_index].img);
        }
    }
}

void change_main_panel_vals(lv_obj_t **light_label, lv_obj_t **socket_label)
{
    static char fmt_text[7];
    int active_light_count = 0;
    for (size_t i = 0; i < room_array[active_room_index].light_count; i++)
        if (room_array[active_room_index].items[i].val == 1 && room_array[active_room_index].items[i].type == TYPE_LIGHT)
            active_light_count++;

    sprintf(fmt_text, "%d/%d", active_light_count, room_array[active_room_index].light_count);
    char *name_cpy = (char *)malloc(sizeof(fmt_text));
    memcpy(name_cpy, fmt_text, sizeof fmt_text);
    lv_label_set_text(*light_label, name_cpy);
    free(name_cpy);

    if (active_light_count > 0)
    {
        color_icon(room_array[active_room_index].light_img);
        ESP_LOGE(TAG, "pocet akt svetel je: %d",active_light_count);

    }
    else
    {
        uncolor_icon(room_array[active_room_index].light_img);
        ESP_LOGE(TAG, "pocet akt svetel je 0");

    }
    //==========================
    static char fmt_text2[7];
    int active_socket_count = 0;
    for (size_t i = 0; i < room_array[active_room_index].items_count; i++)
        if (room_array[active_room_index].items[i].val > 0 && room_array[active_room_index].items[i].type == TYPE_SOCKET)
            active_socket_count += room_array[active_room_index].items[i].val;

    sprintf(fmt_text2, "%.1fW", (float)active_socket_count);
    char *name_cpy2 = (char *)malloc(sizeof(fmt_text2));
    memcpy(name_cpy2, fmt_text2, sizeof fmt_text2);
    lv_label_set_text(*socket_label, name_cpy2);
    free(name_cpy2);
    //==========================
}

void change_main_panel_vals_all(lv_obj_t **light_label, lv_obj_t **socket_label)
{
    int active_light_count = 0;
    int active_socket_count = 0;
    int all_light_count = 0;
    for (size_t j = 0; j < room_count; j++)
    {
        int subactive_light_count = 0;
        all_light_count += room_array[j].light_count;
        for (size_t i = 0; i < room_array[j].items_count; i++)
            if (room_array[j].items[i].val == 1 && room_array[j].items[i].val == TYPE_LIGHT)
                subactive_light_count++;

        if (subactive_light_count > 0)
            color_icon(room_array[j].light_img);
        else
            uncolor_icon(room_array[j].light_img);
        active_light_count += subactive_light_count;
        //==========================

        int subactive_socket_count = 0;
        for (size_t i = 0; i < room_array[j].items_count; i++)
            if (room_array[j].items[i].val > 0 && room_array[j].items[i].val == TYPE_LIGHT)
                subactive_socket_count += room_array[j].items[i].val;

        if (subactive_socket_count > 0)
            color_icon(room_array[j].socket_img);
        else
            uncolor_icon(room_array[j].socket_img);
        active_socket_count += subactive_socket_count;
        //==========================
    }

    static char fmt_text[7];
    sprintf(fmt_text, "%d/%d", active_light_count, all_light_count);
    char *name_cpy = (char *)malloc(sizeof(fmt_text));
    memcpy(name_cpy, fmt_text, sizeof fmt_text);
    lv_label_set_text(*light_label, name_cpy);
    free(name_cpy);

    static char fmt_text2[7];
    sprintf(fmt_text2, "%.1fW", (float)active_socket_count);
    char *name_cpy2 = (char *)malloc(sizeof(fmt_text2));
    memcpy(name_cpy2, fmt_text2, sizeof fmt_text2);
    lv_label_set_text(*socket_label, name_cpy2);
    free(name_cpy2);
}

void create_room(room_block *newRoom, int width, int height, int xpos, int ypos, size_t size, cJSON *json)
{
    ESP_LOGE(TAG, "================================");
    if (newRoom == NULL)
    {
        ESP_LOGE(TAG, "NEW ROOM je NULL");
        return;
    }
    if (json == NULL)
    {
        ESP_LOGE(TAG, "JSON je NULL");
        return;
    }
    cJSON *room_name = cJSON_GetObjectItemCaseSensitive(json, "name");
    cJSON *room_index = cJSON_GetObjectItemCaseSensitive(json, "index");

    newRoom->name = room_name->valuestring;
    newRoom->index = room_index->valueint;

    int value_font = (int)&font_en_bold_20;
    int header_font = (int)&font_en_bold_28;
    int socket_img = (int)&Socket_s;
    int light_img = (int)&Bulb_s;

    // set bigger size if requested
    if (size != 1)
    {
        value_font = (int)&font_en_bold_28;
        header_font = (int)&font_en_bold_32;
        socket_img = (int)&Socket;
        light_img = (int)&Bulb;
    }
ESP_LOGW(TAG, "NEW ROOM4");
    // draw room cell
    newRoom->panel = draw_panel(page_main->panel_main, width, height, xpos, ypos, event_click_room);
    draw_header(newRoom->panel, &newRoom->header, &newRoom->header_2, newRoom->name, header_font);
    draw_box(newRoom->panel, &newRoom->light_block, &newRoom->light_img, &newRoom->light_val, NULL, light_img, value_font, LV_ALIGN_IN_BOTTOM_LEFT);
    draw_box(newRoom->panel, &newRoom->socket_block, &newRoom->socket_img, &newRoom->socket_val, NULL, socket_img, value_font, LV_ALIGN_IN_BOTTOM_RIGHT);
    draw_middle_line(newRoom->panel, &newRoom->line);
    lv_obj_set_event_cb(newRoom->panel, event_click_room);

    ESP_LOGI(TAG, "vytvoril se panel");

    // newRoom->items = (item_block *)malloc(sizeof(item_block) * newRoom->items_count);

    // create parent panel for all items
    newRoom->item_panel = create_def_obj(page_detail->panel_main, lv_obj_get_width(page_detail->panel_main), lv_obj_get_height(page_detail->panel_main), NULL);
ESP_LOGW(TAG, "NEW ROOM5");
    char new_topic[1024];
    snprintf(new_topic, sizeof(new_topic), "%s/%s", MAIN_TOPIC, newRoom->name);
    esp_mqtt_client_subscribe(client, new_topic, 0);
    ESP_LOGI(TAG, "nove odebiram tento topic: %s", new_topic);

ESP_LOGW(TAG, "NEW ROOM6");
    cJSON *room_items = cJSON_GetObjectItemCaseSensitive(json, "items");
    generate_items(newRoom->index, room_items);
ESP_LOGW(TAG, "NEW ROOM7");
    ESP_LOGE(TAG, "================================");

    return;
}

void generate_items(int room_index, cJSON *items)
{
    // dimesnions of item box
    int item_width = 105;
    int item_height = 130;
    int item_x_space = 115;
    int item_y_space = 150;
    int margin = 10;

    int light_current_count = 0;
    int socket_current_count = 0;
    int extra_current_count = 0;

    

    ESP_LOGE(TAG, "============= PRVNI PRISTUP K PAMETI.. SPADNE? ===================");
    room_array[room_index].items_count = cJSON_GetArraySize(items);

    // if(room_array[room_index].items != NULL)
    //     free(room_array[room_index].items);
    ESP_LOGE(TAG, "============= DRUHY PRISTUP K PAMETI.. SPADNE? ===================");
    room_array[room_index].items = (item_block *)malloc(sizeof(item_block) * room_array[room_index].items_count);
    ESP_LOGE(TAG, "============= TRETI PRISTUP K PAMETI.. SPADNE? ===================");
    ESP_LOGE(TAG, "============= %d tolik prvku jsem nove naalokoval.. SPADNE? ===================", room_array[room_index].items_count);

    for (size_t i = 0; i < room_array[room_index].items_count; i++)
    {
        ESP_LOGE(TAG, "============= %d Item.. SPADNE? ===================", i);
        ESP_LOGW(TAG, "============= vazne jsem tady ===================");

        cJSON *item_json = cJSON_GetArrayItem(items, i);
        cJSON *item_type = cJSON_GetObjectItemCaseSensitive(item_json, "typ");
        cJSON *item_name = cJSON_GetObjectItemCaseSensitive(item_json, "nam");
        cJSON *item_val = cJSON_GetObjectItemCaseSensitive(item_json, "val");
        cJSON *item_sVal = cJSON_GetObjectItemCaseSensitive(item_json, "sVal");
        cJSON *item_top = cJSON_GetObjectItemCaseSensitive(item_json, "top");
        cJSON *item_on_cmd = cJSON_GetObjectItemCaseSensitive(item_json, "on");
        cJSON *item_off_cmd = cJSON_GetObjectItemCaseSensitive(item_json, "off");
        cJSON *item_red_cmd = cJSON_GetObjectItemCaseSensitive(item_json, "red");

        room_array[room_index].items[i].index = i;
        room_array[room_index].items[i].type = item_type->valueint;
        room_array[room_index].items[i].name = item_name->valuestring;
        room_array[room_index].items[i].val = item_val->valueint;
        room_array[room_index].items[i].sVal = item_sVal->valuestring;
        room_array[room_index].items[i].topic = item_top->valuestring;
        room_array[room_index].items[i].on_cmd = item_on_cmd->valuestring;
        room_array[room_index].items[i].off_cmd = item_off_cmd->valuestring;
        room_array[room_index].items[i].read_cmd = item_red_cmd->valuestring;

        if (room_array[room_index].items[i].type == TYPE_LIGHT)
        {
            ESP_LOGE(TAG, "je to lampa");
            room_array[room_index].items[i].panel = draw_panel(room_array[room_index].item_panel,
                                                               item_width,
                                                               item_height,
                                                               margin + (item_x_space * light_current_count++),
                                                               margin + (item_y_space * ROW_LIGHT),
                                                               event_click_item);
            ESP_LOGE(TAG, "je to lampa");
            draw_header(room_array[room_index].items[i].panel,
                        &room_array[room_index].items[i].header,
                        &room_array[room_index].items[i].header_2,
                        item_name->valuestring,
                        (int)&font_en_24);
            ESP_LOGE(TAG, "je to lampa");
            draw_box(room_array[room_index].items[i].panel,
                     &room_array[room_index].items[i].block,
                     &room_array[room_index].items[i].img,
                     &room_array[room_index].items[i].value_label,
                     &room_array[room_index].items[i].val,
                     (int)&Bulb_s,
                     (int)&font_en_24,
                     LV_ALIGN_CENTER);
        }
        else if (room_array[room_index].items[i].type == TYPE_SOCKET)
        {
            ESP_LOGE(TAG, "je to zasuvka");
            room_array[room_index].items[i].panel = draw_panel(room_array[room_index].item_panel,
                                                               item_width,
                                                               item_height,
                                                               margin + (item_x_space * socket_current_count++),
                                                               margin + (item_y_space * ROW_SOCKET),
                                                               event_click_item);
            ESP_LOGE(TAG, "je to zasuvka");
            draw_header(room_array[room_index].items[i].panel,
                        &room_array[room_index].items[i].header,
                        &room_array[room_index].items[i].header_2,
                        item_name->valuestring,
                        (int)&font_en_24);
            ESP_LOGE(TAG, "je to zasuvka");
            draw_box(room_array[room_index].items[i].panel,
                     &room_array[room_index].items[i].block,
                     &room_array[room_index].items[i].img,
                     &room_array[room_index].items[i].value_label,
                     &room_array[room_index].items[i].val,
                     (int)&Socket_s,
                     (int)&font_en_24,
                     LV_ALIGN_CENTER);
        }
        else if (room_array[room_index].items[i].type == TYPE_TEMP)
        {
            ESP_LOGE(TAG, "je to temp");

            room_array[room_index].items[i].panel = draw_panel(room_array[room_index].item_panel,
                                                               item_width,
                                                               item_height,
                                                               margin + (item_x_space * extra_current_count++),
                                                               margin + (item_y_space * ROW_EXTRA),
                                                               event_click_item);
            ESP_LOGE(TAG, "je to temp");
            draw_header(room_array[room_index].items[i].panel,
                        &room_array[room_index].items[i].header,
                        &room_array[room_index].items[i].header_2,
                        item_name->valuestring,
                        (int)&font_en_24);
            ESP_LOGE(TAG, "je to temp");
            draw_box(room_array[room_index].items[i].panel,
                     &room_array[room_index].items[i].block,
                     &room_array[room_index].items[i].img,
                     &room_array[room_index].items[i].value_label,
                     &room_array[room_index].items[i].val,
                     (int)&Temp,
                     (int)&font_en_24,
                     LV_ALIGN_CENTER);
        }
        else if (room_array[room_index].items[i].type == TYPE_HUMI)
        {
            ESP_LOGE(TAG, "je to humi");

            room_array[room_index].items[i].panel = draw_panel(room_array[room_index].item_panel,
                                                               item_width,
                                                               item_height,
                                                               margin + (item_x_space * extra_current_count++),
                                                               margin + (item_y_space * ROW_EXTRA),
                                                               event_click_item);
            ESP_LOGE(TAG, "je to humi");
            draw_header(room_array[room_index].items[i].panel,
                        &room_array[room_index].items[i].header,
                        &room_array[room_index].items[i].header_2,
                        item_name->valuestring,
                        (int)&font_en_24);
            ESP_LOGE(TAG, "je to humi");
            draw_box(room_array[room_index].items[i].panel,
                     &room_array[room_index].items[i].block,
                     &room_array[room_index].items[i].img,
                     &room_array[room_index].items[i].value_label,
                     &room_array[room_index].items[i].val,
                     (int)&Humi,
                     (int)&font_en_24,
                     LV_ALIGN_CENTER);
        }
        else if (room_array[room_index].items[i].type == TYPE_CO2)
        {
            ESP_LOGE(TAG, "je to co2");

            room_array[room_index].items[i].panel = draw_panel(room_array[room_index].item_panel,
                                                               item_width,
                                                               item_height,
                                                               margin + (item_x_space * extra_current_count++),
                                                               margin + (item_y_space * ROW_EXTRA),
                                                               event_click_item);
            ESP_LOGE(TAG, "je to co2");
            draw_header(room_array[room_index].items[i].panel,
                        &room_array[room_index].items[i].header,
                        &room_array[room_index].items[i].header_2,
                        item_name->valuestring,
                        (int)&font_en_24);
            ESP_LOGE(TAG, "je to co2");
            draw_box(room_array[room_index].items[i].panel,
                     &room_array[room_index].items[i].block,
                     &room_array[room_index].items[i].img,
                     &room_array[room_index].items[i].value_label,
                     &room_array[room_index].items[i].val,
                     (int)&co,
                     (int)&font_en_24,
                     LV_ALIGN_CENTER);
        }
        else if (room_array[room_index].items[i].type == TYPE_UNKNOW)
        {
            ESP_LOGE(TAG, "je to netusim");

            room_array[room_index].items[i].panel = draw_panel(room_array[room_index].item_panel,
                                                               item_width,
                                                               item_height,
                                                               margin + (item_x_space * extra_current_count++),
                                                               margin + (item_y_space * ROW_EXTRA),
                                                               event_click_item);
            ESP_LOGE(TAG, "je to netusim");
            draw_header(room_array[room_index].items[i].panel,
                        &room_array[room_index].items[i].header,
                        &room_array[room_index].items[i].header_2,
                        item_name->valuestring,
                        (int)&font_en_24);
            ESP_LOGE(TAG, "je to netusim");
            draw_box(room_array[room_index].items[i].panel,
                     &room_array[room_index].items[i].block,
                     &room_array[room_index].items[i].img,
                     &room_array[room_index].items[i].value_label,
                     &room_array[room_index].items[i].val,
                     (int)&unknow,
                     (int)&font_en_24,
                     LV_ALIGN_CENTER);
        }
        ESP_LOGE(TAG, "tak mam naalokovano a jdu odebirat");

    
        ESP_LOGE(TAG, "tak mam naalokovano a jdu odebirat toto %s", room_array[room_index].items[i].topic);
        esp_mqtt_client_subscribe(client, room_array[room_index].items[i].topic, 0);
        ESP_LOGI(TAG, "nove odebiram tento topic: %s", room_array[room_index].items[i].topic);
    }
    if (room_array[room_index].index == active_room_index)
        lv_obj_set_hidden(room_array[room_index].item_panel, false);
    else
        lv_obj_set_hidden(room_array[room_index].item_panel, true);
}

void set_room_dimension(int room_count, int *width, int *height, int *space_x, int *space_y, int *row, int *culomn, int *size)
{
    switch (room_count)
    {
    case 1:
        *width = 250;
        *height = 200;
        *space_x = 180;
        *space_y = 120;
        *row = 1;
        *culomn = 1;
        *size = 2;
        break;
    case 2:
        *width = 250;
        *height = 200;
        *space_x = 32;
        *space_y = 110;
        *row = 1;
        *culomn = 2;
        *size = 2;
        break;
    case 3:
        *width = 250;
        *height = 200;
        *space_x = 32;
        *space_y = 20;
        *row = 2;
        *culomn = 2;
        *size = 2;
        break;
    case 4:
        *width = 250;
        *height = 200;
        *space_x = 32;
        *space_y = 20;
        *row = 2;
        *culomn = 2;
        *size = 2;
        break;
    case 5:
        *width = 185;
        *height = 175;
        *space_x = 10;
        *space_y = 40;
        *row = 2;
        *culomn = 3;
        *size = 1;

        break;
    case 6:
        *width = 185;
        *height = 175;
        *space_x = 10;
        *space_y = 40;
        *row = 2;
        *culomn = 3;
        *size = 1;

        break;
    case 7:
        *width = 185;
        *height = 140;
        *space_x = 10;
        *space_y = 10;
        *row = 3;
        *culomn = 3;
        *size = 1;

        break;
    case 8:
        *width = 185;
        *height = 140;
        *space_x = 10;
        *space_y = 10;
        *row = 3;
        *culomn = 3;
        *size = 1;

        break;
    case 9:
        *width = 185;
        *height = 140;
        *space_x = 10;
        *space_y = 10;
        *row = 3;
        *culomn = 3;
        *size = 1;

        break;

    default:
        *width = 250;
        *height = 200;
        *space_x = 32;
        *space_y = 20;
        *row = 2;
        *culomn = 2;
        *size = 2;
        break;
    }
    return;
}

void generate_rooms(size_t count, cJSON *json)
{
    // init size of room cells
    int width = 0;
    int height = 0;
    int space_x = 0;
    int space_y = 0;
    int row = 0;
    int culomn = 0;
    int size = 0;
    room_count = count;

    // setup size based on count
    set_room_dimension(room_count, &width,
                       &height,
                       &space_x,
                       &space_y,
                       &row,
                       &culomn,
                       &size);

    // dynamicly allocated memory for rooms
    room_array = (room_block *)malloc(sizeof(room_block) * room_count);
    // cJSON *rooms = cJSON_GetObjectItemCaseSensitive(json, "rooms");

    for (size_t i = 0; i < room_count; i++)
    {
        cJSON *room = cJSON_GetArrayItem(json, i);
        // printf(cJSON_Print(room));
        cJSON *room_light = cJSON_GetObjectItemCaseSensitive(room, "lightCount");
        cJSON *room_socket = cJSON_GetObjectItemCaseSensitive(room, "socketCount");
        cJSON *room_extra = cJSON_GetObjectItemCaseSensitive(room, "extraCount");

        if (cJSON_IsNumber(room_light))
            room_array[i].light_count = room_light->valueint;
        else
            room_array[i].light_count = 0;

        if (cJSON_IsNumber(room_socket))
            room_array[i].socket_count = room_socket->valueint;
        else
            room_array[i].socket_count = 0;

        if (cJSON_IsNumber(room_extra))
            room_array[i].extera_count = room_extra->valueint;
        else
            room_array[i].extera_count = 0;

        ESP_LOGI(TAG, "ROOM %d", i);
        ESP_LOGI(TAG, "light_count %d", room_array[i].light_count);
        ESP_LOGI(TAG, "socket_count %d", room_array[i].socket_count);
        ESP_LOGI(TAG, "extera_count %d", room_array[i].extera_count);
    }

    // creating room cells
    int index_current_room = 0;
    for (size_t i = 0; i < row; i++)
    {
        for (size_t j = 0; j < culomn; j++)
        {
            // set auto-name for room
            static char fmt_text[7];
            sprintf(fmt_text, "ROOM %d", index_current_room);
            char *name_cpy = (char *)malloc(sizeof(fmt_text));
            memcpy(name_cpy, fmt_text, sizeof fmt_text);

            cJSON *room = cJSON_GetArrayItem(json, index_current_room);

            if (index_current_room < room_count)
                create_room(&room_array[index_current_room],
                            width,
                            height,
                            space_x + (j * (width + space_x)),
                            space_y + (i * (height + space_y)),
                            size, room);
            index_current_room++;
        }
    }
    return;
}

void house_init(cJSON *json)
{
    ESP_LOGW(TAG, "JDU POSTAVIT DUM");

    if (json != NULL)
    {
        printf("\n====JSON====\n");
        printf(cJSON_Print(json));
        house_destroy();
        int room_count_json = cJSON_GetArraySize(json);

        printf("pocet mistnosti \"%d\"\n", room_count_json);
        room_count = room_count_json;
        generate_rooms(room_count, json);
    }
    else
        ESP_LOGE(TAG, "\n====JSON IS NULL====\n");
}

void house_destroy()
{
    ESP_LOGW(TAG, "JDU ZNICIT DUM");
    ESP_LOGE(TAG, "DUM MA %d MISTNOSTI", room_count);
    for (size_t j = 0; j < room_count; j++)
    {
        ESP_LOGE(TAG, "MISTNOST %d MA %d ITEMU", j, room_array[j].items_count);
        for (size_t i = 0; i < room_array[j].items_count; i++)
        {
            ESP_LOGE(TAG, "ITEM %d", i);
            lv_obj_del(room_array[j].items[i].panel);
        }
        free(room_array[j].items);
        lv_obj_del(room_array[j].panel);
        ESP_LOGE(TAG, "MISTNOST %d ZNICEA", j);
    }

    free(room_array);
}