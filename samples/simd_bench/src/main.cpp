#include <rvi/line_container.hpp>
#include <cmath>
#include <chrono>
#include <iostream>
#include <benchmark/benchmark.h>

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
    lc.clear();
    for(int i = 0; i < sz; ++i)
    {
        lc.push_back(rand_vec2(), rand_color(), rand_vec2(), rand_color());
    }
}

void apply_rotation_std(line_container& lc, float rotation);
void apply_rotation_sse(line_container& lc, float rotation);
void apply_rotation_avx(line_container& lc, float rotation);
void apply_scale_both_std(line_container& lc, const vector2& );
void apply_scale_both_sse(line_container& lc, const vector2&);
void apply_scale_both_avx(line_container& lc, const vector2&);
void apply_offset_std(line_container& lc, const vector2&);
void apply_offset_sse(line_container& lc, const vector2&);
void apply_offset_avx(line_container& lc, const vector2&);

static void bm_rot_std(benchmark::State& state)
{
    line_container lc;
    rand_fill_container(lc, 1000);
    for (auto _ : state)
    {
        apply_rotation_std(lc, rand_float());
    }
}

static void bm_rot_sse(benchmark::State& state)
{
    line_container lc;
    rand_fill_container(lc, 1000);
    for (auto _ : state)
    {
        apply_rotation_sse(lc, rand_float());
    }
}

static void bm_rot_avx(benchmark::State& state)
{
    line_container lc;
    rand_fill_container(lc, 1000);
    for (auto _ : state)
    {
        apply_rotation_avx(lc, rand_float());
    }
}

// ---

static void bm_sca_std(benchmark::State& state)
{
    line_container lc;
    rand_fill_container(lc, 1000);
    for (auto _ : state)
    {
        apply_scale_both_std(lc, rand_vec2());
    }
}

static void bm_sca_sse(benchmark::State& state)
{
    line_container lc;
    rand_fill_container(lc, 1000);
    for (auto _ : state)
    {        
        apply_scale_both_sse(lc, rand_vec2());
    }
}

static void bm_sca_avx(benchmark::State& state)
{
    line_container lc;
    rand_fill_container(lc, 1000);
    for (auto _ : state)
    {
        apply_scale_both_avx(lc, rand_vec2());
    }
}

// ---

static void bm_pos_std(benchmark::State& state)
{
    line_container lc;
    rand_fill_container(lc, 1000);
    for (auto _ : state)
    {
        apply_offset_std(lc, rand_vec2());
    }
}

static void bm_pos_sse(benchmark::State& state)
{
    line_container lc;
    rand_fill_container(lc, 1000);
    for (auto _ : state)
    {        
        apply_offset_sse(lc, rand_vec2());
    }
}

static void bm_pos_avx(benchmark::State& state)
{
    line_container lc;
    rand_fill_container(lc, 1000);
    for (auto _ : state)
    {
        apply_offset_avx(lc, rand_vec2());
    }
}

BENCHMARK(bm_rot_std);
BENCHMARK(bm_rot_sse);
BENCHMARK(bm_rot_avx);
BENCHMARK(bm_sca_std);
BENCHMARK(bm_sca_sse);
BENCHMARK(bm_sca_avx);
BENCHMARK(bm_pos_std);
BENCHMARK(bm_pos_sse);
BENCHMARK(bm_pos_avx);

BENCHMARK_MAIN();

void apply_transform_std(line_container& lc, const transform2& tform)
{
    bool scale = tform.scale != transform2::default_value().scale;
    bool position = tform.position != transform2::default_value().position;
    bool rotation = tform.rotation != transform2::default_value().rotation;

    const float radAngle = rvi::math::deg2rad(tform.rotation);
    const float angleSin = std::sin(radAngle);
    const float angleCos = std::cos(radAngle);

    float* pos_ptr = lc.positions_data();
    for(size_t i = 0; i < lc.size() * 4; i += 4)
    {
        // -- SCALE --
        if(scale)
        {
            pos_ptr[i + 0] *= tform.scale.x; //end
            pos_ptr[i + 1] *= tform.scale.y;
            pos_ptr[i + 2] *= tform.scale.x; //end
            pos_ptr[i + 3] *= tform.scale.y;
        }

        // -- ROTATION --
        if(rotation)
        {
            pos_ptr[i + 2] -= pos_ptr[i + 0];
            pos_ptr[i + 3] -= pos_ptr[i + 1];
        
            const float aux_x = pos_ptr[i + 2];
            const float aux_y = pos_ptr[i + 3];

            // [rx] = [cos(a) , -sin(a)][x]
            pos_ptr[i + 2] = (aux_x * +angleCos) + (aux_y * -angleSin);
            // [ry] = [sin(a) ,  cos(a)][y]
            pos_ptr[i + 3] = (aux_x * +angleSin) + (aux_y * +angleCos);

            pos_ptr[i + 2] += pos_ptr[i + 0];
            pos_ptr[i + 3] += pos_ptr[i + 1];
        }

        if(position)
        {
            // -- OFFSET --
            pos_ptr[i + 0] += tform.position.x; //start
            pos_ptr[i + 1] += tform.position.y;
            pos_ptr[i + 2] += tform.position.x; //end
            pos_ptr[i + 3] += tform.position.y;
        }
    }
}

void apply_offset_std(line_container& lc , const vector2& offset)
{
    float* pos_ptr = lc.positions_data();
    for(size_t i = 0; i < lc.size() * 4; i += 4)
    {
        pos_ptr[i + 0] += offset.x; //start
        pos_ptr[i + 1] += offset.y;
        pos_ptr[i + 2] += offset.x; //end
        pos_ptr[i + 3] += offset.y;
    }
}

void apply_rotation_std(line_container& lc, float rotation)
{
    const float radAngle = math::deg2rad(rotation);
    const float angleSin = std::sin(radAngle);
    const float angleCos = std::cos(radAngle);

    float* pos_ptr = lc.positions_data();
    for(size_t i = 0; i < lc.size() * 4; i += 4)
    {
        pos_ptr[i + 2] -= pos_ptr[i + 0];
        pos_ptr[i + 3] -= pos_ptr[i + 1];
    
        const float aux_x = pos_ptr[i + 2];
        const float aux_y = pos_ptr[i + 3];

        // [rx] = [cos(a) , -sin(a)][x]
        pos_ptr[i + 2] = (aux_x * +angleCos) + (aux_y * -angleSin);
        // [ry] = [sin(a) ,  cos(a)][y]
        pos_ptr[i + 3] = (aux_x * +angleSin) + (aux_y * +angleCos);

        pos_ptr[i + 2] += pos_ptr[i + 0];
        pos_ptr[i + 3] += pos_ptr[i + 1];
    }
}

void apply_scale_both_std(line_container& lc, const vector2& scale)
{
    float* pos_ptr = lc.positions_data();
    for(size_t i = 0; i < lc.size() * 4; i += 4)
    {
        pos_ptr[i + 0] *= scale.x;
        pos_ptr[i + 1] *= scale.y;
        pos_ptr[i + 2] *= scale.x;
        pos_ptr[i + 3] *= scale.y;
    }
}

void apply_scale_start_std(line_container& lc, const vector2& scale)
{
    float* pos_ptr = lc.positions_data();
    for(size_t i = 0; i < lc.size() * 4; i += 4)
    {
        pos_ptr[i + 0] *= scale.x;
        pos_ptr[i + 1] *= scale.y;
    }
}

void apply_scale_end_std(line_container& lc, const vector2& scale)
{
    float* pos_ptr = lc.positions_data();
    for(size_t i = 0; i < lc.size() * 4; i += 4)
    {
        pos_ptr[i + 2] *= scale.x;
        pos_ptr[i + 3] *= scale.y;
    }
}

//----------------------------------------------
// Vtable methods SSE-vectorized implementation
//----------------------------------------------
#include <xmmintrin.h>
#include <rvi/math.hpp>

void apply_transform_sse(line_container& lc, const transform2& tform)
{
    float _iv_zero[4] = { 0, 0, 0, 0 };
    __m128 vzero = _mm_load_ps(_iv_zero);

    float _iv_scale[4] = { tform.scale.x, tform.scale.y, tform.scale.x, tform.scale.y };
    __m128 vscale = _mm_load_ps(_iv_scale);

    float _iv_position[4] = { tform.position.x, tform.position.y, tform.position.x, tform.position.y };
    __m128 vposition = _mm_load_ps(_iv_position); 

    const float rad_angle = math::deg2rad(tform.rotation);
    const float angle_sin = std::sin(rad_angle);
    const float angle_cos = std::cos(rad_angle);
    float _iv_rot_table[4] = { angle_cos, -angle_sin, angle_sin, angle_cos };
    __m128 vrot_table = _mm_load_ps(_iv_rot_table);

    float* _fptr0 = lc.positions_data();

    for(size_t i = 0; i < lc.size() * 4; i += 4)
    {
        float* fptr = _fptr0 + i;
        __m128 vvec = _mm_load_ps(fptr);

        // -- SCALE --
        vvec = _mm_mul_ps(vvec, vscale);
        __m128 vspos = _mm_movelh_ps(vvec, vzero); // f[0], f[1], 0, 0

        // -- ROTATION --
        float _iv_rotator_temp_subadd[4] { 0, 0, fptr[0], fptr[1] };
        __m128 vtemp_rot_subadd = _mm_load_ps(_iv_rotator_temp_subadd);
        vtemp_rot_subadd = _mm_mul_ps(vtemp_rot_subadd, vscale);
        vvec = _mm_sub_ps(vvec, vtemp_rot_subadd);
        __m128 vhi = _mm_unpackhi_ps(vvec, vvec); // sx,sy,ex,ey -> ex,ex,ey,ey
        vhi = _mm_shuffle_ps(vhi, vhi, _MM_SHUFFLE(3, 1, 2, 0)); // x,x,y,y -> x,y,x,y
        vhi = _mm_mul_ps(vhi, vrot_table);
        vhi = _mm_add_ps(vhi, _mm_shuffle_ps(vhi, vhi, _MM_SHUFFLE(2, 3, 0, 1)));
        vhi = _mm_shuffle_ps(vhi, vhi, _MM_SHUFFLE(3, 1, 2, 0));
        vhi = _mm_movehl_ps(vhi, vzero); // 0, 0, x, y
        vvec = _mm_or_ps(vspos, vhi);
        vvec = _mm_add_ps(vvec, vtemp_rot_subadd);
    
        // -- OFFSET --
        vvec = _mm_add_ps(vvec, vposition);
        
        _mm_store_ps(fptr, vvec);
    }
}

void apply_offset_sse(line_container& lc, const vector2& offset)
{
    float _iv_offset[4] = { offset.x, offset.y, offset.x, offset.y };
    __m128 voffset = _mm_load_ps(_iv_offset);

    float* fptr0 = lc.positions_data();
    for(size_t i = 0; i < lc.size() * 4; i += 4)
    {
        float* fptr = fptr0 + i;
        __m128 vpos = _mm_load_ps(fptr);
        _mm_store_ps(fptr, _mm_add_ps(vpos, voffset));
    }
}

void apply_scale_both_sse(line_container& lc, const vector2& scale)
{
    float _iv_scale[4] = { scale.x, scale.y, scale.x, scale.y };
    __m128 vscale = _mm_load_ps(_iv_scale);

    float* fptr0 = lc.positions_data();
    for(size_t i = 0; i < lc.size() * 4; i += 4)
    {
        float* fptr = fptr0 + i;
        __m128 vpos = _mm_load_ps(fptr);
        _mm_store_ps(fptr, _mm_mul_ps(vpos, vscale));
    }
}

void apply_scale_start_sse(line_container& lc, const vector2& scale)
{
    float _iv_scale[4] = { scale.x, scale.y, 1.0F, 1.0F };
    __m128 vscale = _mm_load_ps(_iv_scale);

    float* fptr0 = lc.positions_data();
    for(size_t i = 0; i < lc.size() * 4; i += 4)
    {
        float* fptr = fptr0 + i;
        __m128 vpos = _mm_load_ps(fptr);
        _mm_store_ps(fptr, _mm_mul_ps(vpos, vscale));
    }
}

void apply_scale_end_sse(line_container& lc, const vector2& scale)
{
    float _iv_scale[4] = { 1.0F, 1.0F, scale.x, scale.y };
    __m128 vscale = _mm_load_ps(_iv_scale);

    float* fptr0 = lc.positions_data();
    for(size_t i = 0; i < lc.size() * 4; i += 4)
    {
        float* fptr = fptr0 + i;
        __m128 vpos = _mm_load_ps(fptr);
        _mm_store_ps(fptr, _mm_mul_ps(vpos, vscale));
    }
}

void apply_rotation_sse(line_container& lc, float angle)
{
    const float rad_angle = math::deg2rad(angle);
    const float angle_sin = std::sin(rad_angle);
    const float angle_cos = std::cos(rad_angle);
    float _iv_rot_table[4] = { angle_cos, -angle_sin, angle_sin, angle_cos };
    __m128 vrot_table = _mm_load_ps(_iv_rot_table);

    float _iv_zero[4] = { 0, 0, 0, 0 };
    __m128 vzero = _mm_load_ps(_iv_zero);

    float* _fptr0 = lc.positions_data();

    for(size_t i = 0; i < lc.size() * 4; i += 4)
    {
        float* fptr = _fptr0 + i;
        __m128 vvec = _mm_load_ps(fptr);

        __m128 vspos = _mm_movelh_ps(vvec, vzero); // f[0], f[1], 0, 0
        __m128 vtemp_rot_subadd = _mm_movelh_ps(vvec, vzero);
        
        vvec = _mm_sub_ps(vvec, vtemp_rot_subadd);
        __m128 vhi = _mm_unpackhi_ps(vvec, vvec); // sx,sy,ex,ey -> ex,ex,ey,ey
        vhi = _mm_shuffle_ps(vhi, vhi, _MM_SHUFFLE(3, 1, 2, 0)); // x,x,y,y -> x,y,x,y
        vhi = _mm_mul_ps(vhi, vrot_table);
        vhi = _mm_add_ps(vhi, _mm_shuffle_ps(vhi, vhi, _MM_SHUFFLE(2, 3, 0, 1)));
        vhi = _mm_shuffle_ps(vhi, vhi, _MM_SHUFFLE(3, 1, 2, 0));
        vhi = _mm_movehl_ps(vhi, vzero); // 0, 0, x, y
        vvec = _mm_or_ps(vspos, vhi);
        vvec = _mm_add_ps(vvec, vtemp_rot_subadd);
        _mm_store_ps(fptr, vvec);
    }
}


//----------------------------------------------
// Vtable methods AVX-vectorized implementation
//----------------------------------------------
#include <immintrin.h>

void apply_transform_avx(line_container& lc, const transform2& tform) 
{
    rt_assert(false, "Not implemented!");
}

void apply_offset_avx(line_container& lc, const vector2& offset)
{
    const float& x = offset.x;
    const float& y = offset.y;
    float _iv_offset[8] = { x, y, x, y, x, y, x, y };
    __m256 voffset = _mm256_load_ps(_iv_offset);

    float* fptr0 = lc.positions_data();
    for(size_t i = 0; i < lc.size() * 4; i += 8)
    {
        float* fptr = fptr0 + i;
        __m256 vpos = _mm256_load_ps(fptr);
        vpos = _mm256_add_ps(vpos, voffset);
        _mm256_store_ps(fptr, vpos);
    }

    // Remaining line, for odd line sizes
    if((lc.size() % 2) == 1)
    {
        float* fptr = lc.positions_data() + ((lc.size() - 1) * 4);
        fptr[0] += x;
        fptr[1] += y;
        fptr[2] += x;
        fptr[3] += y;
    }
}

void apply_scale_both_avx(line_container& lc, const vector2& scale)
{
    const float& x = scale.x;
    const float& y = scale.y;
    float _iv_scale[8] = { x, y, x, y, x, y, x, y };
    __m256 vscale = _mm256_load_ps(_iv_scale);

    float* fptr0 = lc.positions_data();
    for(size_t i = 0; i < lc.size() * 4; i += 8)
    {
        float* fptr = fptr0 + i;
        __m256 vpos = _mm256_load_ps(fptr);
        vpos = _mm256_mul_ps(vpos, vscale);
        _mm256_store_ps(fptr, vpos);
    }

    // Remaining line, for odd line sizes
    if((lc.size() % 2) == 1)
    {
        float* fptr = lc.positions_data() + ((lc.size() - 1) * 4);
        fptr[0] *= x;
        fptr[1] *= y;
        fptr[2] *= x;
        fptr[3] *= y;
    }
}

void apply_scale_start_avx(line_container& lc, const vector2& scale)
{
    const float& x = scale.x;
    const float& y = scale.y;
    float _iv_scale[8] = { x, y, 1, 1, x, y, 1, 1 };
    __m256 vscale = _mm256_load_ps(_iv_scale);

    float* fptr0 = lc.positions_data();
    for(size_t i = 0; i < lc.size() * 4; i += 8)
    {
        float* fptr = fptr0 + i;
        __m256 vpos = _mm256_load_ps(fptr);
        vpos = _mm256_mul_ps(vpos, vscale);
        _mm256_store_ps(fptr, vpos);
    }

    // Remaining line, for odd line sizes
    if((lc.size() % 2) == 1)
    {
        float* fptr = lc.positions_data() + ((lc.size() - 1) * 4);
        fptr[0] *= x;
        fptr[1] *= y;
    }
}

void apply_scale_end_avx(line_container& lc, const vector2& scale)
{
    const float& x = scale.x;
    const float& y = scale.y;
    float _iv_scale[8] = { 1, 1, x, y, 1, 1, x, y };
    __m256 vscale = _mm256_load_ps(_iv_scale);

    float* fptr0 = lc.positions_data();
    for(size_t i = 0; i < lc.size() * 4; i += 8)
    {
        float* fptr = fptr0 + i;
        __m256 vpos = _mm256_load_ps(fptr);
        vpos = _mm256_mul_ps(vpos, vscale);
        _mm256_store_ps(fptr, vpos);
    }

    // Remaining line, for odd line sizes
    if((lc.size() % 2) == 1)
    {
        float* fptr = lc.positions_data() + ((lc.size() - 1) * 4);
        fptr[2] *= x;
        fptr[3] *= y;
    }
}

void apply_rotation_avx(line_container& lc, float angle)
{
    const float rad_angle = math::deg2rad(angle);
    const float angle_sin = std::sin(rad_angle);
    const float angle_cos = std::cos(rad_angle);
    
    float _iv_rot_table[8] = { 
        angle_cos, -angle_sin, angle_sin, angle_cos,
        angle_cos, -angle_sin, angle_sin, angle_cos
    };
    __m256 vrot_table = _mm256_load_ps(_iv_rot_table);

    float _iv_zero[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    __m256 vzero = _mm256_load_ps(_iv_zero);

    float* _fptr0 = lc.positions_data();

    for(size_t i = 0; i < lc.size() * 4; i += 8)
    {
        float* fptr = _fptr0 + i;
        __m256 vvec = _mm256_load_ps(fptr);

        __m256 vspos = _mm256_blend_ps(vzero, vvec, 0b11001100);
        __m256 vtemp_rot_subadd = _mm256_blend_ps(vzero, vvec, 0b00110011);
        vvec = _mm256_sub_ps(vvec, vtemp_rot_subadd);
        __m256 vhi = _mm256_unpackhi_ps(vvec, vvec);
        vhi = _mm256_shuffle_ps(vhi, vhi, _MM_SHUFFLE(3, 1, 2, 0)); // x,x,y,y -> x,y,x,y
        vhi = _mm256_mul_ps(vhi, vrot_table);
        vhi = _mm256_add_ps(vhi, _mm256_shuffle_ps(vhi, vhi, _MM_SHUFFLE(2, 3, 0, 1)));
        vhi = _mm256_shuffle_ps(vhi, vhi, _MM_SHUFFLE(3, 1, 2, 0));
        vhi = _mm256_blend_ps(vzero, vhi, 0b00110011); // 0, 0, x, y
        vvec = _mm256_or_ps(vspos, vhi);
        vvec = _mm256_add_ps(vvec, vtemp_rot_subadd);
        _mm256_store_ps(fptr, vvec);
    }

    // Remainder (4 floats -> SSE)
    if(lc.size() % 2 == 1)
    {
        float* fptr = _fptr0 + ((lc.size() - 1) * 4);
        __m128 vzero_sse = _mm256_castps256_ps128(vzero);
        __m128 vrot_table_sse = _mm256_castps256_ps128(vrot_table);

        __m128 vvec = _mm_load_ps(fptr);
        __m128 vspos = _mm_movelh_ps(vvec, vzero_sse); // f[0], f[1], 0, 0

        float _iv_rotator_temp_subadd[4] { 0, 0, fptr[0], fptr[1] };
        __m128 vtemp_rot_subadd = _mm_load_ps(_iv_rotator_temp_subadd);
        vvec = _mm_sub_ps(vvec, vtemp_rot_subadd);
        __m128 vhi = _mm_unpackhi_ps(vvec, vvec); // sx,sy,ex,ey -> ex,ex,ey,ey
        vhi = _mm_shuffle_ps(vhi, vhi, _MM_SHUFFLE(3, 1, 2, 0)); // x,x,y,y -> x,y,x,y
        vhi = _mm_mul_ps(vhi, vrot_table_sse);
        vhi = _mm_add_ps(vhi, _mm_shuffle_ps(vhi, vhi, _MM_SHUFFLE(2, 3, 0, 1)));
        vhi = _mm_shuffle_ps(vhi, vhi, _MM_SHUFFLE(3, 1, 2, 0));
        vhi = _mm_movehl_ps(vhi, vzero_sse); // 0, 0, x, y
        vvec = _mm_or_ps(vspos, vhi);
        vvec = _mm_add_ps(vvec, vtemp_rot_subadd);
        _mm_store_ps(fptr, vvec);
    }
}