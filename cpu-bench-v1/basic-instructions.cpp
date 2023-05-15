#include <chrono>
#include <iostream>

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    volatile int result = 0;
    for (int i = 0; i < 1000000; ++i) {
        result += i;
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::micro> diff_micro = end-start;

    std::cout << "Time to complete 1M basic operations: " << diff_micro.count() << " us\n";

    return 0;
}
