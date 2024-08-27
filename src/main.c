// #include <stdio.h>
// #include "vec.h"
// #include "color.h"
#include "camera.h"

int main() {
  int image_width = 512;
  int image_height = 256;
  // double aspect_ratio = (double) image_width / (double) image_height;
  // double focal_length = 1.0;
  // double viewport_height = 2.0;
  // double viewport_width = viewport_height * ((double)image_width / image_height);
  // Vec3 camera_center = {0, 0, 0};

  // // Calculate the vectors across the horizontal and down the vertical viewport edges.
  // Vec3 viewport_u = {viewport_width, 0, 0};
  // Vec3 viewport_v = {0, -viewport_height, 0};

  // // Calculate the horizontal and vertical delta vectors from pixel to pixel.
  // Vec3 pixel_delta_u = div_vec3(viewport_u, int2vec(image_width));
  // Vec3 pixel_delta_v = div_vec3(viewport_v, int2vec(image_height));

  // // Calculate the location of the upper left pixel.
  // Vec3 viewport_upper_left = sub_vec3(
  //     sub_vec3(
  //         sub_vec3(camera_center, new_vec(0, 0, focal_length)),
  //         div_vec3(viewport_u, double2vec(2.0))
  //     ),
  //     div_vec3(viewport_v, double2vec(2.0))
  // );
  // Vec3 pixel00_loc = add_vec3(
  //     viewport_upper_left,
  //     mul_vec3(double2vec(0.5), add_vec3(pixel_delta_u, pixel_delta_v))
  // );
  // printf("P3\n%d %d\n255\n", image_width, image_height);
  // for (int j=0; j < image_height; j++) {
  //   for(int i =0; i < image_width; i++) {
  //     Vec3 pixel_i = mul_vec3(pixel_delta_u, int2vec(i));
  //     Vec3 pixel_j = mul_vec3(pixel_delta_v, int2vec(j));
  //     Vec3 pixel_center = add_vec3(pixel00_loc, pixel_i);
  //     pixel_center = add_vec3(pixel_center, pixel_j);

  //     Vec3 ray_directon = sub_vec3(pixel_center, camera_center);
  //     Ray ray = { .origin=camera_center, .direction=ray_directon };
  //     Vec3 ray_col = ray_color(ray); 
  //     ScreenColor col = write_color(ray_col);
  //     printf("%d %d %d\n", col.r, col.g, col.b);
  //   }    
  // }
  Camera* cam = new_cam(image_width, image_height);
  return 0;
}
