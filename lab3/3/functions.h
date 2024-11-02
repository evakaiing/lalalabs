#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define EPS 1e-9


typedef enum return_code {
    OK,
    INVALID_INPUT,
    MEMORY_ALLOCATION_ERROR,
    OVERFLOW_ERROR,
    DEREFERENCING_NULL_POINTER_ATTEMPT,
    FILE_PATH_LENGTH_ERROR,
    FILE_OPENNING_ERROR
} return_code;

typedef struct Employee {
    unsigned int id;
    char name[100];
    char last_name[100];
    double wages;
} Employee;

return_code input_handling(const char* argv);
return_code upload_info(Employee** info, FILE* input_file, int* size);
int comp_for_d(const void *a, const void *b);
int comp_for_a(const void *a, const void *b);

