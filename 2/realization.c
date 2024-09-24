#include "functions.h"
#include <math.h>

int is_prime(int n) {
    if (n < 2) return 0;
    for (int i = 2; i <= sqrt(n); ++i) {
        if (n % i == 0) return 0;
    }
    return 1;
}

long long factorial(int n) {
    if (n == 0 || n == 1) {
        return 1;
    }
    unsigned long long result = 1;
    for (int i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}

double calculate_e_using_limit(double eps) {
    double e_previous = 0.0;
    double e_current = 2.0;
    int n = 1;

    while(fabs(e_current - e_previous) > eps) {
        e_previous = e_current;
        ++n;
        e_current = pow(1.0 + 1.0 / n, n);
    }
    return e_current;
}

double calculate_pi_using_limit(double eps) {
    double pi_previous = 0.0;
    double pi_current = 4.0;
    int n = 2;
    double factorial_n = factorial(n);
    double factorial_2n = factorial(2 * n);
    while(fabs(pi_current - pi_previous) > eps) {
        pi_previous = pi_current;
        ++n;
        pi_current = pow(pow(2.0, n) * factorial_n, 4.0) / pow(n * factorial_2n, 2.0);
        double factorial_n = factorial(n);
        double factorial_2n = factorial(2.0 * n);
    }
    return pi_current;
}

double calculate_ln_using_limit(double eps) {
    double ln_previous = 0.0;
    double ln_current = 1.0;

    int n = 1;

    while(fabs(ln_previous - ln_current) > eps) {
        ln_previous = ln_current;
        ++n;
        ln_current = n * (pow(2.0, 1.0 / n) - 1.0);
    }

    return ln_current;
}

double calculate_sqrt_using_limit(double eps) {
    double current = 0.75;
    double previous = 0;
    int n = 1;
    while(fabs(previous - current) > eps) {
        previous = current;
        ++n;
        current = previous - (pow(previous, 2) / 2) + 1;
    }
    return current;
}

double calculate_gamma_using_limit(double eps) {
    double current = 0;
    double previous = 0;
    int m = 1;
    while(fabs(previous - current) > eps) {
        previous = current;
        ++m;
        double combination = (double)factorial(10) / factorial(10 - m) * factorial(m);
        current += combination * (pow(-1, m) / m) * log(factorial(m));
    }
    return current;
}


double calculate_e_using_row(double eps) {
    double e_current = 1.0;
    double e_previous = 0.0;
    unsigned long long factorial = 1;
    int n;

    for (n = 1; n < 20; ++n) {
        e_previous = e_current;
        factorial *= n;
        e_current += (1.0 / factorial);
        if (fabs(e_current - e_previous) < eps) {
            break;
        }
    }

    return e_current;
}

double calculate_pi_using_row(double eps) {
    double pi_current = 1.0;
    double pi_previous = 0.0;
    int n = 1;
    while(fabs(pi_current - pi_previous) > eps) {
        pi_previous = pi_current;
        ++n;
        pi_current -= 1.0 / (2.0 * n - 1.0);
        ++n;
        pi_current += 1.0 / (2.0 * n - 1.0);
    }
    return 4 * pi_current;
}

double calculate_ln_using_row(double eps) {
    double current = 1.0;
    double previous = 0.0;
    int n = 1;
    while(fabs(current - previous) > eps) {
        previous = current;
        ++n;
        current -= 1.0 / n;
        ++n;;
        current += 1.0 / n;
    }
    return current;
}

double calculate_sqrt_using_row(double eps) {
    double current = 1.0;
    double previous = 0.0;
    int k = 2;
    while(fabs(current - previous) > eps) {
        previous = current;
        current *= pow(2.0, pow(2.0, -k));
        ++k;
    }
    return current;
}

double calculate_gamma_using_row(double eps) {
    // ≈ 0,5772156649
    double current = 0.5;
    double previous = 0.0;
    int k = 2;
    double sqrt_k;
    while(fabs(current - previous) > eps) {
        previous = current;
        ++k;
        sqrt_k = sqrt(k);
        if (fmod(sqrt_k, 1.0) == 0) {
            ++k;
            sqrt_k = sqrt(k);
        }
        current += (1.0 / pow((int)sqrt_k, 2)) - (1.0 / k);
    }
    double pi = calculate_pi_using_row(eps);
    return current - (pow(pi, 2) / 6);
}


double calculate_e_using_equation(double eps) {
    double f;
    double x = 2;
    double df;

    f  = log(x) - 1.0;
    while(fabs(f) > eps) {
        df = 1.0 / x;
        x = x - f / df;
        f  = log(x) - 1.0;
    }

    return x; 
}

double calculate_pi_using_equation(double eps) {
    double f;
    double x = 3;
    double df;

    f  = cos(x) + 1.0;
    while(fabs(f) > eps) {
        df = -sin(x);
        x = x - f / df;
        f  = cos(x) + 1.0;
    }

    return x; 
}

double calculate_ln_using_equation(double eps) {
    double f;
    double x = 0.5;
    double df;
    f  = exp(x) - 2;

    while(fabs(f) > eps) {
        df = exp(x);
        x = x - f / df;
        f  = exp(x) - 2;
    }

    return x; 
}

double calculate_sqrt_using_equation(double eps) {
    double f;
    double x = 0.5;
    double df;
    f  = pow(x, 2) - 2;

    while(fabs(f) > eps) {
        df = 2 * x;
        x = x - f / df;
        f  = pow(x, 2) - 2;
    }

    return x; 
}

double calculate_gamma_using_equation(double eps) {
    double composition = 0.5;
    int p = 2;
    double current = log(2) * 0.5;
    double previous = 0;

    while(fabs(current - previous) > eps) {
        previous = current;
        do {
            ++p;
        } while(is_prime(p) == 0);
        composition *= (p - 1.0) / p;
        current = log(p) * composition;
    }

    return -log(current);
}


