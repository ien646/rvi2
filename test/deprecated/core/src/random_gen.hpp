#pragma once

#include <random>
#include <ctime>
#include <cinttypes>

class random_gen
{
private:
    std::mt19937 rand_gen;
    std::uniform_real_distribution<float> rand_dist_float;
    std::uniform_int_distribution<int> rand_dist_int;
    
public:
    random_gen();
    random_gen(int seed);

    float get_random_float(bool avoid_zeroes = false);
    int get_random_int();
};