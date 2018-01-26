#include "../../lib/jsmn.h"

#ifndef SEARCH_CITY
#define SEARCH_CITY
/**
 * Search the "to_search" string parameter in the given string "data"
 * that is an array of chars with all the parsed cities.
 * Return 1 if there is a match, 0 otherwise.
 * 
 * @param char * to_search
 * @param char * data
 * @param jsmntok_t * tokens
 * @return boolean
 */
int search_city(char * to_search, char * data, jsmntok_t * tokens);
#endif