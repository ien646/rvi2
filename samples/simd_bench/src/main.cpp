#define CURRENT_ARCH_X86_FORCE_AVX 1
#include <rvi/line_container.hpp>
#include <cmath>
#include <chrono>
#include <iostream>

using namespace rvi;

float rand_float()
{
    return std::sqrt(std::abs(rand()));
}

vector2 rand_vec2()
{
    return vector2(rand_float(), rand_float());
}

color_rgba rand_color()
{
    return color_rgba((u8)rand(), (u8)rand(), (u8)rand(), (u8)rand());
}

transform2 rand_tform()
{
    return transform2(rand_vec2(), rand_vec2(), rand_float());
}

void rand_fill_container(line_container& lc, size_t sz)
{
    for(int i = 0; i < sz; ++i)
    {
        lc.push_back(rand_vec2(), rand_color(), rand_vec2(), rand_color());
    }
}

using cclock = std::chrono::high_resolution_clock;

int main()
{
    line_container lc;
    rand_fill_container(lc, 100000);

    auto start = cclock::now();
    lc.apply_rotation(rand_float());
    auto end = cclock::now();
#if CURRENT_ARCH_X86_FORCE_AVX
    std::cout << "[AVX]:" << (end - start).count() / 1000000 << "ms" << std::endl;
#elif CURRENT_ARCH_X86_FORCE_SSE
    std::cout << "[SSE]:" << (end - start).count() / 1000000 << "ms" << std::endl;
#elif CURRENT_ARCH_X86_FORCE_NOVEC
    std::cout << "[STD]:" << (end - start).count() / 1000000 << "ms" << std::endl;
#endif
    system("pause");
    return 0;
}