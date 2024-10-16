#include "functions.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


return_code read_file(FILE* file_in, char** numbers, int* count, char* max_numbers) {
    char current_symbol, previous_sybmbol = 0;
    char buf[BUFSIZ];
    char* p_buf = buf;
    int i = 0;
    int max_number_in_current_symbol = 0;
    char max_symbol;
    while(!feof(file_in)) {
        current_symbol = fgetc(file_in);
        if (isalnum(current_symbol)) {
            *p_buf++ = current_symbol;
            int value_current_symbol = isalpha(current_symbol) ? current_symbol - 'A' + 10 : current_symbol - '0';

            if (value_current_symbol > max_number_in_current_symbol) {
                max_number_in_current_symbol = value_current_symbol;
                max_symbol = current_symbol;
            }
        } else if (isalnum(previous_sybmbol)) {
            *p_buf  = 0;
            numbers[i] = (char *)malloc(strlen(buf) + 1);
            if (numbers[i] == NULL) {
                return ERROR_MEMORY;
            }
            strcpy(numbers[i], buf);
            max_numbers[i++] = max_symbol;
            p_buf = buf;
            max_number_in_current_symbol = 0;
        }
        previous_sybmbol = current_symbol;
    }
    *count = i;
    return OK;
}

return_code gorner_scheme(char* str_to_convert, int base_from, int* res) {
    *res = 0;
    int sign = 1;
    if (*str_to_convert == '-') {
        sign = -1;
        ++str_to_convert;
    }
    char* p_str_to_convert = str_to_convert - 1;
    while (*++p_str_to_convert) {
        *res = *res * base_from  + ((isalpha(*p_str_to_convert) 
        ? *p_str_to_convert - 'A' + 10 : *p_str_to_convert - '0'));
    }
    *res *= sign;
    return OK;
}