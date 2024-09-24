#ifndef CAMERA_H
#define CAMERA_H

#include "hitable_list.h"
#include <jpeglib.h>
#include <math.h>
#include <pngconf.h>
#include <time.h>
#include "ray.h"
#include "utils.h"
#include "vec.h"
#include "color.h"

typedef struct {
  int width, height;
  double focus_distance,viewport_height,vfov, defocus_angle;
  Vec3_d camera_center, v_up, look_from, look_at; //Camera origin
} CameraSettings ;

static inline CameraSettings* new_camera_settings(int width, int height, double focus_distance, double viewport_height, double vfov, Vec3_d look_from, Vec3_d look_at, double defocus_angle){
  CameraSettings* _cam = (CameraSettings*)malloc(sizeof(CameraSettings));
  double theta = deg2rad(vfov);
  double h = tan(theta/2);
  _cam->width = width;
  _cam->height=height;
  _cam->viewport_height=2.0 * h * focus_distance;
  _cam->look_from = look_from;
  _cam->look_at = look_at;
  _cam->vfov=vfov;
  _cam->defocus_angle = defocus_angle;
  _cam->v_up=vec3d_new(0.0, 1.0, 0.0); 
  // _cam->focal_length=vec3d_length(vec3d_sub(_cam->look_from, _cam->look_at));
  _cam->focus_distance = focus_distance;
  return _cam;
}

static inline Vec3_d sample_square() {
  return vec3d_new( random_double()  - 0.5 , random_double() - 0.5 , 0.0);
}
static inline Vec3_d defocus_disk_sample(Vec3_d camera_origin, Vec3_d defocus_u, Vec3_d defocus_v) {
  Vec3_d p = random_in_unit_disk();
  Vec3_d _disk_u = vec3d_scale(defocus_u, vec3d_x(p) );
  Vec3_d _disk_v = vec3d_scale( defocus_v,vec3d_y(p) );
  return vec3d_add(_disk_v, vec3d_add(camera_origin, _disk_u));
}

static inline Ray get_ray(CameraSettings* camera,Vec3_d pixel00_loc,Vec3_d pixel_delta_u, Vec3_d pixel_delta_v, int i, int j, Vec3_d defocus_u, Vec3_d defocus_v) {
  Vec3_d offset = sample_square();
  Vec3_d pixel_sample = vec3d_add(vec3d_add(pixel00_loc, vec3d_mul(vec3d_from_float((double) i + vec3d_x(offset)), pixel_delta_u)), vec3d_mul(vec3d_from_float((double) j + vec3d_y(offset)), pixel_delta_v));
  Vec3_d ray_origin = (camera->defocus_angle <=0) ? camera->camera_center : defocus_disk_sample(camera->camera_center, defocus_u, defocus_v);
  Vec3_d ray_dir = vec3d_unit(vec3d_sub(pixel_sample, ray_origin));
  double ray_time = random_double();
  Ray final_ray = {.origin=ray_origin, .direction=ray_dir, .ray_time=ray_time};
  return final_ray;
}



static inline void render(CameraSettings* cam, HitableList* world, int samples_per_pixel, int max_depth, char* output_name) {
  unsigned char* IMAGE_BUFFER = new_jpeg_buffer(cam->width, cam->height); 
  // png_bytep* IMAGE_BUFFER = new_png_buffer(cam->width, cam->height);
  double aspect_ratio = (double) cam->width / (double) cam->height;
  double viewport_width = cam->viewport_height * aspect_ratio;
  cam->camera_center = cam->look_from;
  Vec3_d u,v,w; 
  w = vec3d_unit(vec3d_sub(cam->look_from, cam->look_at));
  u = vec3d_unit(vec3d_cross(cam->v_up, w));
  v = vec3d_cross(w, u);

  Vec3_d viewport_u = vec3d_scale(u, viewport_width);
  Vec3_d viewport_v = vec3d_scale(v, - cam->viewport_height);
  // Vec3_d viewport_u = vec3d_new(viewport_width, 0.0, 0.0);
  // Vec3_d viewport_v = vec3d_new(0.0, -cam->viewport_height, 0.0);

  Vec3_d pixel_delta_u = vec3d_div(viewport_u, vec3d_from_int(cam->width));
  Vec3_d pixel_delta_v = vec3d_div(viewport_v, vec3d_from_int(cam->height));
  double defocus_radius = cam->focus_distance * tan(deg2rad(cam->defocus_angle / 2.0));

  Vec3_d defocus_disk_u = vec3d_scale(u, defocus_radius);
  Vec3_d defocus_disk_v = vec3d_scale(v,defocus_radius);

 Vec3_d viewport_upper_left = vec3d_sub(
    vec3d_sub(
        vec3d_sub(
            cam->look_from,
            vec3d_mul(w, vec3d_from_float(cam->focus_distance))
        ),
        vec3d_div(viewport_u, vec3d_from_float(2.0))
    ),
    vec3d_div(viewport_v, vec3d_from_float(2.0))
);
Vec3_d pixel00_loc;
  pixel00_loc = vec3d_add(viewport_upper_left,
                          vec3d_mul(vec3d_from_float(0.5),
                                    vec3d_add(pixel_delta_u, pixel_delta_v)));
  double pixel_samples_scale = 1.0 / (double) samples_per_pixel;

  for (int j = 0; j < cam->height; j++) {
    for (int i = 0; i < cam->width; i++) {
      Vec3_d pixel_color = vec3d_from_float(0.0);
      for (int sample = 0; sample < samples_per_pixel; sample++ ) {
        Vec3_d _ray_color = ray_color(get_ray(cam,pixel00_loc, pixel_delta_u, pixel_delta_v, i, j, defocus_disk_u, defocus_disk_v), world, max_depth);
        pixel_color = vec3d_add(pixel_color, _ray_color);
      }
      ScreenColor col = write_color(vec3d_mul(pixel_color, vec3d_from_float(pixel_samples_scale)), 1);
      int pixel_index = (j * cam->width + i) * 3;

      /// print pixel values 
      /// for debugging flag
      #ifdef DEBUG_PIXELS
      printf("PIXELS x: %f y: %f z: %f\n", col.r, col.g, col.b);
      #endif
      store_pixel_in_buffer_jpeg(IMAGE_BUFFER, pixel_index, col.r, col.g, col.b);
    }
  }
  write_img_buffer(IMAGE_BUFFER, cam->width, cam->height, OUTPUT_JPEG, output_name);
}

#endif
