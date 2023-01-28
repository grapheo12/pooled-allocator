#include "pooled_allocator.hpp"
#include <chrono>
#include <random>
#include <iostream>

#define GB *1024ll*1024*1024
#define OPS 1000000

int main()
{
    size_t sz = 20 GB;
    auto arena = new Arena(sz);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> dist1(0, sz - 1);
    std::uniform_int_distribution<size_t> dist2(0, 1);

    using namespace std::chrono;
    auto start = high_resolution_clock::now();
    for (int i = 0; i < OPS; i++){
        if (dist2(gen) == 0){
            // READ
            char c;
            arena->Read(dist1(gen), &c, 1);
        }else{
            // WRITE
            arena->Write(dist1(gen), "A", 1);
        }

        if (i % 1000 == 0){
            std::cout << "Ran op#" << i << std::endl;
        }
    }
    auto end = high_resolution_clock::now();
    

    std::cout << "Total time for " << OPS << "operations: " << (duration_cast<milliseconds>(end - start)).count() << "ms" << std::endl;
    std::cout << "Throughput: " << ((double)OPS / (duration_cast<milliseconds>(end - start)).count()) * 1e+3 << "ops/s" << std::endl;
    std::cout << "Size: " << sz << std::endl;
    return 0;
}