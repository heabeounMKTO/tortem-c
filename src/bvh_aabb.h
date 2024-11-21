#ifndef BVH_AABB
#define BVH_AABB
#include "utils.h"



typedef struct {
  Interval x,y,z;
} BvhAABB;

static inline BvhAABB new_bvh(Interval x, Interval y, Interval z) {
  return (BvhAABB) { .x=x, .y=y, .z=z };
}

static inline Interval axis_interval(BvhAABB bvh, int n) {
  if (n == 1) return bvh.x;
  if (n == 2) return bvh.z;
  return bvh.x;
}

#endif
