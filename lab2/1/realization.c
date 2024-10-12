#include <stdio.h>
#include "functions.h"
#include <ctype.h>
#include <stdlib.h>
#include <limits.h>


return_code convert_str_to_int(const char* str, int* res) {
    // long strtol(const char *str, char **endptr, int base);

    char* end_ptr = NULL;

    long tmp = strtol(str, &end_ptr, 10);

    if (*end_ptr != '\0') {
        return INVALID_INPUT;
    }

    if (tmp > LONG_MAX) {
        return OVERFLOW_ERROR;
    }

    *res = (int)tmp;

    return OK;
}


return_code flag_handling(const char* flag) {
    if (flag[0] == '-'){
            switch(flag[1]) {
                case 'l':
                case 'r':
                case 'u':
                case 'n':
                case 'c':
                    return OK; 
                default:
                    return INVALID_INPUT; 
            }
    }
    return INVALID_INPUT;
} 

size_t strlen(char * str) {
    char* end = str;
    while(*end++);
    return end - str - 1;
}

char* str_cpy(char* dist, char* src) {
    char *res = dist;
    
    while(*dist++ == *src++);
    
    return res;
}


// int isupper(const char symbol) {
//     return (symbol >= 'A' && symbol <= 'Z');
// }

return_code for_u(char* input_str, char** output_str) {
    (*output_str) = (char*)malloc(strlen(input_str) + 1);
    if (!(*output_str)) {
        return MEMORY_ALLOCATION_ERROR;
    }

    int cnt = 0;
    char* p_input_str = input_str;
    while(*p_input_str != '\0') {
        if (cnt % 2 != 0) {
            if (isdigit(*p_input_str)) {
                continue;
            } else if (isupper(*p_input_str)) {
                continue;
            }
            
            (*output_str)[cnt] = toupper(*p_input_str);
        } else {
            (*output_str)[cnt] = *p_input_str;
        }
        ++p_input_str;
        ++cnt;
    }

     (*output_str)[cnt] = '\0';

    return OK;
}

void str_cat(char* str_to_cat, char* what_to_concatenate) {
    char* p_str_to_cat = str_to_cat + strlen(str_to_cat);
    while(*what_to_concatenate != '\0') {
        *p_str_to_cat++ = *what_to_concatenate++;
    }
    *p_str_to_cat = '\0';   
}

return_code str_reverse(char* input_str, char** output_str) {
    char* p_input_str, *p_output_str;
    *output_str = (char*)malloc(sizeof(input_str));
    if (!(*output_str)) {
        return MEMORY_ALLOCATION_ERROR;
    }

    p_input_str = input_str + strlen(input_str) - 1;
    p_output_str = *output_str;

    for(int i = 0; i < strlen(input_str); ++i) {
        *p_output_str++ = *p_input_str--;
    }

    *p_output_str = '\0';

    return OK;
}

return_code for_n(char* str, char** output_str) {
    (*output_str) = (char*)malloc(strlen(str) + 1);
    int digit_cnt = 0;
    int alphas_cnt = 0;
    int other_symbols_cnt = 0;
    char digits[BUFSIZ] = {0};
    char alphas[BUFSIZ] = {0};
    char other_symbols[BUFSIZ] = {0};

    char* p_str = str;
    int cnt = 0;
    for (int i = 0; i < strlen(str);++i) {
        if (isdigit(*p_str)) {
            digits[digit_cnt++] = *p_str++;
        } else if(isalpha(*p_str)) {
            alphas[alphas_cnt++] = *p_str++;
        } else {
            other_symbols[other_symbols_cnt++] = *p_str++;
        }
    }

    str_cat((*output_str), digits);
    str_cat((*output_str), alphas);
    str_cat((*output_str), other_symbols);
}
return_code for_c(char** argv, int count_of_str, unsigned int number_seed, char** result) {
    int i, j;
    int capacity = 0;
    int* used_indices = (int*)calloc(count_of_str, sizeof(int));

    if (!used_indices) {
        return MEMORY_ALLOCATION_ERROR;
    }


    for (i = 0; i < count_of_str; ++i) {
        capacity += strlen(argv[i]);
    }

    *result = (char*)malloc(capacity + 1);

    if (!(*result)) {
        free(used_indices);
        return MEMORY_ALLOCATION_ERROR;
    }

    **result = '\0';

    srand(number_seed);

    for (i = 0; i < count_of_str; ++i) {
        int random_num;
        do {
            random_num = rand() % count_of_str;
        } while (used_indices[random_num]);
        used_indices[random_num] = 1;

        str_cat(*result, argv[random_num]);
    }

    free(used_indices);
    return OK;
}