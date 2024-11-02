#include <stdio.h>
#include <math.h>

#define EPS 1e-10
#define PI 3.14

typedef enum return_code {
    OK, 
    INVALID_INPUT, 
    NO_ROOTS
} return_code;


return_code method_dichotomy(double* result, double left, double right, double epsilon, double (*f)(double))
{
    if(f(left) * f(right) > 0)
    {
        return NO_ROOTS;
    }
    if(epsilon <= 0)
    {
        return INVALID_INPUT;
    }
    *result = (left + right) / 2;
    while (fabs(f(*result)) >= epsilon)
    {
        if(f(*result) * f(left) < 0)
        {
            right = *result;
        }
        else
        {
            left = *result;
        }
        *result = (left + right) / 2;
    }
    return OK;
}

double func1(double x)
{
    return x * x * x - 5 * x + 1;
}

double func2(double x)
{
    return pow(x-1, 2) / (x-1);
}

double func3(double x)
{
    return x - 5;
}

double func4(double x)
{
    return x * x * x * x - 10 * x * x * x + 35 * x * x - 50 * x + 24;
}

double func5(double x)
{
    return exp(x) - 3;
}





int main() {
    double res1;
    double res2;
    double res3;
    return_code st = method_dichotomy(&res1, 0, 2, EPS, func2);
    if (st == NO_ROOTS) {
        printf("No roots in this segment\n");
        return NO_ROOTS;
    } else if (st == INVALID_INPUT) {
        printf("Incorrect input\n");
        return INVALID_INPUT;
    }

    method_dichotomy(&res2, -3, -2, EPS, func1);
    method_dichotomy(&res3, 0, 2, EPS, func5);

    printf("%lf\n", res1);
    // printf("%lf\n", PI / 6);
    printf("%lf\n", res2);
    printf("%lf\n", res3);
}