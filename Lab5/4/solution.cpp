#include <iostream>
#include <math.h>
#define EPS 1e-9

class Complex {
private:
    double re = 0;
    double im = 0;

public:
    Complex(): re(0.0), im(0.0) {};
    Complex(double real): re(real), im(0.0) {};
    Complex(double real, double imag): re(real), im(imag) {};

    Complex& operator+=(const Complex& other) {
        this->re += other.re;
        this->im += other.im;

        return *this;
    }

    Complex& operator-=(const Complex& other) {
        this->re -= other.re;
        this->im -= other.im;

        return *this;
    }

    Complex& operator*=(const Complex& other) {
        double re = this->re * other.re - this->im * other.im;
        double im = this->re * other.im + this->im * other.re;

        this->re = re;
        this->im = im;

        return *this;
    }

    Complex& operator/=(const Complex& other) {
        // a1 + b1i / a2 + b2i == (a1a2 + b1b2 / a2^2 + b2^ 2)+ ((b1a2 - b2a1) / a2^2 + b2^2)
        double denominator = ((other.im * other.im) + (other.re * other.re));
        if ((denominator - EPS) < 0) {
            throw std::runtime_error("Division by a zero");
        }
        double re = (this->re * other.re + this->im * other.im) / ((other.im * other.im) + (other.re * other.re));
        double im = (this->im * other.re - other.im * this->re) / ((other.im * other.im) + (other.re * other.re));

        this->re = re;
        this->im = im;

        return *this;
    }

    friend Complex operator+(const Complex& c1, const Complex& c2);

    Complex operator-(const Complex& c) {
        return (*this -= c);
    }

    Complex operator*(const Complex& c) {
        return (*this *= c);
    }

    Complex operator/(const Complex& c) {
        return (*this /= c);
    }

    double abs() {
        double result;
        result = sqrt(this->re * this->re + this->im * this->im);
        return result;
    }

    double arg() {
        if (this->re > 0) {
            return std::atan(this->im / this->re);
        } else if (this->re < 0 && this->im >= 0) {
            return std::atan(this->im / this->re) + M_PI;
        } else if (this->re < 0 && this->im < 0) {
            return std::atan(this->im / this->re) - M_PI;
        } else if (this->re == 0 && this->im > 0) {
            return M_PI / 2;
        } else if (this->re == 0 && this->im < 0) {
            return -M_PI / 2;
        } else {
            throw std::runtime_error("arg is undefined");
        }
    }

    friend std::ostream& operator<<(std::ostream& os, Complex c) {
        os << c.re << " + " << c.im << "i";
        return os;
    }
    


};

Complex operator+(const Complex& c1, const Complex& c2) {
    return Complex(c1.re + c2.re, c1.im + c2.im);
}

int main() {
    Complex c1(5, 3), c2(7, 2);
    c1 += c2;
    std::cout << c1 << '\n';

    Complex res;
    res = 5.0 + c2;
    std::cout << res << '\n';

    c1 -= c2;
    std::cout << c1 << '\n';

    res = c1 - c2;
    std::cout << res << '\n';

    c1 = {1, 4};
    c2 = {3, 5};
    c1 *= c2;

    std::cout << c1 << '\n';

    c1 = {4, 2};
    c2 = {3, -1};
    c1 /= c2;
    std::cout << c1 << '\n';

    try {
        c1 = {4, 2};
        c2 = {0, 0};
        c1 /= c2;
    } catch (const std::runtime_error& e) {
        std::cout << e.what() << '\n';
    }

    std::cout << c1.abs() << '\n'; // sqrt(16 + 4)

    try {
        std::cout << c2.arg();
    } catch (const std::runtime_error& e) {
        std::cout << e.what() << '\n';
    }

    Complex z = {1, 1};
    std::cout << z.arg() << ' ' << M_PI / 4 << '\n';
}