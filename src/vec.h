#ifndef HB_VEC_H
#define HB_VEC_H
#define RUAPU_IMPLEMENTATION
#include <stdio.h>
#include <math.h>

#ifdef HB_VEC_SCALAR
#define HB_VEC_USE_SCALAR 1
#else 
#define HB_VEC_USE_SCALAR 0
#endif

/// NOT USE SIMD (get that `avx` NONSENSE out of my face kied)
#if HB_VEC_USE_SCALAR

typedef struct {
  float x,y,z;
} Vec3;

typedef struct {
 double x,y,z;
} Vec3_d;

typedef struct {
  int default_fallback;
} available_isa;

#elif defined(__i386__) || defined(__x86_64__) || defined(_M_IX86) || defined(_M_X64)
#include <immintrin.h>
#include <emmintrin.h>
typedef struct  {
  int mmx, sse, sse2,sse3,ssse3,sse41,sse42,sse4a,xop,avx,f16c,fma,avx2,avx512f,avx512bw,avx512cd,avx512dq,avx512vl,avx512vnni,avx512bf16,avx512ifma,avx512vbmi,avx512vbmi2,avx512fp16,avx512er,avx5124fmaps,avx5124vnniw,avxvnni,avxvniint8,avxvnniint16,avxifma,amxfp16,amxbf16,amxint8,amxtile,bmi1,bmi2,gfni,aesni,vaes,sha,rdrand,rdseed,tsx;
} available_isa;

typedef struct {
  __m128 data;
} Vec3;

// 64 bit vector, avx
typedef struct {
  __m256d data;
} Vec3_d;

#elif __aarch64__ 
#include <arm_neon.h>
typedef struct {
  int neon,vfpv4,lse,cpuid,asimdrdm,asimdhp,asimddp,asimdfhm,bf16,i8mm,frint,jscvt,fcma,mte,mte2,sve,sve2,svebf16,svei8mm,svef32mm,svef64mm,sme,smef16f16,smef64f64,pmull,crc32,aes,sha1,sha2,sha3,sha512,sm3,sm4,svepmull,svebitperm,svaes,svesha3,svesm4,amx;
} available_isa;

typedef struct {
  float32x4_t data;
} Vec3;

typedef struct {
  double x,y,z;
} Vec3_d;

#elif __arm__ || defined(_M_ARM)
typedef struct {
  int msa,mmi,sx,asx,msa2,crypto;
} available_isa;

// default fallback
#else 

typedef struct {
  float x,y,z;
} Vec3;

typedef struct {
  int default_fallback;
} available_isa;

#endif


// f32 ops

void debug_vec();



/// use scalar operations, 
/// guaranteed to run on all them platforms
/// also no SIMD debugging fiasco
#if HB_VEC_USE_SCALAR


// f32 opps
static inline Vec3 vec3_new(float x, float y, float z) {
 Vec3 v ={ .x=x, .y=y, .z=z };
  return v;
}

static inline void vec3_print(Vec3 v) {
  printf("x: %f y: %f z: %f", v.x, v.y, v.z);
}

static inline Vec3 vec3_from_float(float f) {
  Vec3 v = { f, f, f };
  return v;
}

static inline Vec3 vec3_from_int(int i) {
  Vec3 v = {(float) i , (float) i, (float) i};
  return v;
}

static inline Vec3 vec3_add(Vec3 v1, Vec3 v2) {
  Vec3 v = {.x=v1.x + v2.x , .y=v1.y+v2.y, .z=v1.z + v2.z};
  return v;
}

static inline Vec3 vec3_sub(Vec3 v1, Vec3 v2) {
  Vec3 v = {.x=v1.x - v2.x , .y=v1.y - v2.y, .z=v1.z - v2.z};
  return v;
}

static inline Vec3 vec3_mul(Vec3 v1, Vec3 v2) {
  Vec3 v = {.x=v1.x * v2.x , .y=v1.y * v2.y, .z=v1.z * v2.z};
  return v;
}

static inline Vec3 vec3_div(Vec3 v1, Vec3 v2) {
    Vec3 result;
    if (v2.x != 0.0f) {
        result.x = v1.x / v2.x;
    } else {
        result.x = 0.0f; // Handle division by zero as needed
    }
    if (v2.y != 0.0f) {
        result.y = v1.y / v2.y;
    } else {
        result.y = 0.0f; // Handle division by zero as needed
    }
    if (v2.z != 0.0f) {
        result.z = v1.z / v2.z;
    } else {
        result.z = 0.0f; // Handle division by zero as needed
    }
    return result;
}
static inline Vec3 vec3_negate(Vec3 v) {
  Vec3 neg = { -v.x, -v.y, -v.z };
  return neg;
}

static inline float vec3_dot(Vec3  v1, Vec3 v2) {
  return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

static inline float vec3_length(Vec3 v) {
  return sqrt(vec3_dot(v,v));
}

static inline Vec3 vec3_unit(Vec3 v) {
  float len = vec3_length(v);
  Vec3 vec = {len, len,len};
  return vec3_div(v, vec);
}

static inline float vec3x(Vec3 v) { return v.x; }
static inline float vec3y(Vec3 v) { return v.y; }
static inline float vec3z(Vec3 v) {return v.z;}

/// f64 opps
static inline Vec3_d vec3d_new(double x, double y, double z) {
  Vec3_d v = { x ,y ,z };
  return v;
}

static inline void vec3d_print(Vec3_d v) {
  printf("x: %f y: %f z: %f\n", v.x, v.y, v.z);
}

static inline Vec3_d vec3d_add(Vec3_d v1, Vec3_d v2) {
  Vec3_d v = {.x=v1.x + v2.x , .y=v1.y+v2.y, .z=v1.z + v2.z};
  return v;
}

static inline Vec3_d vec3d_from_float(double f) {
  Vec3_d v = { f, f, f };
  return v;
}

static inline Vec3_d vec3d_from_int(int i) {
  Vec3_d v = { (double) i, (double) i, (double) i };
  return v;
}

static inline Vec3_d vec3d_sub(Vec3_d v1, Vec3_d v2) {
  Vec3_d v = {.x=v1.x - v2.x , .y=v1.y - v2.y, .z=v1.z - v2.z};
  return v;
}

static inline Vec3_d vec3d_mul(Vec3_d v1, Vec3_d v2) {
  Vec3_d v = {.x=v1.x * v2.x , .y=v1.y * v2.y, .z=v1.z * v2.z};
  return v;
}

static inline Vec3_d vec3d_div(Vec3_d v1, Vec3_d v2) {
    Vec3_d result;
    if (v2.x != 0.0f) {
        result.x = v1.x / v2.x;
    } else {
        result.x = 0.0f; // Handle division by zero as needed
    }
    if (v2.y != 0.0f) {
        result.y = v1.y / v2.y;
    } else {
        result.y = 0.0f; // Handle division by zero as needed
    }
    if (v2.z != 0.0f) {
        result.z = v1.z / v2.z;
    } else {
        result.z = 0.0f; // Handle division by zero as needed
    }
    return result;
}

static inline Vec3_d vec3d_negate(Vec3_d v) {
  Vec3_d neg = { -v.x, -v.y, -v.z };
  return neg;
}

static inline double vec3d_dot(Vec3_d  v1, Vec3_d v2) {
  return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}


static inline double vec3d_length(Vec3_d v) {
  double dot_v = vec3d_dot(v,v);
  return sqrt(dot_v);
}

static inline Vec3_d vec3d_unit(Vec3_d v) {
  double len = vec3d_length(v);
  Vec3_d vec = {len, len,len};
  return vec3d_div(v, vec);
}

static inline double vec3d_x(Vec3_d v) { return v.x; }
static inline double vec3d_y(Vec3_d v) { return v.y; }
static inline double vec3d_z(Vec3_d v) {return v.z;}


#elif defined(__i386__) || defined(__x86_64__) || defined(_M_IX86) ||            \
    defined(_M_X64)
#include <emmintrin.h> // SSE2 electric boogaloo
#include <immintrin.h> //AVX
#include <pmmintrin.h> // SSE3
#include <xmmintrin.h>

/* 32 bit float vector operations */

static inline Vec3 vec3_new(float x, float y, float z) {
  Vec3 v;
  v.data = _mm_set_ps(0.0f, z, y, x);
  return v;
}

static inline void vec3_print(Vec3 v) {
  printf("x: %f y: %f z: %f\n", v.data[0], v.data[1], v.data[2]);
}

static inline Vec3 vec3_from_float(float f) {
  Vec3 v;
  v.data = _mm_set1_ps(f);
  return v;
}

static inline Vec3 vec3_negate(Vec3 v) {
  Vec3 v_neg;
  __m128 neg = _mm_set1_ps(-1.0f);
  v_neg.data = _mm_mul_ps(v.data, neg);
  return v_neg;
}

static inline Vec3 vec3_from_int(int i) {
  Vec3 v = {.data = _mm_set1_ps((float)i)};
  return v;
}

static inline Vec3 vec3_add(Vec3 v1, Vec3 v2) {
  Vec3 add = {.data = _mm_add_ps(v1.data, v2.data)};
  return add;
}

static inline Vec3 vec3_div(Vec3 v1, Vec3 v2) {
  Vec3 div = {.data = _mm_div_ps(v1.data, v2.data)};
  return div;
}

static inline Vec3 vec3_mul(Vec3 v1, Vec3 v2) {
  Vec3 mul = {.data = _mm_mul_ps(v1.data, v2.data)};
  return mul;
}

static inline Vec3 vec3_sub(Vec3 v1, Vec3 v2) {
  Vec3 sub = {.data = _mm_sub_ps(v1.data, v2.data)};
  return sub;
}

static inline float vec3_dot(Vec3 v1, Vec3 v2) {
  // If sse4.1 is available use _mm_dp_ps 
  // which calculates dot prod with a single instruction
  #ifdef __SSE4_1__
    return _mm_cvtss_f32(_mm_dp_ps(v1.data, v2.data, 0x71));
  #else
    __m128 mul = _mm_mul_ps(v1.data, v2.data);
    __m128 sum = _mm_hadd_ps(mul, mul);
    sum = _mm_hadd_ps(sum, sum);
    return _mm_cvtss_f32(sum);
  #endif
}

static inline float vec3_length(Vec3 v) {
  float dot_v = vec3_dot(v, v);
  return sqrtf(dot_v);
}

static inline Vec3 vec3_unit(Vec3 v) {
  float len = vec3_length(v);
  return vec3_div(v, vec3_from_float(len));
}

static inline float vec3x(Vec3 v) { return v.data[0]; }
static inline float vec3y(Vec3 v) { return v.data[1]; }
static inline float vec3z(Vec3 v) { return v.data[2]; }

/* 64 bit float vector operations */
static inline Vec3_d vec3d_new(double x, double y, double z) {
  Vec3_d v;
  v.data = _mm256_set_pd(0.0, z, y, x);
  return v;
}

static inline void vec3d_print(Vec3_d v) {
  printf("x: %f y: %f z: %f\n", v.data[0], v.data[1], v.data[2]);
}

static inline Vec3_d vec3d_from_float(double f) {
  Vec3_d v;
  v.data = _mm256_set1_pd(f);
  return v;
}

static inline Vec3_d vec3d_negate(Vec3_d v) {
  Vec3_d v_neg;
  __m256d neg = _mm256_set1_pd(-1.0);
  v_neg.data = _mm256_mul_pd(v.data, neg);
  return v_neg;
}

static inline Vec3_d vec3d_from_int(int i) {
  Vec3_d v = {.data = _mm256_set1_pd((double)i)};
  return v;
}

static inline Vec3_d vec3d_add(Vec3_d v1, Vec3_d v2) {
  Vec3_d add = {.data = _mm256_add_pd(v1.data, v2.data)};
  return add;
}

static inline Vec3_d vec3d_div(Vec3_d v1, Vec3_d v2) {
  Vec3_d div = {.data = _mm256_div_pd(v1.data, v2.data)};
  return div;
}

static inline Vec3_d vec3d_mul(Vec3_d v1, Vec3_d v2) {
  Vec3_d mul = {.data = _mm256_mul_pd(v1.data, v2.data)};
  return mul;
}

static inline Vec3_d vec3d_sub(Vec3_d v1, Vec3_d v2) {
  Vec3_d sub = {.data = _mm256_sub_pd(v1.data, v2.data)};
  return sub;
}
// using _mm_store_pd causes segfault, 
// cast to pd128 insyead
static inline double vec3d_dot(Vec3_d v1, Vec3_d v2) {
  __m256d mul = _mm256_mul_pd(v1.data, v2.data);
   /* `_mm256_hadd_pd` doesn't work across the 128-bit lanes
   we use a combination of _mm256_add_pd and _mm256_permute4x64_pd */
    __m256d sum = _mm256_add_pd(mul, _mm256_permute4x64_pd(mul, 0b01001110));
    sum = _mm256_add_pd(sum, _mm256_permute4x64_pd(sum, 0b10010011));
  return _mm_cvtsd_f64(_mm256_castpd256_pd128(sum));
}

static inline double vec3d_length(Vec3_d v) {
  double dot_v = vec3d_dot(v, v);
  return sqrtf(dot_v);
}

static inline Vec3_d vec3d_unit(Vec3_d v) {
  double len = vec3d_length(v);
  return vec3d_div(v, vec3d_from_float(len));
}

static inline double vec3d_x(Vec3_d v) { return v.data[0]; }
static inline double vec3d_y(Vec3_d v) { return v.data[1]; }
static inline double vec3d_z(Vec3_d v) { return v.data[2]; }

#elif __aarch64__
#include <arm_neon.h>
static inline Vec3 vec3_new(float x, float y, float z) {
  Vec3 v;
  float32x4_t vec = {x, y, z, 0.0f};
  v.data = vec;
  return v;
}

static inline void vec3_print(Vec3 v) {
  float values[4];
  vst1q_f32(values, v.data);
  printf("x: %f, y: %f, z: %f\n", values[0], values[1], values[2]);
}

static inline Vec3 vec3_add(Vec3 v1, Vec3 v2) {
  Vec3 v;
  float32x4_t av = vaddq_f32(v1.data, v2.data);
  v.data = av;
  return v;
}

static inline Vec3 vec3_from_float(float f) {
  Vec3 v;
  float32x4_t vec = {f, f, f, 0.0f};
  v.data = vec;
  return v;
}

static inline Vec3 vec3_negate(Vec3 v) {
  Vec3 neg = {.data = vmulq_f32(v.data, vdupq_n_f32(-1.0))};
  return neg;
}

static inline Vec3 vec3_from_int(int i) {
  Vec3 v;
  float f = (float)i;
  float32x4_t vec = {f, f, f, 0.0f};
  v.data = vec;
  return v;
}

static inline Vec3 vec3_div(Vec3 v1, Vec3 v2) {
  Vec3 v;
  float32x4_t dv = vdivq_f32(v1.data, v2.data);
  v.data = dv;
  return v;
}

static inline Vec3 vec3_mul(Vec3 v1, Vec3 v2) {
  Vec3 v;
  float32x4_t mv = vmulq_f32(v1.data, v2.data);
  v.data = mv;
  return v;
}

static inline Vec3 vec3_sub(Vec3 v1, Vec3 v2) {
  Vec3 v;
  float32x4_t sv = vsubq_f32(v1.data, v2.data);
  v.data = sv;
  return v;
}

static inline float vec3_dot(Vec3 v1, Vec3 v2) {
  float32x4_t mul = vmulq_f32(v1.data, v2.data);
  float32x2_t sum1 =
      vadd_f32(vget_low_f32(mul), vget_high_f32(mul)); // Add x and y
  float result = vget_lane_f32(vpadd_f32(sum1, sum1), 0);
  return result;
}

static inline float vec3_length(Vec3 v) {
  float dot_v = vec3_dot(v, v);
  return sqrtf(dot_v);
}

static inline Vec3 vec3_unit(Vec3 v) {
  float len = vec3_length(v);
  return vec3_div(vec3_from_float(len), v);
}


#elif __arm__



#else


#endif





#endif
