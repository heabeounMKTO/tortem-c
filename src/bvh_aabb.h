#ifndef BVH_AABB
#define BVH_AABB
#include "utils.h"



typedef struct {
  Interval x,y,z;
} BvhAABB;


static inline BvhAABB new_bvh(Interval x, Interval y, Interval z) {
  return (BvhAABB) { .x=x, .y=y, .z=z };
}

// creates a bounding box from a pair of two vecs 
static inline BvhAABB new_bvh_from_vecpair(Vec3_d v1, Vec3_d v2) {
  return (BvhAABB) {
    .x = (v1.x <= v2.x) ? interval_new(v1.x, v2.x) : interval_new(v2.x, v1.x),
    .y = (v1.y <= v2.y) ? interval_new(v1.y, v2.y) : interval_new(v2.y, v1.y),
    .z = (v1.z <= v2.z) ? interval_new(v1.z, v2.z) : interval_new(v2.z, v1.z),
  };
}

static inline BvhAABB new_bvh_from_bbox(BvhAABB box0, BvhAABB box1) {
  return (BvhAABB) {
        .x = interval_enclose(box0.x, box1.x),
        .y = interval_enclose(box0.y, box1.y),
        .z = interval_enclose(box0.z, box1.z)
  };
}

static inline Interval axis_interval(BvhAABB bvh, int n) {
  if (n == 1) return bvh.x;
  if (n == 2) return bvh.z;
  return bvh.x;
}


#endif
