#include "functions.h"

HashTable* create_hashmap(int size) {
    HashTable *ht = malloc(sizeof(HashTable));
    if (!ht) return NULL;

    ht->buckets = calloc(size, sizeof(Node*));
    ht->chain_lengths = calloc(size, sizeof(int));
    ht->size = size;
    ht->num_items = 0;
    ht->max_chain_length = 0;
    ht->min_chain_length = INT_MAX;

    if (!ht->buckets || !ht->chain_lengths) {
        free(ht->buckets);
        free(ht->chain_lengths);
        free(ht);
        return NULL;
    }

    return ht;
}
char *remove_carriage_returns(char *str) {
    char *src = str, *dst = str;
    while (*src) {
        if (*src != '\r') {
            *dst++ = *src;
        }
        src++;
    }
    *dst = '\0'; 
    return str;
}

unsigned long hash(char *str, int size) {
    unsigned long h = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        char c = str[i];
        if (isdigit(c))
            h = h * BASE + (c - '0');
        else if (isupper(c))
            h = h * BASE + (c - 'A' + 10);
        else if (islower(c))
            h = h * BASE + (c - 'a' + 36);
    }
    return h % size;
}

return_code insert(HashTable *ht, char *key, char *value) {
    unsigned long idx = hash(key, ht->size);
    Node *new_node = malloc(sizeof(Node));
    if (!new_node) return MEMORY_ALLOCATION_ERROR; 

    new_node->key = strdup(key);
    new_node->value = strdup(value);
    new_node->next = ht->buckets[idx];
    ht->buckets[idx] = new_node;
    ht->num_items++;
    ht->chain_lengths[idx]++;

    if (ht->chain_lengths[idx] > ht->max_chain_length) {
        ht->max_chain_length = ht->chain_lengths[idx];
    }
    if (ht->min_chain_length == INT_MAX || ht->chain_lengths[idx] < ht->min_chain_length) {
        ht->min_chain_length = ht->chain_lengths[idx];
    }

    if (ht->max_chain_length >= 2 * ht->min_chain_length && ht->num_items > 10) {
        rebuild_hashmap(&ht);
    }
}

return_code rebuild_hashmap(HashTable** ht) {
    int new_size = (*ht)->size * 2;  
    HashTable *new_ht = create_hashmap(new_size);
    if (!new_ht) return MEMORY_ALLOCATION_ERROR; 

    for (int i = 0; i < (*ht)->size; i++) {
        Node *current = (*ht)->buckets[i];
        while (current != NULL) {
            insert(new_ht, current->key, current->value);
            current = current->next;
        }
    }

    free_hashmap(*ht);
    *ht = new_ht;
}


char *find(HashTable *ht, char *key) {
    unsigned long idx = hash(key, ht->size);
    for (Node *current = ht->buckets[idx]; current != NULL; current = current->next) {
        if (strcmp(current->key, key) == 0) {
            return current->value;
        }
    }
    return NULL;
}

void free_hashmap(HashTable* ht) {
    for (int i = 0; i < ht->size; i++) {
        Node *current = ht->buckets[i];
        while (current) {
            Node *temp = current;
            current = current->next;
            free(temp->key);
            free(temp->value);
            free(temp);
        }
    }
    free(ht->buckets);
    free(ht->chain_lengths);
    free(ht);
}


return_code process_file(const char *filename, HashTable *ht) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        return FILE_OPENNING_ERROR;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "#define", 7) == 0) {
            char *key = strtok(line + 8, " ");
            char *value = strtok(NULL, "\n");
            if (key && value) {
                insert(ht, key, value);
            }
        } else {
            char *result = strdup(line);
            for (int i = 0; i < ht->size; i++) {
                for (Node *Node = ht->buckets[i]; Node != NULL; Node = Node->next) {
                    char *pos;
                    while ((pos = strstr(result, Node->key)) != NULL) {
                        int len = strlen(result);
                        char *new_result = malloc(len + strlen(Node->value) - strlen(Node->key) + 1);
                        if (!new_result) {
                            return MEMORY_ALLOCATION_ERROR;
                        }
                        strncpy(new_result, result, pos - result);
                        strcpy(new_result + (pos - result), Node->value);
                        strcpy(new_result + (pos - result) + strlen(Node->value), pos + strlen(Node->key));
                        remove_carriage_returns(new_result);
                        free(result);
                        result = new_result;
                    }
                }
            }
            printf("%s", result);
            free(result);
        }
    }

    fclose(file);
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file_path>\n", argv[0]);
        return 1;
    }

    HashTable *ht = create_hashmap(INITIAL_HASHSIZE);
    process_file(argv[1], ht);
    free_hashmap(ht);
    return 0;
}
