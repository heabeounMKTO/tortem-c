#include "vec.h"
#include "ray.h"

Vec3 orig(Ray r) {
  return r.origin;
}

Vec3 dir(Ray r) {
  return r.direction;
}

Vec3 ray_at(Ray r, double t) {
  Vec3 vec_t = double2vec(t);
  return add_vec3(r.origin, mul_vec3(vec_t, r.direction));
}
