#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "lib/jsmn.h"
#include "src/include/Buffer.h"
#include "src/include/read_file.h"
#include "src/include/parse_json.h"
#include "src/include/search_city.h"
#include "src/include/get_weather_data.h"

int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("Please specify the name of a city to search for\n");
        exit(0);
    } else {
        printf("Search for weather forecast in: %s\n", argv[1]);
    }
    
    // Read data from file
    char * data = read_file("./data/city.json");

    // Parse the json. 209580 is the precomputed number of
    // tokens that will be used to allocate the memory.
    jsmntok_t * cities_tokens = parse_json(data, 209580);

    // Search the city
    int found = search_city(argv[1], data, cities_tokens);

    printf("Tokens size: %i\n", cities_tokens[0].size);

    if (!found) {
        printf("%s was not found in the archive. Please provide another city to search for\n", argv[1]);
        exit(0);
    }

    //printf("Searched city: \"%s\" was found\n", argv[1]);  

    char * weather_data = get_weather_data(argv[1]);

    jsmntok_t * weather_tokens = parse_json(weather_data, 256);

    printf("%s\n", weather_data);
    printf("Tokens size: %i\n", weather_tokens[0].size);

    free(data);
    free(cities_tokens);
    free(weather_tokens);
    return 0;
}
