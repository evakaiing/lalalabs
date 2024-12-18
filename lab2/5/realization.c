#include "functions.h"

#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <limits.h>
#include <stdlib.h>
#include <ctype.h>

int is_valid_symbol_in_base(char c, int base) {
    if (c == '+' || c == '-') {
        return 1;
    }
    if (base >= 2 && base <= 9) {
        return (c >= '0' && c < ('0' + base));
    }
    return isdigit(c) || (c >= 'A' && c < ('A' + base - 10));
}

void print_universal(void* stream, TYPE_OF_PRINT type, const char* format, ...) {
    va_list args;
    va_start(args, format);

    if (type == PRINT_TO_FILE_STREAM) {
        vfprintf((FILE*)stream, format, args);
    } else if (type == PRINT_TO_STRING) {
        vsprintf((char*)stream + strlen(stream), format, args);
    }

    va_end(args);
}

return_code print_to_stream_reversed(void* stream, TYPE_OF_PRINT type, const char* reversed_str, int ind_of_end) {
    if (!reversed_str) {
        return DEREFERENCING_NULL_POINTER_ATTEMPT;
    }
    if (ind_of_end < 0) {
        return INVALID_INPUT;
    }
    for (int i = ind_of_end; i >= 0; --i) {
        print_universal(stream, type, "%c", reversed_str[i]);
    }
    return OK;
}

return_code convert_to_decimal(const char* num_repr_in_base, int end_of_num_repr, format_for_char format_char,int base, int* decimal_result) {
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

return_code convert_decimal_to_base(int x, int base, format_for_char format_char, char* representation, int* ind) {
    if (representation == NULL || ind == NULL) {
        return DEREFERENCING_NULL_POINTER_ATTEMPT;
    }
    if (!(base >= 2 && base <= 36)) {
        return INVALID_INPUT;
    }

    *ind = 0;
    if (x == 0) {
        representation[0] = '0';
        ++(*ind);
        return OK;
    }

    int is_negative = (x < 0) ? 1 : 0;
    x = abs(x);

    while (x > 0) {
        int digit = x % base;
        if (digit < 10) {
            representation[*ind] = '0' + digit;
        } else {
            representation[*ind] = format_char('A' + (digit - 10));
        }
        ++(*ind);
        x /= base;
    }
    if (is_negative) {
        representation[*ind] = '-';
        ++(*ind);
    }
    return OK;
}

return_code generate_fibonacci(unsigned int n, unsigned int* size, unsigned int** fib_result) {
    if (!size || ! fib_result) {
        return DEREFERENCING_NULL_POINTER_ATTEMPT;
    }
    if (n < 1) {
        return INVALID_INPUT; 
    }
    unsigned int fib_cap = INITIAL_SIZE_OF_FIB; 
    unsigned int* fib = malloc(fib_cap * sizeof(unsigned int));
    if (!fib) {
        return MEMORY_ALLOCATION_ERROR;
    }
    fib[0] = 1;
    fib[1] = 2;
    *size = 2;
    unsigned int next_fib;
    do {
        if (UINT_MAX - fib[*size - 1] < fib[*size - 2]) {
            free(fib);
            return ERROR_OVERFLOW;
        }
        next_fib = fib[*size - 1] + fib[*size - 2];
        
        fib[(*size)++] = next_fib;
        
        if (*size >= fib_cap) {
            fib_cap *= 2;
            unsigned int* new_fib = realloc(fib ,fib_cap * sizeof(unsigned int));
            if (!new_fib) {
                free(fib);
                return MEMORY_ALLOCATION_ERROR;
            }
            fib = new_fib;
        }
    } while (next_fib < n);
    *fib_result = fib;
    return OK;
}

return_code print_memory_dump(void* stream, TYPE_OF_PRINT type_of_print, void *ptr, long unsigned int size_of_data_under_pointer) {
    if (!stream || !ptr) {
        return DEREFERENCING_NULL_POINTER_ATTEMPT;
    }
    unsigned char *byte_ptr = (unsigned char *)ptr;
    for (long unsigned int i = 0; i < size_of_data_under_pointer; ++i) {
        unsigned char byte_value = *(byte_ptr + i);
        
        for (int j = 7; j >= 0; --j) {
            print_universal(stream, type_of_print, "%d", (byte_value >> j) & 1);
        }
        
        print_universal(stream, type_of_print, " ");
    }
    return OK;
}

return_code print_number_in_base_to_decimal(void* stream, TYPE_OF_PRINT type_of_print, format_for_char format_char, char const* num_repr, int base) {
    int decimal_value = 0;
    int res = convert_to_decimal(num_repr, strlen(num_repr), format_char, base, &decimal_value);
    if (res != OK) {
        return res;
    }
    print_universal(stream, type_of_print, "%d", decimal_value);
    return OK;
}

return_code print_number_in_base(void* stream, TYPE_OF_PRINT type_of_print, format_for_char format_char, int number, int base) {
    if (!(base >= 2 && base <= 36)) {
        base = 10;
    }
    char base_repr[100];
    int ind_of_repr = 0;
    convert_decimal_to_base(number, base, format_char, base_repr, &ind_of_repr);
    print_to_stream_reversed(stream, type_of_print, base_repr, ind_of_repr - 1);
    return OK;
}

return_code print_zeckendorf(void* stream, TYPE_OF_PRINT type_of_print, unsigned int num) {
    unsigned int* fib;
    unsigned int size = 0;
    int result_of_fib_generation = generate_fibonacci(num, &size, &fib);
    if (result_of_fib_generation != OK) {
        return result_of_fib_generation;
    }

    char* result = (char*)malloc(size + 1);
    if (!result) {
        free(fib);
        return MEMORY_ALLOCATION_ERROR;
    }

    int amount_of_numbers = 0;
    
    for (int i = size - 1; i >= 0; --i) {
        if (fib[i] <= num) {
            result[amount_of_numbers++] = '1';
            num -= fib[i];
        } else if (amount_of_numbers > 0) {
            result[amount_of_numbers++] = '0';
        }
    }

    print_to_stream_reversed(stream, type_of_print, result, amount_of_numbers - 1);
    print_universal(stream, type_of_print, "%c", '1');

    free(fib);
    free(result);
    return OK;
}


return_code print_int_to_roman(void* stream, TYPE_OF_PRINT type_of_print, int num) {
    if (!stream) {
        return INVALID_INPUT;
    }
    int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    char* symbols[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};

    if (num < 0) {
        print_universal(stream, type_of_print, "%c", '-');
        num *= -1;
    }

    if (num > 4000) {
        for (int i = 0; i < num / 1000; ++i) {
            print_universal(stream, type_of_print, "%c", 'M');
        }
        num = num % 1000;
    }

    for (int i = 0; i < 13; i++) {
        while (num >= values[i]) {
            print_universal(stream, type_of_print, "%s", symbols[i]);
            num -= values[i];           
        }
    }
    return OK;
}

return_code handle_custom_flags(void* stream, TYPE_OF_PRINT type_of_print, const char* pos, va_list* args, int* to_move) {
    if (!stream || !pos || !args || !to_move) {
        return DEREFERENCING_NULL_POINTER_ATTEMPT;
    }
    int result = 0;
    *to_move = 0;
    switch (*pos) {
        case 'R':
            if (*(pos + 1) == 'o') {
                int num = va_arg(*args, int);
                result = print_int_to_roman(stream, type_of_print, num);
                if (result == OK) {
                    *to_move = 2;
                }
                return result;
            }
            break;

        case 'Z':
            if (*(pos + 1) == 'r') {
                unsigned int num = va_arg(*args, unsigned int);
                result = print_zeckendorf(stream, type_of_print, num);
                if (result == OK) {
                    *to_move = 2;
                }
                return result;  
            }
            break;

        case 'C':
            if (*(pos + 1) == 'v') {
                int number = va_arg(*args, int);
                int base = va_arg(*args, int);
                result = print_number_in_base(stream, type_of_print, tolower, number, base);
                if (result == OK) {
                    *to_move = 2;
                }
                return result;
            } else if (*(pos + 1) == 'V') {
                int number = va_arg(*args, int);
                int base = va_arg(*args, int);
                result = print_number_in_base(stream, type_of_print, toupper, number, base);
                if (result == OK) {
                    *to_move = 2;
                }
                return result;
            }
            break;

        case 't':
            if (*(pos + 1) == 'o') {
                char* num_repr = va_arg(*args, char*);
                int base = va_arg(*args, int);
                
                result = print_number_in_base_to_decimal(stream, type_of_print, tolower, num_repr, base);
                if (result == OK) {
                    *to_move = 2;
                }
                return result;

            } 
            break;

        case 'T':
            if (*(pos + 1) == 'O') {
                char* num_repr = va_arg(*args, char*);
                int base = va_arg(*args, int);
                
                result = print_number_in_base_to_decimal(stream, type_of_print, toupper, num_repr, base);
                if (result == OK) {
                    *to_move = 2;
                }
                
                return result;

            }
            break;
        
        case 'm':
            if (*(pos + 1) == 'i') {
                int num = va_arg(*args, int);
                result = print_memory_dump(stream, type_of_print, (void*)&num, sizeof(num));
                if (result == OK) {
                    *to_move = 2;
                }
                return result;
            } else if (*(pos + 1) == 'u') {
                unsigned int num = va_arg(*args, unsigned int);
                result = print_memory_dump(stream, type_of_print, (void*)&num, sizeof(num));
                if (result == OK) {
                    *to_move = 2;
                }
                return result;
            } else if (*(pos + 1) == 'd') {
                double num = va_arg(*args, double);
                result = print_memory_dump(stream, type_of_print, (void*)&num, sizeof(num));
                if (result == OK) {
                    *to_move = 2;
                }
                return result;
            } else if (*(pos + 1) == 'f') {
                float num = va_arg(*args, double); 
                result = print_memory_dump(stream, type_of_print, (void*)&num, sizeof(num));
                if (result == OK) {
                    *to_move = 2;
                }
                return result;
            }
            break;
        default:
            return OK;
    }
    return OK;
}

return_code general_printf(void* stream, TYPE_OF_PRINT type_of_print, const char* format, va_list* args) {
    if (!stream || !format || !args) {
        return DEREFERENCING_NULL_POINTER_ATTEMPT;
    }
    if (type_of_print == PRINT_TO_STRING) {
        ((char*)stream)[0] = '\0';
    }
    const char* pos = format;
    char buffer[BUFFER_SIZE];
    int buffer_pos = 0;

    while (*pos) {
        if (*pos == '%') {
            pos++;

            int to_move = 0;
            int result_of_flag = handle_custom_flags(stream, type_of_print, pos, args, &to_move);
            if (to_move > 0) {
                pos += to_move;
                continue;
            }

            buffer[buffer_pos++] = '%';
            while (*pos && !strchr("diufFeEgGxXoscpaA", *pos)) {
                buffer[buffer_pos++] = *pos++;
                if (buffer_pos >= BUFFER_SIZE - 1) {
                    break;
                }
            }
            if (buffer_pos < BUFFER_SIZE - 1) {
                buffer[buffer_pos++] = *pos;
            }

            buffer[buffer_pos] = '\0';
            if (type_of_print == PRINT_TO_FILE_STREAM) {
                vfprintf((FILE*)stream, buffer, *args);
            }
            else {
                vsprintf((char*)stream + strlen(stream), buffer, *args);
            }

            buffer_pos = 0;
        } else {
            print_universal(stream, type_of_print, "%c", *pos);
        }
        pos++;
    }
    return OK;
}

return_code overfprintf(FILE* stream, char const* format, ...) {
    va_list args;
    va_start(args, format);
    int res = general_printf((void*)stream, PRINT_TO_FILE_STREAM, format, &args);
    va_end(args);
    return res;
}

return_code oversprintf(char* stream, char const* format, ...) {
    va_list args;
    va_start(args, format);
    int res = general_printf((void*)stream, PRINT_TO_STRING, format, &args);
    va_end(args);
    return res;
}