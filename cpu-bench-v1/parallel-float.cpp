#include <chrono>
#include <iostream>
#include <vector>
#include <thread>

void work(long start, long end) {
    volatile double result = 0.0;
    for(long i = start; i < end; ++i) {
        result += i;
    }
}

int main() {
    const int NUM_THREADS = std::thread::hardware_concurrency();
    const long TOTAL_WORK = 1'000'000'000;  // 1 billion units of work
    long work_per_thread = TOTAL_WORK / NUM_THREADS;

    auto start = std::chrono::high_resolution_clock::now();

    std::vector<std::thread> threads;
    for(int i = 0; i < NUM_THREADS; ++i) {
        long work_start = i * work_per_thread;
        long work_end = (i == NUM_THREADS - 1) ? TOTAL_WORK : (i + 1) * work_per_thread;
        threads.push_back(std::thread(work, work_start, work_end));
    }

    for(auto& thread : threads) {
        thread.join();
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::micro> diff_micro = end-start;

    std::cout << "Time to complete float threads=(" << NUM_THREADS << "): " << diff_micro.count() << " us\n";

    return 0;
}

