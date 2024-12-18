#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum {
    OK,
    INVALID_INPUT,
    MEMORY_ALLOCATION_ERROR,
    DEREFERENCING_NULL_POINTER_ATTEMPT,
    FILE_OPENNING_ERROR,
    ERROR_OVERFLOW,
    DIVISION_BY_ZERO
} return_code;


typedef struct {
    char *name;
    int value;
} MemoryCell;

int compareMemoryCells(const void *a, const void *b) {
    const MemoryCell *cell1 = (const MemoryCell *)a;
    const MemoryCell *cell2 = (const MemoryCell *)b;
    return strcmp(cell1->name, cell2->name);
}

void sortMemoryCells(MemoryCell *cells, int count) {
    qsort(cells, count, sizeof(MemoryCell), compareMemoryCells);
}

MemoryCell* findMemoryCell(MemoryCell *cells, int count, const char *name) {
    int low = 0, high = count - 1, mid;
    while (low <= high) {
        mid = low + (high - low) / 2;
        int cmp = strcmp(cells[mid].name, name);
        if (cmp < 0) {
            low = mid + 1;
        } else if (cmp > 0) {
            high = mid - 1;
        } else {
            return &cells[mid]; 
        }
    }
    return NULL; 
}


return_code addOrUpdateMemoryCell(MemoryCell **cells, int *count, char *name, int value) {
    MemoryCell *cell = findMemoryCell(*cells, *count, name);
    if (cell) {
        cell->value = value;
    } else {
        MemoryCell* tmp;
        tmp = realloc(*cells, (*count + 1) * sizeof(MemoryCell));
        if (!tmp) {
            return MEMORY_ALLOCATION_ERROR;
        }
        *cells = tmp;
        (*cells)[*count].name = strdup(name);
        (*cells)[*count].value = value;
        (*count)++;
        sortMemoryCells(*cells, *count);
    }
}

void freeMemoryCells(MemoryCell *cells, int count) {
    for (int i = 0; i < count; i++) {
        free(cells[i].name);
    }
    free(cells);
}

return_code evaluateExpression(MemoryCell *cells, int count, char *expr, int* result) {
    char *ptr = expr;
    int value = 0;
    int tmp = 0;
    char op = '+';  

    while (*ptr) {
        while (*ptr == ' ') ptr++; 

        char *nextPart = ptr;
        while (*nextPart && !strchr("+-*/%", *nextPart)) nextPart++;
        char currentOp = *nextPart;
        *nextPart = '\0';

        if (isdigit(*ptr) || (*ptr == '-' && isdigit(*(ptr + 1)))) {
            tmp = atoi(ptr);
        } else {
            MemoryCell *cell = findMemoryCell(cells, count, ptr);
            if (!cell) {
                printf("not finded\n");
                return INVALID_INPUT;
            }
            tmp = cell->value;
        }

        switch (op) {
            case '+': value += tmp; break;
            case '-': value -= tmp; break;
            case '*': value *= tmp; break;
            case '/':
                if (tmp == 0) {
                    return DIVISION_BY_ZERO;
                }
                value /= tmp;
                break;
            case '%':
                if (tmp == 0) {
                    return DIVISION_BY_ZERO;
                }
                value %= tmp;
                break;
        }

        op = currentOp;
        ptr = nextPart + 1;
    }

    *result = value;
    return OK;
}


void trim(char *str) {
    char *end, *start = str;
    while (isspace((unsigned char)*start)) start++;
    if (*start == 0) {
        *str = 0;
        return;
    }
    end = start + strlen(start) - 1;
    while (end > start && isspace((unsigned char)*end)) end--;
    *(end + 1) = 0;
    memmove(str, start, end + 1 - start);
}

void executeLine(MemoryCell **cells, int *count, char *line) {
    trim(line); 
    if (line[0] == '\0') return; 

    char *lhs, *rhs;
    if (strstr(line, "print") != NULL) {
        char *token = strtok(line, " ");
        token = strtok(NULL, " \n;");
        if (token) {
            MemoryCell *cell = findMemoryCell(*cells, *count, token);
            if (cell) {
                printf("%s = %d\n", cell->name, cell->value);
            } else {
                printf("undefined\n");
                return;
            }
        } else {
            for (int i = 0; i < *count; i++) {
                printf("%s = %d\n", (*cells)[i].name, (*cells)[i].value);
            }
        }
    } else {
        lhs = strtok(line, "=");
        rhs = strtok(NULL, ";\n");
        if (strchr(rhs, '+') || strchr(rhs, '-') || strchr(rhs, '*') || strchr(rhs, '/') || strchr(rhs, '%')) {
            int result = 0;
            return_code rc = evaluateExpression(*cells, *count, rhs, &result);
            if (rc == DIVISION_BY_ZERO) {
                printf("divisiob by zero\n");
                return;
            }
            addOrUpdateMemoryCell(cells, count, lhs, result);
        } else {
            addOrUpdateMemoryCell(cells, count, lhs, atoi(rhs));
        }
    }
}


int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return INVALID_INPUT;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        printf("Error opening file");
        return FILE_OPENNING_ERROR;
    }

    MemoryCell *cells = NULL;
    int cellCount = 0;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, file)) != -1) {
        if (line[read - 1] == '\n') {
            line[read - 1] = '\0';
        }
        executeLine(&cells, &cellCount, line);
    }

    free(line);
    fclose(file);
    freeMemoryCells(cells, cellCount);
    return 0;
}
