#include "color.h"
#include "hitable.h"
#include "hitable_list.h"
#include "interval.h"
#include "vec.h"
#include <stdbool.h>
#include <math.h>
#include "post_process.h"

double hit_sphere(Vec3 center , double radius, Ray r) {
  Vec3 oc = sub_vec3(center, r.origin);
  double a = len_sq(r.direction);
  double h = dot(r.direction, oc);
  double c = len_sq(oc) - (radius * radius);
  double discriminant = h*h - a*c;
  if (discriminant < 0) {
    return -1.0;
  } else {
    return (h - sqrt(discriminant)) / a;
  }
}

/// Converts ray to normalized color 0.0->1.0
Vec3 ray_color(Ray r, HitableList* world, int max_depth)  {
  Interval ray_interval = {.min=0.0, .max=INFINITY};
  HitRecord* world_hits = check_world_hits(world, r, ray_interval);
  if (max_depth <= 0) {
    return new_vec(0.0, 0.0, 0.0);
  }

  if(world_hits->is_hit) {
    Vec3 direction = random_on_hemisphere(world_hits->normal);
    Ray _r = {.direction=direction, .origin=r.origin};
    Vec3 _n = ray_color(_r, world, max_depth - 1);
    return mul_vec3(new_vec(_n.x, _n.y, _n.z), double2vec(0.5));
  } else {
    Vec3 unit_dir = unit_vec(r.direction); 
    double a = 0.5 * (unit_dir.y + 1.0);
    Vec3 final_color = mul_vec3(double2vec(1.0 - a), new_vec(1.0, 1.0, 1.0)); 
    final_color = add_vec3(final_color, mul_vec3(double2vec(a), new_vec(0.5, 0.7, 1.0)));
    return final_color;
  }
  
}


// converts double to rgb values for 
// final display on screen
ScreenColor write_color(Vec3 pixel_color) {
  double r = apply_aces(pixel_color.x);
  double g = apply_aces(pixel_color.y);
  double b = apply_aces(pixel_color.z);
  
  Interval intensity = {.min=0.0, .max=0.99};

  int rbyte = (int) (255.999 * interval_clamp(intensity, r));
  int gbyte = (int) (255.999 * interval_clamp(intensity, g));
  int bbyte = (int) (255.999 * interval_clamp(intensity, b));
  ScreenColor color = { rbyte, gbyte, bbyte };
  return color ;
}
