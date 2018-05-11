#ifndef __HTTP_CLIENT_H__
#define __HTTP_CLIENT_H__


/*
	Represents an HTTP html response
*/
typedef struct http_response
{
//	struct parsed_url *request_uri;
	char *body;
	char *status_code;
	int status_code_int;
	char *status_text;
//	char *request_headers;
	char *response_headers;
}http_response_t;



http_response_t *http_req(char *http_headers, char *url);

#endif
