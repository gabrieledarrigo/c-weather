#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "include/Buffer.h"

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