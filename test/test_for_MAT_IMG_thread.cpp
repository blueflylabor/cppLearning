// multi_thread_convolution.cpp
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION 
#include "stb_image.h"
#include "stb_image_write.h"
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <memory>
#include <cmath>
#include <algorithm>

std::mutex output_mutex;   // 保护输出缓冲区

void process_chunk(const unsigned char* img, unsigned char* output,
                   int width, int height, int channels,
                   int start_y, int end_y) 
{
    const int kernel[3][3] = {{-1,0,1},{-2,0,2},{-1,0,1}};

    for (int y = std::max(1, start_y); y < std::min(height-1, end_y); ++y) {
        for (int x = 1; x < width - 1; ++x) {
            int sum = 0;
            for (int ky = -1; ky <= 1; ++ky) {
                for (int kx = -1; kx <= 1; ++kx) {
                    int idx = ((y + ky) * width + (x + kx)) * channels;
                    sum += img[idx] * kernel[ky + 1][kx + 1];
                }
            }
            int out_idx = (y * width + x) * channels;
            unsigned char result = std::clamp(std::abs(sum), 0, 255);

            std::lock_guard<std::mutex> lock(output_mutex);  // RAII 锁
            for (int c = 0; c < channels; ++c) {
                output[out_idx + c] = result;
            }
        }
    }
}

int main() {
    int width, height, channels;
    unsigned char* img = stbi_load("../../input.jpg", &width, &height, &channels, 0);
    if (!img) {
        std::cerr << "Failed to load image!\n";
        return 1;
    }

    auto output = std::make_unique<unsigned char[]>(width * height * channels);  // RAII

    const int num_threads = std::thread::hardware_concurrency();  // 自动获取 CPU 核数
    std::vector<std::unique_ptr<std::thread>> threads;

    int chunk = height / num_threads;

    std::cout << "Starting " << num_threads << " threads for convolution...\n";

    for (int i = 0; i < num_threads; ++i) {
        int start = i * chunk;
        int end = (i == num_threads - 1) ? height : start + chunk;

        auto t = std::make_unique<std::thread>(
            process_chunk, img, output.get(), width, height, channels, start, end);

        threads.push_back(std::move(t));   // 使用移动语义
    }

    // 等待所有线程完成
    for (auto& t : threads) {
        if (t->joinable()) t->join();
    }

    stbi_write_png("../../output_multi.jpg", width, height, channels, output.get(), width * channels);

    std::cout << "Multi-thread convolution done! Saved as output_multi.png\n";

    stbi_image_free(img);
    std::cout << "OK" << std::endl;
    return 0;
}