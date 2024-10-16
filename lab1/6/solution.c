#include "functions.h"
#include <stdio.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Incorrect input, bye\n");
        return INVALID_INPUT;
    }
    double eps;
    return_code status_of_convertation = convert_str_to_double(argv[1], &eps);
    if (status_of_convertation == INVALID_INPUT) {
        printf("incorrecnt input, bro\n");
        return INVALID_INPUT;
    }

    double integral_a = calculate_integral(eps, integrative_expression_a);
    printf("A: %lf\n", integral_a);

    double integral_b = calculate_integral(eps, integrative_expression_b);
    printf("B: %lf\n", integral_b);

    double integral_c = calculate_integral(eps, integrative_expression_c);
    printf("C: %lf\n", integral_c);

    double integral_d = calculate_integral(eps, integrative_expression_d);
    printf("D: %lf\n", integral_d);
}