#ifndef __HTTP_CLIENT_H__
#define __HTTP_CLIENT_H__

#include "urlparser.h"

#define DEBUG_TRACE_ENABLE
//#define SSL_ENABLE


#ifdef DEBUG_TRACE_ENABLE
    #define DPRINT(fmt, args...) fprintf(stderr, "[%s(): L%d] "fmt"\n", __func__, __LINE__, ##args);
#else
    #define DPRINT(fmt, ...)
#endif

/*
	Represents an HTTP html response
*/
typedef struct http_response
{
    parsed_url_t_2  *request_uri;
    char *body;
    char *status_code;
    int status_code_int;
    /*Donot use this member anymore due to 
      some web site does not return status text
    */
    //char *status_text;
    char *request_headers;
    char *response_headers;
}http_response_t;

/*
	Prototype functions
*/
http_response_t *http_req(char *http_headers, parsed_url_t_2  *purl);
http_response_t *http_get(char *url, char *custom_headers);
http_response_t *http_head(char *url, char *custom_headers);
http_response_t *http_post(char *url, char *custom_headers, char *post_data);
void http_response_free(http_response_t *hresp);

#endif /*__HTTP_CLIENT_H__*/
