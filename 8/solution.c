// организация ввода чисел, пропускать пробелы, валидация строкового представления числа
#include <stdio.h>
#include "functions.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Invalid input\n");
        return ERROR_INPUT;
    }

    char* src = argv[1];
    char* output_file = argv[2];
    char* numbers[BUFSIZ];
    char max_numbers[BUFSIZ];
    int count_of_lines = 0;
    FILE* fi = NULL;
    FILE* fo = NULL;

    if (strcmp(src, output_file) == 0) {
        printf("The same file\n");
        return ERROR_FILE;
    }
    if ((fo = fopen(output_file, "w")) == NULL) {
        printf("Cannot open output file\n");
        return ERROR_FILE;
    }
    if ((fi = fopen(src, "r")) == NULL) {
        printf("Something wrong with file\n");
        fclose(fo);
        return ERROR_FILE;
    }
    return_code read_status = read_file(fi, numbers, &count_of_lines, max_numbers);
    if (read_status == ERROR_MEMORY) {
        printf("Error in memory alllocation\n");
        fclose(fi);
        fclose(fo);
        return ERROR_MEMORY;
    }


    for (int i = 0; i < count_of_lines; ++i) {
        int base = isalpha(max_numbers[i]) ? max_numbers[i] - 'A' + 10 + 1 : max_numbers[i] - '0' + 1;
        int num_in_decimal;
        gorner_scheme(numbers[i], base, &num_in_decimal);
        fprintf(fo, "%s - %d - %d\n", numbers[i], base, num_in_decimal);
        free(numbers[i]);
    } 

    fclose(fi);
    fclose(fo);

    return 0;

}