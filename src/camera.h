#include "ray.h"
#include "utils.h"
#include "vec.h"





static inline Vec3_d sample_square() {
  return vec3d_new( random_double()  - 0.5 , random_double() - 0.5 , 0.0);
}


static inline Ray get_ray(Vec3_d pixel00_loc) {
  Vec3_d offset = sample_square(); 
  Vec3_d pixel_center = vec3d_add(pixel00_loc, vec3d_mul(vec3d_from_int(i), pixel_delta_u));
  pixel_center = vec3d_add(pixel_center, vec3d_mul(vec3d_from_int(j), pixel_delta_v));
}
