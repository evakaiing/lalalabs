#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define OK 0
#define ERROR_INPUT 1
#define ERROR_INPUT_BASE 2

// Функция проверки валидности числа
int is_valid_number(const char* str, int base) {
    // Пример валидации: добавьте свою логику проверки
    while (*str) {
        if (isdigit(*str)) {
            if (abs(*str) - '0' >= base) {
                return ERROR_INPUT_BASE;
            }
        } else if (isalpha(*str)) {
            if (toupper(*str) - 'A' + 10 >= base) {
                return ERROR_INPUT_BASE;
            }
        } else {
            return ERROR_INPUT;
        }
        ++str;
    }
    return OK;
}

// Горнер для конвертации строки в десятичное число
int gorner_scheme(const char* str_to_convert, int base_from, int* res) {
    *res = 0;
    while (*str_to_convert) {
        *res = *res * base_from + ((isalpha(*str_to_convert) 
            ? toupper(*str_to_convert) - 'A' + 10 
            : *str_to_convert - '0'));
        ++str_to_convert;
    }
    return OK;
}

// Обратная схема Горнера для конвертации из десятичного в другую систему
char* reverse_gorner_scheme(int num_to_convert, int base_to, char* buf) {
    char* p_buf = buf + BUFSIZ - 1;
    *p_buf-- = '\0';

    while (num_to_convert > 0) {
        int remainder = num_to_convert % base_to;
        *p_buf = (remainder > 9) ? remainder - 10 + 'A' : remainder + '0';
        p_buf--;
        num_to_convert /= base_to;
    }
    return p_buf + 1;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Incorrect input\n");
        return ERROR_INPUT;
    }

    int base;
    sscanf(argv[1], "%d", &base);

    if (base < 2 || base > 36) {
        printf("Invalid base\n");
        return ERROR_INPUT;
    }

    char current_str[BUFSIZ];  // Выделение достаточного места для ввода строки

    while (scanf("%s", current_str)) {
        if (strcmp(current_str, "STOP") == 0) {
            break;
        }

        int validation_code = is_valid_number(current_str, base);
        if  (validation_code == ERROR_INPUT) {
            printf("Incorrect input\n");
            return ERROR_INPUT;
        } else if (validation_code == ERROR_INPUT_BASE) {
            printf("Numbers must be smaller than the degree of the number system\n");
            return ERROR_INPUT_BASE;
        }

        char buf[BUFSIZ];  // Буфер для конвертации
        int num_in_decimal = 0;

        if (gorner_scheme(current_str, base, &num_in_decimal) != OK) {
            printf("ERROR\n");
            return ERROR_INPUT;
        }

        int number_systems[] = {9, 18, 27, 36};
        for (int i = 0; i < 4; ++i) {  // Поправил условие цикла
            char* num = reverse_gorner_scheme(num_in_decimal, number_systems[i], buf);
            printf("%s ", num);
        }
        printf("\n");  // Добавляем новую строку после каждого числа
    }

    return OK;
}
