#include "camera.h"
#include "hitable_list.h"
#define SAMPLES_PER_PIXEL 200 
#define RAY_MAX_DEPTH 25 

int main() {
  int IMAGE_WIDTH = 512;
  int IMAGE_HEIGHT = 256;
  HitableList* world = init_hit_record_list(0);
  Sphere sphere1 = { .center=vec3d_new(0.0,0.0,-1.0), .radius=0.5 };
  Sphere sphere2 = { .center=vec3d_new(0.0,-100.5,-3.5), .radius=100.0 };
  Sphere sphere3 = { .center=vec3d_new(0.0,0.0,-1.5), .radius=0.5 };
  add_sphere_to_hitablelist(world, &sphere2);
  add_sphere_to_hitablelist(world, &sphere1);
  add_sphere_to_hitablelist(world, &sphere3);
  CameraSettings* cam = new_camera_settings(IMAGE_WIDTH, IMAGE_HEIGHT,1.0, 2.0,vec3d_from_float(0.0));
  render(cam, world, SAMPLES_PER_PIXEL, RAY_MAX_DEPTH);
}
