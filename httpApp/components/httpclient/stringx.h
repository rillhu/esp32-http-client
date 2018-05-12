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
#ifndef __STRINGX_H__
#define __STRINGX_H__

char *str_dup(const char *src);
char *str_replace(char *search , char *replace , char *subject);
char* get_until(char *haystack, char *until);
int str_contains(const char *haystack, const char *needle);
char *str_ndup (const char *str, size_t max);
char* base64_decode(char *b64src);
char* base64_encode(char *clrstr);

#endif /*__STRINGX_H__*/

