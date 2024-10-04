#include <stdio.h>
#include "functions.h"
#include <string.h>
#include <stdlib.h>
#include <limits.h> 

int main(int argc, char* argv[]) {
    if (argc != 4 && argc != 3) {
        printf("Invalid input, bye\n");
        return INVALID_INPUT;
    }
    char* first_arg = argv[1];
    int is_nflag = 0;
    char* name_input_file = NULL;
    char path_input_file[PATH_MAX];
    char* path_output_file = NULL;

    return_code check_validity_of_flag = flag_handling(first_arg, &is_nflag);

    if (check_validity_of_flag == INVALID_INPUT) {
        printf("Invalid input of flags\n");
        return INVALID_INPUT;
    }
    
    name_input_file = argv[2];
    if (is_nflag) {
        path_output_file = argv[3];
    }  else {
        path_output_file = (char*)malloc(PATH_MAX);
        if (!path_output_file) {
            printf("Error in memoty allocation\n");
            return ERROR_MEMORY;
        }
        char current_directory[PATH_MAX];
        get_path_to_current_directory(current_directory);
        convert_path_to_absolute(current_directory, name_input_file, path_input_file);
        return_code status_get_output_filename = get_output_filename(path_input_file, path_output_file);
        if (status_get_output_filename == FILE_PATH_LENGTH_ERROR) {
            printf("FILE_PATH_LENGTH_ERROR");
            free(path_output_file);
            return FILE_PATH_LENGTH_ERROR;
        }
    }

    char flag = is_nflag ? first_arg[2] : first_arg[1];
    FILE* input_file = fopen(path_input_file, "r");
    if (!input_file) {
        printf("Couldn't open input file\n");
        return FILE_OPENNING_ERROR;
    }

    FILE* output_file = fopen(path_output_file, "w");
    if (!output_file) {
        printf("Couldn't open output file\n");
        fclose(input_file);
        return FILE_OPENNING_ERROR;
    }
    switch(flag) {
        case 'd':
            return_code status_d = for_d(input_file, output_file);

            if (status_d == OK) {
                printf("Success\n");
            } else {
                printf("Something wrong\n");
            }
            break;
        case 'i':
            return_code status_i = for_i(input_file, output_file);

            if (status_i == OK) {
                printf("Success\n");
            } else {
                printf("Something wrong\n");
            }
            break;
        case 's':
            return_code status_s = for_s(input_file, output_file);

            if (status_s == OK) {
                printf("Success\n");
            } else {
                printf("Something wrong\n");
            }
            break;
        case 'a':
            return_code status_a = for_a(input_file, output_file);

            if (status_a == OK) {
                printf("Success\n");
            } else {
                printf("Something wrong\n");
            }
            break;
    }   
    if (!is_nflag) {
        free(path_output_file);
    }
    fclose(input_file);
    fclose(output_file);    
}

