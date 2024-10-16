#include "functions.h"
#include <stdarg.h>
#include <math.h>
#include <float.h>
#include <stdlib.h>

int there_is_overflow(double num) {
    if (num >= DBL_MAX) {
        return 1;
    }
    return 0;
}


return_code calculate_geometric_average(double* result, int count_of_values, ...) {
    va_list list_of_values;
    int i;
    va_start(list_of_values, count_of_values);
    *result = 1;
    for (i = 0; i < count_of_values; ++i) {
        double value;
        value = va_arg(list_of_values, double);
        if (value < 0) {
            return INVALID_INPUT;
        }
        *result *= value;
        if (there_is_overflow(*result)) return OVERFLOW_ERROR;
    }

    *result = pow(*result, 1.0 / count_of_values);

    va_end(list_of_values);

    return OK;
}

return_code fast_exponentiation(double num_to_exponentation, int degree, double* result) {
    *result = 1;
    return_code status_exponentation;
    if (degree < 0) {
        status_exponentation = fast_exponentiation(1.0 / num_to_exponentation, -degree, result);
    } else if (degree == 0) {
        *result = 1;
        return OK;
    } else {
        if (degree % 2 == 0) {
            status_exponentation = fast_exponentiation(num_to_exponentation, degree / 2, result);
            if (there_is_overflow(*result)) {
                return OVERFLOW_ERROR;
            }

            *result *= *result;
            return OK;
        } else {
            status_exponentation = fast_exponentiation(num_to_exponentation, degree - 1, result);

            if (there_is_overflow(*result)) {
                return OVERFLOW_ERROR;
            }

            *result *= num_to_exponentation;
            return OK;
        }
    }

    return status_exponentation;
}