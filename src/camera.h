#include "hitable_list.h"
#include <math.h>
#include <time.h>
#include "ray.h"
#include "utils.h"
#include "vec.h"
#include "color.h"

typedef struct {
  int width, height;
  double focal_length,viewport_height,vfov;
  Vec3_d camera_center, v_up, look_from, look_at; //Camera origin
} CameraSettings ;

static inline CameraSettings* new_camera_settings(int width, int height, double focal_length, double viewport_height, Vec3_d camera_center, double vfov, Vec3_d look_from, Vec3_d look_at){
  CameraSettings* _cam = (CameraSettings*)malloc(sizeof(CameraSettings));
  double theta = deg2rad(vfov);
  double h = tan(theta/2);
  _cam->width = width;
  _cam->height=height;
  _cam->viewport_height=2.0 * h * focal_length;
  _cam->camera_center=camera_center;
  _cam->vfov=vfov;
  _cam->v_up=vec3d_new(0.0, 1.0, 0.0); 
  _cam->look_from = look_from;
  _cam->look_at = look_at;
  _cam->focal_length=vec3d_length(vec3d_sub(_cam->look_from, _cam->look_at));
  return _cam;
}


static inline Vec3_d sample_square() {
  return vec3d_new( random_double()  - 0.5 , random_double() - 0.5 , 0.0);
}


static inline Ray get_ray(CameraSettings* camera,Vec3_d pixel00_loc,Vec3_d pixel_delta_u, Vec3_d pixel_delta_v, int i, int j) {
  Vec3_d offset = sample_square();
  Vec3_d pixel_sample = vec3d_add(vec3d_add(pixel00_loc, vec3d_mul(vec3d_from_float((double) i + vec3d_x(offset)), pixel_delta_u)), vec3d_mul(vec3d_from_float((double) j + vec3d_y(offset)), pixel_delta_v));
  Vec3_d ray_origin = camera->camera_center;
  Vec3_d ray_dir = vec3d_unit(vec3d_sub(pixel_sample, ray_origin));
  Ray final_ray = {.origin=ray_origin, .direction=ray_dir};
  return final_ray;
}



static inline void render(CameraSettings* cam, HitableList* world, int samples_per_pixel, int max_depth) {
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
  Vec3_d u,v,w; 
  w = vec3d_unit(cam->look_from, cam->look_at);
  u = vec3d_unit(vec3d_cross(cam->v_up, w));
  v = vec3d_cross(w, u);
        
  double pixel_samples_scale = 1.0 / (double) samples_per_pixel;
  printf("P3\n%i %i\n255\n", cam->width, cam->height);
  for (int j = 0; j < cam->height; j++) {
    for (int i = 0; i < cam->width; i++) {
      Vec3_d pixel_color = vec3d_from_float(0.0);
      for (int sample = 0; sample < samples_per_pixel; sample++ ) {
        Vec3_d _ray_color = ray_color(get_ray(cam,pixel00_loc, pixel_delta_u, pixel_delta_v, i, j), world, max_depth);
        pixel_color = vec3d_add(pixel_color, _ray_color);
      }
      ScreenColor col = write_color(vec3d_mul(pixel_color, vec3d_from_float(pixel_samples_scale)), 1);
      printf("%d %d %d\n", col.r, col.g, col.b);
    }
  }

}


