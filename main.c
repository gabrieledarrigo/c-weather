#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "lib/jsmn.h"
#include "src/include/Buffer.h"
#include "src/include/Parsed_Json.h"
#include "src/include/check_json_string.h"
#include "src/include/get_weather_data.h"
#include "src/include/parse_json.h"
#include "src/include/print_weather_data.h"
#include "src/include/read_file.h"
#include "src/include/search_city.h"

int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("\n--------------------------------------------------------\n");
        printf("| Please specify the name of a city to search for\n");
        printf("--------------------------------------------------------\n\n");
        exit(1);
    } else {
        printf("\n--------------------------------------------------------\n");
        printf("| Searching for current weather conditions in: %s\n", argv[1]);
        printf("--------------------------------------------------------\n\n");
    }
    
    // Read data from file
    char * data = read_file("./data/city.json");

    // Parse the json. 209580 is the precomputed number of
    // tokens that will be used to allocate the memory.
    struct Parsed_Json cities = parse_json(data, 209580);

    // Search the city
    int found = search_city(argv[1], data, cities.tokens);

    if (found == -1) {
        printf("\nError: THe city with name %s was not found in the archive. Please provide another city to search for\n", argv[1]);
        exit(1);
    }

    // Retrieve the data from the API
    char * weather_data = get_weather_data(argv[1]);

    // Parse the api json result
    struct Parsed_Json weather = parse_json(weather_data, 2048);

    // Print the result
    print_weather_data(weather_data, weather);

    free(data);
    free(cities.tokens);
    free(weather.tokens);
    return 0;
}
