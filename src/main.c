#define SAMPLES_PER_PIXEL 100 
#define RAY_MAX_DEPTH 30 

#include "material.h"
#include "camera.h"
#include "hitable_list.h"
int main() {
  int IMAGE_WIDTH = 512;
  int IMAGE_HEIGHT = 256;
  Material sphere_m_test = new_mat(LAMBERTIAN, vec3d_new(0.5,0.5,0.5));
  Material sphere_m_test2 = new_mat(LAMBERTIAN, vec3d_new(0.7,0.1,0.1));
  Material sphere_m_test3 = new_mat(METAL, vec3d_new(0.9,0.86,0.9));
  Material sphere_m_test4 = new_mat(METAL, vec3d_new(0.25,0.86,0.9));
  HitableList *world = init_hit_record_list(10);
  Sphere sphere1 = {.center = vec3d_new(1.0, 0.0, -1.0), .radius = 0.5, .sphere_mat=sphere_m_test};
  Sphere sphere2 = {.center = vec3d_new(0.0, -100.5, -3.5), .radius = 100.0, .sphere_mat=sphere_m_test2};
  Sphere sphere3 = {.center = vec3d_new(0.0, 0.24, -1.0), .radius = 0.5, .sphere_mat=sphere_m_test3};
  Sphere sphere4 = {.center = vec3d_new(-1.5, 0.14, -1.0), .radius = 0.55, .sphere_mat=sphere_m_test4};
  add_sphere_to_hitablelist(world, &sphere2);
  add_sphere_to_hitablelist(world, &sphere1);
  add_sphere_to_hitablelist(world, &sphere3);
  add_sphere_to_hitablelist(world, &sphere4);
  CameraSettings *cam = new_camera_settings(IMAGE_WIDTH, IMAGE_HEIGHT, 1.0, 2.0,
                                            vec3d_from_float(0.0));
  render(cam, world, SAMPLES_PER_PIXEL, RAY_MAX_DEPTH);
}
