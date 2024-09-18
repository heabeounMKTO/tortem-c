#include "vec.h"
#include "ray.h"



Vec3_d orig(Ray r) {
  return r.origin;
}

Vec3_d dir(Ray r) {
  return r.direction;
}

Vec3_d ray_at(Ray r, float t) {
  Vec3_d vec_t = vec3d_from_float(t);
  Vec3_d at = vec3d_add(r.origin, vec3d_mul(vec_t, r.direction));
  return at; 
}
