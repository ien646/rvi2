#include <cstdlib>

static float rand_float()
{
    float base = static_cast<float>(std::rand());
    float div = static_cast<float>(std::rand());
    if(div == 0.0F)
    {
        div += 0.1F;
    }
    return base / div;
}