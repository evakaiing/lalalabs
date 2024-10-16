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
    TRANSFER_NEGATIVE_NUMBER_ATTEMPT
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

// char* str_reverse(char* str) {
//     char* p_str = str;
//     char* p_end_str = str + strlen(str);

//     while(p_str != '\0') {
//         *p_str++ = *p_end_str--;
//     }
    
//     return str;
// }


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

        int digit1 = (p_first_num >= first_num) ? *p_first_num-- - '0' : 0;
        int digit2 = (p_second_num >= second_num) ? *p_second_num-- - '0' : 0;

        if (digit1 >= base || digit2 >= base) {
            return INVALID_INPUT;
        }

        int sum = digit1 + digit2 + carry;

        carry = sum / base;

        *p_result-- = (sum % base) + '0';  
    }
    if (carry != 0) {
        *p_result = carry + '0';
    } else {
        p_result++;
    }

    while (*p_result == '0' && *(p_result + 1) != '\0') {
        p_result++;
    }

    memmove(*result, p_result, strlen(p_result) + 1);
    
    return OK;
}


return_code summation(int* result, int base, int count, ...) {
    va_list args;
    int i;
    char final_str[BUFSIZ] = "0";
    char* result_cur;

    if (base < 2 || base > 36) {
        return INVALID_INPUT;
    }

    va_start(args, count);

    for (i = 0; i < count; ++i) {
        char* str;
        str = va_arg(args, char*);
        
        if (str[0] == '-') {
            return TRANSFER_NEGATIVE_NUMBER_ATTEMPT;
        }


        return_code st = column_addition(&result_cur, str, final_str, base);
        if (st != OK) {
            va_end(args);
            return st;
        }

        strcpy(final_str, result_cur);
        free(result_cur);
    }

    va_end(args);

    return_code status_of_convertion = convert_str_to_num_in_current_base(final_str, result, base);
    if (status_of_convertion != OK) {
        return status_of_convertion;
    }

    return OK;
}


int main() {
    int result1 = 0;
    int result2 = 0;

    return_code status = summation(&result1, 2, 2, "101", "111100", "10011");

    if (status == INVALID_INPUT) {
        printf("Invalid input of number\n");
        return INVALID_INPUT;
    } else if (status == OVERFLOW_ERROR) {
        printf("Overflow error\n");
        return OVERFLOW_ERROR;
    } else if (status == TRANSFER_NEGATIVE_NUMBER_ATTEMPT) {
        printf("Requires not a negative number\n");
    }
    printf("%d\n", result1);

    return_code status2 = summation(&result2, 10, 2, "00123", "");

    if (status2 == INVALID_INPUT) {
        printf("Invalid input of number\n");
        return INVALID_INPUT;
    } else if (status2 == OVERFLOW_ERROR) {
        printf("Overflow error\n");
        return OVERFLOW_ERROR;
    } else if (status2 == TRANSFER_NEGATIVE_NUMBER_ATTEMPT) {
        printf("Requires not a negative number\n");
    }
    printf("%d\n", result2);
}
