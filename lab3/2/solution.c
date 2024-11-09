#include "functions.h"

int main() {
    Vector v_1 = {.data = (double[]){-1.0, -100.0, -3.0, 10.0}, .n = 4};
    Vector v_2 = {.data = (double[]){0.0, 4.0, 6.0, 100.}, .n = 4};
    size_t count_res = 0;
    Vector *res = NULL;
    double matrix_A[] = {120.0, 21.0, 44.0, 55.5, 13.0, 12.0, 3.0, 4.0,
                         20, 9, 5, 3, 19, 25, 4, 25};
    double p = 11.2;

    switch (search_longest_vectors(&res, &count_res, 3, 3, v_1, v_2, v_2, a_norm, &matrix_A, inf_norm, NULL, p_norm, &p)) {
        case MEMORY_ALLOCATION_ERROR:
            printf("Memory allocation error\n");
            delete_vector_arr(&res, count_res);
            return MEMORY_ALLOCATION_ERROR;

        case INVALID_INPUT:
            printf("Invalid input\n");
            delete_vector_arr(&res, count_res);
            return MEMORY_ALLOCATION_ERROR;
        case OK:
            for (size_t i = 0; i < count_res - 1; ++i) {
                if (!res[i].data) {
                    printf("\n");
                    continue;
                }

                printf("( ");

                for (size_t j = 0; j < res[i].n; ++j) {
                    printf("%lf ", res[i].data[j]);
                }

                printf(")\n");
            }
        }

    delete_vector_arr(&res, count_res);
    return 0;
}