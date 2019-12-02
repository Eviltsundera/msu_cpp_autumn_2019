#include <iostream>
#include <string>
#include <sstream>
#include <vector>

template<class T>
std::string convert(T&& arg) 
{
    std:: stringstream s;
    s << arg;
    return s.str();
}

template<class... ArgsT>
std::string format(const std::string& str, ArgsT && ... args) {
    std::vector<std::string> formating_args = {convert(std::forward<ArgsT>(args))...};
    //int counter = 0;
    std::stringstream ans_str;

    for(int i = 0; i < str.length(); i++) {
        if (str[i] == '{') {
            int h_counter = 1;
            std::string tmp = "";
            int good_number_flag = 0;//0 - digit haven't seen
                                     //1 - digit have seen
                                     //2 - space have seen after digit

            while (str[i + h_counter] != '}') {
                if (!std::isdigit(str[i + h_counter]) 
                    && !std::isspace(str[i + h_counter])) {
                        throw std::runtime_error("Format error! Some trash in the string.");
                }

                if(std::isdigit(str[i + h_counter])) {
                    if(good_number_flag == 2) {
                        throw std::runtime_error("Format error! Spaces inside the bumber.");
                    }
                    tmp += str[i + h_counter];
                    good_number_flag = 1;
                }

                if(std::isspace(str[i + h_counter]) && good_number_flag == 1) {
                    good_number_flag = 2;
                }

                h_counter++;
            }

            try {
                if (tmp == "")
                    throw std::runtime_error("Format error! Missing argument.");

                int argnum = std::stoi(tmp, nullptr, 10);
                if (argnum >= formating_args.size())
                    throw std::runtime_error("Format error! Too large argument.");
                ans_str << formating_args[argnum];
            } 
            catch(std::invalid_argument& ){
                throw std::runtime_error("Format error! Unknown error with argument -\\../-");
            }


            i += h_counter;

        } else {
            if (str[i] == '}') 
                throw std::runtime_error("Unexpected right bracket!");
            ans_str << str[i];
        }
    }

    std::string ans = ans_str.str();
    return ans;
}

template<class... ArgsT>
bool test(const std::string& ans, const std::string& str, ArgsT && ... args) {
    try {
        if (format(str, std::forward<ArgsT>(args)...) == ans) {
            std:: cout << "OK" << '\n';
            return true;
        } else {
            std::cout << "WA\n";
            return false;
        }
    }
    catch(std::runtime_error& e) {
        std::cout << "Runtime error: " << e.what() << '\n';
        return false;
    }
    return false;
}

int main() {
    test("one+one = 2", "{1}+{1} = {0}", 2, "one");
    test("sss 1", "sss {0", 1);
    test("hehehe haha", "hehehe {{0}", "haha");
    test("lol d", "lol {}", "d");
    test("a 1 b 2 c 3", "a {0} b {1} c {3}", 1, 2 ,3);
    test("a 1 b 2 c 3", "a {0} b {1} c {2} }", 1, 2 ,3);
    return 0;
}