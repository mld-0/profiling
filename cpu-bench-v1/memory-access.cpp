#include <chrono>
#include <iostream>
#include <vector>

int main() {
    const long SIZE = 100'000'000;
    std::vector<int> data(SIZE);
    auto start = std::chrono::high_resolution_clock::now();

	for (long i = 0; i < SIZE; ++i) {
		data[i] = i;
	}

	volatile int x = data[0];
	volatile int y = data[SIZE-1];
    
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::micro> diff_micro = end-start;
    std::cout << "Time to perform memory access: " << diff_micro.count() << " us\n";
    return 0;
}
