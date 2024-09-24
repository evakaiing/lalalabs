#include <stdio.h>
#include "functions.h"
#include "realization.c"


int main(int argc, char* argv[]) {
    double eps = 1e-12;
    // double res = calculate_e_using_limit(eps);

    // printf("%lf\n", res);

    printf("e %lf\n", calculate_e_using_limit(eps));
    printf("pi %lf\n", calculate_pi_using_limit(eps));
    printf("ln %lf\n", calculate_ln_using_limit(eps));
    printf("ln %lf\n", calculate_ln_using_limit(eps));
    printf("sqrt %lf\n", calculate_sqrt_using_limit(eps));
    printf("gamma %lf\n", calculate_gamma_using_limit(eps));
    // printf("pi %lf\n", calculate_pi_using_row(eps));
    // printf("ln %lf\n", calculate_ln_using_row(eps));
    // printf("sqrt %lf\n", calculate_sqrt_using_row(eps));
    // printf("gamma %lf\n", calculate_gamma_using_row(eps));
    // printf("e %lf\n", calculate_e_using_equation(eps));
    // printf("pi %lf\n", calculate_pi_using_equation(eps));
    // printf("ln %lf\n", calculate_ln_using_equation(eps));
    // printf("sqrt %lf\n", calculate_sqrt_using_equation(eps));
    // printf("gamma %lf\n", calculate_gamma_using_equation(eps));
    return 0;
}