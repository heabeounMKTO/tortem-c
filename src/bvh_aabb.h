#ifndef BVH_AABB
#define BVH_AABB
#include "utils.h"
#include "ray.h"


typedef struct {
  Interval x,y,z;
} BvhAABB;


static inline BvhAABB bvh_new_aabb( Interval x, Interval y, Interval z ) {
  return (BvhAABB) { .x=x,.y=y,.z=z }; 
}

static inline BvhAABB bvh_aabb_from_two_points( const Vec3_d a,  const Vec3_d b) {
  double x1,x2,y1,y2,z1,z2;
  x1 = vec3d_x(a);
  x2 = vec3d_x(b);
  y1 = vec3d_y(a);
  y2 = vec3d_y(b);
  z1 = vec3d_z(a);
  z2 = vec3d_z(b);
  return (BvhAABB) {
    .x = (x1 <= x2) ? interval_new(x1, x2) : interval_new(x2, x1),
    .y = (y1 <= y2) ? interval_new(y1, y2) : interval_new(y2, y1),
    .z = (z1 <= z2) ? interval_new(z1, z2) : interval_new(z2, z1),
  };
}

static inline Interval bvh_aabb_axis_interval(BvhAABB _bvh, int n) {
  switch(n) {
    case 1: 
      return _bvh.y;
    case 2:
      return _bvh.z;
    default:
      return _bvh.x;
  }
}


bool bvh_aabb_hit(const Ray r, Interval ray_t);


#endif
