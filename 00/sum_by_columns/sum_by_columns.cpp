#include <chrono>
#include <iostream>

class Timer
{
    using clock_t = std::chrono::high_resolution_clock;
    using microseconds = std::chrono::microseconds;
public:
    Timer()
        : start_(clock_t::now())
    {
    }

    ~Timer()
    {
        const auto finish = clock_t::now();
        const auto us = 
            std::chrono::duration_cast<microseconds>
                (finish - start_).count();
        std::cout << us << " us" << std::endl;
    }

private:
    const clock_t::time_point start_;
};

int main()
{
    int rows, columns;
    std::cout << "input size\n";
    std::cin >> rows >> columns;
    int **matrix = new int *[rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new int[columns * sizeof(int)];
    } 

    Timer t;
    long long int sum = 0;
    
    for (int j = 0; j < columns; j++)
        for (int i = 0; i < rows; i++)
            sum += matrix[i][j];

    std::cout << sum << std::endl;

    return 0;
}
