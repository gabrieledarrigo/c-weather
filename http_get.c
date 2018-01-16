#include <stdio.h>
#include <curl/curl.h>

static struct Buffer {
    char *memory;
    size_t size;
};

size_t write_to_memory(void *data, size_t size, size_t nmemb, void *pointer) {
    size_t real_size = size * nmemb;

    struct Buffer * buffer = (struct Buffer *) pointer;

    buffer->memory = realloc(buffer->memory, buffer->size + real_size);
    buffer->size = real_size;

    if (buffer->memory == NULL) {
        printf("Not enough memory");
        return 1;
    }

    memcopy();
}

void http_get() {
    curl_global_init(CURL_GLOBAL_ALL);

    struct Buffer buffer;
    buffer.memory = malloc(1);
    buffer.size = 0;

    CURL *handle;
    CURLcode result;
    handle = curl_easy_init();

    curl_easy_setopt(handle, CURLOPT_URL, "http://api.openweathermap.org/data/2.5/weather?q=Milano&appid=82390064987812e43f9ec57cb01311b6");
    // curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_to_memory);
    // curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void *) &buffer);
    result = curl_easy_perform(handle);

    printf("ciao");
    return 0;
};
