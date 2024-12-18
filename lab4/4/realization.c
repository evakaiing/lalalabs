#include "functions.h"

#include "functions.h"

return_code string_to_long(const char *str, long *result, int base) {
    char *endinp;
    if (!result || !str) {
        return MEMORY_ALLOCATION_ERROR;
    }
    *result = strtol(str, &endinp, base);
    if (*result == LONG_MAX || *result == LONG_MIN) {
        return INVALID_INPUT;
    }
    if (*endinp != '\0') {
        return INVALID_INPUT;
    }
    return OK;
}

return_code validate_file(char **argv) {
    if (!argv) {
        return INVALID_INPUT;
    }
    char full_path_1[BUFSIZ], full_path_2[BUFSIZ];
    full_path_2[0] = '\0';
    if (!realpath(argv[1], full_path_1)) {
        return INVALID_INPUT;
    }
    realpath(argv[3], full_path_2);
    if (!strcmp(full_path_1, full_path_2)) {
        return INVALID_INPUT;
    }
    return OK;
}

return_code gorner_scheme(long num, long base, char *result) {
    if (!result) {
        return DEREFERENCING_NULL_POINTER_ATTEMPT;
    }
    int i, flag_minus = 0;
    char temp;
    int len_result = 0;
    if (num == 0) {
        result[0] = '0';
        result[1] = '\0';
        return OK;
    }
    if (num < 0) {
        num = labs(num);
        flag_minus = 1;
    }
    while (num) {
        result[len_result++] = ((num % base > 9) ? (num % base - 10 + 'A') : (num % base + '0'));
        num /= base;
    }
    if (flag_minus) {
        result[len_result++] = '-';
    }
    for (i = 0; i < len_result / 2; i++) {
        temp = result[i];
        result[i] = result[len_result - 1 - i];
        result[len_result - 1 - i] = temp;
    }
    result[len_result] = '\000';
    return OK;
}

return_code convert_to_bitstr(long num, char *result) {
    size_t i;
    if (!result) {
        return DEREFERENCING_NULL_POINTER_ATTEMPT;
    }

    for (i = 0; i < sizeof(long) * 8; ++i) {
        result[i] = ((1ul << i) & num) ? '1' : '0';
    }
    result[i] = '\0';
    return OK;
}

return_code string_init(String *string) {
    if (!string) {
        return DEREFERENCING_NULL_POINTER_ATTEMPT;
    }
    string->capacity = 1;
    string->len = 0;
    if (!(string->arr = (char *)malloc(sizeof(char)))) {
        return MEMORY_ALLOCATION_ERROR;
    }
    string->arr[0] = '\0';
    return OK;
}

return_code delete_string_content(String *string) {
    if (!string) {
        return DEREFERENCING_NULL_POINTER_ATTEMPT;
    }
    free(string->arr);
    string->arr = NULL;
    string->len = 0;
    string->capacity = 0;
    return OK;
}

int string_compare(const String *str_1, const String *str_2) {
    if (str_1->len != str_2->len) {
        return str_1->len - str_2->len;
    }
    return strcmp(str_1->arr, str_2->arr);
}

int is_equal(const String *str_1, const String *str_2) {
    return strcmp(str_1->arr, str_2->arr) == 0;
}

return_code string_dup(String *dest, const String *source) {
    if (!dest || !source) {
        return DEREFERENCING_NULL_POINTER_ATTEMPT;
    }

    dest->capacity = source->capacity;
    dest->len = source->len;
    if (!source->arr) {
        dest->arr = NULL;
        return OK;
    }
    dest->arr = (char *)malloc(source->capacity * sizeof(char));
    if (!dest->arr) {
        return MEMORY_ALLOCATION_ERROR;
    }
    strcpy(dest->arr, source->arr);
    return OK;
}

String *string_destroy(String *str) {
    if (!str) {
        return NULL;
    }
    free(str->arr);
    free(str);
    return NULL;
}

return_code add_char_to_string(String *str, char ch) {
    if (!str) {
        return DEREFERENCING_NULL_POINTER_ATTEMPT;
    }
    if (str->capacity == 0) {
        if (string_init(str)) {
            return MEMORY_ALLOCATION_ERROR;
        }
    }
    if (str->capacity == str->len + 1) {
        char *for_realloc;
        str->capacity *= 2;
        for_realloc = (char *)realloc(str->arr, str->capacity * sizeof(char));
        if (!for_realloc) {
            return MEMORY_ALLOCATION_ERROR;
        }
        str->arr = for_realloc;
    }
    str->arr[str->len++] = ch;
    str->arr[str->len] = '\0';
    return OK;
}

return_code read_word(String *str) {
    char ch;
    if (!str) {
        return DEREFERENCING_NULL_POINTER_ATTEMPT;
    }

    if (string_init(str) == MEMORY_ALLOCATION_ERROR) {
        return MEMORY_ALLOCATION_ERROR;
    }

    ch = getchar();
    while (ch != EOF && !isspace(ch)) {
        if (add_char_to_string(str, ch)) {
            return MEMORY_ALLOCATION_ERROR;
        }
        ch = getchar();
    }
    return OK;
}

return_code read_string(FILE *input, String *str) {
    char ch;
    if (!input || !str) {
        return DEREFERENCING_NULL_POINTER_ATTEMPT;
    }

    if (string_init(str) == MEMORY_ALLOCATION_ERROR) {
        return MEMORY_ALLOCATION_ERROR;
    }

    ch = getc(input);

    while (ch != EOF && ch != ';') {
        if (ch == '%') {
            while (ch != EOF && ch != '\n') {
                ch = getc(input);
            }
        } else if (ch == '{') {
            while (ch != EOF && ch != '}') {
                ch = getc(input);
            }
            if (ch == EOF) {
                return INVALID_INPUT;
            }
        } else if (ch != EOF && !isspace(ch)) {
            ch = toupper(ch);
            if (add_char_to_string(str, ch)) {
                return MEMORY_ALLOCATION_ERROR;
            }
        }
        ch = getc(input);
    }
    if (ch != EOF) {
        if (add_char_to_string(str, ch)) {
            return MEMORY_ALLOCATION_ERROR;
        }
    }
    return OK;
}

return_code read_vector(Vector *vector, const char *value, long base) {
    if (!vector) {
        return DEREFERENCING_NULL_POINTER_ATTEMPT;
    }

    vector->init = 1;
    if (string_to_long(value, &vector->value, (int)base)) {
        return INVALID_INPUT;
    }
    return OK;
}

return_code calculate_operation(Vector *a, Vector *b, const char *op, Vector *result) {
    if (!a || !b || !result) {
        return DEREFERENCING_NULL_POINTER_ATTEMPT;
    }

    if (!a->init || !b->init) {
        return DEREFERENCING_NULL_POINTER_ATTEMPT;
    }

    result->init = 1;
    if (!strcmp(op, "+")) {
        result->value = a->value | b->value;
    } else if (!strcmp(op, "&")) {
        result->value = a->value & b->value;
    } else if (!strcmp(op, "->")) {
        result->value = (!a->value) | b->value;
    } else if (!strcmp(op, "<-")) {
        result->value = a->value | (!b->value);
    } else if (!strcmp(op, "~")) {
        result->value = ((!a->value) | b->value) & (a->value | (!b->value));
    } else if (!strcmp(op, "<>")) {
        result->value = a->value ^ b->value;
    } else if (!strcmp(op, "+>")) {
        result->value = a->value & (!b->value);
    } else if (!strcmp(op, "?")) {
        result->value = (!a->value) | (!b->value);
    } else if (!strcmp(op, "!")) {
        result->value = (!a->value) & (!b->value);
    }
    return OK;
}

return_code init_vectors_arr(Vector *v_arr) {
    if (!v_arr) {
        return MEMORY_ALLOCATION_ERROR;
    }

    for (int i = 0; i < COUNT_VECTORS; ++i) {
        v_arr[i].init = 0;
        v_arr[i].name = 'A' + i;
        v_arr[i].value = 0;
    }
    return OK;
}

void write_message(const char *msg, FILE *out, ...) {
    va_list args;
    if (!msg) {
        return;
    }

    va_start(args, out);
    if (out) {
        vfprintf(out, msg, args);
    } else {
        vprintf(msg, args);
    }
    va_end(args);
}