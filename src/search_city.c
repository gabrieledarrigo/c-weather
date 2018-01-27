#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/jsmn.h"

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
int search_city(char * to_search, char * data, jsmntok_t * tokens) {
    //Iterate the json array to find the desired city.
    for (int i = 1; i <= tokens[0].size; i++) {

        // Compute the length of the string
        int length = tokens[i].end - tokens[i].start;
        char city[length + 1];

        // Copy the value of the string.
        strncpy(city, data + tokens[i].start, length);
        city[length] = '\0';

        if (strcmp(to_search, city) == 0) {
            return 1;
        }
    }

    return 0;
}