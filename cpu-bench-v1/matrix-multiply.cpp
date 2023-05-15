#include <chrono>
#include <iostream>
#include <vector>
#include <random>

int main() {
    const int SIZE = 500; // Adjust this value based on your CPU capability
    std::vector<std::vector<int>> matrix1(SIZE, std::vector<int>(SIZE));
    std::vector<std::vector<int>> matrix2(SIZE, std::vector<int>(SIZE));
    std::vector<std::vector<int>> result(SIZE, std::vector<int>(SIZE));

    // Initialize the matrices with random values
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100);

    for(int i = 0; i < SIZE; ++i) {
        for(int j = 0; j < SIZE; ++j) {
            matrix1[i][j] = dis(gen);
            matrix2[i][j] = dis(gen);
        }
    }

    auto start = std::chrono::high_resolution_clock::now();

    // Perform matrix multiplication
    for(int i = 0; i < SIZE; ++i) {
        for(int j = 0; j < SIZE; ++j) {
            result[i][j] = 0;
            for(int k = 0; k < SIZE; ++k) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::micro> diff_micro = end-start;
    std::cout << "Time to calculate matrix multiply: " << diff_micro.count() << " us\n";

    return 0;
}

