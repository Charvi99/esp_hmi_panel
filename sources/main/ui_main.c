/**
 * @file ui_main.c
 * @brief Sensor UI src.
 * @version 0.1
 * @date 2021-03-07
 *
 * @copyright Copyright 2021 Espressif Systems (Shanghai) Co. Ltd.
 *
 *      Licensed under the Apache License, Version 2.0 (the "License");
 *      you may not use this file except in compliance with the License.
 *      You may obtain a copy of the License at
 *
 *               http://www.apache.org/licenses/LICENSE-2.0
 *
 *      Unless required by applicable law or agreed to in writing, software
 *      distributed under the License is distributed on an "AS IS" BASIS,
 *      WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *      See the License for the specific language governing permissions and
 *      limitations under the License.
 */

#include "ui_main.h"

/* Log defination */
#define TAG ((const char *)"ui_main")
#define UI_LOG_TRACE(...) ESP_LOGD(TAG, ##__VA_ARGS__)

//====================================

page *page_main = NULL;
page *page_detail = NULL;

room_block *room_array = NULL;
int room_count = 0;
int active_room_index = -1;

cJSON *blueprint;
bool build_house_flag = false;

bool global_light_override = false;

void init_screen(page *current_page)
{
    current_page->screen = lv_obj_create(NULL, NULL);

    current_page->panel_main = init_main_panel(current_page->screen);

    current_page->panel_side = (side_panel *)malloc(sizeof(side_panel));
    current_page->panel_side->panel = init_side_panel(current_page->screen, current_page->panel_side);
}

void init_room_click_event()
{
    for (size_t i = 0; i < room_count; i++)
    {
        ESP_LOGD(TAG, "I USED init_room_vals %d times", i);
        event_click_room(room_array[i].panel, LV_EVENT_CLICKED);
        event_click_exit(NULL, LV_EVENT_CLICKED);
    }
}

void ui_init(int mqtt_status)
{
    lv_port_sem_take();

    clear_blueprint();

    page_main = (page *)malloc(sizeof(page));
    page_detail = (page *)malloc(sizeof(page));

    init_screen(page_main);
    init_screen(page_detail);

    init_room_click_event();

    lv_scr_load(page_main->screen);

    if (mqtt_status == -1)
        show_error("WIFI NOT CONNECTED\n CLICK TO RESTART");
    else if (mqtt_status == -2)
        show_error("WIFI IS CONNECTED\n BUT MQTT IS NOT\n CLICK TO RESTART");

    lv_port_sem_give();
}

void show_error(char *message)
{
    lv_obj_t *panel = create_def_obj(page_main->panel_main, 500, 150, message);
    lv_obj_set_click(panel, true);
    lv_obj_set_event_cb(panel, esp_restart);

    lv_obj_align(panel, NULL, LV_ALIGN_IN_LEFT_MID, 50, 0);
    lv_obj_set_style_local_bg_color(panel, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, COLOR_LIGHT);
    lv_obj_set_style_local_value_font(panel, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, &font_en_bold_28);
    lv_obj_set_style_local_value_color(panel, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, COLOR_DARK);

    lv_obj_t *no_wifi_img = lv_img_create(panel, NULL);
    lv_img_set_src(no_wifi_img, &no_wifi);
    lv_obj_align(no_wifi_img, NULL, LV_ALIGN_IN_LEFT_MID, 20, 0);
    uncolor_icon(no_wifi_img);
}

void receive_data(char *topic, int topic_len, char *data, int data_len)
{

    printf("TOPIC=%.*s\r\n", topic_len, topic);
    printf("DATA=%.*s\r\n", data_len, data);

    /* ------- TOPIC PARSE AND PREPARE ------- */
    char topic_parse[topic_len + 1];
    int topic_part_counter = 0;
    for (size_t i = 0; i < topic_len; i++)
    {
        if (topic[i] == '/')
            topic_part_counter++;
        topic_parse[i] = topic[i];
    }
    topic_parse[topic_len] = '\0';

    /* ------- DATA PARSE AND PREPARE ------- */
    char data_parse[data_len + 1];
    for (size_t i = 0; i < data_len; i++)
        data_parse[i] = data[i];
    data_parse[data_len] = '\0';

    ESP_LOGW(TAG, "==========");
    ESP_LOGW(TAG, "topic len: %d", topic_len);
    ESP_LOGW(TAG, "topic parts: %d", topic_part_counter);
    ESP_LOGW(TAG, "topic parsed: %s", topic_parse);
    ESP_LOGW(TAG, "==========");
    ESP_LOGW(TAG, "data len: %d", data_len);
    ESP_LOGW(TAG, "data parsed: %s", data_parse);
    ESP_LOGW(TAG, "==========");

    /* --- TOPIC CONTAINS ONE PART ADRESS -> new room init  --- */
    if (topic_part_counter == 0)
    {
        if ((strcmp(topic_parse, MAIN_TOPIC) == 0))
        {
            if ((data[0] == '{') && (build_house_flag == true))
            {
                cJSON *json = cJSON_Parse(data);
                if (json != NULL)
                    add_to_blueprint(json);
                // house_init(json);
                else
                    ESP_LOGW(TAG, "Prichozi json se nenacetl");
            }
            else if ((data[0] == 's') && (build_house_flag == false))
            {
                ESP_LOGW(TAG, "======== ZAHAJEN ZAPIS BLUEPRINTU =======");
                build_house_flag = true;
                clear_blueprint();
            }
            else if ((data[0] == 'e') && (build_house_flag == true))
            {
                ESP_LOGW(TAG, "======== UKONCEN ZAPIS BLUEPRINTU =======");
                build_house_flag = false;
                house_init(blueprint);
            }
        }
        else if ((strcmp(topic_parse, RESET_TOPIC) == 0))
        {
            esp_restart();
        }
    }

    /* --- TOPIC CONTAINS MORE PART ADRESS -> item interaction  --- */
    else
    {
        for (size_t i = 0; i < room_count; i++)
        {
            for (size_t j = 0; j < room_array[i].items_count; j++)
            {
                if (strcmp(topic_parse, room_array[i].items[j].topic) == 0)
                {
                    ESP_LOGI(TAG, "V MISTNOSTI: %s BYL STISKNUT ITEM %s", room_array[i].name, room_array[i].items[j].name);
                    if (strcmp(data_parse, room_array[i].items[j].on_cmd))
                        set_item_value_1(i, j, 0);
                    else if (strcmp(data_parse, room_array[i].items[j].off_cmd))
                        set_item_value_1(i, j, 1);
                    else if (strcmp(data_parse, room_array[i].items[j].read_cmd))
                    {
                        esp_mqtt_client_publish(client, room_array[i].items[j].topic, room_array[i].items[j].sVal, 0, 1, 0);
                    }
                }
            }
        }
    }
}

void add_to_blueprint(cJSON *newData)
{
    if (cJSON_IsNull(newData))
        return;

    int count = cJSON_GetArraySize(blueprint);

    char item_index_char[5];
    sprintf(item_index_char, "%d", count);
    cJSON_AddItemToObject(blueprint, item_index_char, newData);
    ESP_LOGW(TAG, "========== TISKNU NOVY BLUEPRINT =========");
    printf(cJSON_Print(blueprint));
    ESP_LOGW(TAG, "===================");
}

void clear_blueprint()
{
    if (blueprint != NULL)
        cJSON_Delete(blueprint);

    blueprint = cJSON_CreateObject();
}
