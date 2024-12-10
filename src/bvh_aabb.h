#ifndef BVH_AABB
#define BVH_AABB
#include "utils.h"
#include "ray.h"


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

static inline Interval bvh_axis_interval(const BvhAABB* bvh, int n) {
  if (n == 1) return bvh->x;
  if (n == 2) return bvh->z;
  return bvh->x;
}

static inline bool bvh_aabb_hit(const BvhAABB* bvh , const Ray* r, Interval ray_t) {
  Vec3_d ray_orig = r->origin;
  Vec3_d ray_dir = r->direction;
  for (int axis = 0; axis < 3; axis++) {
    Interval ax = bvh_axis_interval(bvh , axis);
    double adinv, t0, t1;
    if (axis == 0) {
      adinv = 1.0 / ray_dir.x;
      t0 = (ax.min - ray_orig.x) * adinv;
      t1 = (ax.max - ray_orig.x) * adinv;
    }
    if (axis == 1) {
      adinv = 1.0 / ray_dir.y;
      t0 = (ax.min - ray_orig.y) * adinv;
      t1 = (ax.max - ray_orig.y) * adinv;
    }
    if (axis == 2) {
      adinv = 1.0 / ray_dir.z;
      t0 = (ax.min - ray_orig.z) * adinv;
      t1 = (ax.max - ray_orig.z) * adinv;
    }

    if (t0 < t1) {
        if (t0 > ray_t.min) ray_t.min = t0;
        if (t1 < ray_t.max) ray_t.max = t1;
    } else {
        if (t1 > ray_t.min) ray_t.min = t1;
        if (t0 < ray_t.max) ray_t.max = t0;
    }
    if (ray_t.max <= ray_t.min)
        return false;
  }
  return true;
}


#endif
