#include "utils.h"
#include "vec.h"
#include <stdlib.h>
#include "ray.h"
#include <stdbool.h>
#include "hitable_list.h"
#include "hitable.h"
typedef struct {
  short int r,g,b;
} ScreenColor;


// Vec3_d ray_color(const Ray r, HitableList* world, int depth); 

static inline Vec3_d ray_color(const Ray r, HitableList* world, int depth) {
  
  // static int max_recursion = 0;
  // if (depth > max_recursion) {
  //   max_recursion = depth;
  //   fprintf(stderr, "\nMax recursion depth: %d", max_recursion);
  //   fflush(stderr);
  // }

  if (depth <= 0) {
    return vec3d_from_float(0.0);
  }
  HitRecord* rec = (HitRecord*)malloc(sizeof(HitRecord));
  Interval _inv = interval_new(0.001, INFINITY);
  bool check_w =check_world_hits(world, r, _inv, rec); 
  if (check_w) {
    Vec3_d direction = random_on_hemisphere(rec->normal);
    Ray _temp_ray = {.origin=rec->p, .direction=direction};
    Vec3_d temp_raycol = ray_color(_temp_ray, world, depth-1);

    if (is_nan_vec3d(temp_raycol) || is_inf_vec3d(temp_raycol)) {
      // fprintf(stderr, "\nInvalid value detected in ray_color\n");
      return vec3d_from_float(0.0);
    }

    Vec3_d final =vec3d_mul(temp_raycol, vec3d_from_float(0.5));
    free_hit_record(rec);
    return final;
    // return vec3d_mul(vec3d_add(rec->normal , vec3d_from_float(1.0)), vec3d_from_float(0.5));
  }
  else {
    free_hit_record(rec);
    Vec3_d unit_dir = vec3d_unit(r.direction);
    double a = 0.5 * (vec3d_y(unit_dir) + 1.0);
    Vec3_d final_color = vec3d_mul(vec3d_from_float(1.0 - a), vec3d_new(1.0, 1.0, 1.0)); 
    final_color = vec3d_add(final_color, vec3d_mul(vec3d_from_float(a), vec3d_new(0.5, 0.7, 1.0)));
    return final_color;
  }
}




static inline Vec3_d apply_aces(Vec3_d col) {
  double a = 2.34;
  double b = 0.03;
  double c = 2.43;
  double d = 0.59;
  double e = 0.14;

  double _r = (vec3d_x(col) * (a * vec3d_x(col) + b)) /
              (vec3d_x(col) * (c * vec3d_x(col) + d) + e);
  double _g = (vec3d_y(col) * (a * vec3d_y(col) + b)) /
              (vec3d_y(col) * (c * vec3d_y(col) + d) + e);
  double _b = (vec3d_z(col) * (a * vec3d_z(col) + b)) /
              (vec3d_z(col) * (c * vec3d_z(col) + d) + e);
  Vec3_d _applied = vec3d_new(_r, _g, _b);
  return _applied;
}

static inline ScreenColor write_color(Vec3_d pixel_color, short int apply_curve) {
  Vec3_d applied_curve;
  if (apply_curve == 1) {
    applied_curve = apply_aces(pixel_color);
  } else {
    applied_curve = pixel_color;
  }
  const Interval intensity = {.min = 0.0f, .max = 0.99f};
  const int rbyte =
      (short int)(255.99f * interval_clamp(intensity, vec3d_x(applied_curve)));
  const int gbyte =
      (short int)(255.99f * interval_clamp(intensity, vec3d_y(applied_curve)));
  const int bbyte =
      (short int)(255.99f * interval_clamp(intensity, vec3d_z(applied_curve)));
  ScreenColor color = {rbyte, gbyte, bbyte};
  return color;
}

