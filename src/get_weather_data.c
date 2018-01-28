#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "include/Buffer.h"

/**
 * Save the data from received from the server into a Buffer struct.
 * @see https://curl.haxx.se/libcurl/c/CURLOPT_WRITEDATA.html for the function signature.
 */
size_t write_to_buffer(void *data, size_t size, size_t nmemb, void *pointer) {
    size_t real_size = size * nmemb;

    // Cast the received pointer to the Buffer structured data.
    struct Buffer * buffer = (struct Buffer *) pointer;

    // Reallocate the memory for the Buffer char pointer
    buffer->memory = realloc(buffer->memory, buffer->size + real_size + 1);
    buffer->size += real_size;

    if (buffer->memory == NULL) {
        printf("Failed to allocate memory for the http get data");
        return 1;
    }

    // Copy the fetched data to the Buffer char pointer
    memcpy(buffer->memory, data, real_size);
    buffer->memory[real_size] = '\0';
    
    return real_size;
};

/**
 * Retrieve the weather data from https://openweathermap.org/api
 * with an HTTP GET request.
 * Return an array of chars.
 * 
 * @param char * city
 * @return char * buffer.memory
 */
char * get_weather_data(char * city) {
    curl_global_init(CURL_GLOBAL_ALL);

    // Build the url
    char base_url[] = "http://api.openweathermap.org/data/2.5/weather?appid=82390064987812e43f9ec57cb01311b6&units=metric&q=";
    char length = strlen(base_url) + strlen(city);
    char * url = malloc(sizeof(char) * length + 1);
    memset(url, 0, length);

    strcat(url, base_url);
    strcat(url, city);
    
    // Allocate an empty buffer that will hold the http get data
    struct Buffer buffer;
    buffer.memory = NULL;
    buffer.size = 0;

    CURL *handle;
    int result;
    handle = curl_easy_init();

    // Set curl options
    curl_easy_setopt(handle, CURLOPT_URL, url);
    curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_to_buffer);
    curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void *) &buffer);
    result = curl_easy_perform(handle);

    if (result != CURLE_OK) {
        printf("A problem occurred during the HTTP CALL to:\n\n%s\n\nWith the following error: %s\n\n", url, curl_easy_strerror(result));
        exit(1);
    }

    free(handle);

    return buffer.memory;
};