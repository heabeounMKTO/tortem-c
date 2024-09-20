#include "hitable.h"
#include <stdlib.h>

HitRecord *new_hit_record(Vec3_d point, Vec3_d normal, double t) {
  HitRecord *record = (HitRecord *)malloc(sizeof(HitRecord));
  record->p = point;
  record->normal = normal;
  record->t = t;
  return record;
}

void set_front_face(HitRecord *record, const Ray r,
                    const Vec3_d outward_normal) {
  if (vec3d_dot(r.direction, outward_normal) > 0.0) {
    record->normal = vec3d_negate(outward_normal);
    record->front_face = false;
  } else {
    record->normal = outward_normal;
    record->front_face = true;
  }
}
void free_hit_record(HitRecord *record) {
  // Avoid double free's lmao
  if (record != NULL) {
    free(record);
  }
}
