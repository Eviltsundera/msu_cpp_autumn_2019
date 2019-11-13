#include <iostream>
#include <cmath>
#include <string>
#include <iomanip>



class BigInt
{
public:
    //static const int MAX_DIGIT = static_cast<int>(1e9 - 1);
    //static const int MIN_DIGIT = static_cast<int>(1e9 - 1);
    static const int BASE = static_cast<int>(1e9);
    bool is_negative;
    int* digit_array;
    int ar_size;

    //////////////////////////
    // Constructors section//

    BigInt() { // basic constructor
        digit_array = nullptr;
        is_negative = false;
        ar_size = 0;
    }

    BigInt(int num) { // constructor from integer value
        is_negative = (num < 0);
        int tmp = is_negative ? -num : num;
        if (tmp < BASE) {
            digit_array = (int*)malloc(sizeof(int));
            digit_array[0] = tmp;
            ar_size = 1;
        } else {
            digit_array = (int*)malloc(2 * sizeof(int));
            digit_array[0] = tmp % BASE;
            digit_array[1] = tmp / BASE;
            ar_size = 2;
        }
    }

    BigInt(const std::string& str) { // string constructor
        if (!str.length()) {
            is_negative = false;
            ar_size = 0;
        } else {
            if (str[0] == '-') {
                is_negative = true;
            }
            else is_negative = false;

            if (!is_negative) {
                ar_size = static_cast<int>(str.length() / 9) + 1;
            } else ar_size = static_cast<int>(str.length() - 1) / 9 + 1;
            
            digit_array = (int*)malloc(ar_size * sizeof(int));
            int counter = 0;
            for (int i = str.length(); i > 0; i -= 9) {
                if (!is_negative) {
                    if (i < 9) {
                    digit_array[counter] = atoi(str.substr(0, i).c_str());
                    counter++;
                    } else {
                        digit_array[counter] = atoi(str.substr(i - 9, 9).c_str());
                        counter++;
                    }
                } else {
                    if (i < 10) {
                        digit_array[counter] = atoi(str.substr(1, i).c_str());
                        counter++;
                    } else {
                        digit_array[counter] = atoi(str.substr(i - 9, 9).c_str());
                        counter++;
                    }
                }
            }
        }
    }

    BigInt(const BigInt &copied) // copy constructor
            : is_negative(copied.is_negative)
            , ar_size(copied.ar_size)
    {
        digit_array = (int*)malloc(ar_size * sizeof(int));
        std::copy(copied.digit_array, copied.digit_array + copied.ar_size, digit_array);
    }

    // End of constructor section//
    ///////////////////////////////

    /////////////////////////////
    //comparative operators section//

    bool operator==(const BigInt &num) const {
        if (num.ar_size != ar_size) return false;
        for (int i = ar_size - 1; i >= 0; i--) {
            if (num.digit_array[i] != digit_array[i]) return false;
        }
        return true;
    }

    bool operator !=(const BigInt &num) const{
        return !(operator==(num));
    }

    bool operator >(const BigInt &num) const {
        if (is_negative && !num.is_negative) return false;
        if (!is_negative && num.is_negative) return true;

        if (!is_negative) {
            if (ar_size > num.ar_size) return true;
            else if (ar_size < num.ar_size) return false;

            for (int i = ar_size - 1; i >= 0; i--) {
                if (digit_array[i] > num.digit_array[i]) return true;
                else if (digit_array[i] < num.digit_array[i]) return false;
            }
            return false;
        } else {
            if (ar_size > num.ar_size) return false;
            else if (ar_size < num.ar_size) return true;

            for (int i = ar_size - 1; i >= 0; i--) {
                if (digit_array[i] > num.digit_array[i]) return false;
                else if (digit_array[i] < num.digit_array[i]) return true;
            }
            return false;
        }
    }

    bool operator >=(const BigInt &num) const {
        return operator>(num) || operator==(num);
    }

    bool operator <=(const BigInt &num) const  {
        return !(operator>(num));
    }

    bool operator <(const BigInt &num) const {
        return operator<=(num) && !operator==(num);
    }

    //end of comparative section//
    //////////////////////////

    ////////////////////////
    //assigment operators//
    BigInt& operator=(const BigInt& copied) {
        is_negative = copied.is_negative;
        ar_size = copied.ar_size;
        free(digit_array);
        digit_array = (int*)malloc(ar_size * sizeof(int));
        std::copy(copied.digit_array, copied.digit_array + copied.ar_size, digit_array);
        return *this;
    }

    BigInt& operator=(const int n) {
        BigInt tmp = BigInt(n);
        return operator=(tmp);
    }

    BigInt& operator=(const std::string& str) {
        BigInt tmp = BigInt(str);
        return operator=(tmp);
    }
    //end of assigment section//
    ///////////////////////////


    /////////////////////////
    //ariphmetic operators//

    BigInt operator-() const {
        //BigInt copy;
        BigInt res(*this);
        res.is_negative = !res.is_negative;
        return res;
    }

    BigInt operator+(const BigInt& other) const {
        if (is_negative) {
            if (other.is_negative) return -(-(*this) + (-other));
            else return other - (-(*this));
        }
        else if (other.is_negative) return *this - (-other);

        int carry = 0;
        BigInt tmp;
        tmp = *this;

        if (other.ar_size > ar_size) {
            tmp.ar_size = other.ar_size;
            tmp.digit_array = (int*)realloc(tmp.digit_array, tmp.ar_size * sizeof(int));
            for (int i = ar_size; i < tmp.ar_size; i++) tmp.digit_array[i] = 0;
        }

        for (int i = 0; i < tmp.ar_size || carry != 0; i++) {
            if (i == tmp.ar_size) {
                tmp.ar_size++;
                tmp.digit_array = (int*)realloc(tmp.digit_array, tmp.ar_size * sizeof(int));
                tmp.digit_array[tmp.ar_size - 1] = 0;
            }
            tmp.digit_array[i] += carry + (i < other.ar_size ? other.digit_array[i] : 0);
            carry = tmp.digit_array[i] >= BASE;
            if (carry) tmp.digit_array[i] -= BASE;
            //std::cout << i << ' ' << tmp.digit_array[i] << ' ' << carry << '\n';
        }
        //std::cout << tmp.digit_array[0] << ' ' << tmp.digit_array[1] << '\n';
        return tmp;
    }

    BigInt operator-(const BigInt& other) const {
        if (other.is_negative) return (*this) + (-other);
        else if (is_negative) return - (-(*this) + other);
        else if ((*this) < other) return -(other - *this);

        int carry = 0;
        static BigInt tmp;
        tmp = *this;

        for (int i = 0; i < other.ar_size || carry != 0; i++) {
            tmp.digit_array[i] -= carry + (i < other.ar_size ? other.digit_array[i] : 0);
            carry = tmp.digit_array[i] < 0;
            if (carry) tmp.digit_array[i] += BASE;
        }
        tmp.remove_zeroes();
        return tmp;
    }

    //end of ariphmetic section//
    ////////////////////////////

    void remove_zeroes() {
        int i = ar_size - 1;
        while(digit_array[i] == 0 && i >= 0) {
            i--;
            ar_size--;
        }

        if (!ar_size) {
            digit_array = (int*)realloc(digit_array, ar_size * sizeof(int));
            is_negative = false;
        } else {
            digit_array = (int*)realloc(digit_array, ar_size * sizeof(int));
        }
    }

    ~BigInt() {
        free(digit_array);
    }
};

std::ostream& operator<<(std::ostream& os, const BigInt &n) {
    if (n.ar_size == 0) {
        os << 0;
        return os;
    }

    if (n.is_negative) os << '-';
    os << n.digit_array[n.ar_size - 1];
    char old_fill = os.fill('0');
    for (int i = n.ar_size - 2; i >= 0; i--) os << std::setw(9) <<  n.digit_array[i];
    os.fill(old_fill);
    return os;
}


int main()
{
    std::string str = "1234567900000000000000000000000";
    BigInt n = 2000000000;
    BigInt m = str;
    std::cout << m << " + " << n << " = " << (m + n) << "\n";
    std::cout << m << " - " << n << " = " << (m - n) << "\n";
    std::cout << n << " - " << m << " = " << (n - m) << "\n";

    BigInt tmp = 75;
    BigInt a = tmp;
    BigInt b = -tmp;
    std::cout << tmp << " " << a << " " << b << "\n";
    b = a;
    std::cout << tmp << " " << a << " " << b << "\n";
    str = "1234567900000000000000000780000";
    n = str;
    std::cout << n - m << "\n\n\n\n";

    a = "12345678999";
    b = "23456789999";
    std::cout << a << " + " << b << " = " << a + b << "\n";
    std::cout << -a << " + " << b << " = " << -a + b << "\n";
    std::cout << a << " + " << -b << " = " << a + (-b) << "\n";
    std::cout << -a << " + " << -b << " = " << -a + (-b) << "\n";
    std::cout << a << " - " << b << " = " << a - b << "\n";
    std::cout << -a << " - " << b << " = " << -a - b << "\n";
    std::cout << a << " - " << -b << " = " << a - (-b) << "\n";
    std::cout << -a << " - " << -b << " = " << -a - (-b) << "\n";
    return 0;
}
