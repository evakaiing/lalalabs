#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include <ctype.h>
#include <stdio.h>

typedef enum return_code 
{
    OK,
    INVALID_INPUT,
    FILE_OPENNING_ERROR,
    ERROR_OVERFLOW,
    ERROR_MEMORY,
    FILE_PATH_LENGTH_ERROR
} return_code;


return_code is_valid_flag(const char* flag);
return_code get_lexems_from_file(FILE* file, char** lexems, int* cnt_of_lexems);
return_code for_r(char** lexems_from_file1, char** lexems_from_file2, FILE* output_file);
return_code for_a(char** lexems, FILE* output_file);

#endif