#include <math.h>
#include <limits.h>
#include <float.h>
#include <stdlib.h>

enum return_code {
    OK,
    ERROR_INPUT,
    ERROR_OVERFLOW,
    ERROR_UNDERFLOW
};

int convert_str_to_double(const char* str, double* res, const double eps);
int convert_str_to_double_for_eps(const char* str, double* res);
int there_is_overflow(double x);
double factorial(int n);

int for_a(double eps, double x, double* res);
int for_b(double eps, double x, double* res);
int for_c(double eps, double x, double* res);
int for_d(double eps, double x, double* res);
