#include "hitable.h"
#include "vec.h"
#include <stdlib.h>
#include <stdbool.h>

 
HitRecord* new_hit_record(Vec3 point, Vec3 normal, double t, bool front_face, bool is_hit) {
  HitRecord* record = (HitRecord*)malloc(sizeof(HitRecord));
  record->point = point;
  record->normal = normal;
  record->t = t;
  record->front_face = front_face;
  record->is_hit = is_hit;
  return record;
}

HitRecord* no_hits() {
  HitRecord* record = new_hit_record(new_vec(0.0,0.0,0.0), new_vec(0.0,0.0,0.0), -1.0, false, false); 
  return record;
}

void free_hit_record(HitRecord* record) {
  // avoid double free's lmao
  if (record != NULL) {
    free(record);
  }
}

