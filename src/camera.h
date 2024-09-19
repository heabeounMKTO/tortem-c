#include "hitable_list.h"
#include "ray.h"
#include "utils.h"
#include "vec.h"

typedef struct {
  int width, height;
  double focal_length,viewport_height;
  Vec3_d camera_center;
} CameraSettings ;


static inline void render(const CameraSettings* cam, const HitableList* world) {
  double aspect_ratio = (double) cam->width / (double) cam->height;
  double viewport_width = cam->viewport_height * aspect_ratio;
  Vec3_d viewport_u = vec3d_new(viewport_width, 0.0, 0.0);
  Vec3_d viewport_v = vec3d_new(0.0, -cam->viewport_height, 0.0);

  Vec3_d pixel_delta_u = vec3d_div(viewport_u, vec3d_from_int(cam->width));
  Vec3_d pixel_delta_v = vec3d_div(viewport_v, vec3d_from_int(cam->height));
  Vec3_d viewport_upper_left = vec3d_sub(
      vec3d_sub(vec3d_sub(cam->camera_center, vec3d_new(0.0, 0.0, cam->focal_length)),
                vec3d_div(viewport_u, vec3d_from_float(2.0))),
      vec3d_div(viewport_v, vec3d_from_float(2.0)));

  Vec3_d pixel00_loc;
  pixel00_loc = vec3d_add(viewport_upper_left,
                          vec3d_mul(vec3d_from_float(0.5),
                                    vec3d_add(pixel_delta_u, pixel_delta_v)));
  


}


static inline Vec3_d sample_square() {
  return vec3d_new( random_double()  - 0.5 , random_double() - 0.5 , 0.0);
}


static inline Ray get_ray(Vec3_d pixel00_loc) {
  Vec3_d offset = sample_square(); 
  Vec3_d pixel_center = vec3d_add(pixel00_loc, vec3d_mul(vec3d_from_int(i), pixel_delta_u));
  pixel_center = vec3d_add(pixel_center, vec3d_mul(vec3d_from_int(j), pixel_delta_v));
}
