#include "ui_main.h"

void app_main(void)
{
  /* Initialize MQTT */
  esp_err_t ret = nvs_flash_init();
  if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
  {
    ESP_ERROR_CHECK(nvs_flash_erase());
    ret = nvs_flash_init();
  }
  ESP_ERROR_CHECK(sensor_init());
  ESP_ERROR_CHECK(bsp_lcd_init());
  ESP_ERROR_CHECK(lvgl_init(LVGL_SCR_SIZE / 8, LV_BUF_ALLOC_EXTERNAL));

  int mqtt_status = mqtt_init();

  /* Initialize UI */
  ui_init(mqtt_status);

}