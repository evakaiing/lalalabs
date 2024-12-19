#include <iostream>
#include <bitset>
#include <climits>
#include <cstdint>

class binary_int {
private:
    int value = 0;
public:
    binary_int(int val): value(val) {};
    binary_int(const binary_int& other): value(other.value) {};
    binary_int& operator=(const binary_int& other) {
        if (this == &other) {
            return *this;
        }

        this->value = other.value;

        return *this;
    }

    binary_int operator-() const{
        return (~this->value + 1);
    }

    binary_int& operator++() {
        return ++(*this);
    }

    binary_int operator++(int) { // a++
        binary_int temp = *this;
        ++(*this);
        return temp;
    }

    binary_int& operator--() {
        int borrow = 1;
        int temp = this->value;
        while(borrow != 0) {
            int new_borrow = (~temp) & borrow;
            temp = temp ^ borrow;
            borrow = new_borrow << 1;
        }
        if ((this->value < 0 && temp > 0) || (this->value > 0 && temp < 0)) {
            throw std::overflow_error("overflow in --\n");
        }
        this->value = temp;
        return *this;
    }

    binary_int operator--(int) {
        binary_int temp = this->value;
        --(*this);
        return temp;
    }

    binary_int& operator+=(const binary_int& other) {
        int carry = 0;
        int a = this->value;
        int b = other.value;
        while (b != 0) {
            carry = (a & b) << 1;
            a ^= b;
            b = carry;
        }

        if ((this->value > 0 && other.value > 0 && a < 0) || 
            (this->value < 0 && other.value < 0 && a > 0)) {
            throw std::overflow_error("overflow in +=\n");
        }

        this->value = a;
        return *this;
    }

    binary_int& operator-=(const binary_int& other) {
        *this += -other;
        return *this;
    }


   binary_int& operator*=(const binary_int& other) {
    int a = this->value;
    int b = other.value;
    int result = 0;

    while (b != 0) {
        if (b & 1) {
            int64_t temp_result = static_cast<int64_t>(result) + a;
            if (temp_result > INT32_MAX || temp_result < INT32_MIN) {
                throw std::overflow_error("overflow in *=\n");
            }
            result = static_cast<int>(temp_result);
        }
        int64_t temp_a = static_cast<int64_t>(a) << 1;
        if (temp_a > INT32_MAX || temp_a < INT32_MIN) {
            throw std::overflow_error("overflow in *=\n");
        }
        a = static_cast<int>(temp_a);
        b >>= 1;
    }

    this->value = result;
    return *this;
}
    binary_int a, b;
    binary_int c = a + b;
    friend binary_int operator+(binary_int lhs, const binary_int& other) {
        lhs += other;
        return lhs;
    }

    friend binary_int operator-(binary_int lhs, const binary_int& other) {
        lhs -= other;
        return lhs;
    }

    friend binary_int operator*(binary_int lhs, const binary_int& other) {
        lhs *= other;
        return lhs;
    }


    binary_int& operator>>=(const int& offset) {
        this->value >>= offset;
        return *this;
    }

    binary_int& operator<<=(const int& offset) {
        this->value <<= offset;
        return *this;
    }


    binary_int operator<<(const int& offset) const {
        binary_int temp = *this;
        temp <<= offset;
        return temp;
    }
    
    binary_int operator>>(const int& offset) const {
        binary_int temp = *this;
        temp >>= offset;
        return temp;
    }


    friend std::ostream& operator<<(std::ostream& os, const binary_int& obj) {
        os << std::bitset<sizeof(int) * 8>(obj.value);
        return os;
    }

    std::pair<binary_int, binary_int> split() {
        if (this->value == INT_MAX) {
            return {0, 0};
        }
        int total_bits = sizeof(int) * 8;
        int half = total_bits / 2;

        int seniors_bits = ~((1 << half) - 1);
        int lower_bits = (1 << half) - 1;
        
        seniors_bits = this->value & seniors_bits;
        lower_bits = this->value & lower_bits;

        return {seniors_bits, lower_bits};
    }

    ~binary_int() {};
};

int main() {
    binary_int a(5), b(2);
    binary_int c = a + b;
    std::cout << -a << '\n';
    std::cout << c << '\n';

    c -= b;
    std::cout << c << '\n';

    a *= b;
    std::cout << "a: " << a << '\n';

    binary_int d = a * b;
    std::cout << d << '\n';

    binary_int offseted_num = a << 2;
    std::cout << offseted_num << '\n';
    a >>= 1;
    std::cout << "one more time a >>= 1: " << a << '\n';
    std::cout << "\n\n\n\n";


    // max overflow addition check
    try {
        binary_int a(INT32_MAX);
        // binary_int c = a + 1;
        // std::cout << c << '\n';  
        ++a;
        std::cout << "check overflow intmax\n";
    } catch (const std::overflow_error& e) {
        std::cout << e.what();
    }

    // min overflow addition check
    try {
        binary_int a(INT32_MIN);
        // binary_int c = a - 1;
        // std::cout << c << '\n';  
        --a;
        std::cout << "check overflow intmin\n";
    } catch (const std::overflow_error& e) {
        std::cout << e.what();
    }

    // overflow multiply check
    try {
        binary_int a(INT32_MAX);
        c = a * 2;
        a *= 2;
        std::cout << "check overflow intmax\n";
    } catch (const std::overflow_error& e) {
        std::cout << e.what();
    }
    a++++;
    // int min multiply check
    try {
        binary_int a(INT32_MIN);
        // c = a * (-2);
        a *= 2;
        std::cout << "check overflow intmin\n";
    } catch (const std::overflow_error& e) {
        std::cout << e.what();
    }

}
