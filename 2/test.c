#include <math.h>
#include <stdio.h>

// Функция для вычисления факториала
unsigned long long factorial(int n) {
    if (n == 0 || n == 1) return 1;
    unsigned long long result = 1;
    for (int i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}

// Функция для вычисления гамма с использованием лимита
double calculate_gamma_using_limit(double eps) {
    double current = 0.0;
    double previous = -1.0;  // Инициализируем для первой итерации
    int m = 1;

    // Цикл продолжается, пока разница больше eps
    while (fabs(current - previous) > eps) {
        previous = current;

        // Вычисляем биномиальный коэффициент C_m^k для k = m
        double combination = (double)factorial(m) / (factorial(m) * factorial(0)); // C_m^m = 1 всегда

        // Обновляем текущее значение по формуле
        current += combination * (pow(-1, m) / m) * log(factorial(m));

        ++m;
    }

    return current;
}

int main() {
    double eps = 1e-6;  // Точность вычисления
    double result = calculate_gamma_using_limit(eps);
    printf("Approximation of Gamma: %.12f\n", result);
    return 0;
}
