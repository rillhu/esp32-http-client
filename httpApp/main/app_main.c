/* 
HTTP lib test project
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
            //.ssid = "HNA-Cloud",
            //.password = "hnaresearch",

        },
    };
    ESP_LOGI(TAG, "Setting WiFi configuration SSID %s...", wifi_config.sta.ssid);
    ESP_ERROR_CHECK( esp_wifi_set_mode(WIFI_MODE_STA) );
    ESP_ERROR_CHECK( esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config) );
    ESP_ERROR_CHECK( esp_wifi_start() );
    
    esp_wifi_connect();
}


char *urls[4] = 
    {
        "http://www.baidu.com",
        "http://www.example.com",
        "http://www.wechat.com",
        "http://www.sina.com"
    };
        
void http_task(void *pvParameters)
{
    (void)pvParameters;
    unsigned int i = 0;
    while(1){

#if 0   //raw mode to send http request
        printf("http get, heap_size: %d\n",esp_get_free_heap_size());

        //Note shou comment the free(hresp->request_headers); if use this test case.
        parsed_url_t_2 *purl = parse_url("http://www.baidu.com");
        printf("uri: %s\n",purl->uri);    
        printf("scheme: %s\n",purl->scheme);    
        printf("host: %s\n",purl->host);    
        printf("ip: %s\n",purl->ip);    
        printf("port: %s\n",purl->port);
        http_response_t *hresp = http_req("GET / HTTP/1.1\r\nHost:www.baidu.com\r\nConnection:close\r\n\r\n",purl);
        //printf("s_code: %s\n", hresp->status_code);
        //printf("s_code_int: %d\n", hresp->status_code_int);
        //printf("s_text: %s\n", hresp->status_text);    
        //printf("body222: \n%s\n", hresp->body);
        
        http_response_free(hresp);
        
        printf("http free, heap_size: %d\n",esp_get_free_heap_size());
#endif

#if 0   //http get test 
        char * url = "http://www.baidu.com";    //prefer to use such format to transfer the url, not directly write in function call.
        http_response_t *hresp = http_get(url, NULL);
        
        printf("http get, heap_size: %d\n",esp_get_free_heap_size());
        if(hresp != NULL){
            printf("s_code: %s\n", hresp->status_code);
            printf("s_code_int: %d\n", hresp->status_code_int);
            printf("s_text: %s\n", hresp->status_text);    
            printf("body: \n%s\n", hresp->body);
            http_response_free(hresp);            
            printf("done1\n");
        }
        
        printf("done2\n");
        
        printf("http free, heap_size: %d\n",esp_get_free_heap_size());
#endif

#if 0   //http post test
        char * url2 = "http://www.example.com";    //prefer to use such format to transfer the url, not directly write in function call.

        http_response_t *hresp2 = http_post(url2, NULL,"title=test&sub%5B%5D=1&sub%5B%5D=2&sub%5B%5D=3");
        
        if(hresp != NULL){
            printf("s_code: %s\n", hresp2->status_code);
            printf("s_code_int: %d\n", hresp2->status_code_int);
            printf("s_text: %s\n", hresp2->status_text);    
            printf("body: \n%s\n", hresp2->body);

            http_response_free(hresp2);
        }
        
        printf("http free2, heap_size: %d\n",esp_get_free_heap_size());
#endif

#if 1   //https get test
        char * url = urls[i++&0x3];//"http://www.example.com";    //prefer to use such format to transfer the url, not directly write in function call.
        http_response_t *hresp = http_get(url, NULL);
        
        printf("http get, heap_size: %d\n",esp_get_free_heap_size());
        if(hresp != NULL){
            printf("s_code: %s\n", hresp->status_code);
            printf("s_code_int: %d\n", hresp->status_code_int);
            //printf("s_text: %8s\n", hresp->status_text);
            char buf[128];
            snprintf(buf,127,"%s",hresp->body);
            printf("body: \n%s\n",buf);
            http_response_free(hresp);            
            printf("done1\n");
        }
        
        printf("done2\n");
        
        printf("http free, heap_size: %d\n",esp_get_free_heap_size());
#endif


#if 0   //A test case to get weather report from openweathermap
        http_response_t *hresp3 = http_get("http://api.openweathermap.org/data/2.5/forecast/daily?id=1790630&mode=json&units=metric&cnt=1&appid=69e96c570859995c79a7f1dd9a40be3c ", NULL);
        printf("s_code: %s\n", hresp3->status_code);
        printf("s_code_int: %d\n", hresp3->status_code_int);
        printf("s_text: %s\n", hresp3->status_text);    
        printf("body: \n%s\n", hresp3->body);
        http_response_free(hresp3);
        printf("done\n");
#endif

#if 0   
        //A method to check the heap size status, it is useful to determine which part of you code 
        // does not free memory correctly.
        char *str1 = (char *)malloc(1024);
        memset(str1,'A',1024);
        char *str2 = (char *)malloc(1024);
        memcpy(str2,str1, 1024);

        str1 = (char *)realloc(str1,2048);
        
        memcpy(str1,str2, 1024);
        memcpy(str1+1024,str2, 1024);
        
        printf("111, heap_size: %d\n",esp_get_free_heap_size());        
        free(str1);
        free(str2);
        printf("222, heap_size: %d\n",esp_get_free_heap_size());
#endif        
        vTaskDelay(2000 / portTICK_RATE_MS);
        printf("start again\n");
    }
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
    
    printf("Entering task, heap_size: %d\n",esp_get_free_heap_size());
    xTaskCreate(&http_task, "http_task", 1024*80, NULL, 5, NULL);
    
}


