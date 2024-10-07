#include "functions.h"
#include <limits.h>
#include <math.h>
#include <stdlib.h>

return_code convert_str_to_double(const char* str, double* res) {
    char* end_ptr = NULL;

    double tmp = strtod(str, &end_ptr);


    if (*end_ptr != '\0') {
        return INVALID_INPUT;
    }

    *res = (double)tmp;

    return OK;
}

double integrative_expression_a(double x) {
    if (x == 0) {
        return 1; 
    }
    return log(1 + x) / x;
}

double integrative_expression_b(double x) {
    return exp(-(x * x) / 2);
}

double integrative_expression_c(double x) {
    return log((1 / (1 - x)));
}

double integrative_expression_d(double x) {
    if (x == 0) {
        return 1; 
    }
    return pow(x, x);
}

double right_rectangles_method(double eps, int n, double left_border, double right_border, double (*calculate_expression)(double)) {
    double width = (right_border - left_border) / n;
    double height = 0;
    for (double i = eps; i < n - eps; ++i) {
        double x = left_border + width * i;
        height += calculate_expression(x);
    }

    return width * height;
}

double calculate_integral(double eps, double(*calculate_expression)(double)) {
    double left_border = 0;
    double right_border = 1;
    double previous_result = 0;
    double result = 0;
    int n = 1;

    do {
        previous_result = result;
        result = right_rectangles_method(eps, n, left_border, right_border, calculate_expression);
        n *= 2;
    } while (fabs(result - previous_result) > eps);

    return result;
}