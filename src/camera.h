#ifndef CAMERA_H
#define CAMERA_H
#include "hitable_list.h"
#include "vec.h"
#include "ray.h"

typedef struct {
  double aspect_ratio;
  int image_width;
  int image_height;
  Vec3 origin;
  Vec3 pixel_delta_u;
  Vec3 pixel_delta_v;
  Vec3 pixel00_loc;
} Camera;

Camera* new_cam(int image_width, int image_height);
Ray get_ray(Camera* camera , int i, int j);
Vec3 sample_sq();

//LESSS GOOO
void render(Camera* camera, HitableList world, int samples_per_pixel);

#endif
