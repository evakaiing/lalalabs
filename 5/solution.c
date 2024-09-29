#include <stdio.h>
#include "realization.c"


int main(int argc, char* argv[]) {
    double x;
    double eps;
    double res_a;
    double res_b;
    double res_c;
    double res_d;
    if (argc != 3) {
        printf("Invalid input, invalid\n");
        return ERROR_INPUT;
    } 
    
    if (convert_str_to_double(argv[1], &x, eps) == ERROR_OVERFLOW || convert_str_to_double_for_eps(argv[2], &eps) == ERROR_OVERFLOW) {
        printf("Overflow, underflow\n");
        return ERROR_OVERFLOW;
    } else if (convert_str_to_double(argv[1], &x, eps) == ERROR_INPUT || convert_str_to_double_for_eps(argv[2], &eps) == ERROR_INPUT) {
        printf("Incorret numbers :(\n");
        return ERROR_INPUT;
    }

    enum return_code rc_a = for_a(eps, x, &res_a);
    if (rc_a == ERROR_OVERFLOW) {
        printf("a Overflow\n");
        
    } else {
        printf("a %lf\n", res_a);
    }

    enum return_code rc_b = for_b(eps, x, &res_b);
    if (rc_b == ERROR_OVERFLOW) {
        printf("b inf \n");
    } else {
        printf("b %lf\n", res_b);
    }

    enum return_code rc_c = for_c(eps, x, &res_c);
    if (rc_c == ERROR_OVERFLOW) {
        printf("c inf \n");
    } else if(rc_c == ERROR_INPUT) {
        printf("Ряд расходится при x >= 1\n");
    } else {
        printf("c %lf\n", res_c);
    }

    enum return_code rc_d = for_d(eps, x, &res_d);
    if (rc_d == ERROR_OVERFLOW) {
        printf("d inf \n");
    } else if (rc_d == ERROR_INPUT) {
        printf("Ряд расходится при х >= 1\n");
    }
    else {
        printf("d %lf\n", res_d);
    }


    
}