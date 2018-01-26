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

    //printf("Searched city: \"%s\" was found\n", argv[1]);  

    char * weather_data = get_weather_data(argv[1]);

    // Parse the api json result
    struct Parsed_Json weather = parse_json(weather_data, 512);
    //printf("%s\n", weather_data);

    for (int i = 1; i < weather.number_of_tokens; i++) {
        int length = weather.tokens[i].end - weather.tokens[i].start;
        char string[length + 1];

        memcpy(string, weather_data + weather.tokens[i].start, length);
        string[length] = '\0';

        // printf("\n");
        // printf("Index: %i \n", i);
        // printf("End: %i \n", weather.tokens[i].end);
        // printf("Start %i \n", weather.tokens[i].start);
        // printf("Child %i \n", weather.tokens[i].size);
        // printf("type %i \n", weather.tokens[i].type);
        // printf("string is: %s \n", string);

        if (weather.tokens[i].type == JSMN_STRING && strcmp(string, "coord") == 0) {
            printf("Coordinates\n");
        }
        
        if (weather.tokens[i].type == JSMN_STRING && strcmp(string, "lon") == 0) {
            printf("\tLongitude: %.*s \n", weather.tokens[i + 1].end - weather.tokens[i + 1].start, weather_data + weather.tokens[i + 1].start);
        }
     
        if (weather.tokens[i].type == JSMN_STRING && strcmp(string, "lon") == 0) {
            printf("\tLatitude: %.*s \n", weather.tokens[i + 1].end - weather.tokens[i + 1].start, weather_data + weather.tokens[i + 1].start);
        }

        if (weather.tokens[i].type == JSMN_STRING && strcmp(string, "weather") == 0) {
            printf("Weather\n");
            printf("\tConditions: %.*s \n", weather.tokens[i + 6].end - weather.tokens[i + 6].start, weather_data + weather.tokens[i + 6].start);
            printf("\tW: %.*s \n", weather.tokens[i + 8].end - weather.tokens[i + 8].start, weather_data + weather.tokens[i + 8].start);
        }
    }

    free(data);
    free(cities.tokens);
    free(weather.tokens);
    return 0;
}
