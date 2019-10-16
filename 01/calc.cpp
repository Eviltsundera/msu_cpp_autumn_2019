#include <iostream>
#include <string>

int parse_sum();
int parse_product();
int parse_factor();
bool check_char();
bool check_digit();
char *x;

#define MAX_LENGHT 10000

bool check_char() {
    if (*x >= '0' && *x <= '9') return false;
    if (*x == '-' || *x == '+' || *x == '*' || *x == '/') return false;
    return *x != '\0';
}

bool check_digit() {
    return !(*x >= '0' && *x <= '9');
}
int parse_sum() {
    int pro1 = parse_product();
    while(*x == '+' || *x == '-') {
        char op = *x;
        x++;
        int pro2 = parse_product();
        if (op == '+') {
            pro1 += pro2;
        } else {
            pro1 -= pro2;
        }
    }
    return pro1;
}

int parse_product() {
    int fac1 = parse_factor();
    while(*x == '*' || *x == '/') {
        char op = *x;
        x++;
        int fac2 = parse_factor();
        if (op == '*') {
            fac1 *= fac2;
        } else {
            if (!fac2) {
                std::cout << "DIVISION BY ZERO\n";
                exit(1);
            }
            fac1 /= fac2;
        }
    }
    return fac1;
}

int parse_factor() {
    bool sign = 0;
    if (*x == '-') {
        sign = 1;
        x++;
    }

    if (check_digit()) {
        std::cout << "BAD EXPRESSION\n";
        exit(1);
    }

    int result = 0;
    while(*x >= '0' && *x <= '9') {
        result *= 10;
        result += *x - (int)'0';
        x++;
    }

    if (check_char()) {
        std::cout << "BAD EXPRESSION\n";
        exit(1);
    }
    if (sign) result *= -1;
    return result;
}


int main(int argc, const char *argv[]) {
    //std::cout << "Enter your expresion\n";
    if (argc < 2) {
        return 1;
    }
    std::string tmp_expr = argv[1];
    //getline(argv[1], tmp_expr);

    char expr[MAX_LENGHT];
    x = expr;
    for (unsigned long i = 0; i < tmp_expr.length(); i++) {
        if (tmp_expr[i] == ' ' || tmp_expr[i] == '\t')
            continue;
        if (tmp_expr[i] >= '0' && tmp_expr[i] <= '9' && i >= 2 &&
                (tmp_expr[i - 1] == ' ' || tmp_expr[i - 1] == '\t') && (tmp_expr[i - 2] >= '0' && tmp_expr[i - 2] <= '9')) {
            std::cout << "BAD EXPRESSION\n";
            exit(1);
        }
        *x = tmp_expr[i];
        x++;
    }
    *x = '\0';
    x = expr;
    std::cout << parse_sum() << "\n";
    return 0;
}