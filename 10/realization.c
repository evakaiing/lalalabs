#include "functions.h"
#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

return_code is_valid_number(const char* str, int base) {
    if (str[0] == '-') {
        ++str;
    }
    while (*str) {
        if (isdigit(*str)) {
            if (abs(*str) - '0' >= base) {
                return ERROR_INPUT_BASE;
            }
        } else if (isalpha(*str)) {
            if (abs(*str) - 'A' + 10 >= base) {
                return ERROR_INPUT_BASE;
            }
        } else {
            return ERROR_INPUT;
        }
        ++str;
    }
    return OK;
}

return_code convert_str_to_num(const char* str, int* res) {
    char* end_ptr = NULL;
    *res = strtol(str, &end_ptr, 10);

    if (*end_ptr != '\0') {
        return ERROR_INPUT;
    }

    if (*res > 36) {
        return ERROR_INPUT_BASE;
    }

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

char* reverse_gorner_scheme(int num_to_convert, int base_to, char* buf) {
    int remainder = 0;
    int sign = 1;
    char* p_buf = buf + BUFSIZ - 1;
    if (num_to_convert == 0) {
        *p_buf-- = '0';
        return p_buf + 1;
    }
    if (num_to_convert < 0) {
        sign = -1;
        num_to_convert *= sign;
    }
    *p_buf-- = '\0';

    while (num_to_convert > 0) {
        *p_buf-- = ((remainder = num_to_convert % base_to) > 9 ? remainder - 10 + 'A' : remainder + '0');
        num_to_convert /= base_to;
    }

    if (sign == -1) {
        *p_buf-- = '-';
    }

    return p_buf + 1;
}
