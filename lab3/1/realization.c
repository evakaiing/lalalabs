#include "functions.h"
#include "stdlib.h"

int bit_addition(int first_num, int second_num) {
    int carry = (first_num & second_num) << 1;
    int res = first_num ^ second_num;
    if (carry == 0) {
        return res;
    }

    return bit_addition(res, carry);
}

int convert_to_additional_code(int num) {
    return bit_addition(~num, 1);
}

return_code convert_to_base(int num, int r, int* size, char** ans) {
    int cap = 2;
    *size = 0;
    char* alphabet = "0123456789ABCDEFGHIJKLMNOPQRSTUV";
    int is_negative = 0;

    if (!ans) {
        return DEREFERENCING_NULL_POINTER_ATTEMPT;
    }

    *ans = (char*)malloc(cap);

    if (!(*ans)) {
        return MEMORY_ALLOCATION_ERROR;
    }

    if (r > 5 || r < 1) {
        return INVALID_INPUT;
    }

    if (num < 0){
        num = convert_to_additional_code(num);
        is_negative = 1;
    }

    int r_low_order_bits = bit_addition((1 << r), -1);

    while (num) {
        int remainder = num & r_low_order_bits;
        if (*size == cap) {
            char* tmp;
            cap <<= 1;
            tmp = (char*)realloc(*ans, cap);
            if (!tmp) {
                free(*ans);
                return MEMORY_ALLOCATION_ERROR;
            }

            *ans = tmp;
        }

        (*ans)[*size] = alphabet[remainder];
        *size = bit_addition(*size, 1);

        num >>= r;
    }

    if (is_negative) {
        if (*size == cap) {
            char* tmp;
            cap <<= 1;
            tmp = (char*)realloc(*ans, cap);
            if (!tmp) {
                free(*ans);
                return MEMORY_ALLOCATION_ERROR;
            }

            *ans = tmp;
        }

        (*ans)[*size] = '-';
        *size = bit_addition(*size, 1);
    }
    (*ans)[*size] = '\0';

    return OK;
}