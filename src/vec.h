#ifndef HB_VEC_H
#define HB_VEC_H
#define RUAPU_IMPLEMENTATION
#include <stdio.h>
#include <math.h>

#if defined(__i386__) || defined(__x86_64__) || defined(_M_IX86) || defined(_M_X64)
#include <immintrin.h>

typedef struct  {
  int mmx, sse, sse2,sse3,ssse3,sse41,sse42,sse4a,xop,avx,f16c,fma,avx2,avx512f,avx512bw,avx512cd,avx512dq,avx512vl,avx512vnni,avx512bf16,avx512ifma,avx512vbmi,avx512vbmi2,avx512fp16,avx512er,avx5124fmaps,avx5124vnniw,avxvnni,avxvniint8,avxvnniint16,avxifma,amxfp16,amxbf16,amxint8,amxtile,bmi1,bmi2,gfni,aesni,vaes,sha,rdrand,rdseed,tsx;
} available_isa;

typedef struct {
  __m128 data;
} Vec3;

// TODO: int vec
typedef struct {
 __m128i data; 
} Vec3_i;

#elif __aarch64__ 
#include <arm_neon.h>
typedef struct {
  int neon,vfpv4,lse,cpuid,asimdrdm,asimdhp,asimddp,asimdfhm,bf16,i8mm,frint,jscvt,fcma,mte,mte2,sve,sve2,svebf16,svei8mm,svef32mm,svef64mm,sme,smef16f16,smef64f64,pmull,crc32,aes,sha1,sha2,sha3,sha512,sm3,sm4,svepmull,svebitperm,svaes,svesha3,svesm4,amx;
} available_isa;

typedef struct {
  float32x4_t data;
} Vec3;

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


void debug_vec();
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


// Vec3 random_in_unit_sphere();
// Vec3 random_unit_vec3_sphere();
// Vec3 random_on_hemisphere(Vec3 normal);



#endif
