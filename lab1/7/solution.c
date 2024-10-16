#include "functions.h"
#include "proccessing_file_paths.c"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    char* first_arg = argv[1];
    char flag = first_arg[1];
    return_code status_flag_handling = is_valid_flag(first_arg);

    if (status_flag_handling == INVALID_INPUT) {
        printf("Invalid input of flag\n");
        return INVALID_INPUT;
    }
    
    switch(flag) {
        case 'r':
            if (argc != 5) {
                printf("Invalid input, invalid\n");
                return INVALID_INPUT;
            }
            // -r file1_path file2_path output_file_path
            char* file1_path = argv[2];
            char* file2_path = argv[3];
            char* output_file_path = argv[4];

            FILE* file1 = NULL;
            FILE* file2 = NULL;
            FILE* output_file = NULL;

            char* lexems_of_file1[BUFSIZ];
            char* lexems_of_file2[BUFSIZ];
            int cnt_of_lexems_file1 = 0;
            int cnt_of_lexems_file2 = 0;

            char path_to_current_directory[PATH_MAX];
            char absolute_path_file2[PATH_MAX];
            char absolute_path_file1[PATH_MAX];
            char absolute_output_path[PATH_MAX];

            get_path_to_current_directory(path_to_current_directory);

            convert_path_to_absolute(path_to_current_directory, file1_path, absolute_path_file1);

            convert_path_to_absolute(path_to_current_directory, file2_path, absolute_path_file2);

            convert_path_to_absolute(path_to_current_directory, output_file_path, absolute_output_path);


            if ((strcmp(absolute_path_file1, absolute_path_file2) == 0) ||
                strcmp(absolute_path_file1, absolute_output_path) == 0 || 
                strcmp(absolute_path_file2, absolute_output_path) == 0) {
                printf("The same file\n");
                return INVALID_INPUT;
            }

            if ((file1 = fopen(file1_path, "r")) == NULL) {
                printf("Couldn't open file1\n");
                return FILE_OPENNING_ERROR;
            }

            if ((file2 = fopen(file2_path, "r")) == NULL) {
                printf("Couldn't open file2\n");
                fclose(file1);
                return FILE_OPENNING_ERROR;
            }

            if ((output_file = fopen(output_file_path, "w")) == NULL) {
                printf("Couldn't open output file\n");
                fclose(file1);
                fclose(file2);
                return FILE_OPENNING_ERROR;
            }


            return_code status_of_read_file1 = get_lexems_from_file(file1, lexems_of_file1, &cnt_of_lexems_file1);
            if (status_of_read_file1 == ERROR_MEMORY) {
                printf("Error in memory allocation\n");
                return ERROR_MEMORY;
            }

            return_code status_of_read_file2 = get_lexems_from_file(file2, lexems_of_file2, &cnt_of_lexems_file2);
            if (status_of_read_file2 == ERROR_MEMORY) {
                printf("Error in memory allocation\n");
                return ERROR_MEMORY;
            }

            return_code status_r = for_r(lexems_of_file1, lexems_of_file2, output_file);
            if (status_r == ERROR_MEMORY) {
                printf("Error in memory allocation\n");
                return ERROR_MEMORY;
            }
            
            for (int i = 0; i < cnt_of_lexems_file1; ++i) {
                free(lexems_of_file1[i]);
            }

            for (int i = 0; i < cnt_of_lexems_file2; ++i) {
                free(lexems_of_file2[i]);
            }

            printf("Success\n");
            fclose(file1);
            fclose(file2);
            fclose(output_file);

            break;
        case 'a':
            // -a path_to_file path_to_output_file
            if (argc != 4) {
                printf("Invalid input, invalid\n");
                return INVALID_INPUT;
            }
            char* path_to_input_file = argv[2];
            char* path_to_output_file = argv[3];

            FILE* input_file = NULL;
            FILE* output_file_a = NULL;

            char* lexems[BUFSIZ];
            int cnt_of_lexems = 0;

            char path_to_current_directory_a[PATH_MAX];
            char absolute_path_file[PATH_MAX];
            char absolute_output_path_a[PATH_MAX];

            get_path_to_current_directory(path_to_current_directory_a);

            convert_path_to_absolute(path_to_current_directory_a, path_to_input_file, absolute_path_file);

            convert_path_to_absolute(path_to_current_directory_a, path_to_output_file, absolute_output_path_a);
            printf("%s ", absolute_path_file);
            printf("%s ", absolute_output_path_a);


            if (strcmp(absolute_path_file, absolute_output_path_a) == 0) {
                printf("The same file\n");
                return INVALID_INPUT;
            }


            if ((input_file = fopen(path_to_input_file, "r")) == NULL) {
                printf("Couldn't open input file\n");
                return FILE_OPENNING_ERROR;
            }

            if ((output_file_a = fopen(path_to_output_file, "w")) == NULL) {
                printf("Couldn't open output file\n");
                fclose(input_file);
                return FILE_OPENNING_ERROR;
            }

            return_code status_of_getting_lexems = get_lexems_from_file(input_file, lexems, &cnt_of_lexems);
            if (status_of_getting_lexems == ERROR_MEMORY) {
                printf("Error in memory allocation\n");
                return ERROR_MEMORY;
            }

            return_code status_a = for_a(lexems, output_file_a);

            if (status_a != OK) {
                printf("Something wrong\n");
                return -1;
            }

            printf("Success\n");

            fclose(input_file);
            fclose(output_file_a);

            break;
    }

    return 0;
}