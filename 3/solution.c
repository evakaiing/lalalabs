#include <stdio.h>
#include "for_flags.h"


int main(int argc, char* argv[]) {
    if (argc < 4) {
        printf("Too few arguments\n");
        return ERROR_INPUT;
    }

    const char* first_arg = argv[1];
    if (is_valid_flag(first_arg) == ERROR_INPUT) {
        printf("No way, invalid input, invalid\n");
        return ERROR_INPUT;
    } 

    const char flag = first_arg[1];

    switch(flag) {
        case 'm':
            if (argc > 4) {
                printf("Too much arguments, bro\n");
                return ERROR_INPUT;
            }

            int num1;
            int num2;

            if (convert_str_to_int(argv[2], &num1) == ERROR_OVERFLOW || convert_str_to_int(argv[3], &num2) == ERROR_OVERFLOW) {
                printf("Overflow, bro\n");
                return ERROR_OVERFLOW;
            } else if (convert_str_to_int(argv[2], &num1) == ERROR_INPUT || convert_str_to_int(argv[3], &num2) == ERROR_INPUT) {
                printf("Incorret numbers :(\n");
                return ERROR_INPUT;
            }

            int ans = 0;
            enum return_code rc_m = for_m(num1, num2, &ans);

            if (rc_m == ERROR_INPUT) {
                printf("There are a zeroes, kapets blin\n");
                return ERROR_INPUT;
            } else if (rc_m == ERROR_OVERFLOW) {
                printf("Overflow blin\n");
                return ERROR_OVERFLOW;
            }

            if (ans == 0) {
                printf("Nah, it's not\n");
            } else {
                printf("AGA, kratno\n");
            }
            break;
        case 't':
            if (argc > 6) {
                printf("Too much arguments, bye!");
                return ERROR_INPUT;
            } 

            double num1_t;
            double num2_t;
            double num3_t;
            double eps;

            if (convert_str_to_double_for_eps(argv[2], &eps) != OK) {
                printf("Troubles with epsilon input");
                return ERROR_INPUT;
            }
            if (convert_str_to_double(argv[3], &num1_t, eps) == ERROR_OVERFLOW || 
                convert_str_to_double(argv[4], &num2_t, eps) == ERROR_OVERFLOW || 
                convert_str_to_double(argv[5], &num3_t, eps) == ERROR_OVERFLOW ) {
                printf("Overflow, bro\n");
                return ERROR_OVERFLOW;
            } else if (convert_str_to_double(argv[3], &num1_t, eps) == ERROR_INPUT || 
                convert_str_to_double(argv[4], &num2_t, eps) == ERROR_INPUT || 
                convert_str_to_double(argv[5], &num3_t, eps) == ERROR_INPUT) {
                printf("Incorrect numbers :(\n");
                return ERROR_INPUT;
            } else if (convert_str_to_double(argv[3], &num1_t, eps) == ERROR_UNDERFLOW || 
                convert_str_to_double(argv[4], &num2_t, eps) == ERROR_UNDERFLOW || 
                convert_str_to_double(argv[5], &num3_t, eps) == ERROR_UNDERFLOW) {
                printf("Underflow :(\n");
                return ERROR_UNDERFLOW;
            } 

            // printf("%lf %lf %lf", num1_t, num2_t, num3_t);   

            int ans_t = 0;
            enum return_code rc_t = for_t(eps, num1_t, num2_t, num3_t, &ans_t);
            if (rc_t == ERROR_OVERFLOW) {
                printf("Overflow\n");
                return ERROR_OVERFLOW;
            } 

            if (ans_t == 1) {
                printf("Yeahh\n");
            } else {
                printf("Nah");
            }
            break;
        case 'q':
            if (argc > 6) {
                printf("Too much arguments, bye!\n");
                return ERROR_INPUT;
            } 

            double num1_q;
            double num2_q;
            double num3_q;
            double eps_q;

            if (convert_str_to_double_for_eps(argv[2], &eps_q) != OK) {
                printf("Troubles with epsilon input");
                return ERROR_INPUT;
            }
            if (convert_str_to_double(argv[3], &num1_q, eps_q) == ERROR_OVERFLOW || 
                convert_str_to_double(argv[4], &num2_q, eps_q) == ERROR_OVERFLOW || 
                convert_str_to_double(argv[5], &num3_q, eps_q) == ERROR_OVERFLOW ) {
                printf("Overflow, bro\n");
                return ERROR_OVERFLOW;
            } else if (convert_str_to_double(argv[3], &num1_q, eps_q) == ERROR_INPUT || 
                convert_str_to_double(argv[4], &num2_q, eps_q) == ERROR_INPUT || 
                convert_str_to_double(argv[5], &num3_q, eps_q) == ERROR_INPUT) {
                printf("Incorrect numbers :(\n");
                return ERROR_INPUT;
            } else if (convert_str_to_double(argv[3], &num1_q, eps_q) == ERROR_UNDERFLOW || 
                convert_str_to_double(argv[4], &num2_q, eps_q) == ERROR_UNDERFLOW || 
                convert_str_to_double(argv[5], &num3_q, eps_q) == ERROR_UNDERFLOW) {
                printf("Underflow :(\n");
                return ERROR_UNDERFLOW;
            } 

            enum return_code rc_q = for_q(eps_q, num1_q, num2_q, num3_q);

            if (rc_q == ERROR_OVERFLOW) {
                printf("Overflow\n");
                return ERROR_OVERFLOW;
            } else if (rc_q == ERROR_INPUT) {
                printf("Incorrect numbers\n");
                return ERROR_INPUT;
            } 
            

            break;
    }
}