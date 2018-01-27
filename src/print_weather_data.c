#include <stdio.h>
#include <string.h>
#include "../lib/jsmn.h"
#include "include/Parsed_Json.h"
#include "include/check_json_string.h"

/**
 * Print a string with the desired format from an array of chars.
 * @param char * format
 * @param char * data The array of chars with the parsed json
 * @param jsmntok_t token The token that is used to compure the string length
 */
void print_key_value(char * format, char * data, jsmntok_t token) {
    printf(format, token.end - token.start, data + token.start);
}

/**
 * Output the weather data to the terminal.
 * @param char * data The array of chars with the parsed json
 * @param struct Parsed_Json parsed_json contains all the parsed tokens
 * @return void
 */
void print_weather_data(char * data, struct Parsed_Json weather) {
     for (int i = 1; i < weather.number_of_tokens; i++) {
        int length = weather.tokens[i].end - weather.tokens[i].start;
        char string[length + 1];

        strncpy(string, data + weather.tokens[i].start, length);
        string[length] = '\0';

        if (check_json_string("coord", string, weather.tokens[i]) == 0) {
            printf("Coordinates\n");
        }
        
        if (check_json_string("lon", string, weather.tokens[i]) == 0) {
            print_key_value("\tLatitude: %.*s \n", data,  weather.tokens[i + 1]);
        }

        if (check_json_string("lat", string, weather.tokens[i]) == 0) {
            print_key_value("\tLongitude: %.*s \n", data,  weather.tokens[i + 1]);
        }

        if (check_json_string("weather", string, weather.tokens[i]) == 0) {
            printf("Weather\n");
        }
        
        if (check_json_string("main", string, weather.tokens[i]) == 0 && weather.tokens[i + 1].type != JSMN_OBJECT) {
            print_key_value("\tConditions: %.*s ", data,  weather.tokens[i + 1]);
        }

        if (check_json_string("temp", string, weather.tokens[i]) == 0 && weather.tokens[i + 1].type != JSMN_OBJECT) {
            print_key_value("\n\tTemperature: %.*s °C\n", data,  weather.tokens[i + 1]);
        }

        if (check_json_string("pressure", string, weather.tokens[i]) == 0 && weather.tokens[i + 1].type != JSMN_OBJECT) {
            print_key_value("\tPressure: %.*s hPa\n", data,  weather.tokens[i + 1]);
        }
       
        if (check_json_string("humidity", string, weather.tokens[i]) == 0 && weather.tokens[i + 1].type != JSMN_OBJECT) {
            print_key_value("\tHumidity: %.*s%%\n", data,  weather.tokens[i + 1]);
        }
    }

    printf("\n--------------------------------------------------------\n\n");
}