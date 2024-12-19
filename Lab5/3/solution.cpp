#include <iostream>
#include <bitset>

class logical_values_array {
private:
    unsigned int value = 0;
public:
    logical_values_array() {};

    explicit logical_values_array(unsigned int val): value(val) {};

    logical_values_array operator=(const logical_values_array& other) {
        if (this == &other) {
            return *this;
        }

        this->value = other.value;

        return *this;
    }

    logical_values_array(const logical_values_array& other): value(other.value) {};

    unsigned int get_value() {
        return this->value;
    }

    logical_values_array operator!() const {
        return logical_values_array(~(this->value));
    }

    logical_values_array operator&(const logical_values_array& other) {
        return logical_values_array(this->value & other.value);
    }

    logical_values_array operator|(const logical_values_array& other) {
        return logical_values_array(this->value | other.value);
    }

    logical_values_array implication(const logical_values_array& other) {
        return logical_values_array(!(*this) | other);
    }

    logical_values_array operator^(const logical_values_array& other) {
        return logical_values_array(this->value ^ other.value);
    }

    logical_values_array equivalence(const logical_values_array& other) {
        return logical_values_array((*this & other) | (!(*this) & !other));
    }

    static bool equals(logical_values_array& lhs, const logical_values_array& rhs) {
        return lhs.equivalence(rhs).value == ~0; 
    }
    
    logical_values_array sheffer(const logical_values_array& other) {
        return logical_values_array(!(*this & other));
    }

    logical_values_array pier_arrow(const logical_values_array& other) {
        return logical_values_array(!(*this | other));
    }

    unsigned int get_bit(const unsigned int pos) {
        if (pos >= sizeof(int) * 8) {
            throw std::out_of_range("pos must be < 32");
        }

        return (this->value >> pos) & 1;
    }

    void to_bin(char* buffer) {
        unsigned int num_bits = sizeof(int) * 8;
        if (!buffer) {
            throw std::invalid_argument("dereferencing null pointer attempt");
        }

        for (int i = 0; i < num_bits; ++i) {
            buffer[num_bits - i - 1] = (value & (1 << i)) ? '1' : '0';
        }

        buffer[num_bits] = '\0';
    }

    ~logical_values_array() {};
};


int main () {
    logical_values_array a(0b1011), b(0b0111);
    logical_values_array c;
    c  = a & b;
    std::cout << c.get_value() << '\n';
    c = a | b;
    std::cout << c.get_value() << '\n';
    c = !a;
    std::cout << c.get_value() << '\n';
    c = a.implication(b);
    std::cout << c.get_value() << '\n';
    c = a ^ b;
    std::cout << c.get_value() << '\n';
    c = a.sheffer(b);
    std::cout << c.get_value() << '\n';
    c = a.pier_arrow(b);
    std::cout << c.get_value() << '\n';

    try {
        auto kapets = c.get_bit(55);
        std::cout << kapets;
    } catch (const std::out_of_range& e) {
        std::cout << e.what() << '\n';
    }

    std::cout << c.get_bit(2) << '\n';

    char* binary_representation = new char[sizeof(int) * 8 + 1];
    c.to_bin(binary_representation);

    std::cout << binary_representation << '\n';
    
    delete[] binary_representation;


    logical_values_array a1(0b1011), b1(0b1011), c1(0b0111);
    std::cout << "a == b: " << logical_values_array::equals(a1, b1) << '\n'; 
    std::cout << "a == c: " << logical_values_array::equals(a1, c1) << '\n'; 

}