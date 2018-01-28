#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/Buffer.h"

/**
 * Read a file, given a filename parameter.
 * Return a pointer to the buffer that holds the data.
 * 
 * @param const char * filename
 * @return char * buffer
 **/
char * read_file(const char * filename) {
    FILE * file;
    
    struct Buffer buffer;
    buffer.memory = NULL;
    buffer.size = 0;

    file = fopen(filename, "r+");

    if (file) {
        char temp;

        // Iterate through all file's content and increment the actual file size.
        while ((temp = fgetc(file)) != EOF) {
            buffer.size++;
        }

        // Assign the right amount of data to the buffer and fill it with 0.
        int size = (buffer.size + 1) * sizeof(char);
        buffer.memory = (char *) malloc(size);
        memset(buffer.memory, 0, size);

        rewind(file);
        fread(buffer.memory, buffer.size, 1, file);
    } else {
        perror("Error: ");
    }

    fclose(file);
    return buffer.memory;
}