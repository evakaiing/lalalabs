
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

typedef enum return_code {
    OK,
    ERROR_INPUT_BASE,
    ERROR_INPUT,
    ERROR_OVERFLOW,
    ERROR_MEMORY,
    ERROR_FILE
} return_code;

return_code read_file(FILE* file_in, char** numbers, int* count, char* max_numbers) {
    char current_symbol, previous_sybmbol = 0;
    char buf[BUFSIZ];
    char* p_buf = buf;
    int i = 0;
    int max_number_in_current_symbol = 0;
    char max_symbol;
    while(!feof(file_in)) {
        current_symbol = fgetc(file_in);
        if (isalnum(current_symbol)) {
            *p_buf++ = current_symbol;
            int value_current_symbol = isalpha(current_symbol) ? current_symbol - 'A' + 10 : current_symbol - '0';
            
            if (value_current_symbol > max_number_in_current_symbol) {
                max_number_in_current_symbol = value_current_symbol;
                max_symbol = current_symbol;
            }
        } else if (isalnum(previous_sybmbol)) {
            *p_buf  = 0;
            numbers[i] = (char *)malloc(strlen(buf) + 1);
            if (numbers[i] == NULL) {
                return ERROR_MEMORY;
            }
            strcpy(numbers[i++], buf);
            max_numbers[i] = max_symbol;
            p_buf = buf;
            max_number_in_current_symbol = 0;
        }
        previous_sybmbol = current_symbol;
    }
    *count = i;
    return OK;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Invalid input\n");
        return ERROR_INPUT;
    }

    char* src = argv[1];
    char* numbers[BUFSIZ];
    char max_numbers[BUFSIZ];
    int count_of_lines = 0;
    FILE* fi = NULL;
    if ((fi = fopen(src, "r")) == NULL) {
        printf("Something wrong with file\n");
        return ERROR_FILE;
    }
    return_code read_status = read_file(fi, numbers, &count_of_lines, max_numbers);
    if (read_status == ERROR_MEMORY) {
        printf("Error in memory alllocation\n");
        return ERROR_MEMORY;
    }

    for (int i = 0; i < count_of_lines; ++i) {
        printf("%s - %c", numbers[i], max_numbers[i]);
        free(numbers[i]);
    }

    fclose(fi);

}