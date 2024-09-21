// TODO: refactor materaisl to `new_metal` and `new_lambert`

#include "sphere.h"
#define SAMPLES_PER_PIXEL 10
#define RAY_MAX_DEPTH 10

#include "camera.h"
#include "hitable_list.h"
#include "material.h"

int main() {
  int IMAGE_WIDTH = 512;
  int IMAGE_HEIGHT = 256;
  Material sphere_m_test = new_lambert_mat(vec3d_new(1.0, 0.5, 0.5));
  Material sphere_m_test2 = new_lambert_mat(vec3d_new(0.5, 0.7, 0.9));
  Material sphere_m_fuzz = new_metal_mat(vec3d_new(0.9, 0.89, 0.9), 0.45);
  Material sphere_m_glass = new_dialectric_mat(vec3d_new(1.0, 1.0, 1.0), 1.5);
  Material sphere_m_glass2 = new_dialectric_mat(vec3d_new(1.0, 1.0, 1.0), (1.0/1.5));

  HitableList *world = init_hit_record_list(1);
  // Sphere sphere1 = {.center = vec3d_new(1.0, 0.0, -1.0),
  //                   .radius = 0.5,
  //                   .sphere_mat = sphere_m_test};
  // Sphere sphere2 = {.center = vec3d_new(0.0, -100.5, -3.5),
  //                   .radius = 100.0,
  //                   .sphere_mat = sphere_m_test2};
  // Sphere sphere3_big = {.center = vec3d_new(0.0, 0.24, -1.0),
  //                   .radius = 0.5,
  //                   .sphere_mat = sphere_m_glass};

  // Sphere sphere3_smol = {.center = vec3d_new(0.0, 0.24, -1.0),
  //                   .radius = 0.37,
  //                   .sphere_mat = sphere_m_glass2};

  // Sphere sphere4 = {.center = vec3d_new(-1.2, 0.14, -1.0),
  //                   .radius = 0.55,
  //                   .sphere_mat = sphere_m_fuzz};
  Sphere sphere = new_sphere(vec3d_new(0.0,-100.5,-3.5), sphere_m_test, 100.0); 
  Sphere sphere_big = new_sphere(vec3d_new(0.0,0.24,-1.0), sphere_m_glass, 0.5);
  Sphere sphere_smol = new_sphere(vec3d_new(0.0,0.24,-1.0), sphere_m_glass2, 0.4);
                                 
  add_sphere_to_hitablelist(world, &sphere);
  add_sphere_to_hitablelist(world, &sphere_big);
  add_sphere_to_hitablelist(world, &sphere_smol);
  Vec3_d look_from = vec3d_new(-10.0, 10.0, 1.0);
  Vec3_d look_at = vec3d_new(0.0,0.0,-10.0);
  CameraSettings *cam = new_camera_settings(IMAGE_WIDTH, IMAGE_HEIGHT, 1.0, 2.0,
                                            vec3d_from_float(0.0), 90, look_from, look_at);
  render(cam, world, SAMPLES_PER_PIXEL, RAY_MAX_DEPTH);
}
