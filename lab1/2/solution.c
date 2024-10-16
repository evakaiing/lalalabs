#include <stdio.h>
#include "realization.c"



int main(int argc, char* argv[]) {
    if (argc > 2) {
        printf("Too much arguments\n");
        return ERROR_INPUT;
    } else if (argc < 2) {
        printf("Too few arguments\n");
        return ERROR_INPUT;
    }
    double eps;
    if (convert_str_to_double_for_eps(argv[1], &eps) == ERROR_OVERFLOW) {
        printf("Overflow, bro\n");
        return ERROR_OVERFLOW;
    } else if (convert_str_to_double_for_eps(argv[1], &eps) == ERROR_INPUT) {
        printf("Incorret numbers :(\n");
        return ERROR_INPUT;
    }

    double results[15];
    get_results(eps, results);
    print_results(results);
    
    
    return 0;
}