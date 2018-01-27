#include <string.h>
#include "../lib/jsmn.h"

/**
 * Check if two string parsed from a jsmntok_t token are equal.
 * Return 0 if the string are equals, 0 otherwise
 * 
 * @param char * to_search
 * @param char * string
 * @param jsmntok_t token
 * @return int
 */
int check_json_string(char * to_search, char * string, jsmntok_t token) {
    if (token.type == JSMN_STRING && strcmp(to_search, string) == 0) {
        return 0;
    }

    return -1;
}