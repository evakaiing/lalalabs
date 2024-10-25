#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

typedef enum return_code {
    OK,
    INVALID_INPUT,
    MEMORY_ALLOCATION_ERROR,
    OVERFLOW_ERROR,
    FILE_OPENNING_ERROR
} return_code;

typedef struct Point {
    double x;
    double y;
} Point;

return_code convert_str_to_int_in_current_base(int* result, char* str, int base) {
    char* end_ptr = NULL;

    long tmp = strtol(str, &end_ptr, base);

    if (*end_ptr != '\0') {
        return INVALID_INPUT;
    }

    if (tmp >= INT_MAX || tmp <= INT_MIN) {
        return OVERFLOW_ERROR;
    }

    *result = tmp;

    return OK;
}

void print_number_in_base(int init_number, int base){
    if (init_number == 0);
    else if (labs(init_number) < base){
        if (init_number < 0)
            printf("-");
        if(labs(init_number) < 10)
            printf("%ld", labs(init_number));
        else 
            printf("%c", (char)('A' + labs(init_number) - 10));
    }
    else{
        int reminder = labs(init_number) % base;
        print_number_in_base(init_number / base, base);
        if(reminder < 10)
            printf("%d", reminder);
        else
            printf("%c", 'A' + reminder - 10);
    }
}


return_code find_kaprekar_numbers(int count, int base, ...) {
    char* current_number_in_str;
    int left_part, right_part;
    va_list args;
    int remainder;
    int power;

    va_start(args, base);

    for (int i = 0; i < count; ++i) {
        int number;
        current_number_in_str = va_arg(args, char*);

        return_code status_of_convertation = convert_str_to_int_in_current_base(&number, current_number_in_str, base);

        if (status_of_convertation != OK) {
            va_end(args);
            return status_of_convertation;
        }

        if (INT_MAX / number < number) {
            va_end(args);
            return OVERFLOW_ERROR;
        }

        left_part = number * number;

        right_part = 0;

        power = 1;
        
        while (left_part > 0){                      
            remainder = left_part % base;           
            left_part /= base;                     
            right_part += remainder * power;
            power *= base;

            if(right_part != 0 && left_part + right_part == number){
                printf("%s ^ 2 = ", current_number_in_str);
                print_number_in_base(number * number, base);

                printf(" ==> ");
                print_number_in_base(left_part, base);

                printf(" + ");
                print_number_in_base(right_part, base);

                printf("\n");
                break;
            }
        }
    }

    return OK;
}

double vector_product(Point first, Point second)
{
    return first.x * second.y - first.y * second.x;
}

double cross_product(Point p1, Point p2, Point p3) {
    double dx1 = p2.x - p1.x;
    double dy1 = p2.y - p1.y;
    double dx2 = p3.x - p2.x;
    double dy2 = p3.y - p2.y;
    return dx1 * dy2 - dy1 * dx2;
}

int is_convex(int count, ...) {
    if (count <= 3) {
        return 1; 
    }

    va_list args;
    Point p0, p1, p2, prev1, prev2;
    int initial_turn;
    va_start(args, count);

    p0 = va_arg(args, Point);
    p1 = va_arg(args, Point);
    p2 = va_arg(args, Point);

    initial_turn = (cross_product(p0, p1, p2) >= 0) ? 1 : -1;

    prev1 = p1;
    prev2 = p2;

    for (int i = 3; i < count; i++) {
        Point current = va_arg(args, Point);
        int current_turn = (cross_product(prev1, prev2, current) >= 0) ? 1 : -1;
        if (current_turn != initial_turn) {
            va_end(args);
            return 0;
        }

        prev1 = prev2;
        prev2 = current;
    }

    int last_turn1 = (cross_product(prev1, prev2, p0) >= 0) ? 1 : -1;
    int last_turn2 = (cross_product(prev2, p0, p1) >= 0) ? 1 : -1;
    va_end(args);

    if (last_turn1 != initial_turn || last_turn2 != initial_turn) {
        return 0;
    }

    return 1; 
}


return_code find_polynom(double *res, double x, int n, ...)
{
    va_list args;
    *res = 0;

    if (n < 0)
        return INVALID_INPUT;

    va_start(args, n);
    for (int i = n; i >= 0; --i) {
        double current_coefficent = va_arg(args, double);
        *res += pow(x, i) * current_coefficent;
        if (isinf(*res) || isnan(*res))
        {
            va_end(args);
            return OVERFLOW_ERROR;
        }
    }
    va_end(args);
    return OK;
}


int main() {
    // TEST FOR POINT 3
    return_code rc_1 = find_kaprekar_numbers(3, 10, "45", "9999", "5050");
    return_code rc_2 = find_kaprekar_numbers(2, 16, "CD", "4ED");
    return_code rc_3 = find_kaprekar_numbers(3, 12, "7249", "BB", "12AA");

    if (rc_1 != OK) {
        printf("Error\n");
        return rc_1;
    }

    if (rc_2 != OK) {
        printf("Error\n");
        return rc_2;
    } 


    // TESTS FOR POINT 1

    Point p1 = (Point){0, 0};
    Point p2 = (Point){1, 0};
    Point p3 = (Point){1, 1};
    Point p4 = (Point){0, 1};

    printf("%d\n", is_convex(4, p1, p2, p3, p4)); // 1

    p1 = (Point){0, 0};
    p2 = (Point){1, 0};
    p3 = (Point){0, 1};
    p4 = (Point){1, 1};

    printf("%d\n", is_convex(4, p1, p2, p3, p4)); // 0

    p1 = (Point){0, 0};
    p2 = (Point){10, 0};
    p3 = (Point){0.001, 0.001};

    printf("%d\n", is_convex(3, p1, p2, p3)); // 1

    p1 = (Point){0, 0};

    printf("%d\n", is_convex(1, p1)); // 1

    printf("%d\n", is_convex(0)); // 1

    // TEST FOR POINT 2
    
    double res;
    find_polynom(&res, 2.0, 0, 3.5);
    printf("%lf\n", res);
    
    double res2;
    find_polynom(&res2, 1.0, 3, 2.0, -3.0, 0.0, 1.0); //2x^3 - 3x^2 + 1   0

    printf("%lf\n", res2);


}
