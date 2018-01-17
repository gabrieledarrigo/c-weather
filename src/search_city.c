#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/jsmn.h"

int search_city(char * to_search, char * data, jsmntok_t * tokens) {
    //Iterate the json array to find the desired city.
    for (int i = 1; i <= tokens[0].size; i++) {
        int length = tokens[i].end - tokens[i].start;
        char city[length + 1];
        strncpy(city, data + tokens[i].start, length);
        city[length] = '\0';

        if (strcmp(to_search, city) == 0) {
            printf("Found! %s\n", city);
            return 1;
        }
    }

    return 0;
}