#include "color.h"
#include "ray.h"
#include "utils.h"
#include "vec.h"
#include <stdbool.h>

double hit_sphere(Vec3_d center, double radius, Ray r) {
  Vec3_d oc = vec3d_sub(center, r.origin);
  double a = vec3d_dot(r.direction, r.direction);
  double h = vec3d_dot(r.direction, oc);
  double c = vec3d_dot(oc,oc) - radius*radius;
  double disc = h * h -  a * c;
  
  if (disc < 0.0) {
    return -1.0;
  } else {
    return (h - sqrt(disc)) / a;
  }
}

Vec3_d ray_color(Ray r) {
  double t = hit_sphere(vec3d_new(0.0, 0.0, -1.0), 0.45, r);
  if (t > 0.0) {
    Vec3_d at = ray_at(r, t);
    Vec3_d n = vec3d_unit(vec3d_sub(at, vec3d_new(0.0,0.0,-1.0)));
    return vec3d_mul(
        vec3d_from_float(0.5),
        vec3d_new(vec3d_x(n) + 1.0, vec3d_y(n) + 1.0, vec3d_z(n) + 1.0));
  }

  Vec3_d unit_dir = vec3d_unit(r.direction);
  double a = 0.5 * (vec3d_y(unit_dir) + 1.0);
  Vec3_d final_color =
      vec3d_mul(vec3d_from_float(1.0 - a), vec3d_new(1.0, 1.0, 1.0));
  final_color = vec3d_add(
      final_color, vec3d_mul(vec3d_from_float(a), vec3d_new(0.5, 0.7, 1.0)));
  return final_color;
}

// TODO: refactor into SIMD
Vec3_d apply_aces(Vec3_d col) {
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

// converts double to rgb values for
// setting `apply_curve` to 1 applies ACES tone curve
// setting it to anything other than 1 wont apply anything
// final display on screen
ScreenColor write_color(Vec3_d pixel_color, short int apply_curve) {
  Vec3_d applied_curve;
  if (apply_curve == 1) {
    applied_curve = apply_aces(pixel_color);
  } else {
    applied_curve = pixel_color;
  }
  Interval intensity = {.min = 0.0f, .max = 0.99f};
  int rbyte =
      (int)(255.99f * interval_clamp(intensity, vec3d_x(applied_curve)));
  int gbyte =
      (int)(255.99f * interval_clamp(intensity, vec3d_y(applied_curve)));
  int bbyte =
      (int)(255.99f * interval_clamp(intensity, vec3d_z(applied_curve)));
  ScreenColor color = {rbyte, gbyte, bbyte};
  return color;
}
