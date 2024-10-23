#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

typedef enum return_code {
    OK,
    INVALID_INPUT,
    MEMORY_ALLOCATION_ERROR,
    FILE_OPENNING_ERROR
} return_code;



return_code proccess_file(char* filename, char* substr) {
    int match_len = 0;  
    int char_pos = 0;  
    int line_number = 1;  
    int start_pos = 1; 
    int ch;
    int substr_len = strlen(substr);
    int there_is_line_break;
    int cnt_of_line_break = 0;
    FILE* file = fopen(filename, "r");

    if (file == NULL) {
        return FILE_OPENNING_ERROR;
    }

    char* buffer = (char*)malloc(substr_len);  
    if (buffer == NULL) {
        fclose(file);
        return MEMORY_ALLOCATION_ERROR;
    }


    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            line_number++;
            char_pos = 0;
        } else {
            char_pos++;  
        }


        if (ch == substr[match_len]) {

            if (ch == '\n') {
                there_is_line_break = 1;
                ++cnt_of_line_break;
            }

            buffer[match_len++] = ch;
            if (match_len == substr_len) {
                if (there_is_line_break) {
                    printf("Substr found on line %d, position %d in file %s\n", line_number - cnt_of_line_break, start_pos, filename);
                } else {
                    printf("Substr found on line %d, position %d in file %s\n", line_number, start_pos, filename);
                }
                match_len = 0; 
                start_pos = char_pos + 1;
                there_is_line_break = 0;
            }
        } else {
            if (match_len > 0) {
                fseek(file, -match_len, SEEK_CUR);
                char_pos -= match_len;
            }
            match_len = 0;
            start_pos = char_pos + 1;
        }
    }

    free(buffer);
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
    char* substr = "ab\r\n\r\na";
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
