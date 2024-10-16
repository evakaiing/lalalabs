#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <limits.h>

typedef enum return_code {
    OK,
    INVALID_INPUT,
    MEMORY_ALLOCATION_ERROR,
    OVERFLOW_ERROR, 
    FILE_OPENNING_ERROR
} return_code;

return_code convert_str_to_num_in_current_base(char* str, const int base, int* result) {
    char* end_ptr = NULL;
    long tmp = strtol(str, &end_ptr, base);
    if (*end_ptr != '\0') {
        return INVALID_INPUT;
    }

    if (tmp > INT_MAX) {
        return OVERFLOW_ERROR;
    }

    *result = (int)tmp;

    return OK;
}


return_code summation(int* result, int base, int count, ...) {
    va_list args;
    int i;
    if (base < 2 && base > 36) {
        return INVALID_INPUT;
    }

    va_start(args, count);

    for (i = 0; i < count; ++i) {
        char* str;
        int num;
        str = va_arg(args, char*);
        if (str[0] == '-') {
            return INVALID_INPUT;
        }
    
        return_code status_of_conversion = convert_str_to_num_in_current_base(str, base, &num);
        if (num >= base) {
            return INVALID_INPUT;
        }

        if (status_of_conversion == OVERFLOW_ERROR) {
            return OVERFLOW_ERROR;
        } else if (status_of_conversion == INVALID_INPUT) {
            return INVALID_INPUT;
        }

        *result += num;
    }

    va_end(args);

    return OK;
}


int main() {
    int result = 0;

    return_code status_of_summation = summation(&result, 6, 5, "1", "2", "3", "4", "5");

    if (status_of_summation == INVALID_INPUT) {
        printf("Invalid input\n");
        return INVALID_INPUT;
    } else if (status_of_summation == OVERFLOW_ERROR) {
        printf("Overflow error\n");
        return OVERFLOW_ERROR;
    }

    printf("%d\n", result);

}