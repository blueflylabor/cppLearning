// single_thread_convolution.cpp
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION 
#include "stb_image.h"
#include "stb_image_write.h"
#include <iostream>
#include <vector>
#include <cmath>

int main() {
    // 1. 读取图片（支持 jpg/png/bmp）
    int width, height, channels;
    unsigned char* img = stbi_load("../../input.jpg", &width, &height, &channels, 0);
    
    if (!img) {
        std::cerr << "Failed to load image!\n";
        return 1;
    }

    std::cout << "Loaded image: " << width << "x" << height 
              << " channels=" << channels << std::endl;

    // 2. 创建输出图像缓冲区（RAII 使用 unique_ptr）
    auto output = std::make_unique<unsigned char[]>(width * height * channels);

    // 3. 3x3 Sobel 边缘检测卷积核（水平方向）
    const int kernel[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    // 4. 对每个像素进行卷积
    for (int y = 1; y < height - 1; ++y) {
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
            for (int c = 0; c < channels; ++c) {
                output[out_idx + c] = result;   // 灰度显示边缘
            }
        }
    }

    // 5. 保存结果
    stbi_write_png("../../output_single.jpg", width, height, channels, output.get(), width * channels);
    
    std::cout << "Single thread convolution done! Saved as output_single.png\n";

    stbi_image_free(img);   // 释放原始图片
    std::cout << "OK" << std::endl;
    return 0;
}