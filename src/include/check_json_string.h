#include "../../lib/jsmn.h"

#ifndef CHECK_JSON_STRING
#define CHECK_JSON_STRING
/**
 * Check if two string parsed from a jsmntok_t token are equal.
 * 
 * @param char * to_search
 * @param char * string
 * @param jsmntok_t token
 * @return int
 */
int check_json_string(char * to_search, char * string, jsmntok_t token);
#endif