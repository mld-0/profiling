#include <chrono>
#include <iostream>

int main() {
    const int SIZE = 100'000'000;
    auto start = std::chrono::high_resolution_clock::now();
    
    volatile int sum = 0;
    for (int i = 0; i < SIZE; ++i) {
        sum += i;
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::micro> diff_micro = end-start;
    std::cout << "Time to calculate integer arithmetic: " << diff_micro.count() << " us\n";
    return 0;
}
