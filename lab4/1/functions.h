#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

#define INITIAL_HASHSIZE 128
#define BASE 62

typedef struct Node {
    char *key;
    char *value;
    struct Node *next;
} Node;

typedef struct {
    Node** buckets;
    int* chain_lengths;
    int size;
    int num_items;
    int max_chain_length;
    int min_chain_length;
} HashTable;

typedef enum {
    OK,
    INVALID_INPUT,
    MEMORY_ALLOCATION_ERROR,
    DEREFERENCING_NULL_POINTER_ATTEMPT,
    FILE_OPENNING_ERROR
} return_code;

HashTable *create_hashmap(int size);
unsigned long hash(char *str, int size);
return_code insert(HashTable *ht, char *key, char *value);
char *find(HashTable *ht, char *key);
void free_hashmap(HashTable *ht);
return_code process_file(const char *filename, HashTable *ht);
return_code rebuild_hashmap(HashTable **ht);
int get_chain_length(Node *head);
