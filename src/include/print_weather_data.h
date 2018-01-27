#include "Parsed_Json.h"

#ifndef PRINT_WEATHER_DATA
#define PRINT_WEATHER_DATA
    /**
     * Print the data received from the API.
     * @param char * data
     * @param struct Parsed_Json parsed_json
     * @return void
     */
    void print_weather_data(char * data, struct Parsed_Json parsed_json);
#endif
