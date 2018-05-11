#ifndef __HTTP_CLIENT_H__
#define __HTTP_CLIENT_H__

/*
	Represents an HTTP html response
*/
typedef struct http_response
{
	struct parsed_url_2 *request_uri;
	char *body;
	char *status_code;
	int status_code_int;
	char *status_text;
	char *request_headers;
	char *response_headers;
}http_response_t;



/*
	Prototype functions
*/
http_response_t *http_req(char *http_headers, struct parsed_url_2 *purl);
http_response_t *http_get(char *url, char *custom_headers);
http_response_t *http_head(char *url, char *custom_headers);
http_response_t *http_post(char *url, char *custom_headers, char *post_data);

void http_response_free(http_response_t *hresp);


#endif /*__HTTP_CLIENT_H__*/
