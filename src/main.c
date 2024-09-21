// TODO: refactor materaisl to `new_metal` and `new_lambert`

#define SAMPLES_PER_PIXEL 100
#define RAY_MAX_DEPTH 30

#include "camera.h"
#include "hitable_list.h"
#include "material.h"

int main() {
  int IMAGE_WIDTH = 512;
  int IMAGE_HEIGHT = 256;
  // Material sphere_m_test = new_mat(LAMBERTIAN, vec3d_new(0.5,0.5,0.5));
  Material sphere_m_test = new_lambert_mat(vec3d_new(0.8, 0.5, 0.5));
  Material sphere_m_test2 = new_lambert_mat(vec3d_new(0.5, 0.7, 0.9));
  Material sphere_m_fuzz = new_metal_mat(vec3d_new(0.9, 0.89, 0.9), 0.45);
  Material sphere_m_glass = new_dialectric_mat(vec3d_new(1.0, 1.0, 1.0), 1.5);
  Material sphere_m_glass2 = new_dialectric_mat(vec3d_new(1.0, 1.0, 1.0), (1.0/1.5));

  HitableList *world = init_hit_record_list(10);
  Sphere sphere1 = {.center = vec3d_new(1.0, 0.0, -1.0),
                    .radius = 0.5,
                    .sphere_mat = sphere_m_test};
  Sphere sphere2 = {.center = vec3d_new(0.0, -100.5, -3.5),
                    .radius = 100.0,
                    .sphere_mat = sphere_m_test2};
  Sphere sphere3_big = {.center = vec3d_new(0.0, 0.24, -1.0),
                    .radius = 0.5,
                    .sphere_mat = sphere_m_glass};

  Sphere sphere3_smol = {.center = vec3d_new(0.0, 0.24, -1.0),
                    .radius = 0.37,
                    .sphere_mat = sphere_m_glass2};

  Sphere sphere4 = {.center = vec3d_new(-1.2, 0.14, -1.0),
                    .radius = 0.55,
                    .sphere_mat = sphere_m_fuzz};
  add_sphere_to_hitablelist(world, &sphere2);
  add_sphere_to_hitablelist(world, &sphere1);
  add_sphere_to_hitablelist(world, &sphere3_big);
  add_sphere_to_hitablelist(world, &sphere3_smol);
  add_sphere_to_hitablelist(world, &sphere4);

  CameraSettings *cam = new_camera_settings(IMAGE_WIDTH, IMAGE_HEIGHT, 1.0, 2.0,
                                            vec3d_from_float(0.0));
  render(cam, world, SAMPLES_PER_PIXEL, RAY_MAX_DEPTH);
}
