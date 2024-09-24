#include "vec.h"

#ifndef USE_LINASM_VEC

// f32 opps
void vec3_print(Vec3 v) { printf("x: %f y: %f z: %f", v.x, v.y, v.z); }

float vec3_lengthsq(Vec3 v) { return (v.x * v.x) + (v.y * v.y) + (v.z * v.z); }

Vec3 vec3_from_float(float f) {
  Vec3 v = {f, f, f};
  return v;
}

Vec3 vec3_from_int(int i) {
  Vec3 v = {(float)i, (float)i, (float)i};
  return v;
}

Vec3 vec3_add(Vec3 v1, Vec3 v2) {
  Vec3 v = {.x = v1.x + v2.x, .y = v1.y + v2.y, .z = v1.z + v2.z};
  return v;
}

Vec3 vec3_sub(Vec3 v1, Vec3 v2) {
  Vec3 v = {.x = v1.x - v2.x, .y = v1.y - v2.y, .z = v1.z - v2.z};
  return v;
}

Vec3 vec3_mul(Vec3 v1, Vec3 v2) {
  Vec3 v = {.x = v1.x * v2.x, .y = v1.y * v2.y, .z = v1.z * v2.z};
  return v;
}

Vec3 vec3_div(Vec3 v1, Vec3 v2) {
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
Vec3 vec3_negate(Vec3 v) {
  Vec3 neg = {-v.x, -v.y, -v.z};
  return neg;
}

float vec3_dot(Vec3 v1, Vec3 v2) {
  return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

Vec3 vec3_cross(Vec3 v1, Vec3 v2) {
  return (Vec3){.x = v1.y * v2.z - v1.z * v2.y,
                .y = v1.z * v2.x - v1.x * v2.z,
                .z = v1.x * v2.y - v1.y * v2.x};
}

float vec3_length(Vec3 v) { return sqrt(vec3_dot(v, v)); }

Vec3 vec3_unit(Vec3 v) {
  float len = vec3_length(v);
  Vec3 vec = {len, len, len};
  return vec3_div(v, vec);
}

Vec3 vec3_scale(Vec3 v, float t) { return (Vec3){v.x * t, v.y * t, v.z * t}; }
float vec3x(Vec3 v) { return v.x; }
float vec3y(Vec3 v) { return v.y; }
float vec3z(Vec3 v) { return v.z; }

/// f64 opps

double vec3d_lengthsq(Vec3_d v) {
  return (v.x * v.x) + (v.y * v.y) + (v.z * v.z);
}
void vec3d_print(Vec3_d v) { printf("x: %f y: %f z: %f\n", v.x, v.y, v.z); }

Vec3_d vec3d_add(Vec3_d v1, Vec3_d v2) {
  Vec3_d v = {.x = v1.x + v2.x, .y = v1.y + v2.y, .z = v1.z + v2.z};
  return v;
}

Vec3_d vec3d_from_float(double f) {
  Vec3_d v = {f, f, f};
  return v;
}

Vec3_d vec3d_cross(Vec3_d v1, Vec3_d v2) {
  return (Vec3_d){.x = v1.y * v2.z - v1.z * v2.y,
                  .y = v1.z * v2.x - v1.x * v2.z,
                  .z = v1.x * v2.y - v1.y * v2.x};
}

Vec3_d vec3d_from_int(int i) {
  Vec3_d v = {(double)i, (double)i, (double)i};
  return v;
}

Vec3_d vec3d_sub(Vec3_d v1, Vec3_d v2) {
  Vec3_d v = {.x = v1.x - v2.x, .y = v1.y - v2.y, .z = v1.z - v2.z};
  return v;
}

Vec3_d vec3d_mul(Vec3_d v1, Vec3_d v2) {
  Vec3_d v = {.x = v1.x * v2.x, .y = v1.y * v2.y, .z = v1.z * v2.z};
  return v;
}

Vec3_d vec3d_div(Vec3_d v1, Vec3_d v2) {
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

Vec3_d vec3d_negate(Vec3_d v) {
  Vec3_d neg = {-v.x, -v.y, -v.z};
  return neg;
}
double vec3d_dot(Vec3_d v1, Vec3_d v2) {
  return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

double vec3d_length(Vec3_d v) {
  double dot_v = vec3d_dot(v, v);
  return sqrt(dot_v);
}

Vec3_d vec3d_scale(Vec3_d v, double t) {
  return (Vec3_d){v.x * t, v.y * t, v.z * t};
}

Vec3_d vec3d_unit(Vec3_d v) {
  double len = vec3d_length(v);
  Vec3_d vec = {len, len, len};
  return vec3d_div(v, vec);
}

Vec3_d vec3d_reflect(Vec3_d v, Vec3_d n) {
  Vec3_d _a = vec3d_mul(
      vec3d_mul(vec3d_from_float(2.0), vec3d_from_float(vec3d_dot(v, n))), n);
  return vec3d_sub(v, _a);
}

Vec3_d vec3d_refract(Vec3_d uv, Vec3_d n, double etai_over_etat) {
  double cos_theta = fmin(vec3d_dot(vec3d_negate(uv), n), 1.0);
  Vec3_d r_out_perp =
      vec3d_scale(vec3d_add(uv, vec3d_scale(n, cos_theta)), etai_over_etat);
  Vec3_d r_out_parallel =
      vec3d_scale(n, -sqrt(fabs(1.0 - vec3d_lengthsq(r_out_perp))));
  return vec3d_add(r_out_perp, r_out_parallel);
}

double vec3d_x(Vec3_d v) { return v.x; }
double vec3d_y(Vec3_d v) { return v.y; }
double vec3d_z(Vec3_d v) { return v.z; }

/// Use `LinAsm` SIMD functions
#else
#include <Vector3D.h>

Vec3_d vec3d_add(Vec3_d v1, Vec3_d v2) {
  struct v3D64_t _v1 = {v1.x, v1.y, v1.z};
  struct v3D64_t _v2 = {v2.x, v2.y, v2.z};
  Vector3D_Add_flt64(&_v1, &_v2);
  return (Vec3_d){v1.x, v1.y, v1.z};
}

Vec3_d vec3d_sub(Vec3_d v1, Vec3_d v2) {
  struct v3D64_t _v1 = {v1.x, v1.y, v1.z};
  struct v3D64_t _v2 = {v2.x, v2.y, v2.z};
  Vector3D_Sub_flt64(&_v1, &_v2);
  return (Vec3_d){v1.x, v1.y, v1.z};
}

Vec3_d vec3d_mul(Vec3_d v1, Vec3_d v2) {
  struct v3D64_t _v1 = {v1.x, v1.y, v1.z};
  struct v3D64_t _v2 = {v2.x, v2.y, v2.z};
  Vector3D_Mul_flt64(&_v1, &_v2);
  return (Vec3_d){v1.x, v1.y, v1.z};
}

Vec3_d vec3d_div(Vec3_d v1, Vec3_d v2) {
  struct v3D64_t _v1 = {v1.x, v1.y, v1.z};
  struct v3D64_t _v2 = {v2.x, v2.y, v2.z};
  Vector3D_Div_flt64(&_v1, &_v2);
  return (Vec3_d){v1.x, v1.y, v1.z};
}

double vec3d_dot(Vec3_d v1, Vec3_d v2) {
  struct v3D64_t _v1 = {v1.x, v1.y, v1.z};
  struct v3D64_t _v2 = {v2.x, v2.y, v2.z};
  double _res = (double)Vector3D_ScalarProduct_flt64(&_v1, &_v2);
  return _res;
}

Vec3_d vec3d_cross(Vec3_d v1, Vec3_d v2) {
  struct v3D64_t _v1 = {v1.x, v1.y, v1.z};
  struct v3D64_t _v2 = {v2.x, v2.y, v2.z};
  Vector3D_VectorProduct_flt64(&_v1, &_v2);
  return (Vec3_d){v1.x, v1.y, v1.z};
}

Vec3_d vec3d_unit(Vec3_d v) {
  struct v3D64_t _v = {v.x, v.y, v.z};
  Vector3D_Normalize_flt64(_v);
  return (Vec3_d) { _v.x, _v.y, _v.z }; 
}


#endif
