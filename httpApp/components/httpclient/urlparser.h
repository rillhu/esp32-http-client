/*
	http-client-c 
	Copyright (C) 2012-2013  Swen Kooij
	
	This file is part of http-client-c.

    http-client-c is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    http-client-c is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with http-client-c. If not, see <http://www.gnu.org/licenses/>.

	Warning:
	This library does not tend to work that stable nor does it fully implent the
	standards described by IETF. For more information on the precise implentation of the
	Hyper Text Transfer Protocol:
	
	http://www.ietf.org/rfc/rfc2616.txt
*/
#ifndef __URLPARSER_H__
#define __URLPARSER_H__

/*
	Represents an url
*/
typedef struct parsed_url_2 
{
	char *uri;					/* mandatory */
    char *scheme;               /* mandatory */
    char *host;                 /* mandatory */
	char *ip; 					/* mandatory */
    char *port;                 /* optional */
    char *path;                 /* optional */
    char *query;                /* optional */
    char *fragment;             /* optional */
    char *username;             /* optional */
    char *password;             /* optional */
}parsed_url_t_2;


struct parsed_url_2 *parse_url(const char *url);
void parsed_url_free_2(struct parsed_url_2 *purl);



#endif /*__URLPARSER_H__*/

