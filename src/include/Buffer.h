#include <stdlib.h>

#ifndef BUFFER
#define BUFFER
/**
 * A simple Buffer structure.
 * @var char * memory An array of chars containing the buffer data
 * @var size_t size Array fo chars size
 */
struct Buffer {
    char * memory;
    size_t size;
};
#endif