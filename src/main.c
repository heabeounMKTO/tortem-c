#include <stdio.h>
#include "vec.h"
#include "color.h"
#include "ray.h"
// #define IMAGE_WIDTH 256
// #define IMAGE_HEIGHT 256


int main() {
  int IMAGE_WIDTH = 256;
  int IMAGE_HEIGHT = 256;
  float aspect_ratio = (float) IMAGE_WIDTH / (float) IMAGE_HEIGHT;
  float focal_length = 1.0f;
  float viewport_height = 2.0f;
  float viewport_width = viewport_height * aspect_ratio;
  
  Vec3 origin = vec3_new(0.0f, 0.0f, 0.0f);
  Vec3 viewport_u = vec3_new(viewport_width, 0.0f, 0.0f);
  Vec3 viewport_v = vec3_new(0.0f, -viewport_height, 0.0f); 
  Vec3 pixel_delta_u = vec3_div(viewport_u, vec3_from_int(IMAGE_WIDTH));
  Vec3 pixel_delta_v = vec3_div(viewport_v, vec3_from_int(IMAGE_HEIGHT));
    Vec3 viewport_upper_left = vec3_sub(
      vec3_sub(
          vec3_sub(origin, vec3_new(0.0f, 0.0f, focal_length)),
          vec3_div(viewport_u, vec3_from_float(2.0f))
      ),
      vec3_div(viewport_v, vec3_from_float(2.0f))
  );
  Vec3 pixel00_loc = vec3_add(
      viewport_upper_left,
      vec3_mul(vec3_from_float(0.5f), vec3_add(pixel_delta_u, pixel_delta_v))
  );

  printf("P3\n %i %i\n255\n", IMAGE_WIDTH, IMAGE_HEIGHT); 
  for (int j = 0; j < IMAGE_HEIGHT; j++) {
    for (int i =0; i < IMAGE_WIDTH; i++) {
      Vec3 pixel_i = vec3_mul(pixel_delta_u, vec3_from_int(i));
      Vec3 pixel_j = vec3_mul(pixel_delta_v, vec3_from_int(j));
      Vec3 pixel_center = vec3_add(pixel00_loc, pixel_i);
      pixel_center = vec3_add(pixel_center, pixel_j);
      Vec3 ray_direction = vec3_sub(pixel_center, origin);
      Ray new_ray = {.origin=origin, .direction=ray_direction};   
      Vec3 _ayy = ray_color(new_ray);
      // vec3_print(_ayy);
      ScreenColor _sc = write_color(_ayy, 1);
      printf("%i %i %i\n", _sc.r , _sc.g , _sc.b);
    }
  }
}
