#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/jsmn.h"

/**
 * Parse a json string with jsmn lib.
 * @see https://github.com/zserge/jsmn
 * for parsing implementation detail.
 * Return the parsed tokens.
 * 
 * @param int number_of_tokens
 * @param char * data
 * @return jsmntok_t * tokens
 */
jsmntok_t * parse_json(char * data, int number_of_tokens) { 
    jsmn_parser parser;
    jsmn_init(&parser);

    // Calculate the memory required for the tokens
    size_t size = sizeof(jsmntok_t) * number_of_tokens;
    jsmntok_t * tokens = malloc(size);

    int result = jsmn_parse(&parser, data, strlen(data), tokens, number_of_tokens);

    if (result < 0) {
        printf("Failed to parse JSON");
        perror("Err");
        exit(1);
    }

    if (tokens[0].type != JSMN_ARRAY && tokens[0].type != JSMN_OBJECT) {
        printf("The first element should be an array or an object");
        exit(1);
    }

    return tokens;
}