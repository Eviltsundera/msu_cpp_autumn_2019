#include <iostream>
#include <cstdint>
#include <sstream>

enum class Error
{
    NoError,
    CorruptedArchive
};

class Serializer
{
    static constexpr char Separator = ' ';
    std::ostream& out_;
public:
    explicit Serializer(std::ostream& out)
            : out_(out)
    {
    }

    template <class T>
    Error save(T& object)
    {
        return object.serialize(*this);
    }

    template <class... ArgsT>
    Error operator()(ArgsT... args)
    {
        return process(args...);
    }

private:
    void print(uint64_t n) {
        out_ << n;
    }

    void print(bool val) {
        if (val) out_ << "true";
        else out_ << "false";
    }

    template <class T>
            Error process(T&& arg)
    {
        print(arg);
        out_ << "\n";
        return Error::NoError;
    }

    template <class T, class... Args>
            Error process(T&& arg, Args&& ... args)
    {
        print(arg);
        out_ << Separator;
        process(std::forward<Args>(args)...);
        return Error::NoError;
    }
};

class Deserializer
{
    std::istream& in_;
    static constexpr char Separator = ' ';
public:
    explicit Deserializer(std::istream& in)
        :in_(in)
    {
    }

    template <class T>
    Error load(T& object)
    {
        return object.serialize(*this);
    }

    template<class... ArgsT>
    Error operator()(ArgsT &&... args) {
        return process(args...);
    }

    template<class T, class... ArgsT>
    Error process(T &&val, ArgsT &&... args) {
        if (process(val) != Error::NoError)
            return Error::CorruptedArchive;
        return process(std::forward<ArgsT>(args)...);
    }

    Error process(bool &val) {
        std::string text;
        in_ >> text;

        if (text == "true")
            val = true;
        else if (text == "false")
            val = false;
        else
            return Error::CorruptedArchive;
        return Error::NoError;
    }

    Error process(uint64_t &val) {
        std::string text;
        in_ >> text;
        if (text.empty())
            return Error::CorruptedArchive;
        val = 0;
        for (auto i: text) {
            if (!(i >= '0' && i <= '9')) {
                return Error::CorruptedArchive;
            }
            val = val * 10 + i - '0';
        }
        return Error::NoError;
    }
};

struct Data
{
    uint64_t a;
    bool b;
    uint64_t c;

    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a, b, c);
    }
};

int main()
{
    Data x { 1, true, 2 };

    std::stringstream stream;
    std::string res;
    Serializer serializer(stream);
    serializer.save(x);
    Data y { 0, false, 0 };

    Deserializer deserializer(stream);
    const Error err = deserializer.load(y);

    assert(err == Error::NoError);

    std:: cout << y.a << ' ' << y.b << ' ' << y.c;
    assert(x.a == y.a);
    assert(x.b == y.b);
    assert(x.c == y.c);
    return 0;
}