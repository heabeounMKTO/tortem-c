#include "hitable_list.h"
#include "vec.h"
#include "utils.c"
#include "camera.h"
#include "color.h"

Vec3 sample_sq() {
  Vec3 random_vec = { random_double() - 0.5, random_double() - 0.5, 0.0 };
  return random_vec;
}


Ray get_ray(Camera* camera, int i, int j) {
  Vec3 offset = sample_sq();

  // MAN MADE HORRORS BEYOND MY COMPREHENSION
  Vec3 pixel_sample = add_vec3(add_vec3(camera->pixel00_loc, mul_vec3(double2vec((double) i + offset.x), camera->pixel_delta_u)), mul_vec3(double2vec((double)i + offset.y), camera->pixel_delta_v));
  // bottom text
  Vec3 ray_origin = camera->origin;
  Vec3 ray_dir = sub_vec3(pixel_sample, ray_origin);
  Ray final_ray = { .origin=ray_origin, .direction=ray_dir };
  return final_ray;
}

void render(Camera* camera, HitableList world, int samples_per_pixel) {
  double pixel_samples_scale = 1.0 / (double) samples_per_pixel;
   for (int j=0; j < camera->image_height; j++) {
    for(int i =0; i < camera->image_width; i++) {
      // Vec3 pixel_i = mul_vec3(camera->pixel_delta_u, int2vec(i));
      // Vec3 pixel_j = mul_vec3(camera->pixel_delta_v, int2vec(j));
      // Vec3 pixel_center = add_vec3(camera->pixel00_loc, pixel_i);
      // pixel_center = add_vec3(pixel_center, pixel_j);

      // Vec3 ray_directon = sub_vec3(pixel_center, camera_center);
      // Ray ray = { .origin=camera_center, .direction=ray_directon };
      // Vec3 ray_col = ray_color(ray); 
      // ScreenColor col = write_color(ray_col);
      Vec3 pixel_color = {0.0,0.0,0.0};
      for (int sample=0; sample < samples_per_pixel; sample++) {
        Vec3 _ray_color = ray_color(get_ray(camera, i, j));
        pixel_color = add_vec3(pixel_color, _ray_color); 
      }
      ScreenColor col = write_color(pixel_color);
      printf("%d %d %d\n", col.r, col.g, col.b);
    }    
  } 
}
