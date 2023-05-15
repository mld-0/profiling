#include <chrono>
#include <iostream>
#include <vector>
#include <random>

int main() {
    const int SIZE = 10'000'000;  // Adjust this to be larger than the smaller CPU's cache size
    std::vector<int> data(SIZE);

    // Initialize the vector with random values
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100);

    for(int i = 0; i < SIZE; ++i) {
        data[i] = dis(gen);
    }

    auto start = std::chrono::high_resolution_clock::now();

    // Repeatedly access the entire array
    volatile int sum = 0;
    for (int repeat = 0; repeat < 10; ++repeat) {
        for (int i = 0; i < SIZE; ++i) {
            sum += data[i];
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::micro> diff_micro = end-start;

    std::cout << "Time to complete random memory access: " << diff_micro.count() << " us\n";

    return 0;
}
