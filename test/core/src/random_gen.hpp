#pragma once

#include <random>
#include <ctime>
#include <cinttypes>

static std::mt19937 Rand_Generator(static_cast<int>(time(0)));
static std::uniform_real_distribution<float> Rand_Dist_Float(-1000.0F, 1000.0F);
static std::uniform_int_distribution<int> Rand_Dist_Int(-1000, 1000);

static float GetRandomFloat(bool avoidZeros = false)
{
    float result = Rand_Dist_Float(Rand_Generator);
    bool isInvalid = std::isnan(result) && std::isinf(result);
    bool isZero = (result == 0);
    while(isInvalid || (avoidZeros && isZero))
    {
        result = Rand_Dist_Float(Rand_Generator);
    }
    return result;
}

static int GetRandomInt()
{
    return Rand_Dist_Int(Rand_Generator);
}