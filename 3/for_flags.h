#include <string.h>
#include <float.h>
#include <math.h> 
#include <limits.h>
#include <stdlib.h>

enum return_code {
    OK,
    ERROR_INPUT,
    ERROR_OVERFLOW,
    ERROR_UNDERFLOW
};

int is_valid_flag(const char* arg) {
    if (strlen(arg) != 2) {
        return ERROR_INPUT;
    }

    if (arg[0] == '/' || arg[0] == '-') {
        char f = arg[1];
        switch(f) {
            case 'q':
            case 'm':
            case 't':
                return OK;
                break;
            default:
                return ERROR_INPUT;
        }
        return OK;
    }

    return ERROR_INPUT;
}

int convert_str_to_int(const char* str, int* res) {
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

int convert_str_to_double_for_eps(const char* str, double* res) {
    char* end_ptr = NULL;

    double tmp = strtod(str, &end_ptr);


    if (*end_ptr != '\0') {
        return ERROR_INPUT;
    }

    if (fabs(tmp) > DBL_MAX) {
        return ERROR_OVERFLOW;
    }

    if (fabs(tmp) < DBL_MIN && tmp != 0) {
        return ERROR_UNDERFLOW;
    }

    *res = (double)tmp;

    return OK;
}

int convert_str_to_double(const char* str, double* res, const double eps) {
    // double strtod(const char *str, char **endptr);

    char* end_ptr = NULL;

    double tmp = strtod(str, &end_ptr);

    if (*end_ptr != '\0') {
        return ERROR_INPUT;
    }

    if (fabs(tmp) > DBL_MAX - eps) {
        return ERROR_OVERFLOW;
    }

    if (fabs(tmp) < DBL_MIN && tmp != 0) {
        return ERROR_UNDERFLOW;
    }


    *res = (double)tmp;

    return OK;
}

int there_is_overflow(const double coefficent1, const double coefficent2, const double eps) {
    if (coefficent1 * coefficent2 > DBL_MAX - eps) {
        return 1;
    } 
    return 0;
}

// validation turn into functions for flags

int arrays_are_equal(double arr1[3], double arr2[3], double eps) {
    for (int i = 0; i < 3; ++i) {
        if (fabs(arr1[i] - arr2[i]) >= eps) {
            return 0;
        }
    }
    return 1;
}

int is_unique_permutation(double permutations[6][3],
        int count_uniqie_permitations, 
        double current[3],
        double eps) {
    for (int i = 0; i < count_uniqie_permitations; ++i) {
        if (arrays_are_equal(permutations[i], current, eps)) {
            return 0;
        }
    }
    return 1;
}

int solve_quadratic_equation(double coefficent1, 
        double coefficent2, double coefficent3, 
        double eps, 
        double* ans1,
        double* ans2,
        int* count_of_answers) {
    if (fabs(coefficent1) < eps) {
        if (fabs(coefficent2) < eps) {
            if (fabs(coefficent3) < eps) {   
                return ERROR_INPUT; // 0 = 0
            } else {
                return ERROR_INPUT; // 5 != 0
            }
        } else {
            *ans1 = -coefficent3 / coefficent2;
            *count_of_answers = 1;
            return OK;
        }
    }

    double discriminant = coefficent2 * coefficent2 - 4 * coefficent1 * coefficent3;
    if (discriminant > DBL_MAX - eps) {
        return ERROR_OVERFLOW;
    }

    if (fabs(discriminant) < eps) {
        *ans1 = -coefficent2 / (2 * coefficent1);
        *count_of_answers = 1;
    } else if (discriminant > 0) {
        *ans1 = (-coefficent2 + sqrt(discriminant)) / (2 * coefficent1);
        *ans2 = (-coefficent2 - sqrt(discriminant)) / (2 * coefficent1);
        *count_of_answers = 2;
    } else if (discriminant < 0) {
        return *count_of_answers = 0;
    }

    return OK;
}   


void print_answers(int* count_of_answers, double* ans1, double* ans2) {
    if (*count_of_answers == 1) {
        printf("The only one - %lf\n", *ans1);
        printf("\n");
    } else if (*count_of_answers == 2) {
        printf("The first solution - %lf, the second - %lf\n", *ans1, *ans2);
        printf("\n");       
    } else {
        printf("Infifnite solutions\n");
        printf("\n");
    }
}


int for_q(const double eps, const double coefficent1, 
        const double coefficent2, 
        const double coefficent3) {
    
    int permutation[6][3] =  { {0, 1, 2}, {0, 2, 1}, {1, 0, 2}, {1, 2, 0}, {2, 0, 1}, {2, 1, 0} };
    double coefficents_for_permutations[3] = { coefficent1, coefficent2, coefficent3 };
    double unique_permutations[6][3];
    int count_of_unique_permutations = 0;  

    if (fabs(coefficent1) > DBL_MAX - eps ||
        fabs(coefficent2) > DBL_MAX - eps || 
        fabs(coefficent3) > DBL_MAX - eps) {
        return ERROR_OVERFLOW;
    } else if ((fabs(coefficent1) < eps &&
                fabs(coefficent2) < eps &&
                fabs(coefficent3) < eps)) {
        return ERROR_INPUT;
    }

    for (int i = 0; i < 6; ++i) {
        double current_permutation[3] = { coefficents_for_permutations[permutation[i][0]],
                                          coefficents_for_permutations[permutation[i][1]], 
                                          coefficents_for_permutations[permutation[i][2]] };

        double first_solution;
        double second_solution;
        int count_of_answers = 0; 

        if (is_unique_permutation(unique_permutations, count_of_unique_permutations, current_permutation, eps)) {
            for (int j = 0; j < 3; ++j) {
                unique_permutations[count_of_unique_permutations][j] = current_permutation[j];
            }
            ++count_of_unique_permutations;

            
            int rc = solve_quadratic_equation(current_permutation[0],
                                              current_permutation[1], 
                                              current_permutation[2],
                                              eps, 
                                              &first_solution, 
                                              &second_solution, 
                                              &count_of_answers);

            if (rc != OK) {
                return rc;
            } else {
                printf("Solutions for coefficents: %lf %lf %lf\n", current_permutation[0], current_permutation[1], current_permutation[2]);
                print_answers(&count_of_answers, &first_solution, &second_solution);
            }
        }
    }
    return OK;
}


int for_m(const int first_num, const int second_num, int* flag) {

    if (first_num == 0 || second_num == 0) {
        return ERROR_INPUT;
    }

    if (abs(first_num) > INT_MAX || abs(second_num) > INT_MAX) {
        return ERROR_OVERFLOW;
    }

    if (second_num % first_num == 0) {
        *flag = 1;
    }
    return OK;
}

int for_t(const double eps, 
            const double coefficent1, 
            const double coefficent2, 
            const double coefficent3, 
            int* ans) {
    // eps? 
    if (there_is_overflow(coefficent1, coefficent1, eps) || there_is_overflow(coefficent2, coefficent2, eps) || there_is_overflow(coefficent3, coefficent3, eps)) {
        return ERROR_OVERFLOW;
    }
    double hypotenuse = fmax(fmax(coefficent1, coefficent2), coefficent3);
    double sum = 0;
    
    if (fabs(hypotenuse - coefficent1) <= eps) {
        sum = coefficent2 * coefficent2 + coefficent3 * coefficent3;
    } else if (fabs(hypotenuse - coefficent2) <= eps) {
        sum = coefficent1 * coefficent1 + coefficent3 * coefficent3;
    } else {
        sum = coefficent1 * coefficent1 + coefficent2 * coefficent2;
    }
    if (sum > DBL_MAX - eps) {
        return ERROR_OVERFLOW;
    }
    if (fabs(hypotenuse - sum) <= eps) {
        *ans = 1;
    }
    return OK;
}
