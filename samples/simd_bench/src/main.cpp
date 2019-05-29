#include <rvi/line_container.hpp>
#include <random>

using namespace rvi;

#define LINES 10000000

line_container lc_no_simd;
line_container lc_simd;

std::mt19937 rand_eng;
std::uniform_int_distribution<unsigned short> dist_ubyte(0, 255);
std::uniform_real_distribution<float> dist_float(0.0F, 5.0F);

#define RAND_FLOAT() dist_float(rand_eng)
#define RAND_UBYTE() dist_ubyte(rand_eng)
#define RAND_VEC2() vector2(RAND_FLOAT(), RAND_FLOAT())
#define RAND_CRGBA() color_rgba(RAND_UBYTE(), RAND_UBYTE(), RAND_UBYTE(), RAND_UBYTE())
#define RAND_TFORM() transform2(RAND_VEC2(), RAND_VEC2(), RAND_FLOAT())

void refill_all()
{
    lc_no_simd.clear();
    lc_simd.clear();
    for(int i = 0; i < LINES; ++i)
    {
        vector2 spos = RAND_VEC2(), epos = RAND_VEC2();
        color_rgba scol = RAND_CRGBA(), ecol = RAND_CRGBA();

        lc_simd.push_back(spos, scol, epos, ecol);
        lc_no_simd.push_back(spos, scol, epos, ecol);
    }
}

void ff_no_simd(transform2& tform)
{
    lc_no_simd.apply_transform(tform);
}

#include <pmmintrin.h> // SSE3
void ff_simd(transform2& tform)
{
    float _iv_zero[4] = { 0, 0, 0, 0 };
    __m128 vzero = _mm_load_ps(_iv_zero);

    float _iv_scale[4] = { tform.scale.x, tform.scale.y, tform.scale.x, tform.scale.y };
    __m128 vscale = _mm_load_ps(_iv_scale);

    float _iv_position[4] = { tform.position.x, tform.position.y, tform.position.x, tform.position.y };
    __m128 vposition = _mm_load_ps(_iv_position); 

    const float rad_angle = rvi::math::deg2rad(tform.rotation);
    const float angle_sin = std::sin(rad_angle);
    const float angle_cos = std::cos(rad_angle);
    float _iv_rot_table[4] = { angle_cos, -angle_sin, angle_sin, angle_cos };
    __m128 vrot_table = _mm_load_ps(_iv_rot_table);

    float _iv_mask_upper[4] = { 0,0,1,1 };
    __m128 vmask_upper = _mm_load_ps(_iv_mask_upper);

    float _iv_mask_lower[4] = { 1,1,0,0 };
    __m128 vmask_lower = _mm_load_ps(_iv_mask_lower);

    float* _fptr0 = &*lc_simd.position_begin();

    for(size_t i = 0; i < LINES * 4; i += 4)
    {
        float* fptr = _fptr0 + i;
        __m128 vvec = _mm_load_ps(fptr);      

        vvec = _mm_mul_ps(vvec, vscale);
        __m128 vspos = _mm_mul_ps(vvec, vmask_lower); // f[0], f[1], 0, 0

        // -- ROTATION --
        // _positions[i + 2] -= _positions[i + 0];
        // _positions[i + 3] -= _positions[i + 1];
        float _iv_rotator_temp_subadd[4] { 0, 0, fptr[0], fptr[1] };
        __m128 vtemp_rot_subadd = _mm_load_ps(_iv_rotator_temp_subadd);
        vtemp_rot_subadd = _mm_mul_ps(vtemp_rot_subadd, vscale);
        vvec = _mm_sub_ps(vvec, vtemp_rot_subadd);
     
        // const float aux_x = _positions[i + 2];
        // const float aux_y = _positions[i + 3];

        __m128 vhi = _mm_unpackhi_ps(vvec, vvec); // sx,sy,ex,ey -> ex,ex,ey,ey
        vhi = _mm_shuffle_ps(vhi, vhi, _MM_SHUFFLE(3, 1, 2, 0)); // x,x,y,y -> x,y,x,y
 
        // // [rx] = [cos(a) , -sin(a)][x]
        // _positions[i + 2] = (aux_x * +angleCos) + (aux_y * -angleSin);
        // // [ry] = [sin(a) ,  cos(a)][y]
        // _positions[i + 3] = (aux_x * +angleSin) + (aux_y * +angleCos);
        
        vhi = _mm_mul_ps(vhi, vrot_table);
        vhi = _mm_hadd_ps(vzero, vhi);
        vvec = _mm_or_ps(vspos, vhi);
 
        // _positions[i + 2] += _positions[i + 0];
        // _positions[i + 3] += _positions[i + 1];

        vvec = _mm_add_ps(vvec, vtemp_rot_subadd);
     
        // // -- OFFSET --
        // _positions[i + 0] += tform.position.x; //start
        // _positions[i + 1] += tform.position.y;
        // _positions[i + 2] += tform.position.x; //end
        // _positions[i + 3] += tform.position.y;
        vvec = _mm_add_ps(vvec, vposition);
        
        _mm_store_ps(fptr, vvec);
    }
}

#include <iostream>
#include <chrono>

using cclock = std::chrono::high_resolution_clock;

int main()
{
    refill_all();

    transform2 tform = RAND_TFORM();
    auto nstart = cclock::now();
    ff_no_simd(tform);
    auto nend = cclock::now();

    auto sstart = cclock::now();
    ff_simd(tform);
    auto send = cclock::now();

    std::cout << "No SIMD: " << (nend - nstart).count() / 1000000.0F << std::endl;
    std::cout << "SIMD:    " << (send - sstart).count() / 1000000.0F << std::endl;

    size_t sz = lc_simd.size();
    for(size_t i = 0; i < sz; ++i)
    {
        float va = *(lc_no_simd.position_cbegin() + i);
        float vb= *(lc_simd.position_cbegin() + i);
        if(va != vb)
        {
            std::cout << "Found unequal values at index [" << i << "] " << va << "!=" << vb << std::endl;
        }
        if(i % 100 == 0)
        {
            std::cout << "\r Verifiying values equality... " << i << '/' << sz;
        }
    }
    int ret = 0;
    std::cin >> ret;
    return ret;
}