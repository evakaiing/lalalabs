#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <limits.h>
#include <string.h>

typedef enum return_code {
    OK,
    INVALID_INPUT,
    MEMORY_ALLOCATION_ERROR,
    OVERFLOW_ERROR, 
    FILE_OPENNING_ERROR,
    TRANSFER_NEGATIVE_NUMBER_ATTEMPT,
    DEREFERENCE_NULL_POINTER_ATTEMPT
} return_code;

return_code convert_str_to_num_in_current_base(char* str, int* result, const int base) {
    char* end_ptr = NULL;
    long tmp = strtol(str, &end_ptr, 10);
    if (*end_ptr != '\0') {
        return INVALID_INPUT;
    }

    if (tmp > INT_MAX) {
        return OVERFLOW_ERROR;
    }

    *result = (int)tmp;

    return OK;
}

return_code char_to_digit(char ch, int base) {
    if (ch >= '0' && ch <= '9') {
        return ch - '0'; 
    } else if (ch >= 'A' && ch <= 'Z') {
        return ch - 'A' + 10; 
    } else if (ch >= 'a' && ch <= 'z') {
        return ch - 'a' + 10; 
    } else {
        return INVALID_INPUT; 
    }
}

char digit_to_char(int digit) {
    if (digit >= 0 && digit <= 9) {
        return digit + '0';  
    } else if (digit >= 10 && digit < 36) {
        return digit - 10 + 'a';  
    } else {
        return ' ';  
    }
}


return_code column_addition(char** result, char* first_num, char* second_num, const int base) {
    char* p_first_num, *p_second_num, *p_result;
    int carry = 0;
    int len1 = strlen(first_num);
    int len2 = strlen(second_num);
    int max_len = len1 > len2 ? len1 : len2;

    *result = (char*)malloc(max_len + 2); 
    if (!(*result)) {
        return MEMORY_ALLOCATION_ERROR;
    }


    p_first_num = first_num + len1 - 1;
    p_second_num = second_num + len2 - 1;
    p_result = *result + max_len;  
    *(p_result + 1) = '\0'; 

    while (p_first_num >= first_num || p_second_num >= second_num || carry != 0) {
        int digit1 = (p_first_num >= first_num) ? char_to_digit(*p_first_num--, base) : 0;
        int digit2 = (p_second_num >= second_num) ? char_to_digit(*p_second_num--, base) : 0;

        if (digit1 >= base || digit2 >= base) {
            free(*result);
            return INVALID_INPUT;
        }

        int sum = digit1 + digit2 + carry;
        carry = sum / base;  

        *p_result-- = digit_to_char(sum % base);
    }


    if (carry != 0) {
        *p_result = digit_to_char(carry);
    } else {
        p_result++;
    }

    while (*p_result == '0' && *(p_result + 1) != '\0') {
        p_result++;
    }

    memmove(*result, p_result, strlen(p_result) + 1);

    return OK;
}


return_code summation(char** result, int base, int count, ...) {
    va_list args;
    int i;
    char* final_str = NULL;
    char* result_cur = NULL;
    int capacity = 2;

    if (base < 2 || base > 36) {
        return INVALID_INPUT;
    }

    final_str = (char*)malloc(capacity);
    if (!final_str) {
        return MEMORY_ALLOCATION_ERROR;
    }
    strcpy(final_str, "0");

    va_start(args, count);

    for (i = 0; i < count; ++i) {
        char* str = va_arg(args, char*);

        if (str[0] == '-') {
            free(final_str);
            va_end(args);
            return TRANSFER_NEGATIVE_NUMBER_ATTEMPT;
        }

        return_code st = column_addition(&result_cur, str, final_str, base);
        if (st != OK) {
            free(final_str);
            va_end(args);
            return st;
        }

        int new_length = strlen(result_cur) + 1;
        if (new_length > capacity) {
            capacity = new_length * 2;
            char* temp = realloc(final_str, capacity);
            if (!temp) {
                free(result_cur);
                free(final_str);
                va_end(args);
                return MEMORY_ALLOCATION_ERROR;
            }
            final_str = temp;
        }

        strcpy(final_str, result_cur);
        free(result_cur);  
    }

    va_end(args);

    *result = (char*)malloc(strlen(final_str) + 1);
    if (!(*result)) {
        free(final_str);
        return MEMORY_ALLOCATION_ERROR;
    }
    strcpy(*result, final_str);

    free(final_str);  

    return OK;
}



int main() {
    char* result1;
    char* result2;

    return_code status = summation(&result1, 2, 2, "101", "111100");

    if (status == INVALID_INPUT) {
        printf("Invalid input of number\n");
        return INVALID_INPUT;
    } else if (status == OVERFLOW_ERROR) {
        printf("Overflow error\n");
        return OVERFLOW_ERROR;
    } else if (status == TRANSFER_NEGATIVE_NUMBER_ATTEMPT) {
        printf("Requires not a negative number\n");
    }
    printf("%s\n", result1);

    return_code status2 = summation(&result2, 36, 2, "zzzzzzzzzzzzzzzzzzzzzzzz", "zzzzzzzzzzzzzzzzzzzz");

    if (status2 == INVALID_INPUT) {
        printf("Invalid input of number\n");
        return INVALID_INPUT;
    } else if (status2 == OVERFLOW_ERROR) {
        printf("Overflow error\n");
        return OVERFLOW_ERROR;
    } else if (status2 == TRANSFER_NEGATIVE_NUMBER_ATTEMPT) {
        printf("Requires not a negative number\n");
    }
    printf("%s\n", result2);
}
