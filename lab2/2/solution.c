#include "functions.h"
#include <stdio.h>

int main(int argc, char* argv[]) {
    int count_of_values;
    
    double first_result;
    double second_result = 0;
    double num_to_exponentation = 2;
    int degree = 8;

    return_code status = calculate_geometric_average(&first_result, 5, 0.0, 5.0, 4.0, 8.0, 10.0);
    return_code status_2 = fast_exponentiation(num_to_exponentation, degree, &second_result);

    if (status == OVERFLOW_ERROR || status_2 == OVERFLOW_ERROR) {
        printf("Overflow error\n");
        return OVERFLOW_ERROR;
    }
    if (status == INVALID_INPUT || status_2 == INVALID_INPUT) {
        printf("Invalid_input\n");
        return INVALID_INPUT;
    }


    printf("For numbers 7, 5, 4, 8, 10 geom average: %lf\n",  first_result);
    printf("for %lf and degree %d result of exponentation: %lf\n", num_to_exponentation, degree, second_result);
}