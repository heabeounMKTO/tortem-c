#include "hitable.h"
#include "vec.h"
#include <stdlib.h>
#include <stdbool.h>

inline HitRecord* new_hit_record(Vec3_d point, Vec3_d normal, double t) {
  HitRecord* record = (HitRecord*)malloc(sizeof(HitRecord));
  record->p = point;
  record->normal = normal;
  record->t = t;
  return record;
}

inline void set_front_face(HitRecord* record, const Ray r, const Vec3_d outward_normal){
  bool front_face = vec3d_dot(r.direction, outward_normal) < 0.0;
  if (front_face) {
    record->normal = outward_normal;
  } else {
    record->normal = vec3d_negate(outward_normal);
  }
}
inline void free_hit_record(HitRecord* record) {
  // avoid double free's lmao
  if (record != NULL) {
    free(record);
  }
}
