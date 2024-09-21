#include "for_flags.h"
#include <stdio.h>

// usage: gcc solution.c -lm -g

int main(int argc, char* argv[]) {

    if (argc != 3) {
        printf("bro :(\n");
        return 0;
    }

    const char *first_arg = argv[1];
    const char *second_arg = argv[2];

    int num = 0;
    

    if (convert_str_to_num(first_arg, &num) == OK && is_valid_flag(second_arg) == OK) {
        char f = second_arg[1];
        switch(f) {
            case 'h':
                int res[100];
                int count = 0;
                enum return_code return_code = for_h(num, res, &count);
                if (return_code == ERROR_INPUT) {
                    printf("Error: division by a zero\n");
                    return ERROR_INPUT;
                } 

                for (int i = 0; i < count; ++i) {
                    printf("%d ", res[i]);
                }

                printf("\n");
                break;
            case 'p':
                int f = 0;
                enum return_code rc = for_p(num, &f);
                if (rc == ERROR_INPUT) {
                    printf("I'm a nothing, bro :(\n");
                    return ERROR_INPUT;
                }
                if (f == 0) {
                    printf("A prime\n");
                } else {
                    printf("A composite\n");
                }

                printf("\n");
                break;
            case 'f':
                long res_f = 1;
                enum return_code rc_f = for_f(num, &res_f);

                if (rc_f == ERROR_INPUT) {
                    printf("Negative number, bro :(\n");
                    return ERROR_INPUT;
                } else if (rc_f == ERROR_OVERFLOW) {
                    printf("Too big, bro :(\n Overflow\n");
                    return ERROR_OVERFLOW;
                }

                printf("%ld\n", res_f);

                printf("\n");
                break;
            case 'a':
                int res_a = 0;
                enum return_code rc_a = for_a(num, &res_a);

                if (rc_a == ERROR_INPUT) {
                    printf("Nah, error input\n");
                    return ERROR_INPUT;
                } else if (rc_a == ERROR_OVERFLOW) {
                    printf("Nah, overflow\n");
                    return ERROR_OVERFLOW;
                }

                printf("%d\n", res_a);

                printf("\n");
                break;

            case 's':
                char hex[20];
                int ind = 0;
                enum return_code rc_s = for_s(num, hex, &ind);
                for (int i = ind - 1; i >= 0; --i) {
                    printf("%c ", hex[i]);
                }

                printf("\n");
                break;
            case 'e':
                int** nums;
                enum return_code rc_e = for_e(num, &nums);
                if (rc_e == ERROR_INPUT) {
                    printf("Error input, bro\n");
                    return ERROR_INPUT;
                } else if (rc_e == ERROR_MEMORY) {
                    printf("Error in memory allocation :(");
                    return ERROR_INPUT;
                } 

                for (int i = 0; i < 10; ++i) {
                    for (int j = 0; j < num; ++j) {
                        printf("%d ", nums[i][j]);
                    }
                    printf("\n");
                }

                for (int i = 0; i < 10; ++i) {
                    free(nums[i]);    
                }
                free(nums);

                break;
            default:    
                printf("Incorrect input");
        }  
    } else {
        printf("Invalid input, invalid\n");
        return ERROR_INPUT;
    }
}