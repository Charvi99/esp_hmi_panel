# LVGL smart home panel

Project demonstrate how you can use LVGL graphic libray on ESP32-S2-HMI-DevKit-1

## Get started 
### Software Required
* VScode with ESP-IDF 
* Visual Studio with C# 
* clone repository with configuration app on: https://github.com/Charvi99/esp_hmi_panel_App

### Hardware Required

* An ESP32-S2-HMI-DevKit-1 development board
* A USB-C cable for Power supply and programming

### Configure the Project

Open the project configuration menu (`idf.py menuconfig`). 

In the `HMI Board Config` menu:

* Set the board type to `ESP32-S2-HMI-DevKit-V2` in `HMI board`.
* Set LCD display IC to `RM68120` in `LCD Drivers`.

### Build and Flash

Run `idf.py -p PORT flash monitor` to build, flash and monitor the project.

