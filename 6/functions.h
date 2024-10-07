#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include <stdio.h>

typedef enum return_code 
{
    OK,
    INVALID_INPUT,
    FILE_OPENNING_ERROR,
    ERROR_OVERFLOW,
    ERROR_MEMORY,
    FILE_PATH_LENGTH_ERROR
} return_code;


return_code convert_str_to_double(const char* str, double* res);
double integrative_expression_a(double x);
double integrative_expression_b(double x);
double integrative_expression_c(double x);
double integrative_expression_d(double x);
double right_rectangles_method(double eps, int n, double left_border, double right_border, double (*calculate_expression)(double));
double calculate_integral(double eps, double(*calculate_expression)(double));

#endif