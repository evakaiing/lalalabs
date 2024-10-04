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


return_code flag_handling(const char* flag, int* is_nflag);
return_code for_d(FILE* input_file, FILE* output_file);
return_code for_i(FILE* input_file, FILE* output_file);
return_code for_s(FILE* input_file, FILE* output_file);
return_code for_a(FILE* input_file, FILE* output_file);

int is_absolute_path(char* path);
return_code convert_path_to_absolute(char* path_to_current_directory, char* input_path, char* result);
return_code get_path_to_current_directory(char* path_for_current_directory);
return_code get_output_filename(char* input_path, char* output_path);

