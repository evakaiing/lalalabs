
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdio.h>

enum return_code 
{
    OK,
    ERROR_INPUT,
    ERROR_OVERFLOW,
    ERROR_MEMORY
};

int is_valid_flag(const char* flag) {
    if (strlen(flag) != 2) {
        return ERROR_INPUT;
    }
    if (flag[0] == '-' || flag[0] == '/') {
        switch(flag[1]) {
            case 'h':
            case 'p':
            case 's':
            case 'e':
            case 'a':
            case 'f':
                return OK; 
            default:
                return ERROR_INPUT; 
        }
    }
    return ERROR_INPUT;
}

int convert_str_to_num(const char* str, int* res) {
    // long strtol(const char *str, char **endptr, int base);

    char* end_ptr = NULL;

    long tmp = strtol(str, &end_ptr, 10);

    if (*end_ptr != '\0') {
        return ERROR_INPUT;
    }

    if (tmp > INT_MAX || tmp < INT_MIN) {
        return ERROR_OVERFLOW;
    }

    *res = (int)tmp;

    return OK;
}



int to_hex(int num, char* hex, int* ind, int* sign) {
    *sign = num < 0 ? -1 : 1;

    if (num == 0) {
        hex[(*ind)++] = '0';
    }

    while(num > 0) {
        int digit = num % 16;
        if (digit < 10) {
            hex[(*ind)++] = '0' + digit;
        } else {
            hex[(*ind)++] = 'A' + (digit - 10);
        }
        num = num / 16;
    }

    return OK;
}


int for_h(int num, int* res, int* count) { 

    if (num == 0) {
        return ERROR_INPUT;
    }

    num = abs(num);


    for (int i = 1; i <= 100; ++i) {
        if (i % num == 0) {
            res[(*count)++] = i;
        }
    }

    return OK;

}

int for_p(int num, int* f) {
    num = abs(num);

    if (num < 2) {
        return ERROR_INPUT;
    } 

    for (int i = 2; i <= (int)sqrt(num); ++i) {
        if (num % i == 0) {
            *f = 1;
        }
    }
    return OK;
}


int for_f(const int num, long* res) {
    if (num < 0) {
        return ERROR_INPUT;
    } 
    
    if (num > 20) {
        return ERROR_OVERFLOW;
    }

    if (num < 2) {
        *res = num;
    }
    for (int i = 2; i <= num; ++i) {
        *res *= i;
    }

    if (*res >= INT_MAX) {
        return ERROR_OVERFLOW;
    }

    return OK;
}

int for_a(const int num, int* res) {
    if (num < 0) {
        return ERROR_INPUT;
    } 

    for (int i = 1; i <= num; ++i) {
        if (*res > INT_MAX - i) {
            return ERROR_OVERFLOW;
        }
        *res += i;
    }

    return OK;
}

int for_s(int num, char* hex, int* ind, int* sign) {
    enum return_code rc = to_hex(num, hex, ind, sign);
}

int for_e(const int num, size_t*** nums) {

    if (num > 10 || num <= 0) {
        return ERROR_INPUT;
    }
    *nums = (size_t**)malloc(10 * sizeof(size_t*));

    if (*nums == NULL) {
        return ERROR_MEMORY;
    }

    for (int i = 0; i < 10; ++i) {
        (*nums)[i] = (size_t*)malloc(num * sizeof(size_t));
        if ((*nums)[i] == NULL) {
            for (int j = 0; j < i; ++j) {
                free(nums[i]);
            }
            free(nums);
            return ERROR_MEMORY;
        }
    }
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < num; ++j) {
            (*nums)[i][j] = pow(i + 1, j + 1);  
        }
    }      
}


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
                int sign = 1;
                enum return_code rc_s = for_s(num, hex, &ind, &sign);
                for (int i = ind - 1; i >= 0; --i) {
                    if (sign == -1) {
                        printf("-");
                    }
                    printf("%c ", hex[i]);
                }

                printf("\n");
                break;
            case 'e':
                size_t** nums;
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
                        printf("%ld ", nums[i][j]);
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