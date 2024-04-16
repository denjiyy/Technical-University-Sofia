#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;
int current_odd = 1;
int current_even = 2;

void print_next_odd() {
    std::lock_guard<std::mutex> lock(mtx);
    if (current_odd < 10) {
        std::cout << "th1: " << current_odd << std::endl;
        current_odd += 2;
    }
}

void print_next_even() {
    std::lock_guard<std::mutex> lock(mtx);
    if (current_even <= 10) {
        std::cout << "th2: " << current_even << std::endl;
        current_even += 2;
    }
}

int main() {
    while (current_odd < 10) {
        std::thread th1(print_next_odd);
        th1.join();
    }
    while (current_even <= 10) {
        std::thread th2(print_next_even);
        th2.join();
    }

    current_odd = 1;
    current_even = 2;

    for (int i = 1; i <= 10; ++i) {
        if (i % 2 == 0) {
            std::thread th2(print_next_even);
            th2.join();
        }
        else {
            std::thread th1(print_next_odd);
            th1.join();
        }
    }

    return 0;
}