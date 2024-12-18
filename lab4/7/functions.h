#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    int value;
} MemoryCell;

int compareMemoryCells(const void *a, const void *b);
void sortMemoryCells(MemoryCell *cells, int count);
MemoryCell* findMemoryCell(MemoryCell *cells, int count, char *name);
void addOrUpdateMemoryCell(MemoryCell **cells, int *count, char *name, int value);
