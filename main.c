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

    if (tokens[0].type != JSMN_ARRAY) {
        printf("The first element should be an array");
        exit(1);
    }

    return tokens;
}

int main(int argc, char *argv[]) {
    printf("Number of argc: %i\n", argc);

    if (argc == 1) {
        printf("Please specify the name of a city\n");
        exit(0);
    } else {
        printf("Search for weather forecast in: %s\n", argv[1]);
    }

    char * data;
    jsmntok_t * tokens;
    
    // Read data from file
    data = read_file();
    // Parse the json
    tokens = parse_json(data);

    printf("Tokens size: %i\n", tokens[0].size);

    //Iterate the json array to find the desired city.
    for (int i = 1; i <= tokens[0].size; i++) {
        int length = tokens[i].end - tokens[i].start;
        char city[length + 1];
        strncpy(city, data + tokens[i].start, length);
        city[length] = '\0';

        printf("To search: %s - Actual: %s\n", argv[1], city);

        if (strcmp(argv[1], city) == 0) {
            printf("Found! %s\n", city);
            break;
        }
    }

    printf("Searched city: %s not found\n", argv[1]);
    free(data);
    free(tokens);
    return 0;
}
