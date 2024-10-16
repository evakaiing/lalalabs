#ifndef FUNCTIONS_H
#define FUNCTIONS_H


typedef enum return_code {
    OK,
    ERROR_INPUT_BASE,
    ERROR_INPUT,
    ERROR_OVERFLOW,
    ERROR_MEMORY
} return_code;

return_code is_valid_number(const char* str, int base);
return_code is_valid_base(const char* str);
return_code convert_str_to_num(const char* str, int* res);

return_code gorner_scheme(char* str_to_convert, int base_from, int* res);
char* reverse_gorner_scheme(int num_to_convert, int base_to, char* buf);

#endif