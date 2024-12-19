#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <fstream>
#include <limits.h>
#include <cstring>
#include <filesystem>


class encoder {
private:
    std::vector<int> s;
    std::vector<std::byte> key;

    std::vector<int> initialize_s() {
        s.clear();
        for (int i = 0; i < 256; ++i) {
            s.push_back(i);
        }
        int j = 0;
        for (int i = 0; i < 256; ++i) {
            j = (j + s[i] + static_cast<int>(this->key[i % this->key.size()])) % 256;
            std::swap(s[i], s[j]);
        }

        return s;
    }

    std::string rc4(std::string text) {
        int i = 0;
        int j = 0;
        std::string result;
        for (char current : text) {
            i= (i + 1) % 256;
            j = (j + s[i]) % 256;
            std::swap(s[i], s[j]);
            int t = (s[i] + s[j]) % 256; 
            int k = s[t];
            result.push_back(current ^ k);
        }

        return result;
    }

    void checkPaths(const std::string& path_to_input_file, const std::string& path_to_output_file) const {
        if (std::filesystem::absolute(path_to_input_file) == std::filesystem::absolute(path_to_output_file)) {
            throw std::runtime_error("The same files");
        }
    }

    std::string read_file(std::string path_input) {
        std::ifstream input_file(path_input);
        if (!input_file) {
            throw std::runtime_error("Couldn't open the input_file");
        }

        std::string text;
        char ch;
        while(input_file.get(ch)) {
            text += ch;
        }

        return text;
    }

    void write_in_file(const std::string& path_to_output_file, const std::string& text) {
        std::ofstream file(path_to_output_file, std::ios::binary);
        if (!file) {
            throw std::runtime_error("Couldn't open output file");
        }
        file.write(text.c_str(), text.size());
        file.close();
    }


public:
    encoder(const std::vector<std::byte> input_key): key(input_key) {
        if (key.empty()) {
            throw std::runtime_error("Key is empty");
        }
        initialize_s();
    }

    encoder(const encoder& other): key(other.key) {};
    encoder operator=(const encoder& other) {
        if (this == &other) {
            return *this;
        }

        this->key = other.key;

        return *this;
    }
    void encode(std::string path_to_input_file, std::string path_to_output_file, bool need_to_encrypt) {
        try {
            checkPaths(path_to_input_file, path_to_output_file);
            if (!need_to_encrypt && (std::filesystem::is_empty(path_to_input_file))) {
                throw std::runtime_error("Couldn't to decrypt empty file");
            }
            std::string text = read_file(path_to_input_file);

            this->initialize_s();

            std::string result = rc4(text);
            write_in_file(path_to_output_file, result);


        } catch (const std::runtime_error& e) {
            std::cout << e.what() << '\n';
        }

    }

    void set_key(const std::vector<std::byte>& new_key) {
        if (new_key.empty()) {
            throw std::runtime_error("New key cannot be empty");
        }
        key = new_key;    
        initialize_s();  
    }
};


int main() {
    std::vector<std::byte> key = {std::byte(0x1), std::byte(0x2), std::byte(0x3)};
    std::vector<std::byte> new_key = {std::byte(0x5), std::byte(0x2), std::byte(0x1)};
    encoder test(key);
    encoder test_2(new_key);
    test.encode("text.txt", "encrypted.txt", true);
    test.encode("encrypted.txt", "decrypted.txt", false);

    test.set_key(new_key);

    test.encode("text.txt", "encrypted2.txt", true);
    test.encode("encrypted2.txt", "decrypted2.txt", false);

}