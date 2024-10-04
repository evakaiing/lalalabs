#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>

typedef enum return_code {
    OK,
    ERROR_INPUT_BASE,
    ERROR_INPUT,
    ERROR_OVERFLOW,
    ERROR_MEMORY,
    ERROR_FILE
} return_code;

return_code read_file(FILE* file_in, char** numbers, int* count_of_lines, char* max_numbers);
return_code gorner_scheme(char* str_to_convert, int base_from, int* res);

#endif