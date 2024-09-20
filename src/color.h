#include "vec.h"
#include <stdlib.h>
#include "ray.h"
#include <stdbool.h>
#include "hitable_list.h"
#include "hitable.h"
typedef struct {
  short int r,g,b;
} ScreenColor;


static inline Vec3_d ray_color(const Ray r, HitableList* world) {
  HitRecord* rec = (HitRecord*)malloc(sizeof(HitRecord));
  Interval _inv = interval_new(0.001, INFINITY);
  bool check_w =check_world_hits(world, r, _inv, rec); 
  if (check_w) {
    return vec3d_mul(vec3d_add(rec->normal , vec3d_from_float(1.0)), vec3d_from_float(0.5));
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
  Interval intensity = {.min = 0.0f, .max = 0.99f};
  const int rbyte =
      (int)(255.99f * interval_clamp(intensity, vec3d_x(applied_curve)));
  const int gbyte =
      (int)(255.99f * interval_clamp(intensity, vec3d_y(applied_curve)));
  const int bbyte =
      (int)(255.99f * interval_clamp(intensity, vec3d_z(applied_curve)));
  ScreenColor color = {rbyte, gbyte, bbyte};
  return color;
}

