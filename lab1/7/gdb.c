#include "functions.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

return_code is_valid_flag(const char* flag) {
    if(strlen(flag) != 2) {
        return INVALID_INPUT;
    }
    if (flag[0] == '/' || flag[0] == '-') {
        switch(flag[1]) {
            case 'a':
            case 'r':
                return OK; 
            default:
                return INVALID_INPUT; 
        }
    }
    return INVALID_INPUT;
}

char* reverse_gorner_scheme(int ascii_code, int base_to, char* buf) {
    int remainder = 0;
    char* p_buf = buf + BUFSIZ - 1; 
    if (ascii_code == 0) {
        *p_buf-- = '0';
        return p_buf + 1;
    }
    *p_buf-- = '\0';
    while(ascii_code > 0) {
        *p_buf-- = ((remainder = ascii_code % base_to) > 9) ? remainder + 'A' - 10 : remainder + '0';
        ascii_code /= base_to;
    }
    return p_buf + 1;
}

return_code get_lexems_from_file(FILE* file, char** lexems, int* cnt_of_lexems) {
    char current_symbol;
    char buf[BUFSIZ] = {0};
    char* p_buf = buf;
    *cnt_of_lexems = 0;
    char previous_symbol = 0;

    while((current_symbol = fgetc(file)) != EOF) {
        if (isalnum(current_symbol)) {
            *p_buf++ = current_symbol;
        } else {
            if (isalnum(previous_symbol)) {
                *p_buf = '\0';
                lexems[*cnt_of_lexems] = (char *)malloc(strlen(buf) + 2);
                p_buf = buf;

                if (lexems[*cnt_of_lexems] == NULL) {
                    return ERROR_MEMORY;
                }

                strcpy(lexems[(*cnt_of_lexems)++], buf);

            }
        }
        previous_symbol = current_symbol;
    }

    if (isalnum(previous_symbol)) {
        *p_buf = 0;
        lexems[*cnt_of_lexems] = (char*)malloc(strlen(buf) + 2);
        if (lexems[*cnt_of_lexems] == NULL) {
            return ERROR_MEMORY;
        }
        strcpy(lexems[(*cnt_of_lexems)++], buf);
    }

    lexems[*cnt_of_lexems] = NULL;

    return OK;

}

return_code for_r(char** lexems_from_file1, char** lexems_from_file2, FILE* output_file) {
    char current_symbol_in_file1;
    char current_symbol_in_file2;
    int cnt_file1 = 0;
    int cnt_file2 = 0;
    while (lexems_from_file1[cnt_file1] && lexems_from_file2[cnt_file2]) {
        char* lexem_to_put = NULL;
        if ((cnt_file1 + cnt_file2) % 2 == 0) {
            lexem_to_put = (char*)malloc(strlen(lexems_from_file1[cnt_file1]) + 2);
            if (!lexem_to_put) {
                return ERROR_MEMORY;
            }
            strcpy(lexem_to_put, lexems_from_file1[cnt_file1++]);
            strcat(lexem_to_put, " ");
            fputs(lexem_to_put, output_file);
        } else {
            lexem_to_put = (char*)malloc(strlen(lexems_from_file2[cnt_file2]) + 2);
            if (!lexem_to_put) {
                return ERROR_MEMORY;
            }
            strcpy(lexem_to_put, lexems_from_file2[cnt_file2++]);
            strcat(lexem_to_put, " ");
            fputs(lexem_to_put, output_file);
        }
        free(lexem_to_put);
    }

    while (lexems_from_file2[cnt_file2] != NULL) {
        char* lexem_to_put = (char*)malloc(strlen(lexems_from_file2[cnt_file2]) + 2);

        if (!lexem_to_put) {
            return ERROR_MEMORY;
        }
        strcpy(lexem_to_put, lexems_from_file2[cnt_file2++]);
        strcat(lexem_to_put, " ");
        fputs(lexem_to_put, output_file);
        free(lexem_to_put);
    }

    while (lexems_from_file1[cnt_file1] != NULL) {
        char* lexem_to_put = (char*)malloc(strlen(lexems_from_file1[cnt_file1]) + 2);

        if (!lexem_to_put) {
            return ERROR_MEMORY;
        }

        strcpy(lexem_to_put, lexems_from_file1[cnt_file1++]);
        strcat(lexem_to_put, " ");
        fputs(lexem_to_put, output_file);
        free(lexem_to_put);
    }
    return OK;
}


return_code for_a(char** lexems, FILE* output_file) {
    int number_of_current_lexem = 1;
    while(lexems[number_of_current_lexem] != NULL) {
        char* current_lexem = lexems[number_of_current_lexem - 1];
        if (number_of_current_lexem % 10 == 0) { // numeration start with 0
            int length_of_lexem = strlen(current_lexem);
            for (int i = 0; i < length_of_lexem; ++i) {
                char current_symbol = current_lexem[i];
                if (isalpha(current_symbol) && isupper(current_symbol)) { // +22
                    int difference_ascii_codes = abs('A' - 'a');
                    char symbol_to_put = (char)current_symbol + difference_ascii_codes;
                    fputc(symbol_to_put, output_file);
                    fputc(' ', output_file);

                }
                char ascii_code_in_4[BUFSIZ];

                reverse_gorner_scheme((int)current_symbol, 4, ascii_code_in_4);
                
                fputs(ascii_code_in_4, output_file);
            }

        } else if (number_of_current_lexem % 2 == 0 || number_of_current_lexem % 5 == 0) {
            if (number_of_current_lexem % 2 == 0) {
                int length_of_lexem = strlen(current_lexem);
                for (int i = 0; i < length_of_lexem; ++i) {
                    char current_symbol = current_lexem[i];
                    if (isalpha(current_symbol) && isupper(current_symbol)) {
                        int difference_ascii_codes = abs('A' - 'a');
                        char symbol_to_put = (char)(current_symbol) + difference_ascii_codes;
                        fputc(symbol_to_put, output_file);
                        fputc(' ', output_file);
                        ++current_symbol;
                    }
                }
            } else {
                int length_of_lexem = strlen(current_lexem);
                for (int i = 0; i < length_of_lexem; ++i) {
                    char current_symbol = current_lexem[i];
                    char ascii_code_in_4[BUFSIZ];
                    reverse_gorner_scheme((int)(current_symbol)++, 4, ascii_code_in_4);
                    fputs(ascii_code_in_4, output_file);
                }
            }
        }
        ++number_of_current_lexem;
    }
    
    return OK;

}

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

            if (strcmp(file1_path, file2_path) == 0) {
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
            fclose(output_file);


    }
}