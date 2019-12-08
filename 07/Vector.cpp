#include <iostream>
#include <iterator>

template<
        typename _Category,
        typename _Tp,
        typename _Distance = ptrdiff_t,
        typename _Pointer = _Tp*,
        typename _Reference = _Tp&>
struct iterator
{
    /// One of the @link iterator_tags tag types@endlink.
    typedef _Category  iterator_category;
    /// The type "pointed to" by the iterator.
    typedef _Tp        value_type;
    /// Distance between iterators is represented as this type.
    typedef _Distance  difference_type;
    /// This type represents a pointer-to-value_type.
    typedef _Pointer   pointer;
    /// This type represents a reference-to-value_type.
    typedef _Reference reference;
};

template <class T>
class Iterator
        : public std::iterator<std::forward_iterator_tag, T>
{
    T* ptr_;
public:
    explicit Iterator(T* ptr)
            : ptr_(ptr)
    {
    }

    bool operator==(const Iterator<T>& other) const
    {
        return ptr_ == other.ptr_;
    }

    bool operator!=(const Iterator<T>& other) const
    {
        return !(*this == other);
    }

    T& operator*() const
    {
        return *ptr_;
    }

    Iterator& operator++()
    {
        ++ptr_;
        return *this;
    }

    Iterator&operator--()
    {
        --ptr_;
        return *this;
    }
};

template<class T>
class Vector
{
public:
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using iterator = Iterator<T>;
    using reverse_iterator = std::reverse_iterator<Iterator<T>>;

    Vector () {
        data_ = new T[16];
        reserv = 16;
        size_ = 0;
    }

    Vector(std::initializer_list<T> init) {
        size_t i = 0;
        data_ = new T[16];
        reserv = 16;
        size_ = 0;
        auto current = init.begin();
        const auto end = init.end();

        while(current != end) {
            if (size_ >= reserv) {
                T *help = new T[2 * reserv];
                for (size_t j = 0; j < reserv; j++) {
                    help[j] = data_[j];
                }

                delete []data_;
                data_ = help;
                reserv *= 2;
            }

            data_[i] = *current;
            i++;
            current++;
            size_++;
        }

    }

    size_t size() {
        return size_;
    }

    T& operator[](size_t i) {
        if (i >= size_)
            throw std::runtime_error("SEGFAULT\n");

        return data_[i];
    }

    void push_back(T&& val) {
        if (size_ >= reserv) {
            T *help = new T[2 * reserv];
            for (int j = 0; j < reserv; j++) {
                help[j] = data_[j];
            }

            delete[]data_;
            data_ = help;
            reserv *= 2;
        }

        data_[size_] = val;
        size_++;
    }

    void push_back(const T& val) {
        if (size_ >= reserv) {
            T *help = new T[2 * reserv];
            for (size_t j = 0; j < reserv; j++) {
                help[j] = data_[j];
            }

            delete[]data_;
            data_ = help;
            reserv *= 2;
        }

        data_[size_] = val;
        size_++;
    }

    T pop_back() {
        T ans = data_[size_ - 1];
        size_--;

        if (size_ == 0) {
            reserv = 0;
            delete [] data_;
            return ans;
        }

        if (size_ <= reserv / 2 && reserv > 16) {
            T *help = new T[reserv / 2];
            for (size_t j = 0; j < size_; j++) {
                help[j] = data_[j];
            }

            delete[]data_;
            data_ = help;
            reserv /= 2;
        }

        return ans;
    }

    bool empty() {
        return !size_;
    }

    void clear() {
        size_ = 0;
        reserv = 0;
        delete []data_;
    }

    iterator begin() const  noexcept {
        return iterator(data_);
    }

    iterator end() const noexcept  {
        return iterator(data_ + size_);
    }

    reverse_iterator rbegin() const noexcept {
        return reverse_iterator(end());
    }

    reverse_iterator rend() const noexcept {
        return reverse_iterator(begin());
    }
protected:
    size_t size_;
    size_t reserv;
    T *data_;
};


int main()
{
    Vector<int> a = {1, 2, 3, 4 , 5};
    for (int i = 0; i < a.size(); i++) {
        std::cout << a[i] << ' ';
    }
    std::cout << "\n";

    for (int i = 6; i < 100; i++)
        a.push_back(i);

    for (int i = 0; i < a.size(); i++) {
        std::cout << a[i] << ' ';
    }
    std::cout << "\n";

    for (int i = 0; i < 50; i++)
        std::cout << a.pop_back() << ' ';
    std::cout << '\n';

    for (int i = 0; i < a.size(); i++) {
        std::cout << a[i] << ' ';
    }
    std::cout << "\n";

   // a.clear();
    //std::cout << a[0];

    auto it = a.rbegin();
    while(it != a.rend()) {
        std::cout << *it << ' ';
        ++it;
    }
    return 0;
}