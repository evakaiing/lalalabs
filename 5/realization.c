#include "functions.h"

int convert_str_to_double(const char* str, double* res, const double eps) {
    // double strtod(const char *str, char **endptr);

    char* end_ptr = NULL;

    double tmp = strtod(str, &end_ptr);

    if (*end_ptr != '\0') {
        return ERROR_INPUT;
    }

    if (fabs(tmp) > DBL_MAX - eps) {
        return ERROR_OVERFLOW;
    }

    *res = (double)tmp;

    return OK;
}

int convert_str_to_double_for_eps(const char* str, double* res) {
    char* end_ptr = NULL;

    double tmp = strtod(str, &end_ptr);


    if (*end_ptr != '\0') {
        return ERROR_INPUT;
    }

    if (fabs(tmp) > DBL_MAX) {
        return ERROR_OVERFLOW;
    }

    *res = (double)tmp;

    return OK;
}

int there_is_overflow(double x) {
    if (isinf(x) || fabs(x) > DBL_MAX) {
        return 1;
    }
    return 0;
}

double factorial(int n) {
    int i;
    if (n == 0 || n == 1) {
        return 1;
    }

    double result = 1;
    for (i = 2; i <= n; ++i) {
        result *= i;
    }

    return result;
}

int for_a(double eps, double x, double* res) {
    double current = 1;
    double previous = 0;
    int n = 1;

    while(fabs(current - previous) > eps) {
        previous = current;
        current += pow(x, n) / factorial(n);

        if (there_is_overflow(current)) {
            return ERROR_OVERFLOW;
        } 

        ++n;
    }
    *res = current;
    return OK;
}

int for_b(double eps, double x, double* res) {
    double current = 0;
    int n = 0;
    double to_add = 1;  

    while(fabs(to_add) > eps) {
        if (n % 2 == 0) {
            current += to_add;
        } else {
            current -= to_add;
        }
        to_add *= (x / (2 * n + 1)) * (x / (2 * n + 2));
        ++n;
    }

    if (there_is_overflow(current)) {
        return ERROR_OVERFLOW;
    }
    *res = current;
    return OK;
}


int for_c(double eps, double x, double* res) {
    double current = 0;
    double to_add = 1;
    int n = 0;
    if(fabs(x) >= 1) {
        return ERROR_INPUT;
    }

    while(fabs(to_add) > eps) {
        if (there_is_overflow(current) || there_is_overflow(to_add)) {
            return ERROR_OVERFLOW;
        }
        current += to_add;

        to_add *= (27 * x * x); 
        to_add *= (n + 1) * (n + 1) * (n + 1); 
        to_add /= (3 * n + 1) * (3 * n + 2) * (3 * n + 3); 
        
        ++n;
    } 
    *res = current;
    return OK;
}

int for_d(double eps, double x, double* res) {
    double current = 0;
    double to_add = -x * x / 2;
    int n = 1;
    if (fabs(x) >= 1) {
        return ERROR_INPUT;
    }
    while(fabs(to_add) > eps) {
        if (there_is_overflow(current) || there_is_overflow(to_add)) {
            return ERROR_OVERFLOW;
        }
        current += to_add;
        to_add *= -1 * x * x * (2 * n - 1); // fixed
        to_add /= (2 * n);

        ++n;
    }
    *res = current;
    return OK;
}