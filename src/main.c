// TODO: refactor materaisl to `new_metal` and `new_lambert`

#include "sphere.h"
#include "vec.h"
#define SAMPLES_PER_PIXEL 80
#define RAY_MAX_DEPTH 20 

#include "camera.h"
#include "hitable_list.h"
#include "material.h"

int main() {
  int IMAGE_WIDTH = 1024;
  int IMAGE_HEIGHT = 512;
  Material sphere_m_test = new_metal_mat(vec3d_new(0.7, 0.57, 0.67), 0.01);
  Material sphere_m_test2 = new_lambert_mat(vec3d_new(0.5, 0.7, 0.9));
  Material sphere_m_fuzz = new_metal_mat(vec3d_new(0.65, 0.9, 0.9), 0.45);
  Material sphere_m_fuzz2 = new_metal_mat(vec3d_new(0.95, 0.95, 0.95), 0.0);
  Material sphere_m_glass = new_dialectric_mat(vec3d_new(1.0, 1.0, 1.0), 1.5);
  Material sphere_m_glass2 = new_dialectric_mat(vec3d_new(1.0, 1.0, 1.0), (1.0 / 1.45));
  Material sphere_m_glass4 = new_dialectric_mat(vec3d_new(1.0, 1.0, 1.0), (1.0/2.4));
  Material sphere_m_glass3 = new_dialectric_mat(vec3d_new(1.0, 1.0, 1.0), (1.45));

  HitableList *world = init_hit_record_list(1);
  Sphere sphere = new_sphere(vec3d_new(0.0, -100.5, -3.5), sphere_m_test, 100.0);
  Sphere sphere_big = new_sphere(vec3d_new(0.0, 0.0, -1.0), sphere_m_glass, 0.5);
  Sphere sphere_smol = new_sphere(vec3d_new(0.0, 0.0, -1.0), sphere_m_glass2, 0.45);
  Sphere sphere2 = new_sphere(vec3d_new(2.0,0.5,-2.2),sphere_m_fuzz, 1.0);
  Sphere sphere3 = new_sphere(vec3d_new(-1.0,0.5,-2.0),sphere_m_test2, 0.689);

  Sphere sphere_big2 = new_sphere(vec3d_new(1.0, 0.135, 0.0), sphere_m_fuzz2, 0.7);
  // Sphere sphere_smol2 = new_sphere(vec3d_new(1.0, 0.135, 0.0), sphere_m_fuzz2, 0.4);
  
  add_sphere_to_hitablelist(world, &sphere);
  add_sphere_to_hitablelist(world, &sphere_big);
  add_sphere_to_hitablelist(world, &sphere_smol);
  add_sphere_to_hitablelist(world, &sphere2);
  add_sphere_to_hitablelist(world, &sphere3);
  add_sphere_to_hitablelist(world, &sphere_big2);
  // add_sphere_to_hitablelist(world, &sphere_smol2);
  Vec3_d look_from = vec3d_new(-2.0, 2.0, -1.0);
  Vec3_d look_at = vec3d_new(0.0,0.0,-1.0);
  CameraSettings *cam = new_camera_settings(IMAGE_WIDTH, IMAGE_HEIGHT, 1.0, 2.0,
                                             90, look_from, look_at);
  render(cam, world, SAMPLES_PER_PIXEL, RAY_MAX_DEPTH);
}
