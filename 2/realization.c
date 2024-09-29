#include "functions.h"



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


double fast_exponentiation(double num_to_exponentation, int degree) {
    double result = 1;
    double base = num_to_exponentation;

    while(degree > 0) {
        if (degree % 2 == 1) {
            result *= base;
        }
        base *= base;

        degree /= 2;
    }

    return result;
}

int is_prime(int n) {
    if (n < 2) return 0;
    for (int i = 2; i <= sqrt(n); ++i) {
        if (n % i == 0) return 0;
    }
    return 1;
}

long long factorial(int n) {
    if (n == 0 || n == 1) {
        return 1;
    }
    unsigned long long result = 1;
    for (int i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}

double calculate_harmonic_number(double number) {
    double sum = 1;
    for (int i = 2; i <= number; i++)
    {
        sum += 1.0 / i;
    }

    return sum;
}

return_code calculate_e_using_limit(double eps, double* result) {
    double e_previous = 0.0;
    double e_current = 2.0;
    int n = 1;

    while(fabs(e_current - e_previous) > eps) {
        e_previous = e_current;
        ++n;
        e_current = fast_exponentiation(1.0 + 1.0 / n, n);
    }
    if (isnan(e_current)) {
        return ERROR_EPS;
    }  
    *result = e_current;
    return OK;
}

return_code calculate_pi_using_limit(double eps, double* result) {
    int n = 2;
    double current = 4.0, previous = 0;
    while (fabs(previous - current) > eps) {
        previous = current;
        current *= (4.0 * n * (n - 1.0)) / fast_exponentiation(2.0 * n - 1.0, 2);
        n++;
    } 
    *result = current;
    if (isnan(*result)) {
        return ERROR_EPS;
    }
    return OK;
}

return_code calculate_ln_using_limit(double eps, double* result)
{
    double n = 1;
    double current = 1, previous = 0;
    while (fabs(previous - current) > eps)
    {
        previous = current;
        n *= 2;
        current = n * (pow(2.0, 1.0 / n) - 1.0);
    } 
    *result = current;
    if (isnan(*result)) {
        return ERROR_EPS;
    }
    return OK;
}

return_code calculate_sqrt_using_limit(double eps, double* result) {
    double current = 0.75;
    double previous = 0;
    int n = 1;
    while(fabs(previous - current) > eps) {
        previous = current;
        ++n;
        current = previous - (fast_exponentiation(previous, 2) / 2) + 1;
    }
    *result = current;
    if (isnan(*result)) {
        return ERROR_EPS;
    }
    return OK;
}

return_code calculate_gamma_using_limit(double eps, double* result) {
    double previous = 0;
    double current = 1;
    int n = 1;
    while (fabs(previous - current) > eps) {
        previous = current;
        n *= 2;
        current = calculate_harmonic_number(n) - log(n);

    }

    if (isnan(current)) {
        return ERROR_EPS;
    }
    *result = current;
    return OK;
}


return_code calculate_e_using_row(double eps, double* result) {
    double e_current = 1.0;
    double e_previous = 0.0;
    unsigned long long factorial = 1;
    int n;

    for (n = 1; n < 20; ++n) {
        e_previous = e_current;
        factorial *= n;
        e_current += (1.0 / factorial);
        if (fabs(e_current - e_previous) < eps) {
            break;
        }
    }

    if (isnan(e_current)) {
        return ERROR_EPS;
    }  
    *result = e_current;
    return OK;
}

return_code calculate_pi_using_row(double eps, double* result) {
    double pi_current = 1.0;
    double pi_previous = 0.0;
    int n = 1;
    while(fabs(pi_current - pi_previous) > eps) {
        pi_previous = pi_current;
        ++n;
        pi_current -= 1.0 / (2.0 * n - 1.0);
        ++n;
        pi_current += 1.0 / (2.0 * n - 1.0);
    }
    if (isnan(pi_current)) {
        return ERROR_EPS;
    }  
    *result = 4 * pi_current;
    return OK;
}


return_code calculate_ln_using_row(double eps, double* result) {
    double current = 1.0;
    double previous = 0.0;
    int n = 1;
    while(fabs(current - previous) > eps) {
        previous = current;
        ++n;
        current -= 1.0 / n;
        ++n;;
        current += 1.0 / n;
    }
    if (isnan(current)) {
        return ERROR_EPS;
    }
    *result = current;
    return OK;
}

return_code calculate_sqrt_using_row(double eps, double* result) {
    int k = 2;
    double current = pow(2.0, 1.0/4.0), previous = 0;
    do
    {
        previous = current;
        ++k;
        current *= pow(2,1.0/fast_exponentiation(2,k));
    } while (fabs(previous - current) >= eps);
    *result = current;
    if (isnan(*result)) {
        return ERROR_EPS;
    }
    return OK;
}

return_code calculate_gamma_using_row(double eps, double* result) {
    double previous = 0;
    double current = 0.5;
    int k = 2;
    double l = 0;
    do
    {
        previous = current;
        k++;
        l = sqrt(k);
        if (fmod(l,1.0) == 0)
        {
            k++;
            l = (int)pow(k, 1.0/2.0);
        }
        current += 1.0/pow((int)l,2.0) - 1.0/k;


    } while (fabs(previous - current) >= eps);

    if (isnan(current)) {
        return ERROR_EPS;
    }  
    *result = current - (pow(M_PI, 2) / 6);
    return OK;
}


return_code calculate_e_using_equation(double eps, double* result) {
    double f;
    double x = 2;
    double df;

    f  = log(x) - 1.0;
    while(fabs(f) > eps) {
        df = 1.0 / x;
        x = x - f / df;
        f  = log(x) - 1.0;
    }
    if (isnan(x)) {
        return ERROR_EPS;
    }
    *result = x;
    return OK;
}

return_code calculate_pi_using_equation(double eps, double* result) {
    double f;
    double x = 3;
    double df;

    f  = cos(x) + 1.0;
    while(fabs(f) > eps) {
        df = -sin(x);
        x = x - f / df;
        f  = cos(x) + 1.0;
    }
    if (isnan(x)) {
        return ERROR_EPS;
    }
    *result = x;
    return OK;
}

return_code calculate_ln_using_equation(double eps, double* result) {
    double f;
    double x = 0.5;
    double df;
    f  = exp(x) - 2;

    while(fabs(f) > eps) {
        df = exp(x);
        x = x - f / df;
        f  = exp(x) - 2;
    }
    if (isnan(x)) {
        return ERROR_EPS;
    }
    *result = x;
    return OK;
}

return_code calculate_sqrt_using_equation(double eps, double* result) {
    double f;
    double x = 0.5;
    double df;
    f  = fast_exponentiation(x, 2) - 2;

    while(fabs(f) > eps) {
        df = 2 * x;
        x = x - f / df;
        f  = fast_exponentiation(x, 2) - 2;
    }
    if (isnan(x)) {
        return ERROR_EPS;
    }
    *result = x;
    return OK;
}

return_code calculate_gamma_using_equation(double eps, double* result) {
    int p = 2;
    double current = log(2) * 0.5;
    double previous = 0;
    double product = 0.5;
    do
    {
        previous = current;
        do
        {
            p++;
        } while (!is_prime(p));
        product *= (p - 1.0)/p;
        current = log(p) * product;


    } while (fabs(previous - current) >= eps);
    *result = -log(current);
    if (isnan(current)) {
        return ERROR_EPS;
    }
    return OK;
}




void get_results(double eps, double results[15]) {
    calculate_e_using_limit(eps, &results[0]);
    calculate_pi_using_limit(eps, &results[1]);
    calculate_ln_using_limit(eps, &results[2]);
    calculate_sqrt_using_limit(eps, &results[3]);
    calculate_gamma_using_limit(eps, &results[4]);

    calculate_e_using_row(eps, &results[5]);
    calculate_pi_using_row(eps, &results[6]);
    calculate_ln_using_row(eps, &results[7]);
    calculate_sqrt_using_row(eps, &results[8]);
    calculate_gamma_using_row(eps, &results[9]);

    calculate_e_using_equation(eps, &results[10]);
    calculate_pi_using_equation(eps, &results[11]);
    calculate_ln_using_equation(eps, &results[12]);
    calculate_sqrt_using_equation(eps, &results[13]);
    calculate_gamma_using_equation(eps, &results[14]);
}


void print_results(double results[15]) {
    char* constants[5] = {"e", "pi", "ln", "sqrt", "gamma"};
    printf("Calculation using limits\n");
    for (int i = 0; i < 5; ++i) {
        if (isnan(results[i])) {
            printf("%s Impossible to calculate with a specific epsilon\n", constants[i % 5]);
            continue;
        } 

        printf("%s == %lf\n", constants[i % 5], results[i]);
    }
    printf("\n");

    printf("Calculation using rows\n");
    for (int i = 5; i < 10; ++i) {
        if (isnan(results[i])) {
            printf("%s Impossible to calculate with a specific epsilon\n", constants[i % 5]);
            continue;
        } 
        printf("%s == %lf\n", constants[i % 5], results[i]);
    }
    printf("\n");
    
    printf("Calculation using equations\n");
    for (int i = 10; i < 15; ++i) {
        if (isnan(results[i])) {
            printf("%s Impossible to calculate with a specific epsilon\n", constants[i % 5]);
            continue;
        } 

        printf("%s == %lf\n", constants[i % 5], results[i]);
    }
    printf("\n");

}