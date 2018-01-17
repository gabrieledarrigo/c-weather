#include <stdlib.h>

#ifndef BUFFER
#define BUFFER

/**
 * A simple Buffer structure
 */
struct Buffer {
    char * memory;
    size_t size;
};

#endif
