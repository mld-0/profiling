#include <chrono>
#include <iostream>

long long fib(int n) {
    if (n <= 1)
        return n;
    else
        return fib(n-1) + fib(n-2);
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    long long result = fib(50);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end-start;

    std::cout << "Time to calculate 50th Fibonacci number: " << diff.count() << " s\n";
    std::cout << "Result: " << result << "\n";

    return 0;
}
