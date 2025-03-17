#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <vector>

struct Xorshift {
    uint64_t a;
    Xorshift(uint64_t seed = 123456789) : a(seed) {}
    uint64_t operator()() {
        a ^= a << 13;
        a ^= a >> 7;
        a ^= a << 17;
        return a;
    }
};

double sumRandomElements(const std::vector<double>& A, int K) {
    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::uniform_int_distribution<> dis(0, A.size() - 1);
    // static Xorshift rng{};
    // uint32_t N = A.size();

    double sum1 = 0.0, sum2 = 0.0, sum3 = 0.0, sum4 = 0.0;

    int i = 0;
    for (; i < K >> 2; i++) {
        // sum1 += A[static_cast<uint32_t>(rng()) % N];
        // sum2 += A[static_cast<uint32_t>(rng()) % N];
        // sum3 += A[static_cast<uint32_t>(rng()) % N];
        // sum4 += A[static_cast<uint32_t>(rng()) % N];
        sum1 += A[dis(gen)];
        sum2 += A[dis(gen)];
        sum3 += A[dis(gen)];
        sum4 += A[dis(gen)];
    }

    for (i <<= 2; i < K; ++i) {
        // sum1 += A[static_cast<uint32_t>(rng()) % N];
        sum1 += A[dis(gen)];
    }

    return sum1 + sum2 + sum3 + sum4;
}

// double sumRandomElements(const std::vector<double>& A, int K) {
//     static std::random_device rd;
//     static std::mt19937 gen(rd());

//     std::uniform_int_distribution<> dis(0, A.size() - 1);

//     std::vector<int> A_i(K);
//     std::generate(A_i.begin(), A_i.end(), [&] { return dis(gen); });
//     std::sort(A_i.begin(), A_i.end());

//     double sum = 0.0;

//     for (int i = 0; i < K; ++i) {
//         int index = A_i[i];
//         sum += A[index];
//     }

//     return sum;
// }

// TODO: generate uniform distribution in ascending order
// generate N + K bounds -> (a_i, b[i+1]-b[i] times)

#include <array>
#include <vector>

// double sumRandomElements(const std::vector<double>& A, int K) {
//     // static std::random_device rd;
//     // static std::mt19937 gen(rd());

//     // std::uniform_int_distribution<> dis(0, A.size() - 1);

//     static Xorshift rng{};

//     uint32_t N = A.size();
//     double sum = 0.0;

//     for (int i = 0; i < K; ++i) {
//         // int index = dis(gen);
//         uint32_t index = static_cast<uint32_t>(rng()) % N;
//         sum += A[index];
//     }

//     return sum;
// }

int main() {
    int N = 50000000;
    int K = 50000000;

    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::normal_distribution<> dis(0, 1);

    std::vector<double> A(N);
    std::generate(A.begin(), A.end(), [&] { return dis(gen); });

    auto start = std::chrono::high_resolution_clock::now();
    double result = sumRandomElements(A, K);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;

    std::cout << "Sum: " << result << std::endl;
    std::cout << "Time: " << duration.count() << " sec" << std::endl;

    return 0;
}
