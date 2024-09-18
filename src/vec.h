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

// prints all available CPU's ISA , 
// mostly in part to ruapu
void print_available_isa();
Vec3 vec3_new(float x, float y, float z);
void vec3_print(Vec3 v);
Vec3 vec3_from_float(float f);
Vec3 vec3_negate(Vec3 v);
Vec3 vec3_from_int(int i);
Vec3 vec3_add(Vec3 v1, Vec3 v2);
Vec3 vec3_div(Vec3 v1, Vec3 v2);
Vec3 vec3_mul(Vec3 v1, Vec3 v2);
Vec3 vec3_sub(Vec3 v1, Vec3 v2);
Vec3 vec3_unit(Vec3 v);

float vec3_dot(Vec3 v1, Vec3 v2);
float vec3_length(Vec3 v);
float vec3x(Vec3 v);
float vec3y(Vec3 v);
float vec3z(Vec3 v);


// f64 ops

Vec3_d vec3d_new(double x, double y, double z);
void vec3d_print(Vec3_d v);
Vec3_d vec3d_from_float(double f);
Vec3_d vec3d_negate(Vec3_d v);
Vec3_d vec3d_from_int(int i);
Vec3_d vec3d_add(Vec3_d v1, Vec3_d v2);
Vec3_d vec3d_div(Vec3_d v1, Vec3_d v2);
Vec3_d vec3d_mul(Vec3_d v1, Vec3_d v2);
Vec3_d vec3d_sub(Vec3_d v1, Vec3_d v2);
Vec3_d vec3d_unit(Vec3_d v);
double vec3d_dot(Vec3_d v1, Vec3_d v2);
double vec3d_length(Vec3_d v);
double vec3d_x(Vec3_d v);
double vec3d_y(Vec3_d v);
double vec3d_z(Vec3_d v);

#endif
