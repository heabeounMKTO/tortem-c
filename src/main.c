#include <stdio.h>
#include "vec.h"
#include "color.h"
#include "ray.h"

int main() {
  int IMAGE_WIDTH = 512;
  int IMAGE_HEIGHT = 256;
  double aspect_ratio =(double) IMAGE_WIDTH / (double) IMAGE_HEIGHT; 
  double viewport_height = 2.0;
  double viewport_width = viewport_height * aspect_ratio;
  double focal_length =  1.0;
  Vec3_d camera_center = vec3d_new(0.0,0.0,0.0);
  Vec3_d viewport_u = vec3d_new(viewport_width, 0.0, 0.0);
  Vec3_d viewport_v = vec3d_new(0.0, -viewport_height, 0.0);

  Vec3_d pixel_delta_u = vec3d_div(viewport_u, vec3d_from_int(IMAGE_WIDTH));
  Vec3_d pixel_delta_v = vec3d_div(viewport_v, vec3d_from_int(IMAGE_HEIGHT));
  Vec3_d viewport_upper_left = vec3d_sub(
      vec3d_sub(
          vec3d_sub(camera_center, vec3d_new(0.0, 0.0, focal_length)),
          vec3d_div(viewport_u, vec3d_from_float(2.0))
      ),
      vec3d_div(viewport_v, vec3d_from_float(2.0))
  );

  
  Vec3_d pixel00_loc;
  pixel00_loc = vec3d_add(viewport_upper_left, 
                          vec3d_mul(vec3d_from_float(0.5), 
                                    vec3d_add(pixel_delta_u, pixel_delta_v)));  

  printf("P3\n%i %i\n255\n", IMAGE_WIDTH, IMAGE_HEIGHT); 
  for (int j = 0; j < IMAGE_HEIGHT; j++) {
    for (int i =0; i<IMAGE_WIDTH; i++) {
      Vec3_d pixel_center = vec3d_add(pixel00_loc, vec3d_mul(vec3d_from_int(i), pixel_delta_u));
      pixel_center = vec3d_add(pixel_center, vec3d_mul(vec3d_from_int(j), pixel_delta_v));
      Vec3_d ray_dir = vec3d_sub(pixel_center, camera_center);
      Ray r = {.origin=camera_center, .direction=ray_dir};
      Vec3_d pixel_color = ray_color(r);
      ScreenColor wc = write_color(pixel_color, 0);
      printf("%i %i %i\n", wc.r, wc.g,wc.b);
    }
  }
}
