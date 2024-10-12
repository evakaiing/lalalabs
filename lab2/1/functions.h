#include <stdio.h>

typedef enum return_code {
    OK,
    INVALID_INPUT,
    MEMORY_ALLOCATION_ERROR,
    OVERFLOW_ERROR
} return_code;

return_code flag_handling(const char* flag);

size_t strlen(char* str);

return_code convert_str_to_int(const char* str, int* res);

return_code for_u(char* input_str, char** output_str);

void str_cat(char* str_to_cat, char* what_to_concatenate);

return_code str_reverse(char* input_str, char** output_str);

return_code for_n(char* str, char** output_str);

char* str_cpy(char* dist, char* src);

return_code for_c(char** argv, int count_of_str, unsigned int number_seed, char** result);