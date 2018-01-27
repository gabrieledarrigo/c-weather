#include "../../lib/jsmn.h"

#ifndef CHECK_JSON_STRING
#define CHECK_JSON_STRING
int check_json_string(char * to_search, char * string, jsmntok_t token);
#endif