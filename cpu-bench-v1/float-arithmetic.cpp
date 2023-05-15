#include <chrono>
#include <iostream>

int main() {
    const int SIZE = 1'000'000'000;
    auto start = std::chrono::high_resolution_clock::now();
    
    double sum = 0.0;
    for (int i = 0; i < SIZE; ++i) {
        sum += i * 0.1;
    }

	volatile double x = sum;
    
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::micro> diff_micro = end-start;
    std::cout << "Time to calculate float arithmetic: " << diff_micro.count() << " us\n";
    return 0;
}
