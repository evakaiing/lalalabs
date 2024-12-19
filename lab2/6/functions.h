#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>

#define BUFFER_SIZE 1024

typedef enum {
    OK,
    INVALID_INPUT,
    MEMORY_ALLOCATION_ERROR,
    DEREFERENCING_NULL_POINTER_ATTEMPT,
    FILE_OPENNING_ERROR,
    ERROR_OVERFLOW
} return_code;

typedef enum TYPE_OF_PRINT {
    SCAN_FROM_FILE_STREAM = 1,
    SCAN_FROM_STRING = 2,
} TYPE_OF_SCAN;

typedef int (*format_for_char) (int);

return_code overfscanf(FILE* stream, char const* format, ...);
return_code oversscanf(const char* stream, char const* format, ...);
 
#endif