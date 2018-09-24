#pragma once

#include <random>
#include <ctime>
#include <cinttypes>

static std::mt19937 rand_gen(static_cast<int>(time(0)));
static std::uniform_real_distribution<float> rand_dist_float(-1000.0F, 1000.0F);
static std::uniform_int_distribution<int> rand_dist_int(-1000, 1000);

static float get_random_float(bool avoid_zeroes = false)
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

static int get_random_int()
{
    return rand_dist_int(rand_gen);
}