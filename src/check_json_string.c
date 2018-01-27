#include <string.h>
#include "../lib/jsmn.h"

int check_json_string(char * to_search, char * string, jsmntok_t token) {
    if (token.type == JSMN_STRING && strcmp(to_search, string) == 0) {
        return 0;
    }

    return -1;
}