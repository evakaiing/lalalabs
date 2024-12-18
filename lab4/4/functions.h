#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include "stdio.h"
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#include <stdarg.h>
#include <math.h>
#include <string.h>
#include <time.h>

#define COUNT_VECTORS 26

typedef enum {
    OK,
    INVALID_INPUT,
    MEMORY_ALLOCATION_ERROR,
    DEREFERENCING_NULL_POINTER_ATTEMPT,
    FILE_OPENNING_ERROR,
    ERROR_OVERFLOW
} return_code;


typedef struct String {
    char *arr;
    size_t capacity;
    size_t len;
} String;

typedef struct Vector {
    char name;
    long value;
    char init;
} Vector;

return_code read_string(FILE *input, String *str);
return_code delete_string_content(String *string);
return_code add_char_to_string(String *str, char ch);
return_code string_init(String *string);
return_code init_vectors_arr(Vector *v_arr);
void write_message(const char *msg, FILE *out, ...);
return_code read_vector(Vector *vector, const char *value, long base);
return_code read_word(String *str);
return_code string_to_long(const char *str, long *result, int base);
return_code gorner_scheme(long num, long base, char *result);
return_code calculate_operation(Vector *a, Vector *b, const char *op, Vector *result);
return_code convert_to_bitstr(long num, char *result);
return_code validate_file(char **argv);

#endif