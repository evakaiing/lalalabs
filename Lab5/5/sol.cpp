#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <fstream>
#include <sstream>

struct Token {
    char type;
    std::string value;
};

enum TokenType {
    TYPE,
    IDENTIFIER
};

std::stack<Token> token_stack;
Token current_token;

TokenType classify_string(const std::string &str) {
    if (str == "void" || str == "char" || str == "short" || str == "int" || str == "long" ||
        str == "signed" || str == "unsigned" || str == "float" || str == "double" ||
        str == "struct" || str == "union" || str == "enum") {
        return TYPE;
    } else {
        return IDENTIFIER;
    }
}

void get_token(std::istream &in) {
    char ch;
    current_token.value.clear();

    while (in.get(ch) && std::isspace(ch)) {}

    if (std::isalpha(ch) || ch == '_') {
        current_token.value += ch;
        while (in.get(ch) && (std::isalnum(ch) || ch == '_')) {
            current_token.value += ch;
        }
        in.putback(ch);

        TokenType type = classify_string(current_token.value);
        current_token.type = (type == TYPE) ? 'T' : 'I';

    } else if (std::isdigit(ch)) {
        current_token.value += ch;
        while (in.get(ch) && std::isdigit(ch)) {
            current_token.value += ch;
        }
        in.putback(ch);
        current_token.type = 'N';
    } else {
        current_token.value = ch;
        current_token.type = ch;
    }
}

void read_to_first_identifier(std::istream &in) {
    do {
        get_token(in);
        token_stack.push(current_token);
    } while (current_token.type != 'I');

    std::cout << current_token.value << " as a ";
    token_stack.pop();

    get_token(in);
}

void deal_with_function_args(std::istream &in) {
    while (current_token.type != ')') {
        get_token(in);
    }
    get_token(in);
    std::cout << "function returning ";
}

void deal_with_arrays(std::istream &in) {
    std::cout << "array ";
    get_token(in);

    if (current_token.type == 'N') {
        std::cout << "with size " << current_token.value << " ";
        get_token(in);
    }

    std::cout << "of ";
    get_token(in);
}

void deal_with_pointers() {
    while (!token_stack.empty() && token_stack.top().type == '*') {
        std::cout << "pointer to ";
        token_stack.pop();
    }
}

void deal_with_declarator(std::istream &in) {
    if (current_token.type == '[') {
        deal_with_arrays(in);
    } else if (current_token.type == '(') {
        deal_with_function_args(in);
    }

    while (!token_stack.empty()) {
        deal_with_pointers();

        if (token_stack.top().type == '(') {
            token_stack.pop();
            get_token(in);
            deal_with_declarator(in);
        } else {
            std::cout << token_stack.top().value << " ";
            token_stack.pop();
        }
    }
}

void process_file(const std::string &filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filepath << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::istringstream input_stream(line);
        try {  
            std::cout << "declare ";
            read_to_first_identifier(input_stream);
            deal_with_declarator(input_stream);
            std::cout << std::endl;
        } catch (const std::exception &e) {
            std::cerr << "Error parsing line: " << line << "\n";
        }
    }

    file.close();
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <file_path>" << std::endl;
        return 1;
    }

    process_file(argv[1]);
    return 0;
}
