#include <stdio.h>

typedef enum return_code {
    OK,
    INVALID_INPUT,
    MEMORY_ALLOCATION_ERROR,
    OVERFLOW_ERROR,
    DEREFERENCING_NULL_POINTER_ATTEMPT
} return_code;

int bit_addition(int first_num, int second_num);
return_code convert_to_base(int num, int r, int* size, char** ans);
int convert_to_additional_code(int num);
