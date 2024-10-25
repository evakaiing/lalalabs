


#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPS 1e-6

typedef enum return_code
{
    OK,
    INVALID_INPUT,
    MEMORY_ALLOCATION_ERROR,
    DEREFERENCE_NULL_POINTER_ATTEMPT
} return_code;

double evaluate_polynomial(double x, double *coefs, int max_power) {
    double result = 0;
    double current_power = 1;
    for (int i = 0; i <= max_power; i++) {
        result += current_power * coefs[i];
        current_power *= x;
    }
    return result;
}

double evaluate_decomposition(double x, double* coefficients, int degree, double a) {
    double result = 0.0;
    double current_power = 1;
    for (int i = 0; i <= degree; i++) {
        result += coefficients[i] * current_power;
        current_power *= (x - a); 
    }
    return result;
}


int compare_polynamials(double *f, double *g, double x, int degree, double a) {
    double f_x = evaluate_polynomial(x, f, degree);
    double g_x = evaluate_decomposition(x, g, degree, a);
    printf("f_x = %lf, g_x = %lf\n", f_x, g_x); 
    if (fabs(f_x - g_x) < EPS) {  
        return 1;
    } else {
        return 0;
    }
}

return_code calculate_polynomial(double a, double **g_coefficents, int degree, ...) {
    int n = degree;
    double *start_coefficients;
    va_list args;

    if (degree < 0) return INVALID_INPUT;

    if (!g_coefficents) {
        return DEREFERENCE_NULL_POINTER_ATTEMPT;
    }

    (*g_coefficents) = (double *)malloc((degree + 1) * sizeof(double));
    if ((*g_coefficents) == NULL) {
        return MEMORY_ALLOCATION_ERROR;
    }

    start_coefficients = (double *)malloc(sizeof(double) * (degree + 1));
    if (start_coefficients == NULL) {
        free(*g_coefficents);
        return MEMORY_ALLOCATION_ERROR;
    }

    va_start(args, degree);
    for (int i = 0; i <= degree; i++) {
        double coefficient = va_arg(args, double);
        start_coefficients[i] = coefficient;
        // printf("f%d = %lf\n", i, start_coefficients[i]); 
    }
    va_end(args);


    double factorial = 1.0;
    int curr_power = degree;
    for (int i = 0; i <= n; i++) {
        (*g_coefficents)[i] = evaluate_polynomial(a, start_coefficients, curr_power);
        if (i > 1) {
            factorial *= i;
            (*g_coefficents)[i] /= factorial;  
        }

        // printf("g%d = %lf\n", i, (*g_coefficents)[i]);  

        curr_power--;

        for(int j = 0; j <= curr_power; ++j) {
            double b = start_coefficients[j + 1];
            start_coefficients[j] = b * (j + 1); 
        }
    }

    free(start_coefficients);

    return OK;
}

int main() {
    double a = 3.0;
    int degree = 4;
    double* result;
    double* result2;

    return_code return_code_for_calculation =  calculate_polynomial(a, &result, degree, -2.0, 1.0, -3.0, 0.0, 1.0);

    if (return_code_for_calculation == MEMORY_ALLOCATION_ERROR) {
        printf("Memory allocation error\n");
        free(result);
        return MEMORY_ALLOCATION_ERROR;

    } else if (return_code_for_calculation == DEREFERENCE_NULL_POINTER_ATTEMPT) {
        printf("Attempt of dereferencing null pointer\n");
        free(result);
        return DEREFERENCE_NULL_POINTER_ATTEMPT;
    }

    for (int i = 0; i <= degree; ++i) {
        printf("%lf ", result[i]);
    }

    printf("\n");

    double start_coefficients[] = {-2.0, 1.0, -3.0, 0.0, 1.0};  
    compare_polynamials(start_coefficients, result, 5.0, degree, a); 

    free(result);



    calculate_polynomial(1.0, &result2, 3, 0.0, 0.0, 0.0);

    for (int i = 0; i <= 3; ++i) {
        printf("%lf ", result2[i]);
    }

    free(result2);
    return OK;
}

