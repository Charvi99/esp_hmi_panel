#pragma once

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"

#include "lwip/err.h"
#include "lwip/sys.h"
#include "lwip/sockets.h"
#include "lwip/dns.h"
#include "lwip/netdb.h"

#include "mqtt_client.h"
#include "esp_system.h"
#include "esp_netif.h"

#include "ui_main.h"


#define WIFI_SSID      "UPCD718934"
#define WIFI_PASS      "Uc7yuewwtXph"
// #define WIFI_SSID      "Charv_UPC"
// #define WIFI_PASS      "XKVQQOAC"
// #define ESP_WIFI_SSID      "EspressifSystemsIOT"
// #define ESP_WIFI_PASS      "Espressif32"
#define MAXIMUM_RETRY  5

#define MAIN_TOPIC                  "house"
#define RESET_TOPIC                  "reset"

esp_mqtt_client_handle_t client;

int mqtt_init(void);

bool wifi_init(void);
bool mqtt_start_client(void);

int bundle_topic(char *topic, char *room_name, int item_index);
int unbuild_topic(char *topic, char *main_topic, char *room_topic, char *item_topic);
int mqtt_create_item_payload(char *payload, int _type, const char *_name, int _val);