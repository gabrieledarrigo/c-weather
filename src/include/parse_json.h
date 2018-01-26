#include "../../lib/jsmn.h"
#include "Parsed_Json.h"

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
struct Parsed_Json parse_json(char * data, int number_of_tokens);
#endif