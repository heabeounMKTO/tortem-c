#include "camera.h"
#include "hitable_list.h"
#include "keyframe.h"
#include "material.h"
#include "sphere.h"
#include "vec.h"
#include <time.h>
#define SAMPLES_PER_PIXEL 5
#define RAY_MAX_DEPTH 10

int main() {
  int IMAGE_WIDTH = 800;
  int IMAGE_HEIGHT = 800;
  Material sphere_m_test = new_metal_mat(vec3d_new(0.7, 0.57, 0.67), 0.01);
  Material sphere_m_test2 = new_lambert_mat(vec3d_new(0.5, 0.7, 0.9));
  Material sphere_m_fuzz = new_metal_mat(vec3d_new(0.65, 0.9, 0.9), 0.45);
  Material sphere_m_fuzz2 = new_metal_mat(vec3d_new(0.95, 0.95, 0.95), 0.0);
  Material sphere_m_glass = new_dialectric_mat(vec3d_new(1.0, 1.0, 1.0), 1.5);
  Material sphere_m_glass2 =
      new_dialectric_mat(vec3d_new(1.0, 1.0, 1.0), (1.0 / 1.45));
  Material sphere_m_glass4 =
      new_dialectric_mat(vec3d_new(1.0, 1.0, 1.0), (1.0 / 2.4));
  Material sphere_m_glass3 =
      new_dialectric_mat(vec3d_new(1.0, 1.0, 1.0), (1.45));

  HitableList *world = init_hit_record_list(1);
  Sphere sphere =
      new_sphere(vec3d_new(0.0, -100.5, -3.5), sphere_m_test, 100.0);
  Sphere sphere_big =
      new_sphere(vec3d_new(0.0, 0.0, -1.0), sphere_m_glass, 0.5);
  Sphere sphere_smol =
      new_sphere(vec3d_new(0.0, 0.0, -1.0), sphere_m_glass2, 0.45);
  Sphere sphere2 = new_sphere(vec3d_new(2.0, 0.5, -2.2), sphere_m_fuzz, 1.0);
  Sphere sphere3 =
      new_sphere(vec3d_new(-1.0, 0.5, -2.0), sphere_m_test2, 0.689);

  Sphere sphere_big2 =
      new_sphere(vec3d_new(1.0, 0.135, 0.0), sphere_m_fuzz2, 0.7);
  // Sphere sphere_smol2 = new_sphere(vec3d_new(1.0, 0.135, 0.0),
  // sphere_m_fuzz2, 0.4);

  add_sphere_to_hitablelist(world, &sphere);
  add_sphere_to_hitablelist(world, &sphere_big);
  add_sphere_to_hitablelist(world, &sphere_smol);
  add_sphere_to_hitablelist(world, &sphere2);
  add_sphere_to_hitablelist(world, &sphere3);
  add_sphere_to_hitablelist(world, &sphere_big2);
  // add_sphere_to_hitablelist(world, &sphere_smol2);
  Vec3_d look_from = vec3d_new(-2.0, 2.0, -1.0);
  Vec3_d look_at = vec3d_new(0.0, 0.0, -1.0);
  CameraSettings *cam = new_camera_settings(IMAGE_WIDTH, IMAGE_HEIGHT, 2.1, 2.0,
                                            50, look_from, look_at, 0.01);

#ifdef BENCHMARK_RENDER_TIMES
  clock_t start_render, end_render;
  start_render = clock();
#ifdef TORTEM_RENDER_ANIM
  Keyframe key = keyframe_new(vec3d_new(-2.0, 2.0, -1.0),
                              vec3d_new(-10.0, 6.0, -2.0), 200.0);
  char output_filename[1024];
  render_keyframes(cam, key, output_filename, world);
#else
  char output_filename[1024];
  sprintf(output_filename, "output_still%d.jpg", 1);
  render(cam, world, SAMPLES_PER_PIXEL, RAY_MAX_DEPTH, output_filename);
#endif
  end_render = clock();
  double render_times = ((double)(end_render - start_render)) / CLOCKS_PER_SEC;
  printf("render time: %f\n SAMPLES: %d RAY_DEPTH: %d", render_times,
         SAMPLES_PER_PIXEL, RAY_MAX_DEPTH);
#else
#ifdef TORTEM_RENDER_ANIM
  Keyframe key = keyframe_new(vec3d_new(-2.0, 2.0, -1.0),
                              vec3d_new(-10.0, 6.0, -2.0), 200.0);
  char output_filename[1024];
  render_keyframes(cam, key, output_filename, world);
#else
  char output_filename[1024];
  sprintf(output_filename, "output_still%d.jpg", 1);
  render(cam, world, SAMPLES_PER_PIXEL, RAY_MAX_DEPTH, output_filename);
#endif
#endif
}
