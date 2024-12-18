#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <ctype.h>

#define MAX_ARRAYS 26

typedef struct {
    char name;
    int *elements;
    size_t size;
} IntArray;

typedef enum {
    OK,
    INVALID_INPUT,
    MEMORY_ALLOCATION_ERROR,
    DEREFERENCING_NULL_POINTER_ATTEMPT,
    FILE_OPENNING_ERROR,
    ERROR_OVERFLOW
} return_code;


void init_arrays(IntArray *arrays) {
    for (int i = 0; i < MAX_ARRAYS; i++) {
        arrays[i].name = 'A' + i;
        arrays[i].elements = NULL;
        arrays[i].size = 0;
    }
}

return_code load_array(IntArray* arrays, char array_name, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        return FILE_OPENNING_ERROR;
    }

    char buf[BUFSIZ];
    size_t capacity = 10, size = 0;
    int *elements = malloc(capacity * sizeof(int));
    
    while (fscanf(file, "%s", buf) == 1) {
        if (size >= capacity) {
            capacity *= 2;
            int* tmp = realloc(elements, capacity * sizeof(int));
            if (!tmp) {
                return MEMORY_ALLOCATION_ERROR;
            }
            elements = tmp;
        }

        char* end_ptr;
        long in_int = strtol(buf, &end_ptr, 10);
        if (*end_ptr != '\0') {
            printf("there is some string :(");
            return INVALID_INPUT;
        }
        if (in_int > INT_MAX || in_int < INT_MIN) {
            printf("there is overflow\n");
            return ERROR_OVERFLOW;
        }
        elements[size++] = in_int;
    }
    
    fclose(file);
    arrays[toupper(array_name) - 'A'].elements = elements;
    arrays[toupper(array_name) - 'A'].size = size;
    return OK;
}

return_code save_array(IntArray* arrays, char array_name, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        return FILE_OPENNING_ERROR;
    }
    
    IntArray array = arrays[toupper(array_name) - 'A'];
    for (size_t i = 0; i < array.size; i++) {
        fprintf(file, "%d\n", array.elements[i]);
    }
    
    fclose(file);
}

return_code rand_array(IntArray* arrays, char array_name, int count, int lb, int rb) {
    srand(time(NULL));
    int *elements = malloc(count * sizeof(int));
    if (!elements) {
        return MEMORY_ALLOCATION_ERROR;
    }
    for (int i = 0; i < count; i++) {
        elements[i] = lb + rand() % (rb - lb + 1);
    }
    arrays[toupper(array_name) - 'A'].elements = elements;
    arrays[toupper(array_name) - 'A'].size = count;
}

return_code concat_arrays(IntArray* arrays, char array_name1, char array_name2) {
    IntArray *array1 = &arrays[array_name1 - 'A'];
    IntArray *array2 = &arrays[array_name2 - 'A'];
    int* tmp = NULL;
    tmp = realloc(array1->elements, (array1->size + array2->size) * sizeof(int));
    if (!tmp) {
        return MEMORY_ALLOCATION_ERROR;
    }
    array1->elements = tmp;
    memcpy(array1->elements + array1->size, array2->elements, array2->size * sizeof(int));
    array1->size += array2->size;
}

void print_element(IntArray* arrays, char array_name, size_t index) {
    IntArray array = arrays[toupper(array_name) - 'A'];
    if (index < array.size) {
        printf("%d\n", array.elements[index]);
    } else {
        printf("index out of range\n");
    }
}

void print_range(IntArray* arrays, char array_name, size_t start, size_t end) {
    IntArray array = arrays[toupper(array_name) - 'A'];
    if (start < array.size && end < array.size && start <= end) {
        for (size_t i = start; i <= end; i++) {
            printf("%d ", array.elements[i]);
        }
        printf("\n");
    } else {
        printf("incorrect range\n");
    }
}

void print_all(IntArray* arrays, char array_name) {
    IntArray array = arrays[toupper(array_name) - 'A'];
    for (size_t i = 0; i < array.size; i++) {
        printf("%d ", array.elements[i]);
    }
    printf("\n");
}

void free_array(IntArray* arrays, char array_name) {
    IntArray *array = &arrays[toupper(array_name) - 'A'];
    free(array->elements);
    array->elements = NULL;
    array->size = 0;
}


return_code remove_elements(IntArray* arrays, char array_name, size_t start, size_t count) {
    IntArray *array = &arrays[toupper(array_name) - 'A'];
    if (start + count > array->size) {
        printf("index out of range\n");
        return INVALID_INPUT;
    }

    size_t new_size = array->size - count;
    int *new_elements = malloc(new_size * sizeof(int));
    if (!new_elements) {
        return MEMORY_ALLOCATION_ERROR;
    }
    memcpy(new_elements, array->elements, start * sizeof(int)); 
    memcpy(new_elements + start, array->elements + start + count, (array->size - start - count) * sizeof(int)); // Копирование после удаленных элементов

    free(array->elements);
    array->elements = new_elements;
    array->size = new_size;
}

return_code copy_elements(IntArray* arrays, char source_array, size_t start, size_t end, char dest_array) {
    IntArray *src = &arrays[toupper(source_array) - 'A'];
    if (start > end || end >= src->size) {
        printf("index out of range\n");
        return INVALID_INPUT;
    }

    size_t count = end - start + 1;
    IntArray* dest = &arrays[toupper(dest_array) - 'A'];
    free(dest->elements); 
    dest->elements = malloc(count * sizeof(int));
    if (!dest->elements) {
        return MEMORY_ALLOCATION_ERROR;
    }
    memcpy(dest->elements, src->elements + start, count * sizeof(int));
    dest->size = count;
}

int compare_asc(const void *a, const void *b) {
    int arg1 = *(const int *)a;
    int arg2 = *(const int *)b;
    return (arg1 > arg2) - (arg1 < arg2);
}

int compare_desc(const void *a, const void *b) {
    int arg1 = *(const int *)a;
    int arg2 = *(const int *)b;
    return (arg2 > arg1) - (arg2 < arg1);
}

void sort_array(IntArray *array, char direction) {
    if (direction == '+') {
        qsort(array->elements, array->size, sizeof(int), compare_asc);
    } else if (direction == '-') {
        qsort(array->elements, array->size, sizeof(int), compare_desc);
    }
}

void shuffle_array(IntArray *array) {
    for (size_t i = array->size - 1; i > 0; i--) {
        size_t j = rand() % (i + 1);
        int temp = array->elements[i];
        array->elements[i] = array->elements[j];
        array->elements[j] = temp;
    }
}

return_code print_stats(IntArray *arrays, char array_name) {
    IntArray *array = &arrays[toupper(array_name) - 'A'];
    if (!array)
        return MEMORY_ALLOCATION_ERROR;

    if (array->size == 0) {
        printf("Stats: array is empty\n");
        return OK;
    }

    int *copy_data = (int*)malloc(sizeof(int) * array->size);
    if (!copy_data) {
        return MEMORY_ALLOCATION_ERROR;
    }
    memcpy(copy_data, array->elements, sizeof(int) * array->size);
    qsort(copy_data, array->size, sizeof(int), compare_asc);

    int count = 1, most_freq_num = copy_data[0], max_count = 1;
    double avg = 0, deviation = 0, max_deviation = 0;

    for (size_t i = 0; i < array->size; ++i) {
        avg += copy_data[i];
        if (i > 0 && copy_data[i] == copy_data[i - 1]) {
            count++;
        } else {
            if (count > max_count) {
                max_count = count;
                most_freq_num = copy_data[i - 1];
            }
            count = 1; 
        }
    }

    if (count > max_count) {
        max_count = count;
        most_freq_num = copy_data[array->size - 1];
    }

    avg /= array->size;

    for (size_t i = 0; i < array->size; ++i) {
        deviation = fabs(copy_data[i] - avg);
        if (deviation > max_deviation) {
            max_deviation = deviation;
        }
    }

    printf("Stats %c:\n", array->name);
    printf("Array size: %zu\n", array->size);
    printf("Min: %d; Max: %d\n", copy_data[0], copy_data[array->size - 1]);
    printf("The most frequent: %d, number of occurrences %d\n", most_freq_num, max_count);
    printf("Avg: %.2lf; Max deviation: %.2lf\n", avg, max_deviation);
    printf("\n");

    free(copy_data);
    return OK;
}


void trim_command(char *cmd) {
    char *end = cmd + strlen(cmd) - 1;
    while (end > cmd && isspace((unsigned char)*end)) {
        *end = '\0';
        end--;
    }

    if (*end == ';') {
        *end = '\0';
    }
}


void execute_command(IntArray *arrays, char *command) {
    trim_command(command);
    char cmd[BUFSIZ];
    char array_name, array_name2;
    char filename[PATH_MAX];
    int index, index2, count;
    char dir;
    if (sscanf(command, "Load %c, %s", &array_name, filename) == 2) {
            printf("loading\n");
            return_code rc = load_array(arrays, array_name, filename);
            if (rc == INVALID_INPUT) {
                printf("invalid input\n");
            } else if (rc == MEMORY_ALLOCATION_ERROR) {
                printf("memory allocation error\n");
            } else if (rc == FILE_OPENNING_ERROR) {
                printf("file openning error\n");
            }
        } else if (sscanf(command, "Save %c, %s", &array_name, filename) == 2) {
            printf("saving\n");
            return_code rc = save_array(arrays, array_name, filename);
            if (rc == INVALID_INPUT) {
                printf("invalid input\n");
            } else if (rc == MEMORY_ALLOCATION_ERROR) {
                printf("memory allocation error\n");
            } else if (rc == FILE_OPENNING_ERROR) {
                printf("file openning error\n");
            }
        } else if (sscanf(command, "Rand %c, %d, %d, %d", &array_name, &count, &index, &index2) == 4) {
            printf("rand\n");
            return_code rc = rand_array(arrays, array_name, count, index, index2);
            if (rc == INVALID_INPUT) {
                printf("invalid input\n");
            } else if (rc == MEMORY_ALLOCATION_ERROR) {
                printf("memory allocation error\n");
            } else if (rc == FILE_OPENNING_ERROR) {
                printf("file openning error\n");
            }
        } else if (sscanf(command, "Concat %c, %c", &array_name, &array_name2) == 2) {
            printf("concat\n");
            return_code rc = concat_arrays(arrays, array_name, array_name2);
            if (rc == INVALID_INPUT) {
                printf("invalid input\n");
            } else if (rc == MEMORY_ALLOCATION_ERROR) {
                printf("memory allocation error\n");
            } else if (rc == FILE_OPENNING_ERROR) {
                printf("file openning error\n");
            }
        } else if (sscanf(command, "Sort %c%c", &array_name, &dir) == 2) {
            printf("sort\n");
            sort_array(&arrays[toupper(array_name) - 'A'], dir);
        } else if (sscanf(command, "Shuffle %c", &array_name) == 1) {
            printf("shuffle\n");
            shuffle_array(&arrays[toupper(array_name) - 'A']);
        } else if (sscanf(command, "Print %c, all", &array_name) == 1) {
            print_all(arrays, array_name);
        } else if (sscanf(command, "Print %c, %d", &array_name, &index) == 2) {
            print_element(arrays, array_name, index);
        } else if (sscanf(command, "Print %c, %d, %d", &array_name, &index, &index2) == 3) {
            print_range(arrays, array_name, index, index2);
        } else if (sscanf(command, "Free %c", &array_name) == 1) {
           free_array(arrays, array_name);
        } else if (sscanf(command, "Remove %c, %d, %d", &array_name, &index, &index2) == 3) {
            printf("removing\n");
            return_code rc = remove_elements(arrays, array_name, index, index2);
            if (rc == INVALID_INPUT) {
                printf("invalid input\n");
            } else if (rc == MEMORY_ALLOCATION_ERROR) {
                printf("memory allocation error\n");
            } else if (rc == FILE_OPENNING_ERROR) {
                printf("file openning error\n");
            }
        } else if (sscanf(command, "Copy %c, %d, %d, %c", &array_name, &index, &index2, &array_name2) == 4) {
            printf("copy\n");
            return_code rc = copy_elements(arrays, array_name, index, index2, array_name2);
            if (rc == INVALID_INPUT) {
                printf("invalid input\n");
            } else if (rc == MEMORY_ALLOCATION_ERROR) {
                printf("memory allocation error\n");
            } else if (rc == FILE_OPENNING_ERROR) {
                printf("file openning error\n");
            }
        } else if (sscanf(command, "Stats %c", &array_name) == 1) {
            return_code rc = print_stats(arrays, array_name);
            if (rc == INVALID_INPUT) {
                printf("invalid input\n");
            } else if (rc == MEMORY_ALLOCATION_ERROR) {
                printf("memory allocation error\n");
            } else if (rc == FILE_OPENNING_ERROR) {
                printf("file openning error\n");
            }
        } else {
            printf("Unknown command\n");
        }
}


