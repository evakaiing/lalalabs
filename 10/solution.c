#include "functions.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: base number1 number2 ... numberN\n");
        return ERROR_INPUT;
    }

    char current_str[BUFSIZ];
    char* first_arg = argv[1];
    int base;

    return_code conversion_code = convert_str_to_num(first_arg, &base);

    if (conversion_code == ERROR_INPUT) {
        printf("Invalid base\n");
        return ERROR_INPUT;
    } else if (conversion_code == ERROR_INPUT_BASE) {
        printf("Base must be up to 36\n");
    }

    int default_size_of_massive = 100;
    int* numbers = (int*)malloc(sizeof(int) * default_size_of_massive);
    int i = 0;
    int max_number = 0;
    char buf[BUFSIZ];
    int number_systems[] = {9, 18, 27, 36};
    char buf_for_convert_max_number[BUFSIZ];

    if (numbers == NULL) {
        printf("Error in memory allocation\n");
        return ERROR_MEMORY;
    }

    while(scanf("%s", current_str)) {

        if (strcmp(current_str, "Stop") == 0) {
            break;
        }

        return_code validation_code = is_valid_number(current_str, base);
        if  (validation_code == ERROR_INPUT) {
            printf("Incorrect input\n");
            free(numbers);
            return ERROR_INPUT;
        } else if (validation_code == ERROR_INPUT_BASE) {
            printf("Numbers must be smaller than degree of the number system\n");
            free(numbers);
            return ERROR_INPUT_BASE;
        }
        int num_in_decimal = 0;

        if (gorner_scheme(current_str, base, &num_in_decimal) != OK) {
            printf("ERROR\n");
            free(numbers);
            return ERROR_INPUT;
        }

        if (i > default_size_of_massive) {
            default_size_of_massive *= 2;
            int* ptr = (int*)realloc(numbers, sizeof(int) * default_size_of_massive);
            if (ptr == NULL) {
                printf("Error in memory reallocation\n");
                return ERROR_MEMORY;
            }
            numbers = ptr;
        }

        numbers[i++] = num_in_decimal;

        if (abs(num_in_decimal) >= abs(max_number)) {
            max_number = num_in_decimal;
        }
    }
    printf("\n");
    
    char* max_number_in_start_base = reverse_gorner_scheme(max_number, base, buf_for_convert_max_number);
    printf("%s\n", max_number_in_start_base);

    for (int i = 0; i <= 3; ++i) {
        char* num = reverse_gorner_scheme(max_number, number_systems[i], buf);
        printf("%s ", num);
    }

    free(numbers);
    return 0;
}
