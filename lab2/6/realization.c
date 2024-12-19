#include "functions.h"
#include <regex.h>
#include <stdio.h>
#include <stdarg.h>
#include <limits.h>
#include <ctype.h>
#include <string.h>

int is_valid_symbol_in_base(char c, int base) {
    if (c == '+' || c == '-') {
        return 1;
    }
    if (base >= 2 && base <= 9) {
        return (c >= '0' && c < ('0' + base));
    }
    return isdigit(c) || (c >= 'A' && c < ('A' + base - 10));
}

return_code zeckendorf_to_int(const char* zeckendorf_repr, unsigned int* result) {
    if (!zeckendorf_repr || !result) {
        return DEREFERENCING_NULL_POINTER_ATTEMPT;
    }
    *result = 0;
    unsigned int fib_prev = 1;
    unsigned int fib_curr = 2;

    int len = strlen(zeckendorf_repr);
    for (int i = 0; i < len - 1; i++) {
        if (zeckendorf_repr[i] == '1') {
            *result += fib_prev;
        }
        unsigned int fib_next = fib_prev + fib_curr;
        fib_prev = fib_curr;
        fib_curr = fib_next;
    }
    return OK;
}

return_code is_valid_roman(const char *number, int* is_valid) {
    if (!number || !is_valid) {
        return DEREFERENCING_NULL_POINTER_ATTEMPT;
    }
    regex_t regex;
    int ret;
    
    const char *pattern = "^M{0,3}(CM|CD|D?C{0,3})(XC|XL|L?X{0,3})(IX|IV|V?I{0,3})$";
    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret) {
        *is_valid = 0;
        return INVALID_INPUT;
    }    
    ret = regexec(&regex, number, 0, NULL, 0);
    regfree(&regex);

    *is_valid = (ret == 0);
    return OK;
}

return_code roman_to_int(const char *roman, int *result) {
    if (!roman || !result) {
        return DEREFERENCING_NULL_POINTER_ATTEMPT;
    }
    int total = 0;
    int prev = 0;
    int is_valid = 0;
    int res_of_validation = is_valid_roman(roman, &is_valid);
    if (!is_valid || res_of_validation != OK) {
        return INVALID_INPUT;
    }

    while (*roman) {
        int current = 0;
        switch (*roman) {
            case 'I': current = 1; break;
            case 'V': current = 5; break;
            case 'X': current = 10; break;
            case 'L': current = 50; break;
            case 'C': current = 100; break;
            case 'D': current = 500; break;
            case 'M': current = 1000; break;
            default: return INVALID_INPUT;
        }

        if (current > prev) {
            total += current - 2 * prev;
        } else {
            total += current;
        }

        prev = current;
        roman++;
    }

    *result = total;
    return OK;
}

return_code convert_to_decimal(const char* num_repr_in_base, int end_of_num_repr, format_for_char format_char,int base, int* decimal_result) {
    if (!num_repr_in_base || !decimal_result || !format_char) {
        return DEREFERENCING_NULL_POINTER_ATTEMPT;
    }
    *decimal_result = 0;
    int value;
    int sign = 1;

    if (end_of_num_repr == 0) {
        return OK;
    }

    for (int i = 0; i < end_of_num_repr; i++) {
        char c = (num_repr_in_base[i]);
        if (c != format_char(num_repr_in_base[i])) {
            return INVALID_INPUT;
        }

        if (!is_valid_symbol_in_base(toupper(c), base)) {
            return INVALID_INPUT;
        }

        if (i == 0 && c == '+') {
            continue;
        }
        if (i == 0 && c == '-') {
            sign = -1;
            continue;
        }

        if (isdigit(c)) {
            value = c - '0';
        } else if (isalpha(c)) {
            value = c - format_char('A') + 10;
        } else {
            return INVALID_INPUT;
        }

        if (*decimal_result > INT_MAX / base) {
            return ERROR_OVERFLOW;
        }
        *decimal_result *= base;
        if (value > 0 && (*decimal_result > INT_MAX - value)) {
            return ERROR_OVERFLOW;
        }
        *decimal_result += value;
    }
    *decimal_result *= sign;
    return OK;
}

return_code handle_custom_scan_flags(
    void* stream, TYPE_OF_SCAN type_of_scan, const char* pos,
    va_list* args, int* to_move) {
    int res = 0;
    *to_move = 0;
    switch (*pos) {
        case 'R':
            if (*(pos + 1) == 'o') {
                char buffer[100];
                int* result = va_arg(*args, int*);
                if (type_of_scan == SCAN_FROM_FILE_STREAM) {
                    fscanf((FILE*)stream, "%s", buffer);
                } else {
                    sscanf((const char*)stream, "%s", buffer);
                }
                
                res = roman_to_int(buffer, result);
                if (res != OK) {
                    return res;
                }
                *to_move = 2;
                return OK;
            }
            break;

        case 'Z':
            if (*(pos + 1) == 'r') {
                char buffer[100];
                unsigned int* result = va_arg(*args, unsigned int*);
                if (type_of_scan == SCAN_FROM_FILE_STREAM) {
                    fscanf((FILE*)stream, "%s", buffer);
                } else {
                    sscanf((const char*)stream, "%s", buffer);
                }
                res = zeckendorf_to_int(buffer, result);
                if (res != OK) {
                    return res;
                }
                *to_move = 2;
                return OK;
            }
            break;

        case 'C':
            if (*(pos + 1) == 'v') {
                char buffer[100];
                int* result = va_arg(*args, int*);
                int base = va_arg(*args, int);
                if (base < 2 || base > 36) {
                    base = 10;
                }

                if (type_of_scan == SCAN_FROM_FILE_STREAM) {
                    fscanf((FILE*)stream, "%s", buffer);
                } else {
                    sscanf((const char*)stream, "%s", buffer);
                }

                res = convert_to_decimal(buffer, strlen(buffer), tolower, base, result);
                if (res != OK) {
                    return res;
                }
                *to_move = 2;
                return OK;
            }
            else if(*(pos + 1) == 'V') {
                char buffer[100];
                int* result = va_arg(*args, int*);
                int base = va_arg(*args, int);
                if (base < 2 || base > 36) {
                    base = 10;
                }

                if (type_of_scan == SCAN_FROM_FILE_STREAM) {
                    fscanf((FILE*)stream, "%s", buffer);
                } else {
                    sscanf((const char*)stream, "%s", buffer);
                }

                res = convert_to_decimal(buffer, strlen(buffer), toupper, base, result);
                if (res != OK) {
                    return res;
                }
                *to_move = 2;
                return OK;
            }
            break;
    }
    return OK;
}


return_code general_scanf(void* stream, TYPE_OF_SCAN type_of_scan, const char* format, va_list* args) {
    if (!stream || !format || !args) {
        return DEREFERENCING_NULL_POINTER_ATTEMPT;
    }
    const char* pos = format;
    char buffer[BUFFER_SIZE];

    while (*pos) {
        if (*pos == '%') {
            pos++;

            int to_move = 0;
            int result_of_flag = handle_custom_scan_flags(stream, type_of_scan, pos, args, &to_move);
            if (result_of_flag != OK) {
                return result_of_flag;
            }
            if (to_move > 0) {
                pos += to_move;
                continue;
            }

            buffer[0] = '%'; 
            int buffer_pos = 1;

            while (*pos && !strchr("diufFeEgGxXoscpaA", *pos)) {
                buffer[buffer_pos++] = *pos++;
                if (buffer_pos >= BUFFER_SIZE - 1) {
                    break; 
                }
            }
            char format_to_move = *pos;
            buffer[buffer_pos] = *pos;
            buffer[buffer_pos + 1] = '\0'; 
        
            if (type_of_scan == SCAN_FROM_FILE_STREAM) {
                if (vfscanf((FILE*)stream, buffer, *args) <= 0) {
                    return INVALID_INPUT;
                }
            } else {
                if (vsscanf((const char*)stream, buffer, *args) <= 0) {
                    return INVALID_INPUT;
                }
            }
            // moving *args
            switch (format_to_move) {
                case 'd': case 'i': case 'u': case 'x': case 'X': case 'o':
                    va_arg(*args, int*);
                    break;
                case 'f': case 'F': case 'e': case 'E': case 'g': case 'G': case 'a': case 'A':
                    va_arg(*args, double*);
                    break;
                case 'c':
                    va_arg(*args, int*); 
                    break;
                case 's':
                    va_arg(*args, char*); 
                    break;
                case 'p':
                    va_arg(*args, void**);
                    break;
                case 'n':
                    va_arg(*args, int*);
                    break;
                default:
                    break;
            }

        } else {
            char c;
            if (type_of_scan == SCAN_FROM_FILE_STREAM) {
                if (fscanf((FILE*)stream, "%c", &c) < 0) {
                    return INVALID_INPUT;
                }
            } else {
                if (sscanf((const char*)stream, "%c", &c) < 0) {
                    return INVALID_INPUT;
                }
            }
            if (c != *pos) {
                return INVALID_INPUT;
            }
        }
        pos++;
    }
    return OK;
}

return_code overfscanf(FILE* stream, char const* format, ...) {
    va_list args;
    va_start(args, format);
    int res = general_scanf((void*)stream, SCAN_FROM_FILE_STREAM, format, &args);
    va_end(args);
    return res;
}

return_code oversscanf(const char* stream, char const* format, ...) {
    va_list args;
    va_start(args, format);
    int res = general_scanf((void*)stream, SCAN_FROM_STRING, format, &args);
    va_end(args);
    return res;
}