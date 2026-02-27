#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <memory>
#include <chrono>
#include <random>
#include <iomanip>

const int NUM_THREADS = std::thread::hardware_concurrency();
constexpr int N = 500;
std::mutex cout_mutex;                     // 只用于打印，不影响计算性能

// ====================== 辅助函数 ======================
void print_time(const std::string& name, std::chrono::duration<double> duration) {
    std::lock_guard<std::mutex> lock(cout_mutex);
    std::cout << std::setw(20) << name 
              << ": " << std::fixed << std::setprecision(3) 
              << duration.count() << " 秒\n";
}

// ====================== 单线程矩阵乘法 ======================
void matrix_multiply_single(const double* A, const double* B, double* C) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            double sum = 0.0;
            for (int k = 0; k < N; ++k) {
                sum += A[i * N + k] * B[k * N + j];
            }
            C[i * N + j] = sum;
        }
    }
}

// ====================== 多线程矩阵乘法（每线程计算一块行） ======================
void matrix_multiply_thread(const double* A, const double* B, double* C,
                            int start_row, int end_row) 
{
    for (int i = start_row; i < end_row; ++i) {
        for (int j = 0; j < N; ++j) {
            double sum = 0.0;
            for (int k = 0; k < N; ++k) {
                sum += A[i * N + k] * B[k * N + j];
            }
            C[i * N + j] = sum;
        }
    }
}

// ====================== 主函数 ======================
int main() {
    std::cout << "正在生成 " << N << "x" << N << " 随机矩阵...\n";

    // 使用智能指针 RAII 管理三个大矩阵（避免内存泄漏）
    auto A = std::make_unique<double[]>(N * N);
    auto B = std::make_unique<double[]>(N * N);
    auto C_single = std::make_unique<double[]>(N * N);
    auto C_multi  = std::make_unique<double[]>(N * N);

    // 随机填充矩阵 A 和 B
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(0.0, 10.0);

    for (int i = 0; i < N * N; ++i) {
        A[i] = dis(gen);
        B[i] = dis(gen);
    }

    std::cout << "开始计算...\n\n";

    // ==================== 单线程版本 ====================
    auto start_single = std::chrono::high_resolution_clock::now();
    matrix_multiply_single(A.get(), B.get(), C_single.get());
    auto end_single = std::chrono::high_resolution_clock::now();
    auto time_single = end_single - start_single;

    print_time("单线程矩阵乘法", time_single);

    // ==================== 多线程版本 ====================
    auto start_multi = std::chrono::high_resolution_clock::now();

    std::vector<std::unique_ptr<std::thread>> threads;
    int chunk = N / NUM_THREADS;

    for (int i = 0; i < NUM_THREADS; ++i) {
        int start = i * chunk;
        int end = (i == NUM_THREADS - 1) ? N : start + chunk;

        auto t = std::make_unique<std::thread>(
            matrix_multiply_thread, 
            A.get(), B.get(), C_multi.get(), start, end);

        threads.push_back(std::move(t));        // 使用移动语义
    }

    // 等待所有线程完成
    for (auto& t : threads) {
        if (t->joinable()) t->join();
    }

    auto end_multi = std::chrono::high_resolution_clock::now();
    auto time_multi = end_multi - start_multi;

    print_time("多线程矩阵乘法", time_multi);

    std::cout << "\n加速比: " 
              << std::fixed << std::setprecision(2)
              << time_single.count() / time_multi.count() << "x\n";

    std::cout << "OK" << std::endl;
    return 0;
}