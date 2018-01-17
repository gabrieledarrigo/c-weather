#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/jsmn.h"

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