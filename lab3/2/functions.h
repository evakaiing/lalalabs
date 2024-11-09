#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include "stdio.h"
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#include <stdarg.h>
#include <math.h>
#include <string.h>

typedef enum return_code {
    OK,
    INVALID_INPUT,
    MEMORY_ALLOCATION_ERROR,
    OVERFLOW_ERROR,
    DEREFERENCING_NULL_POINTER_ATTEMPT,
    FILE_PATH_LENGTH_ERROR,
    FILE_OPENNING_ERROR
} return_code;

typedef struct Vector
{
    double* data;
    int n;
} Vector;

typedef double (*norm_t)(Vector*, void *);

void delete_vector_arr(Vector** arr, size_t size);
double a_norm(Vector*vec, void *args);
double inf_norm(Vector*vec, void *args);
double p_norm(Vector*vec, void *args);
return_code search_longest_vectors(Vector** res, size_t* count_res, size_t vectors_cnt, size_t count_norms, ...);

#endif