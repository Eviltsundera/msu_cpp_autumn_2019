#include <iostream>
#include <string>

int parse_sum(char *&x, int& err);
int parse_product(char *&x, int& err);
int parse_factor(char *&x, int& err);
bool check_char(char *&x);
bool check_digit(char *&x);


const int  MAX_LENGHT =  10000;

enum
{
    err_bad_expr = 1,
    err_zero_div = 2
};

bool check_char(char *&x) {
    if (*x >= '0' && *x <= '9') return false;
    if (*x == '-' || *x == '+' || *x == '*' || *x == '/') return false;
    return *x != '\0';
}

bool check_digit(char *&x) {
    return !(*x >= '0' && *x <= '9');
}
int parse_sum(char *&x, int& err) {
    if (err != 0) {
        return 0;
    }
    int pro1 = parse_product(x,err);
    while(*x == '+' || *x == '-') {
        char op = *x;
        x++;
        int pro2 = parse_product(x, err);
        if (op == '+') {
            pro1 += pro2;
        } else {
            pro1 -= pro2;
        }
    }
    return pro1;
}

int parse_product(char *&x, int& err) {
    if (err != 0) {
        return 0;
    }
    int fac1 = parse_factor(x, err);
    while(*x == '*' || *x == '/') {
        char op = *x;
        x++;
        int fac2 = parse_factor(x, err);
        if (op == '*') {
            fac1 *= fac2;
        } else {
            if (!fac2) {
                err = err_zero_div;
                return 0;
                
            }
            fac1 /= fac2;
        }
    }
    return fac1;
}

int parse_factor(char *&x, int& err) {
    if (err != 0) {
        return 0;
    }
    bool sign = 0;
    if (*x == '-') {
        sign = 1;
        x++;
    }

    if (check_digit(x)) {
        err = err_bad_expr;
        return 0;
    }

    int result = 0;
    while(*x >= '0' && *x <= '9') {
        result *= 10;
        result += *x - (int)'0';
        x++;
    }

    if (check_char(x)) {
        err = err_bad_expr;
        return 0;
    }
    if (sign) result *= -1;
    return result;
}

int calc(std::string& tmp_expr, int& err) {
    char *x;
    char expr[MAX_LENGHT];
    x = expr;
    for (unsigned long i = 0; i < tmp_expr.length(); i++) {
        if (tmp_expr[i] == ' ' || tmp_expr[i] == '\t')
            continue;
        if (tmp_expr[i] >= '0' && tmp_expr[i] <= '9' && i >= 2 &&
                (tmp_expr[i - 1] == ' ' || tmp_expr[i - 1] == '\t') && (tmp_expr[i - 2] >= '0' && tmp_expr[i - 2] <= '9')) {
            err = err_bad_expr;
            return 0;
        }
        *x = tmp_expr[i];
        x++;
    }
    *x = '\0';
    x = expr;

    int ans = parse_sum(x, err);
    return ans;
}

int main(int argc, const char *argv[]) {
    //std::cout << "Enter your expresion\n";
    if (argc < 2) {
        return 1;
    }
    std::string tmp_expr = argv[1];
    int err = 0;
    //getline(argv[1], tmp_expr);

    int ans = calc(tmp_expr, err);
    if (err == err_bad_expr) {
        std::cout << "BAD EXPRESSION\n";
        return 1;
    }
    if (err == err_zero_div) {
        std::cout << "DIVISION BY ZERO\n";
        return 1;
    }


    std::cout << ans << '\n';
    return 0;
}
