#include "hitable_list.h"
#include "vec.h"
#include "utils.h"
#include "camera.h"
#include "color.h"

Vec3 sample_sq() {
  Vec3 random_vec = { random_double() - 0.5, random_double() - 0.5, 0.0 };
  return random_vec;
}

Camera* new_cam(int image_width, int image_height) {
  double aspect_ratio = (double) image_width / (double) image_height;
  double focal_length = 1.0;
  double viewport_height = 2.0;
  double viewport_width = viewport_height * ((double)image_width / image_height);
  Vec3 origin = {0.0, 0.0, 0.0};
  Vec3 viewport_u = {viewport_width, 0.0, 0.0};
  Vec3 viewport_v = {0.0, -viewport_height, 0.0};
  Vec3 pixel_delta_u = div_vec3(viewport_u, int2vec(image_width));
  Vec3 pixel_delta_v = div_vec3(viewport_v, int2vec(image_height));
  Vec3 viewport_upper_left = sub_vec3(
      sub_vec3(
          sub_vec3(origin, new_vec(0.0, 0.0, focal_length)),
          div_vec3(viewport_u, double2vec(2.0))
      ),
      div_vec3(viewport_v, double2vec(2.0))
  );
  Vec3 pixel00_loc = add_vec3(
      viewport_upper_left,
      mul_vec3(double2vec(0.5), add_vec3(pixel_delta_u, pixel_delta_v))
  );
  Camera* _cam = (Camera*)malloc(sizeof(Camera));
  _cam->aspect_ratio = aspect_ratio;
  _cam->image_width = image_width;
  _cam->image_height = image_height;
  _cam->origin = origin;
  _cam->pixel_delta_u=pixel_delta_u;
  _cam->pixel_delta_v=pixel_delta_v;
  _cam->pixel00_loc=pixel00_loc;
  return _cam;
}

Ray get_ray(Camera* camera, int i, int j) {
  Vec3 offset = sample_sq();
  // MAN MADE HORRORS BEYOND MY COMPREHENSION
  Vec3 pixel_sample = add_vec3(add_vec3(camera->pixel00_loc, mul_vec3(double2vec((double) i + offset.x), camera->pixel_delta_u)), mul_vec3(double2vec((double) j + offset.y), camera->pixel_delta_v));
  // bottom text
  Vec3 ray_origin = camera->origin;
  Vec3 ray_dir = sub_vec3(pixel_sample, ray_origin);
  Ray final_ray = { .origin=ray_origin, .direction=ray_dir };
  return final_ray;
}

void render(Camera* camera, HitableList world, int samples_per_pixel) {
   double pixel_samples_scale = 1.0 / (double) samples_per_pixel;
   (void) (pixel_samples_scale);
   for (int j=0; j < camera->image_height; j++) {
    for(int i =0; i < camera->image_width; i++) {

      /// old code also segfaults when under -100 for sphere positon for some reason.. 
      // Vec3 pixel_i = mul_vec3(camera->pixel_delta_u, int2vec(i));
      // Vec3 pixel_j = mul_vec3(camera->pixel_delta_v, int2vec(j));
      // Vec3 pixel_center = add_vec3(camera->pixel00_loc, pixel_i);
      // pixel_center = add_vec3(pixel_center, pixel_j);
      // Vec3 ray_directon = sub_vec3(pixel_center, camera->camera_center);
      // Vec3 _ray_color = ray_color(get_ray(camera, i, j), &world);
      // ScreenColor col = write_color(_ray_color);
      // =========================================
      
      Vec3 pixel_color = {0.0,0.0,0.0};
      for (int sample=0; sample < samples_per_pixel; sample++) {
        Vec3 _ray_color = ray_color(get_ray(camera, i, j), &world);
        pixel_color = add_vec3(pixel_color, _ray_color); 
      }
      ScreenColor col = write_color(mul_vec3(pixel_color, double2vec(pixel_samples_scale)));
      printf("%d %d %d\n", col.r, col.g, col.b);
    }    
  } 
}
