#ifndef INTERVAL_H
#define INTERVAL_H
#define NEAR_ZERO 1e-8

#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "vec.h"

// Two numbers with extra steps
typedef struct {
  double min;
  double max;
} Interval;

Interval interval_new(double min, double max);
bool interval_surrounds(Interval interval, double x);
double interval_clamp(Interval interval, double threshold);
double interval_sizeof(Interval interval);

static inline double random_double() {
  return rand() / (double) (RAND_MAX) + 1.0;
}

static inline double random_interval(double min, double max) {
return min + (max - min) * (rand() / (double) RAND_MAX);
}


static inline Vec3_d random_unit_vector() {
      while(true) {
          Vec3_d p = vec3d_new(
              random_interval(-1.0, 1.0),
              random_interval(-1.0, 1.0),
              random_interval(-1.0, 1.0)
          );
          double sq = vec3d_lengthsq(p);
          if(1e-160 < sq && sq <= 1.0) {
          return vec3d_unit(p);    
      } 
    }
}

static inline Vec3_d random_on_hemisphere(Vec3_d normal) {
  Vec3_d on_unit_sphere = random_unit_vector();
  if (vec3d_dot(on_unit_sphere, normal) > 0.0) {
    return on_unit_sphere;
  } else {
    return vec3d_negate(on_unit_sphere);
  }
}
static inline bool is_nan_vec3d(Vec3_d v) {
  return isnan(vec3d_x(v)) || isnan(vec3d_y(v)) || isnan(vec3d_z(v));
}
static inline bool is_inf_vec3d(Vec3_d v) {
  return isinf(vec3d_x(v)) || isinf(vec3d_y(v)) || isinf(vec3d_z(v));
}
static inline bool check_vec3d_near_zero(Vec3_d v) {
  return (fabs(vec3d_x(v)) < NEAR_ZERO  
          && fabs(vec3d_y(v)) < NEAR_ZERO 
          && fabs(vec3d_z(v)) < NEAR_ZERO);
}

static inline Vec3_d vec3d_reflect(Vec3_d v, Vec3_d n) {
  Vec3_d _a = vec3d_mul(vec3d_mul(vec3d_from_float(2.0), vec3d_from_float(vec3d_dot(v,n))), n);
  return vec3d_sub(v, _a);
}

static inline Vec3_d vec3d_refract(Vec3_d uv, Vec3_d n, double etai_over_etat) {
  double cos_theta = fmin(vec3d_dot(vec3d_negate(uv), n), 1.0);
  Vec3_d r_out_perp = vec3d_mul(vec3d_from_float(etai_over_etat), vec3d_add(uv, vec3d_mul(vec3d_from_float(cos_theta) , n)));
  Vec3_d r_out_parallel = vec3d_mul(vec3d_from_float(-sqrt(fabs(1.0 - vec3d_lengthsq(r_out_perp)))) ,n);
  return vec3d_add(r_out_perp , r_out_parallel);
}


#endif

