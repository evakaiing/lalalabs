#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#define BUFFER_SIZE 1024 

typedef enum return_code {
    OK,
    INVALID_INPUT,
    MEMORY_ALLOCATION_ERROR,
    OVERFLOW_ERROR, 
    FILE_OPENNING_ERROR
} return_code;

return_code str_str(char* str, char* sub_str, int** lines, int** entrys, int* count_of_entrys, int start_line) {
    char* p_str = str;
    char* p_sub_str;

    *count_of_entrys = 0;

    int capacity = 2;
    int* temp_entryes;
    int* temp_lines;
    int current_line = start_line; 

    *entrys = (int*)malloc(sizeof(int) * capacity);
    *lines = (int*)malloc(sizeof(int) * capacity);
    if (*entrys == NULL || *lines == NULL) {
        return MEMORY_ALLOCATION_ERROR;
    }

    while (*p_str != '\0') {
        if (*p_str == '\n') {
            current_line++;
        }

        char* p_temp = p_str;
        p_sub_str = sub_str;

        while (*p_temp == *p_sub_str && *p_sub_str != '\0') {
            p_temp++;
            p_sub_str++;
        }

        if (*p_sub_str == '\0') { 
            if (*count_of_entrys == capacity) {
                capacity *= 2;
                temp_entryes = (int*)realloc(*entrys, capacity * sizeof(int));
                temp_lines = (int*)realloc(*lines, capacity * sizeof(int));
                if (!temp_entryes || !temp_lines) {
                    free(*entrys);
                    free(*lines);
                    return MEMORY_ALLOCATION_ERROR;
                }
                *entrys = temp_entryes;
                *lines = temp_lines;
            }

            (*entrys)[*count_of_entrys] = p_str - str;
            (*lines)[*count_of_entrys] = current_line;
            (*count_of_entrys)++;
        }
        ++p_str;
    }
    return OK;
}

return_code proccess_file(const char* filename, char* substr) {
    FILE* file;
    char buffer[BUFFER_SIZE + 1];
    int line_number = 1;
    int* entrys = NULL;
    int* lines = NULL;
    int count_of_entrys = 0;
    int remaining_bytes = 0;  
    char remaining_symbols[100] = {0};

    if ((file = fopen(filename, "r")) == NULL) {
        return FILE_OPENNING_ERROR;
    }

    while (!feof(file)) {
        int read_size = fread(buffer + remaining_bytes, 1, BUFFER_SIZE - remaining_bytes, file);
        buffer[read_size + remaining_bytes] = '\0';  

        if (remaining_bytes > 0) {
            memcpy(buffer, remaining_symbols, remaining_bytes);
        }

        return_code status_of_finding = str_str(buffer, substr, &lines, &entrys, &count_of_entrys, line_number);
        if (status_of_finding == MEMORY_ALLOCATION_ERROR) {
            printf("Memory allocation error\n");
            fclose(file);
            return MEMORY_ALLOCATION_ERROR;
        }

        for (int i = 0; i < count_of_entrys; i++) {
            printf("Substr found on line %d, position %d in file %s\n", lines[i], entrys[i] + 1, filename);
        }

        for (int i = 0; i < read_size + remaining_bytes; i++) {
            if (buffer[i] == '\n') {
                line_number++;
            }
        }
        // for example substr - ab\na  we're copy the last 3 bytes 
        if (read_size >= strlen(substr)) {
            remaining_bytes = strlen(substr) - 1;
            memcpy(remaining_symbols, buffer + read_size + remaining_bytes - strlen(substr), remaining_bytes);
        } else {
            remaining_bytes = read_size;  
            memcpy(remaining_symbols, buffer, remaining_bytes);
        }
    }

    free(entrys);
    free(lines);
    fclose(file);

    return OK;
}

return_code find_substr_in_files(char* substr, ...) {
    char* filename;
    va_list files;
    va_start(files, substr);

    while ((filename = va_arg(files, char*)) != NULL) {
        return_code status_of_proccess_file = proccess_file(filename, substr);
        if (status_of_proccess_file == FILE_OPENNING_ERROR) {
            printf("Error opening file: %s\n", filename);
            va_end(files);
            return FILE_OPENNING_ERROR;
        } else if (status_of_proccess_file == MEMORY_ALLOCATION_ERROR) {
            printf("Memory allocation error\n");
            va_end(files);
            return MEMORY_ALLOCATION_ERROR;
        }
    }

    va_end(files);
    return OK;
}

int main() {
    char* substr = "abaa";
    return_code status = find_substr_in_files(substr, "file1.txt", "file2.txt", NULL);
    if (status == FILE_OPENNING_ERROR) {
        printf("Error file opening\n");
        return FILE_OPENNING_ERROR;
    } else if (status == MEMORY_ALLOCATION_ERROR) {
        printf("Error in memory allocation\n");
        return MEMORY_ALLOCATION_ERROR;
    }
    return OK;
}
