#include "../../lib/jsmn.h"

#ifndef PARSE_JSON
#define PARSE_JSON

/**
 * Parse a json string with jsmn lib.
 * @see https://github.com/zserge/jsmn
 * for parsing implementation detail.
 * 
 * @param char * data
 * @param int number_of_tokens
 * @return jsmntok_t * tokens
 */
jsmntok_t * parse_json(char * data, int number_of_tokens);

#endif