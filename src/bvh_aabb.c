#include "bvh_aabb.h"
#include "ray.h"

bool bvh_aabb_hit(const Ray r, Interval ray_t) {
  Vec3_d ray_origin = r.origin;
  Vec3_d ray_dir = r.direction;
  BvhAABB _aabb;
  for (int axis = 0; axis < 3; axis++) {
    Interval ax = bvh_aabb_axis_interval(_aabb, axis);
    double raydir_idx, rayorg_idx;
    switch (axis) {
    case 0:
      raydir_idx = vec3d_x(ray_dir);
      rayorg_idx = vec3d_x(ray_origin);
      break;
    case 1:
      raydir_idx = vec3d_y(ray_dir);
      rayorg_idx = vec3d_y(ray_origin);
      break;
    case 2:
      raydir_idx = vec3d_z(ray_dir);
      rayorg_idx = vec3d_z(ray_origin);
      break;
    };
    double adinv = 1.0 / raydir_idx;

    double t0 = (ax.min - rayorg_idx) * adinv;
    double t1 = (ax.max - rayorg_idx) * adinv;

    if (t0 < t1) {
      if (t0 > ray_t.min)
        ray_t.min = t0;
      if (t1 < ray_t.min)
        ray_t.max = t1;
    } else {
      if (t0 > ray_t.min)
        ray_t.min = t1;
      if (t1 < ray_t.min)
        ray_t.max = t0;
    }
    if (ray_t.max <= ray_t.min)
      return false;
  }
  return true;
}
