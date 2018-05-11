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

static const char *TAG = "MAIN";

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

#if 0
    parsed_url_t_2 *purl = parse_url("http://www.baidu.com");
    printf("uri: %s\n",purl->uri);    
    printf("scheme: %s\n",purl->scheme);    
    printf("host: %s\n",purl->host);    
    printf("ip: %s\n",purl->ip);    
    printf("port: %s\n",purl->port);
    http_response_t *hresp = http_req("GET / HTTP/1.1\r\nHost:www.baidu.com\r\nConnection:close\r\n\r\n",purl);
    printf("s_code: %s\n", hresp->status_code);
    printf("s_code_int: %d\n", hresp->status_code_int);
    printf("s_text: %s\n", hresp->status_text);    
    printf("body: \n%s\n", hresp->body);
#endif

#if 0
    //memset(hresp,0, sizeof(http_response_t));
    http_response_t *hresp = http_get("http://www.baidu.com", NULL);
    printf("s_code: %s\n", hresp->status_code);
    printf("s_code_int: %d\n", hresp->status_code_int);
    printf("s_text: %s\n", hresp->status_text);    
    printf("body: \n%s\n", hresp->body);

    //http_response_free(hresp);
    
    printf("done\n");
#endif

#if 0
   http_response_t *hresp = http_post("http://www.baidu.com", NULL,"");
    printf("s_code: %s\n", hresp->status_code);
    printf("s_code_int: %d\n", hresp->status_code_int);
    printf("s_text: %s\n", hresp->status_text);    
    printf("body: \n%s\n", hresp->body);

    //http_response_free(hresp);
    
    printf("done2\n");
#endif

    http_response_t *hresp = http_get("http://api.openweathermap.org/data/2.5/forecast/daily?id=1790630&mode=json&units=metric&cnt=1&appid=69e96c570859995c79a7f1dd9a40be3c ", NULL);
    printf("s_code: %s\n", hresp->status_code);
    printf("s_code_int: %d\n", hresp->status_code_int);
    printf("s_text: %s\n", hresp->status_text);    
    printf("body: \n%s\n", hresp->body);

    //http_response_free(hresp);

    printf("done\n");

    
    
}


