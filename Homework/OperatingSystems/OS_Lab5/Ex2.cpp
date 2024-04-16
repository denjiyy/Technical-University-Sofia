#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <mutex>
#include <algorithm>

std::mutex mtx;
std::vector<int> max_values;

void find_max(std::vector<int>::iterator start, std::vector<int>::iterator end) {
    int max_value = *std::max_element(start, end);
    std::lock_guard<std::mutex> lock(mtx);
    max_values.push_back(max_value);
}

int main() {
    std::ifstream file("numbers.txt");
    if (!file) {
        std::cerr << "Could not open the file.\n";
        return 1;
    }

    int num_count;
    file >> num_count;

    std::vector<int> numbers(num_count);
    for (int& num : numbers) {
        file >> num;
    }

    int thread_count = std::thread::hardware_concurrency();
    std::vector<std::thread> threads(thread_count);

    int block_size = num_count / thread_count;
    for (int i = 0; i < thread_count; ++i) {
        auto start = numbers.begin() + i * block_size;
        auto end = (i == thread_count - 1) ? numbers.end() : start + block_size;
        threads[i] = std::thread(find_max, start, end);
    }

    for (auto& th : threads) {
        th.join();
    }

    int global_max = *std::max_element(max_values.begin(), max_values.end());
    std::cout << "Max value is: " << global_max << '\n';

    return 0;
}
