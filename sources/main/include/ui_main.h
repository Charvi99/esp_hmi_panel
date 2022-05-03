/**
 * @file ui_sensor2.h
 * @brief 
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

#pragma once

/* --- GLOBAL LIBRARYS --- */
#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"

#include "lvgl/lvgl.h"
#include "lvgl_port.h"
#include "bsp_lcd.h"

#include "data_simulator.h"
#include "adc081.h"
#include "bh1750.h"
#include "mpu6050.h"
#include "esp_log.h"

/* --- DEFINITION OF STRUCTURES --- */

typedef struct
{
    int index;
    int type;
    char *name;
    int val;
    char* sVal;
    char* topic;
    char* on_cmd;
    char* off_cmd;
    char* read_cmd;


    lv_obj_t *panel;
    lv_obj_t *block;
    lv_obj_t *header;
    lv_obj_t *header_2;
    lv_obj_t *img;
    lv_obj_t *value_label;

} item_block;

typedef struct
{
    int index;
    char *name;

    lv_obj_t *panel;
    lv_obj_t *header;
    lv_obj_t *header_2;
    lv_obj_t *light_block;
    lv_obj_t *light_val;
    lv_obj_t *socket_block;
    lv_obj_t *socket_val;
    lv_obj_t *light_img;
    lv_obj_t *socket_img;
    lv_obj_t *line;

    int items_count;
    int light_count;
    int socket_count;
    int extera_count;

    lv_obj_t *item_panel;
    item_block *items;
} room_block;

typedef struct
{
    lv_obj_t *panel;
    lv_obj_t *img;
    lv_obj_t *sw;
    lv_obj_t *val;
} side_block;

typedef struct
{
    lv_obj_t *panel;
    lv_obj_t *header;
    lv_obj_t *header2;
    lv_obj_t *label;
    side_block *block_light;
    side_block *block_socket;
    lv_obj_t *exit;
} side_panel;

typedef struct
{
    lv_obj_t *screen;
    lv_obj_t *panel_main;
    side_panel *panel_side;

} page;



/* --- PROGRAM LIBRARYS --- */
#include "cJSON.h"
#include "mqtt.h"
#include "ui_event.h"
#include "ui_support.h"
#include "prog_support.h"
#include "data_simulator.h"

/* Color value defination */
#define COLOR_BG lv_color_make(0, 241, 245)
#define COLOR_DEEP lv_color_make(0, 173, 71)
#define COLOR_LIGHT lv_color_make(233, 230, 230)
#define COLOR_DARK lv_color_make(163, 156, 156)
#define COLOR_THEME lv_color_make(182, 212, 97)

/* Image declaration */
LV_IMG_DECLARE(light);
LV_IMG_DECLARE(temp_humid);
LV_IMG_DECLARE(mems);
LV_IMG_DECLARE(Bulb);
LV_IMG_DECLARE(Socket);
LV_IMG_DECLARE(Bulb_s);
LV_IMG_DECLARE(Socket_s);
LV_IMG_DECLARE(Bulb_b);
LV_IMG_DECLARE(Socket_b);

LV_IMG_DECLARE(Temp);
LV_IMG_DECLARE(Humi);
LV_IMG_DECLARE(co);
LV_IMG_DECLARE(unknow);

LV_IMG_DECLARE(no_wifi);


#define TYPE_LIGHT 0
#define TYPE_SOCKET 1
#define TYPE_TEMP 2
#define TYPE_HUMI 3
#define TYPE_CO2 4
#define TYPE_UNKNOW 5

#define ROW_LIGHT 0
#define ROW_SOCKET 1
#define ROW_EXTRA 2

/* --- GLOBAL VARIABLES --- */
extern room_block *room_array;
extern int room_count;
extern int active_room_index;

extern page *page_main;
extern page *page_detail;


void ui_init(int mqtt_status);
void receive_data(char* ,int,char* ,int);

void show_error(char* message);

void house_init(cJSON* json);
void house_destroy();

void add_to_blueprint(cJSON *newData);
void clear_blueprint();

void change_main_panel_vals(lv_obj_t **light_label, lv_obj_t **socket_label);

void generate_items(int room_index, cJSON *items);