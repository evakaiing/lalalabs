#include "functions.h"
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Invalud input\n");
        return INVALID_INPUT;
    }
    char* first_arg = argv[1];
    char* str = argv[2];
    return_code status_of_flag_handling = flag_handling(first_arg);
    if (status_of_flag_handling == INVALID_INPUT) {
        printf("Invalid input\n");
        return INVALID_INPUT;
    }

    switch(first_arg[1]) {
        case 'l':
            if (argc != 3) {
                printf("Invalid amount arguments\n");
                return INVALID_INPUT;
            }

            printf("%ld\n", strlen(str));
            break;
        case 'r':
            if (argc != 3) {
                printf("Invalid amount arguments\n");
                return INVALID_INPUT;
            }
            char* result_r = NULL;
            return_code status_of_reversing_str = str_reverse(str, &result_r);
            if (status_of_reversing_str == MEMORY_ALLOCATION_ERROR) {
                printf("Error in memory allocation\n");
                return MEMORY_ALLOCATION_ERROR;
            }
            printf("%s\n", result_r);
            free(result_r);
            break;
        case 'u':
            if (argc != 3) {
                printf("Invalid amount arguments\n");
                return INVALID_INPUT;
            }
            char* result_u = NULL;
            return_code status_u = for_u(str, &result_u);
            if (status_u == MEMORY_ALLOCATION_ERROR) {
                printf("Error in memory allocation\n");
                return MEMORY_ALLOCATION_ERROR;
            }

            printf("%s\n", result_u);
            free(result_u);
            break;
        case 'n':
            if (argc != 3) {
                printf("Invalid amount arguments\n");
                return INVALID_INPUT;
            }
            char* result_n = NULL;
            return_code status_n = for_n(str, &result_n);
            if (status_n == MEMORY_ALLOCATION_ERROR) {
                printf("Error in memory allocation\n");
                return MEMORY_ALLOCATION_ERROR;
            }

            printf("%s\n", result_n);
            free(result_n);
            break;
        case 'c':
            char* result_c = NULL;
            int count_of_arguments = argc - 3;
            int number_seed = 0;
            return_code status_of_conversion = convert_str_to_int(argv[2], &number_seed);
            if (status_of_conversion == OVERFLOW_ERROR) {
                printf("Overflow\n");
                return OVERFLOW_ERROR;
            } else if (status_of_conversion == INVALID_INPUT) {
                printf("Invalid input of number, bye\n");
                return INVALID_INPUT;
            }

            if (!(abs(number_seed) == number_seed)) {
                printf("This number is negative\n");
                return INVALID_INPUT;
            }

            return_code status_c = for_c(argv + 3, count_of_arguments, number_seed, &result_c);

            if (status_c == MEMORY_ALLOCATION_ERROR) {
                printf("Error in memory allocation\n");
                return MEMORY_ALLOCATION_ERROR;
            }

            printf("%s\n", result_c);
            free(result_c);
            break;
    }
    return OK;
}

