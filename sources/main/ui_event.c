#include "ui_event.h"

#define TAG ((const char *)"ui_event")


void event_click_item(lv_obj_t *obj, lv_event_t event)
{
    if (LV_EVENT_CLICKED == event)
    {
        ESP_LOGW(TAG, "aktivni mistnost %d", active_room_index);

        int item_index = search_for_item(obj, TYPE_LIGHT);
        if (item_index > -1)
        {
            // if (room_array[active_room_index].items[item_index].val == 0)
            // {
            //     room_array[active_room_index].items[item_index].val = 1;
            // }
            // else
            // {
            //     room_array[active_room_index].items[item_index].val = 0;
            // }

            // char topic[50];
            // bundle_topic(topic, room_array[active_room_index].name, room_array[active_room_index].items[item_index].index);

            // char message[100];
            // mqtt_create_item_payload(message, room_array[active_room_index].items[item_index].type, room_array[active_room_index].items[item_index].name, room_array[active_room_index].items[item_index].val);

            esp_mqtt_client_publish(client, room_array[active_room_index].items[item_index].topic, ((room_array[active_room_index].items[item_index].val == 0)?  room_array[active_room_index].items[item_index].on_cmd : room_array[active_room_index].items[item_index].off_cmd), 0, 1, 0);

            change_main_panel_vals(&page_detail->panel_side->block_light->val, &page_detail->panel_side->block_socket->val);


            ESP_LOGW(TAG, "LIGHT NO.%d PRESSED IN ROOM %d TO -%s-", item_index, active_room_index, (room_array[active_room_index].items[item_index].val == 0) ? "OFF" : "ON");
        }
    }
}

void event_click_room(lv_obj_t *obj, lv_event_t event)
{
    if (LV_EVENT_CLICKED == event)
    {
        active_room_index = search_for_room(obj);
        lv_label_set_text(page_detail->panel_side->label, room_array[active_room_index].name);
        lv_obj_set_hidden(room_array[active_room_index].item_panel, false);
        lv_scr_load(page_detail->screen);
        lv_obj_set_style_local_bg_color(page_detail->panel_side->exit, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, COLOR_DARK);

        ESP_LOGI(TAG, "%d", active_room_index);

        change_main_panel_vals(&page_detail->panel_side->block_light->val, &page_detail->panel_side->block_socket->val);

        if (lv_label_get_text(page_detail->panel_side->block_light->val)[0] != '0')
            color_icon(page_detail->panel_side->block_light->img);
        else
            uncolor_icon(page_detail->panel_side->block_light->img);

        if (lv_label_get_text(page_detail->panel_side->block_socket->val)[0] != '0')
            color_icon(page_detail->panel_side->block_socket->img);
        else
            uncolor_icon(page_detail->panel_side->block_socket->img);
    }
}

void event_click_exit(lv_obj_t *obj, lv_event_t event)
{
    if (LV_EVENT_CLICKED == event && active_room_index > -1)
    {
        change_main_panel_vals(&room_array[active_room_index].light_val, &room_array[active_room_index].socket_val);

        if (lv_label_get_text(room_array[active_room_index].light_val)[0] != '0')
            color_icon(page_detail->panel_side->block_light->img);
        else
            uncolor_icon(page_detail->panel_side->block_light->img);

        if (lv_label_get_text(room_array[active_room_index].socket_val)[0] != '0')
            color_icon(page_detail->panel_side->block_socket->img);
        else
            uncolor_icon(page_detail->panel_side->block_socket->img);

        change_main_panel_vals_all(&page_main->panel_side->block_light->val, &page_main->panel_side->block_socket->val);

        if (lv_label_get_text(page_main->panel_side->block_light->val)[0] != '0')
            color_icon(page_main->panel_side->block_light->img);
        else
            uncolor_icon(page_main->panel_side->block_light->img);

        if (lv_label_get_text(page_main->panel_side->block_socket->val)[0] != '0')
            color_icon(page_main->panel_side->block_socket->img);
        else
            uncolor_icon(page_main->panel_side->block_socket->img);

        ESP_LOGW(TAG, "< EXIT");
        lv_obj_set_hidden(room_array[active_room_index].item_panel, true);
        lv_scr_load(page_main->screen);
        lv_label_set_text(page_main->panel_side->label, "HOUSE");
        active_room_index = -1;
    }
}

void event_global_override(lv_obj_t *obj, lv_event_t event)
{
    if (event == LV_EVENT_CLICKED)
    {
        if (obj == page_main->panel_side->block_light->panel)
        {
            ESP_LOGW(TAG, "A");
        }
        else if (obj == page_main->panel_side->block_socket->panel)
        {
            ESP_LOGW(TAG, "B");
        }
        else if (obj == page_detail->panel_side->block_light->panel)
        {
            if (active_room_index != -1)
            {
                event_light_override(active_room_index);
            }
        }
        else if (obj == page_detail->panel_side->block_socket->panel)
        {
        }
    }
}

void event_light_override(int room_index)
{
    if (room_index < 0 || room_index > room_count)
    {
        ESP_LOGI(TAG, "OVERRIDING ALL LIGHTS");
    }
    else
    {
        ESP_LOGI(TAG, "OVERRIDING ROOM#%d LIGHTS", active_room_index);
    }
}
