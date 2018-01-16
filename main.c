#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "./lib/jsmn.h"

struct Buffer {
    char *memory;
    size_t size;
};

/**
 * Read the file in ./data/city.json and return a pointer
 * to the buffer that holds the data.
 * @return char * buffer
 **/
char * read_file() {
    FILE * file;
    char * buffer = NULL;
    int size = 0;

    file = fopen("./data/city.json", "r+");

    if (file) {
        char temp;

        // Iterate through all file's content and increment the actual file size.
        while ((temp = fgetc(file)) != EOF) {
            size++;
        }

        // Assign the right amount of data to the buffer.
        buffer = (char *) malloc((size + 1) * sizeof(char));
        rewind(file);
        fread(buffer, size, 1, file);
    } else {
        perror("Error: ");
    }

    fclose(file);
    return buffer;
}

jsmntok_t * parse_json(char * data) { 
    jsmn_parser parser;
    jsmn_init(&parser);
    int number_of_tokens = 209580;
    
    size_t size = sizeof(jsmntok_t) * number_of_tokens;
    jsmntok_t * tokens = malloc(size);

    int result = jsmn_parse(&parser, data, strlen(data), tokens, number_of_tokens);

    if (result < 0) {
        printf("Failed to parse JSON");
        perror("Err ");
        exit(1);
    }

    // if (tokens[0].type != JSMN_ARRAY || tokens[0].type != JSMN_OBJECT) {
    //     printf("The first element should be an array");
    //     exit(1);
    // }

    return tokens;
}

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

size_t write_to_memory(void *data, size_t size, size_t nmemb, void *pointer) {
    size_t real_size = size * nmemb;

    // cast the received pointer to the Buffer structured data.
    struct Buffer * buffer = (struct Buffer *) pointer;

    // reallocate the memory for the Buffer char pointer
    buffer->memory = realloc(buffer->memory, buffer->size + real_size);
    buffer->size += real_size;

    if (buffer->memory == NULL) {
        printf("Failed to allocate memory for the http get data");
        return 1;
    }

    // Copy the fetched data to the Buffer char pointer
    memcpy(buffer->memory, data, real_size);
    buffer->memory[real_size] = '\0';
}

char * get_weather_data(char * city) {
    curl_global_init(CURL_GLOBAL_ALL);

    char url[] = "http://api.openweathermap.org/data/2.5/weather?appid=82390064987812e43f9ec57cb01311b6&q=";
    strcat(url, city);

    printf("%s\n", url);

    struct Buffer buffer;
    buffer.memory = malloc(1);
    buffer.size = 0;

    CURL *handle;
    CURLcode result;
    handle = curl_easy_init();

    curl_easy_setopt(handle, CURLOPT_URL, url);
    curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_to_memory);
    curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void *) &buffer);
    result = curl_easy_perform(handle);

    return buffer.memory;
};

int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("Please specify the name of a city to search for\n");
        exit(0);
    } else {
        printf("Search for weather forecast in: %s\n", argv[1]);
    }
    
    // Read data from file
    char * data = read_file();

    // Parse the json
    jsmntok_t * cities_tokens = parse_json(data);

    // Search the city
    int found = search_city(argv[1], data, cities_tokens);

    //printf("Tokens size: %i\n", tokens[0].size);

    if (!found) {
        printf("%s was not found in the archive. Please provide another city to search for\n", argv[1]);
        exit(0);
    }

    //printf("Searched city: \"%s\" was found\n", argv[1]);  

    char weather_data[] = get_weather_data( argv[1]);

    jsmntok_t * weather_tokens = parse_json(weather_data);

    printf("%s\n", weather_data);
    printf("Tokens size: %i\n", weather_tokens[0].size);

    free(data);
    free(cities_tokens);
    free(weather_tokens);
    return 0;
}
