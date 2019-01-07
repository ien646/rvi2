#include "random_gen.hpp"
    
random_gen::random_gen()
    : rand_gen(std::mt19937(static_cast<int>(time(0))))
    , rand_dist_float(std::uniform_real_distribution<float>(-1000.0f, 1000.0f))
    , rand_dist_int(std::uniform_int_distribution<int>(-1000, 1000))
{ }

random_gen::random_gen(int seed)
    : rand_gen(std::mt19937(seed))
    , rand_dist_float(std::uniform_real_distribution<float>(-1000.0f, 1000.0f))
    , rand_dist_int(std::uniform_int_distribution<int>(-1000, 1000))
{ }

float random_gen::get_random_float(bool avoid_zeroes)
{
    float result = rand_dist_float(rand_gen);
    bool isInvalid = std::isnan(result) && std::isinf(result);
    bool isZero = (result == 0);
    while(isInvalid || (avoid_zeroes && isZero))
    {
        result = rand_dist_float(rand_gen);
    }
    return result;
}

int random_gen::get_random_int()
{
    return rand_dist_int(rand_gen);
}