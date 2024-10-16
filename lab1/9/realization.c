#include "functions.h"
#include <limits.h>
#include <stdlib.h>


return_code convert_str_to_int(const char* str, int* res) {
    // long strtol(const char *str, char **endptr, int base);

    char* end_ptr = NULL;

    long tmp = strtol(str, &end_ptr, 10);

    if (*end_ptr != '\0') {
        return INVALID_INPUT;
    }

    if (tmp > INT_MAX || tmp < INT_MIN) {
        return ERROR_OVERFLOW;
    }

    *res = (int)tmp;

    return OK;
}

return_code fill_static_array(int* static_array, int right_border, int left_border) {

    for (int i = 0; i < SIZE_OF_STATIC_ARRAY; ++i) {
        static_array[i] = left_border + rand() % (right_border - left_border + 1);
    }

    return OK;
}

return_code swap_min_and_max(int* static_array) {
    int max = INT_MIN;
    int min = INT_MAX;
    int ind_min = 0;
    int ind_max = 0;

    for (int i = 0; i < SIZE_OF_STATIC_ARRAY; ++i) {
        if (static_array[i] > max) {
            max = static_array[i];
            ind_max = i;
        }

        if (static_array[i] < min) {
            min = static_array[i];
            ind_min = i;
        }

    }

    int tmp = static_array[ind_min];
    static_array[ind_min] = static_array[ind_max];
    static_array[ind_max] = tmp;

    return OK;
}

void print_array(const int static_array[SIZE_OF_STATIC_ARRAY]) {
    for (int i = 0; i < SIZE_OF_STATIC_ARRAY; ++i) {
        printf("%d ", static_array[i]);
    }
    printf("\n");
}

void print_dynamic_array(const int* array, const int* size_of_array) {
    for (int i = 0; i < *size_of_array; ++i) {
        printf("%d ", array[i]);
    }
    printf("\n");
}


return_code for_first(int array[SIZE_OF_STATIC_ARRAY], int right_border, int left_border) {
    fill_static_array(array, right_border, left_border);
    printf("Original array\n");
    print_array(array);
    printf("\n");
    swap_min_and_max(array);
    printf("Swapped min and max values\n");
    print_array(array);
    printf("\n");

    return OK;
}

return_code for_second(int* dynamic_array_A, int* dynamic_array_B, int* dynamic_array_C, int* size_of_array) {
    *size_of_array = LEFT_BOARD_SIZE_OF_DYMANIC_ARRAY + rand() % RIGHT_BOARD_SIZE_OF_DYMANIC_ARRAY;

    dynamic_array_A = (int*)malloc(sizeof(int) * (*size_of_array));
    if (!dynamic_array_A) {
        return ERROR_MEMORY;
    }

    dynamic_array_B = (int*)malloc(sizeof(int) * (*size_of_array));
    if (!dynamic_array_B) {
        free(dynamic_array_A);
        return ERROR_MEMORY;
    }

    dynamic_array_C = (int*)malloc(sizeof(int) * (*size_of_array));
    if (!dynamic_array_C) {
        free(dynamic_array_A);
        free(dynamic_array_B);
        return ERROR_MEMORY;
    }

    fill_dynamic_array(dynamic_array_A, size_of_array);
    fill_dynamic_array(dynamic_array_B, size_of_array);

    get_C(dynamic_array_A, dynamic_array_B, dynamic_array_C, size_of_array);

    printf("Array A\n");
    print_dynamic_array(dynamic_array_A, size_of_array);
    printf("\n");

    printf("Array B\n");
    print_dynamic_array(dynamic_array_B, size_of_array);
    printf("\n");

    printf("Array C\n");
    print_dynamic_array(dynamic_array_C, size_of_array);
    printf("\n");

    free(dynamic_array_A);
    free(dynamic_array_B);
    free(dynamic_array_C);
    return OK;
}

return_code fill_dynamic_array(int* dynamic_array, int* size_of_array) {
    for (int i = 0; i < (*size_of_array); ++i) {
        dynamic_array[i] = MIN_AMOUNG_DYNAMIC_ARRAY + rand() % MAX_AMOUNG_DYNAMIC_ARRAY;
    }

    return OK;
}

int compare(const void* a, const void* b) {
    int int_a = *(const int*)a;
    int int_b = *(const int*)b;

    return (int_a - int_b);
}

return_code get_C(int* array_A, int* array_B, int* array_C, int* size_of_array) {
    qsort(array_B, *size_of_array, sizeof(int), compare);
    for (int i = 0; i < (*size_of_array); ++i) {
        array_C[i] = array_A[i] + find_closest_value(array_A[i], array_B, size_of_array);
    }

    return OK;
}


int find_closest_value(int value, int* array, int* size_of_array) {
    int left = 0;
    int right = (*size_of_array) - 1;

    if (value <= array[left]) {
        return array[left];
    }

    if (value >= array[right]) {
        return array[right];
    }

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (array[mid] == value) {
            return array[mid];
        }

        if (array[mid] > value) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    if ((array[left] - value) < (value - array[right])) {
        return array[left];
    } else {
        return array[right];
    }

}
