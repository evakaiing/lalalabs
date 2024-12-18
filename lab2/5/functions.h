#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <stdio.h>

typedef enum {
    OK,
    INVALID_INPUT,
    MEMORY_ALLOCATION_ERROR,
    DEREFERENCING_NULL_POINTER_ATTEMPT,
    FILE_OPENNING_ERROR,
    ERROR_OVERFLOW
} return_code;

typedef enum TYPE_OF_PRINT {
    PRINT_TO_FILE_STREAM = 1,
    PRINT_TO_STRING = 2,
} TYPE_OF_PRINT;

#define INITIAL_SIZE_OF_FIB 10
#define BUFFER_SIZE 1024

typedef void (*printer) (void* stream, TYPE_OF_PRINT type, const char* format, ...);
typedef int (*format_for_char) (int);

void print_universal(void* stream, TYPE_OF_PRINT type, const char* format, ...);

return_code print_int_to_roman(void* stream, TYPE_OF_PRINT type_of_print, int num);
return_code print_zeckendorf(void* stream, TYPE_OF_PRINT type_of_print, unsigned int num);
return_code print_number_in_base(void* stream, TYPE_OF_PRINT type_of_print, format_for_char format_char, int number, int base);
return_code print_memory_dump(void* stream, TYPE_OF_PRINT type_of_print, void *ptr, long unsigned int size_of_data_under_pointer);

return_code handle_custom_flags(void* stream, TYPE_OF_PRINT type_of_print, const char* pos, va_list* args, int* to_move);

return_code overfprintf(FILE* stream, const char* format, ...);
return_code oversprintf(char* stream, char const* format, ...);


#endif