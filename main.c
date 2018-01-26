#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "lib/jsmn.h"
#include "src/include/Buffer.h"
#include "src/include/Parsed_Json.h"
#include "src/include/read_file.h"
#include "src/include/parse_json.h"
#include "src/include/search_city.h"
#include "src/include/get_weather_data.h"


int check_json_string(char * to_search, char * string, jsmntok_t token) {
    if (token.type == JSMN_STRING && strcmp(to_search, string) == 0) {
        return 1;
    }

    return 0;
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("Please specify the name of a city to search for\n");
        exit(1);
    } else {
        printf("Search for weather forecast in: %s\n", argv[1]);
    }
    
    // Read data from file
    char * data = read_file("./data/city.json");

    // Parse the json. 209580 is the precomputed number of
    // tokens that will be used to allocate the memory.
    struct Parsed_Json cities = parse_json(data, 209580);

    // Search the city
    int found = search_city(argv[1], data, cities.tokens);

    if (!found) {
        printf("%s was not found in the archive. Please provide another city to search for\n", argv[1]);
        exit(1);
    }

    char * weather_data = get_weather_data(argv[1]);

    // Parse the api json result
    struct Parsed_Json weather = parse_json(weather_data, 512);

    for (int i = 1; i < weather.number_of_tokens; i++) {
        int length = weather.tokens[i].end - weather.tokens[i].start;
        char string[length + 1];

        strncpy(string, weather_data + weather.tokens[i].start, length);
        string[length] = '\0';

        if (weather.tokens[i].type == JSMN_STRING && strcmp(string, "coord") == 0) {
            printf("Coordinates\n");
        }
        
        if (weather.tokens[i].type == JSMN_STRING && strcmp(string, "lon") == 0) {
            printf("\tLatitude: %.*s \n", weather.tokens[i + 1].end - weather.tokens[i + 1].start, weather_data + weather.tokens[i + 1].start);
        }

        if (weather.tokens[i].type == JSMN_STRING && strcmp(string, "lat") == 0) {
            printf("\tLongitude: %.*s \n", weather.tokens[i + 1].end - weather.tokens[i + 1].start, weather_data + weather.tokens[i + 1].start);
        }

        if (weather.tokens[i].type == JSMN_STRING && strcmp(string, "weather") == 0) {
            printf("Weather\n");
        }
        
        if (weather.tokens[i].type == JSMN_STRING && strcmp(string, "main") == 0 && weather.tokens[i + 1].type != JSMN_OBJECT) {
            printf("\tConditions: %.*s \n", weather.tokens[i + 1].end - weather.tokens[i + 1].start, weather_data + weather.tokens[i + 1].start);
        }

        if (weather.tokens[i].type == JSMN_STRING && strcmp(string, "description") == 0 && weather.tokens[i + 1].type != JSMN_OBJECT) {
            printf("\tDescription: %.*s \n", weather.tokens[i + 1].end - weather.tokens[i + 1].start, weather_data + weather.tokens[i + 1].start);
        }

        if (weather.tokens[i].type == JSMN_STRING && strcmp(string, "temp") == 0 && weather.tokens[i + 1].type != JSMN_OBJECT) {
            printf("\tTemperature: %.*s \n", weather.tokens[i + 1].end - weather.tokens[i + 1].start, weather_data + weather.tokens[i + 1].start);
        }

    }

    free(data);
    free(cities.tokens);
    free(weather.tokens);
    return 0;
}
