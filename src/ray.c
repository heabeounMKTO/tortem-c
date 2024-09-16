#include "vec.h"
#include "ray.h"



Vec3 orig(Ray r) {
  return r.origin;
}

Vec3 dir(Ray r) {
  return r.direction;
}

Vec3 ray_at(Ray r, float t) {
  Vec3 vec_t = vec3_from_float(t);
  Vec3 at = vec3_add(r.origin, vec3_mul(vec_t, r.direction));
  return at; 
}
