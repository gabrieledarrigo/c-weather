#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./lib/jsmn.h"

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

int main() {
    char * data;
    data = read_file();

    jsmn_parser parser;
    jsmn_init(&parser);
    unsigned int number_of_tokens = 209580;
    
    printf("Number of tokens: %d\n", number_of_tokens);

    size_t size = sizeof(jsmntok_t) * number_of_tokens;
    jsmntok_t * tokens = malloc(size);
    printf("%lu\n", size);

    int result = jsmn_parse(&parser, data, strlen(data), tokens, number_of_tokens);

    if (result < 0) {
        printf("Failed to parse JSON");
        perror("Err ");
        return 1;
    }

    if (tokens[0].type != JSMN_ARRAY) {
        printf("The first element should be an array");
        return 1;
    }

    for (int i = 1; i < 22; i++) {
        int length = tokens[i].end - tokens[i].start;
        char city[length + 1];
        strncpy(city, data + tokens[i].start, length);
        city[length + 1] = '\0';

        printf("%s\n", city);
    }


    return 0;
}
