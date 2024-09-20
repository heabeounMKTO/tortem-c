#ifndef HITABLE_H
#define HITABLE_H
#include <stdlib.h>
#include "ray.h"
#include "vec.h"
#include <stdbool.h>


typedef struct {
  Vec3_d p;
  Vec3_d normal;
  double t;
  bool front_face;
} HitRecord;

HitRecord* new_hit_record(Vec3_d point, Vec3_d normal, double t);
void set_front_face(HitRecord* record, const Ray r, const Vec3_d outward_normal);
void free_hit_record(HitRecord* record);



#endif
