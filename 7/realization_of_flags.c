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

void decimal_to_base(int n, int base, char* result) {
    const char digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char buffer[65];
    int index = 0;

    do {
        buffer[index++] = digits[n % base];
        n /= base;
    } while (n > 0);

    for (int i = 0; i < index; i++) {
        result[i] = buffer[index - i - 1];
    }
    result[index] = '\0';
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
        if (number_of_current_lexem % 10 == 0) { 
            int length_of_lexem = strlen(current_lexem);
            for (int i = 0; i < length_of_lexem; ++i) {
                char current_symbol = current_lexem[i];
                if (isalpha(current_symbol) && isupper(current_symbol)) { // +22
                    int difference_ascii_codes = abs('A' - 'a');
                    char symbol_to_put = (char)current_symbol + difference_ascii_codes;
                    fputc(symbol_to_put, output_file);
                }
                char ascii_code_in_4[BUFSIZ] = {0};

                decimal_to_base((int)current_symbol, 4, ascii_code_in_4);
                
                fputs(ascii_code_in_4, output_file);
            }
            fputc(' ', output_file);

        } else if (number_of_current_lexem % 2 == 0 || number_of_current_lexem % 5 == 0) {
            if (number_of_current_lexem % 2 == 0) {
                int length_of_lexem = strlen(current_lexem);
                for (int i = 0; i < length_of_lexem; ++i) {
                    char current_symbol = current_lexem[i];
                    if (isalpha(current_symbol) && isupper(current_symbol)) {
                        int difference_ascii_codes = abs('A' - 'a');
                        char symbol_to_put = (char)(current_symbol) + difference_ascii_codes;
                        fputc(symbol_to_put, output_file);
                    } else if(isalpha(current_symbol)) {
                        fputc(current_symbol, output_file);
                    }
                }
                fputc(' ', output_file);
            } else {
                int length_of_lexem = strlen(current_lexem);
                for (int i = 0; i < length_of_lexem; ++i) {
                    char current_symbol = current_lexem[i];
                    char ascii_code_in_8[BUFSIZ] = {0};
                    decimal_to_base((int)current_symbol, 8, ascii_code_in_8);
                    fputs(ascii_code_in_8, output_file);
                }
                fputc(' ', output_file);
            }

        } else {
            fputs(current_lexem, output_file);
            fputc(' ', output_file);
        }
        ++number_of_current_lexem;
    }
    
    return OK;

}

