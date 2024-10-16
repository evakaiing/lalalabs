#include <stdio.h>
#include "functions.h"
#include <string.h>
#include <ctype.h>

char* reverse_gorner_scheme(int ascii_code, int base_to, char* buf) {
    int remainder = 0;
    char* p_buf = buf + BUFSIZ - 1; 
    while(ascii_code > 0) {
        *p_buf-- = ((remainder = ascii_code % base_to) > 10) ? remainder - 'A' + 10 : remainder - '0';
        ascii_code /= base_to;
    }
    return p_buf + 1;
}

return_code flag_handling(const char* flag, int* is_nflag) {
    if(strlen(flag) == 2) {
        if (flag[0] == '-' || flag[0] == '/') {
            switch(flag[1]) {
                case 'd':
                case 'i':
                case 's':
                case 'a':
                    return OK; 
                default:
                    return INVALID_INPUT; 
            }
        }
    } else if(strlen(flag) == 3) {
        if ((flag[0] == '-' || flag[0] == '/') && flag[1] == 'n') {
            *is_nflag = 1;
            switch(flag[2]) {
                case 'd':
                case 'i':
                case 's':
                case 'a':
                    return OK; 
                default:
                    return INVALID_INPUT; 
            }
        }    
    }
    return INVALID_INPUT;
}


return_code for_d(FILE* input_file, FILE* output_file) {
    if (input_file == NULL || output_file == NULL) {
        return FILE_OPENNING_ERROR;
    }
    
    while (!feof(input_file)) {
        char current_symbol = getc(input_file);
        if (isdigit(current_symbol)) {
            continue;
        }
        putc(current_symbol, output_file);
    }

    return OK;
}

return_code for_i(FILE* input_file, FILE* output_file) {
    int cnt = 0;
    char cnt_char[BUFSIZ];
    char ch;
    int is_line_empty;
    while ((ch = fgetc(input_file)) != EOF) {
        char current_symbol = (char)ch;
        if (current_symbol == '\n') {
            sprintf(cnt_char, "%d", cnt);
            strcat(cnt_char, "\n");
            fputs(cnt_char, output_file);
            cnt = 0;
            is_line_empty = 1;
        }
        if (isalpha(current_symbol)) {
            ++cnt;
            is_line_empty = 0;
        }
    } 


    if (!is_line_empty) {
        sprintf(cnt_char, "%d", cnt);
        fputs(cnt_char, output_file);
        fputs("\n", output_file);
    }

    return OK;
}

return_code for_s(FILE* input_file, FILE* output_file) {
    int cnt = 0;
    char cnt_char[BUFSIZ];
    char ch;
    int is_line_empty;
    while ((ch = fgetc(input_file)) != EOF) {
        char current_symbol = (char)ch;
        if (current_symbol == '\n') {
            sprintf(cnt_char, "%d", cnt);
            strcat(cnt_char, "\n");
            fputs(cnt_char, output_file);
            cnt = 0;
            is_line_empty = 1;
        }
        if (!isalpha(current_symbol) && !isdigit(current_symbol) && !isspace(current_symbol)) {
            ++cnt;
            is_line_empty = 0;
        }
    } 


    if (!is_line_empty) {
        sprintf(cnt_char, "%d", cnt);
        fputs(cnt_char, output_file);
        fputs("\n", output_file);
    }

    return OK;
}

return_code for_a(FILE* input_file, FILE* output_file) {
    char buffer[BUFSIZ];
    char current_symbol;
    while ((current_symbol = fgetc(input_file)) != EOF) {
        if (!isdigit(current_symbol)) {
            char* number_in_hex = reverse_gorner_scheme((int)current_symbol, 16, buffer);
            fputs(number_in_hex, output_file);
        } else {
            fputc(current_symbol, output_file);
        }
    } 

    return OK;
}

int main(int argc, char* argv[]) {
    if (argc != 4 && argc != 3) {
        printf("Invalid input, bye\n");
        return INVALID_INPUT;
    }
    char* first_arg = argv[1];
    int is_nflag = 0;
    char* name_of_input_file = NULL;
    char* name_of_output_file = NULL;
    return_code check_validity_of_flag = flag_handling(first_arg, &is_nflag);

    if (check_validity_of_flag == INVALID_INPUT) {
        printf("Invalid input of flags\n");
        return INVALID_INPUT;
    }

    name_of_input_file = argv[2];
    if (is_nflag) {
        name_of_output_file = argv[3];
    } 
    // generate output file

    char flag = is_nflag ? first_arg[2] : first_arg[1];
    FILE* input_file = fopen(name_of_input_file, "r");
    if (!input_file) {
        printf("Couldn't open input file\n");
        return FILE_OPENNING_ERROR;
    }

    FILE* output_file = fopen(name_of_output_file, "w");
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
    fclose(input_file);
    fclose(output_file);    
}

