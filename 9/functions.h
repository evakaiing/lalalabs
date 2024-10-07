#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include <ctype.h>
#include <stdio.h>

#define SIZE_OF_STATIC_ARRAY 10
#define RIGHT_BOARD_SIZE_OF_DYMANIC_ARRAY 1000
#define LEFT_BOARD_SIZE_OF_DYMANIC_ARRAY 10
#define MIN_AMOUNG_DYNAMIC_ARRAY -1000
#define MAX_AMOUNG_DYNAMIC_ARRAY 1000



typedef enum return_code 
{
    OK,
    INVALID_INPUT,
    ERROR_OVERFLOW,
    ERROR_MEMORY,
} return_code;


return_code convert_str_to_int(const char* str, int* res);
return_code fill_static_array(int* static_array, int right_border, int left_border);
return_code swap_min_and_max(int* static_array);
return_code fill_dynamic_array(int* dynamic_array, int size_of_array);
return_code get_C(int* array_A, int* array_B, int* array_C, const int size_of_array);
int find_closest_value(int value, int* array_B, int size_of_array);

void print_array(const int static_array[SIZE_OF_STATIC_ARRAY]);
return_code for_first(int array[SIZE_OF_STATIC_ARRAY], int right_border, int left_border);
return_code for_second(int* dynamic_array_A, int* dynamic_array_B, int* dynamic_array_C);


#endif