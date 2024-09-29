#include <math.h>
#include <float.h>
#include <stdlib.h>
#define M_PI 3.14159265358979323846


typedef enum return_code {
    OK,
    ERROR_INPUT,
    ERROR_OVERFLOW,
    ERROR_EPS
} return_code;



void get_results(double eps, double results[15]);
void print_results(double results[15]);

return_code calculate_e_using_limit(double eps, double* result);
return_code calculate_pi_using_limit(double eps, double* result);
return_code calculate_ln_using_limit(double eps, double* result);
return_code calculate_sqrt_using_limit(double eps, double* result);
return_code calculate_gamma_using_limit(double eps, double* result);

return_code calculate_e_using_row(double eps, double* result);
return_code calculate_pi_using_row(double eps, double* result);
return_code calculate_ln_using_row(double eps, double* result);
return_code calculate_sqrt_using_row(double eps, double* result);
return_code calculate_gamma_using_row(double eps, double* result);

return_code calculate_e_using_equation(double eps, double* result);
return_code calculate_pi_using_equation(double eps, double* result);
return_code calculate_ln_using_equation(double eps, double* result);
return_code calculate_sqrt_using_equation(double eps, double* result);
return_code calculate_gamma_using_equation(double eps, double* result);

