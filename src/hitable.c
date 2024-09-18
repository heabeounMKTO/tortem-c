#include "hitable.h"
#include "vec.h"
#include <stdlib.h>


HitRecord* new_hit_record(Vec3_d point, Vec3_d normal, double t) {
  HitRecord* record = (HitRecord*)malloc(sizeof(HitRecord));
  record->p = point;
  record->normal = normal;
  record->t = t;
  return record;
}

void free_hit_record(HitRecord* record) {
  // avoid double free's lmao
  if (record != NULL) {
    free(record);
  }
}
