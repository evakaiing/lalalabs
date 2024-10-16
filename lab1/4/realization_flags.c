#include "functions.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

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
    
    char ch;
    while ((ch = fgetc(input_file)) != EOF) {
        if (isdigit(ch)) {
            continue;
        }
        fputc(ch, output_file);
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
        } else if (isalpha(current_symbol)) {
            ++cnt;
            is_line_empty = 0;
        } else if (!isspace(current_symbol)) {
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