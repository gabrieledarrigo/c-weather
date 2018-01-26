#include "../../lib/jsmn.h"

#ifndef PARSED_JSON
#define PARSED_JSON
/**
 * A record that holds the parsed json.
 * @var int number_of_tokens The number of parsed tokens.
 * @var jsmntok_t * tokens The parsed tokens.
 **/
struct Parsed_Json {
    int number_of_tokens;
    jsmntok_t * tokens;
};
#endif