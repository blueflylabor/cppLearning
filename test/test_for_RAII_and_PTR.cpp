#include <iostream>
#include <memory>
#include <vector>
#include <mutex>
#include <limits>
#include <random>
#include <thread>
using namespace std;

class ArrHelper{
    public:
        std::unique_ptr<int []> data;
        size_t size;

        ArrHelper(size_t n) : size(n){
            data = std::make_unique<int []>(n);
            std::cout << "ArrHelper constructed, size = " << size << std::endl;
        }

        ArrHelper(ArrHelper&& other) noexcept : data(std::move(other.data)), size(other.size){
            std::cout << "ArrHelper moved (xval)" << std::endl;
        }

        ArrHelper(const ArrHelper&) = delete;

        ~ArrHelper(){
            std::cout << "ArrHelper destroyed (RAII auto delete)" << std::endl;
        }

        void fill(int val){
            for (size_t i = 0; i < size; i++)
                data[i] = val;
        }

        void show() const{
            std::cout << "Arr : " << std::endl;
            for (size_t i = 0; i < size; i++)
                std::cout << data[i] << " ";
            std:: cout << std::endl;
        }
};

std::mutex mtx;

void worker(int id){
    std::lock_guard<std::mutex> lock(mtx);
    std::cout << "thread " << id << "is working (protected by RAII lock)" << std::endl;
}

int g_max = std::numeric_limits<int>::min();
std::mutex max_mtx;

void findMaxInRange(const int* data, size_t start, size_t end){
    int local_max = std::numeric_limits<int>::min();
    for (size_t i = start; i < end; i++)
        if(data[i] > local_max) 
            local_max = data[i];
    
    std::lock_guard<std::mutex> lock(max_mtx);
    if(local_max > g_max){
        g_max = local_max;
        std::cout << "temp: gmax = " << g_max << std::endl;
    }
}

void findMaxE2Arr(){
    const size_t size = 100'000'000;
    const int thread_count = 6;
    std:;cout << "Creating arr with " << size << " elements..." << std::endl;
    auto bigArr = std::make_unique<int[]>(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(-10000, 100000);
    for (size_t i = 0; i < size; i++)
        bigArr[i] = dis(gen);
    bigArr[666'666] = 10000;
    std::cout << "Starting " << thread_count << " thread..." << std::endl;
    std::vector<std::unique_ptr<std::thread>> threads;
    size_t chunk_size = size / thread_count;
    for (int i = 0; i < thread_count; i++){
        size_t start = i * chunk_size;
        size_t end = (i == thread_count - 1) ? size : start + chunk_size;
        auto t = std::make_unique<std::thread>(findMaxInRange, bigArr.get(), start, end);
        threads.push_back(std::move(t));
    }
    for(auto& t : threads)
        if(t->joinable())
            t->join();
    std::cout << "Max val in arr = " << g_max << std::endl;
    std::cout << "All done. (RAII auto clean up)" << std::endl;

}

void random_test(){
    std::random_device rd;
    for (int i = 0; i < 5; i++)
        std::cout << rd() << " ";
    std::cout << std::endl;
}

void mt19937_random(){
    std::mt19937 gen_fixed(12345);
    std::cout << "Fixed seed (12345):" << std::endl;
    for(int i = 0; i < 5; i++)
        std::cout << gen_fixed() << " ";
    std::cout << std::endl;
}

void mt19937_1000_random(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(-1000, 1000);
    std::cout << "10 random num in [-1000, 1000]" << std::endl;
    for(int i = 0; i < 10; i++)
        std::cout << dist(gen) << " ";
    std::cout << std::endl;
}

void numeric_limits_for_type_of_val(){
    std::cout << "min max lowest digits";
    std::cout << std::numeric_limits<int>::min() << " ";
    std::cout << std::numeric_limits<int>::max() << " ";
    std::cout << std::numeric_limits<double>::lowest() << " ";
    std::cout << std::numeric_limits<int>::digits << std::endl;
}

int main(){
    ArrHelper ah1(5);
    ah1.show();
    ah1.fill(42);
    ah1.show();
    ArrHelper ah2 = std::move(ah1);
    ah2.show();

    random_test();
    mt19937_random();
    mt19937_1000_random();
    numeric_limits_for_type_of_val();
    // findMaxE2Arr();
    

    std::cout << "OK" << std::endl;
    return 0;
}