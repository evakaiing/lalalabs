#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "functions.h"


int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Invalid amount arguments, bye!\n");
        return INVALID_INPUT;
    }

    int right_border = 0;
    int left_border = 0;
    int static_array[SIZE_OF_STATIC_ARRAY];
    int* dynamic_array_A = NULL;
    int* dynamic_array_B = NULL;
    int* dynamic_array_C = NULL;
    int size_of_dynamic_array = 0;


    return_code status_convertation_of_arg1 = convert_str_to_int(argv[1], &right_border);
    return_code status_converetation_of_arg2 = convert_str_to_int(argv[2], &left_border);

    if (status_convertation_of_arg1 == ERROR_OVERFLOW || status_converetation_of_arg2 == ERROR_OVERFLOW) {
        printf("Error overflow :( \n");
        return ERROR_OVERFLOW;
    }

    if (status_convertation_of_arg1 == INVALID_INPUT || status_converetation_of_arg2 == INVALID_INPUT) {
        printf("Введена дичь :( \n");
        return INVALID_INPUT;
    }

    srand(time(NULL));
    for_first(static_array, right_border, left_border);
    for_second(dynamic_array_A, dynamic_array_B, dynamic_array_C, &size_of_dynamic_array);
}