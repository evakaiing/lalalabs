#include <math.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_ACCURACY 100
#define EPSILON 1e-9

typedef enum return_code {
    OK,
    INVALID_INPUT,
    MEMORY_ALLOCATION_ERROR,
    OVERFLOW_ERROR
} return_code;

return_code is_finite_representation(double fraction, int base, int* result) {
    int cnt = 0;
    int cap = 128;
    double *remainders = malloc(cap * sizeof(double)); 
    if (!remainders)
        return MEMORY_ALLOCATION_ERROR;  
    
    while (fraction > EPSILON && cnt < MAX_ACCURACY) {
        fraction *= base;
        int digit = (int)fraction;
        fraction -= digit;
        if (fraction < EPSILON) {
            *result = 1;
            return OK;
        }
        for (int i = 0; i < cnt; i++) {
            if (fabs(fraction - remainders[i]) < EPSILON) {
                *result = 0;
                free(remainders);
                return OK; 
            }
        }

        if (cnt == cap) {
            cap *= 2;
            double *temp = realloc(remainders, cap * sizeof(double));
            if (!temp) {
                free(remainders);
                return MEMORY_ALLOCATION_ERROR;  
            }
            remainders = temp;
        }
        remainders[cnt++] = fraction;
    }

    free(remainders);   
    *result = fraction < EPSILON; 

    return OK;
}


int check_numbers(int count, int base, ...) {
    int i;
    va_list args;
    va_start(args, base);
    for (i = 0; i < count; ++i) {
        int result;
        
        double number = va_arg(args, double);
        int digit = (int)number;
        double fraction = number - digit;

        if (number < 0 && number > 1) {
            printf("Incorrect input\n");
            return INVALID_INPUT;
        }

        return_code status = is_finite_representation(fraction, base, &result);
        if (status == MEMORY_ALLOCATION_ERROR) {
            printf("Memory allocation error\n");
            return MEMORY_ALLOCATION_ERROR;
        }

        if (result == 1) {
            printf("Number %lf have finite representation\n", number);
        } else {
            printf("Number %lf haven't finite representation\n", number);
        }
    }
    va_end(args);
}

int main() {
    check_numbers(4, 10,0.3, 0.1, 0.2, 0.545678765); 
    check_numbers(2, 2, 0.1, 0.5);
    check_numbers(4, 3, 0.1, 0.33333, 0.5, 0.0);
}