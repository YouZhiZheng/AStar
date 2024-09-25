#ifndef RANDOMNUM_H
#define RANDOMNUM_H

#include <random>
#include <utility>

class RandomNumGenerator 
{
public:
    RandomNumGenerator() = delete;
    RandomNumGenerator(size_t max_i_val, size_t max_j_val)
        : rng(std::random_device{}()), dist_i(0, max_i_val - 1), dist_j(0, max_j_val - 1) {}

    // 生成两个随机数并返回为 std::pair
    std::pair<int, int> generateTwo() 
    {
        return {dist_i(rng), dist_j(rng)};
    }

private:
    std::mt19937 rng;                // 随机数引擎（Mersenne Twister）
    std::uniform_int_distribution<size_t> dist_i, dist_j;  // 均匀分布
};

#endif