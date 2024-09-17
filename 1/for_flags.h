
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

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


enum return_code to_hex(unsigned int num, char* hex, int* ind) {
    // один символ занимает 4 бита, в int 64 бит, 64\4 максимум 16 цифр потребуется для представления


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


int for_f(const int num, int* res) {
    if (num < 0) {
        return ERROR_INPUT;
    }
    if (num < 2) {
        *res = num;
    }
    for (int i = 2; i <= num; ++i) {
        *res *= i;
    }

    if (*res == INT_MAX) {
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

int for_s(int num, char* hex, int* ind) {
    unsigned int unsigned_num = (unsigned int)num;
    enum return_code rc = to_hex(unsigned_num, hex, ind);
}

int for_e(const int num, int*** nums) {

    if (num > 10 || num <= 0) {
        return ERROR_INPUT;
    }
    *nums = (int**)malloc(10 * sizeof(int*));

    if (*nums == NULL) {
        return ERROR_MEMORY;
    }

    for (int i = 0; i < 10; ++i) {
        (*nums)[i] = (int*)malloc(num * sizeof(int));
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
