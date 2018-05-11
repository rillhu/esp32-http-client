/* LwIP SNTP example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event_loop.h"
#include "esp_log.h"
#include "esp_attr.h"
#include "esp_sleep.h"
#include "nvs_flash.h"

#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include "lwip/netdb.h"
#include "lwip/dns.h"


#include "http_client.h"

static const char *TAG = "SNTP";

/* Constants that aren't configurable in menuconfig */
#define WEB_SERVER "api.openweathermap.org"
#define WEB_PORT 80

static char *REQUEST = "GET /data/2.5/forecast/daily?id=1790630&mode=json&units=metric&cnt=1&appid=69e96c570859995c79a7f1dd9a40be3c HTTP/1.1\r\n"
        "HOST: api.openweathermap.org\r\n"
        "User-Agent: esp-idf/1.0 esp32\r\n"
        "Cache-Control: no-cache\r\n"
        "Connection: close\r\n" //Donot keep connection due to we use blocking socket.
        "\r\n";


static esp_err_t event_handler(void *ctx, system_event_t *event)
{
    return ESP_OK;
}


static void initialise_wifi(void)
{
    tcpip_adapter_init();
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK( esp_wifi_init(&cfg) );
    ESP_ERROR_CHECK( esp_wifi_set_storage(WIFI_STORAGE_RAM) );
    wifi_config_t wifi_config = {
        .sta = {
            .ssid = "HNA-Cloud",
            .password = "hnaresearch",
        },
    };
    ESP_LOGI(TAG, "Setting WiFi configuration SSID %s...", wifi_config.sta.ssid);
    ESP_ERROR_CHECK( esp_wifi_set_mode(WIFI_MODE_STA) );
    ESP_ERROR_CHECK( esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config) );
    ESP_ERROR_CHECK( esp_wifi_start() );
    
    esp_wifi_connect();
}

void app_main()
{
    nvs_flash_init();
    esp_event_loop_init(event_handler, NULL);
    initialise_wifi();

    /*
        * Wait for wifi is connected
        */
    tcpip_adapter_ip_info_t ip_info;
    tcpip_adapter_get_ip_info(TCPIP_ADAPTER_IF_STA, &ip_info);
    while(ip_info.ip.addr == 0){

        ESP_LOGI(TAG,"WiFi is not ready! Pls set with esp-touch\n");
        vTaskDelay(1000 / portTICK_RATE_MS);
        tcpip_adapter_get_ip_info(TCPIP_ADAPTER_IF_STA, &ip_info);
    }

    vTaskDelay(2000 / portTICK_RATE_MS);
    /* set up the tasks
    */

    //xTaskCreate(&http_get_weather_task, "http_get_weather_task", 1024*40, NULL, 5, NULL);
    http_response_t *hresp = http_req(REQUEST,WEB_SERVER);


}


