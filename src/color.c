#include "color.h"
#include "hitable_list.h"
#include "vec.h"
#include <stdbool.h>

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


Vec3 ray_color(Ray r, HitableList* world)  {
  Interval ray_interval = {.min=0.001, .max=INFINITY};
  HitRecord* world_hits = check_world_hits(world, r, ray_interval);
  double t = hit_sphere(new_vec(0.0,0.0,-1.0), 0.5, r);
  if (t > 0.0) {
    Vec3 at = ray_at(r,t);
    Vec3 N = unit_vec(sub_vec3(at, new_vec(0.0,0.0,-1.0))); 
    return mul_vec3(double2vec(0.5) , new_vec( N.x + 1.0, N.y + 1.0, N.z + 1.0 )); 
  }

  Vec3 unit_dir = unit_vec(r.direction); 
  double a = 0.5 * (unit_dir.y + 1.0);
  Vec3 final_color = mul_vec3(double2vec(1.0 - a), new_vec(1.0, 1.0, 1.0)); 
  final_color = add_vec3(final_color, mul_vec3(double2vec(a), new_vec(0.5, 0.7, 1.0)));
  return final_color;
}


// converts double to rgb values for 
// final display on screen
ScreenColor write_color(Vec3 pixel_color) {
  double r = pixel_color.x;
  double g = pixel_color.y;
  double b = pixel_color.z;
  int rbyte = (int) (255.999 * r);
  int gbyte = (int) (255.999 * g);
  int bbyte = (int) (255.999 * b);
  ScreenColor color = { rbyte, gbyte, bbyte };
  return color ;
}
