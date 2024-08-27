#ifndef HITABLE_H
#define HITABLE_H
#include "vec.h"
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
  Vec3 point;
  Vec3 normal;
  double t;
  bool front_face;
  bool is_hit;
} HitRecord;

HitRecord* new_hit_record(Vec3 point, Vec3 normal, double t,bool front_face, bool is_hit); 
HitRecord* no_hits();
void free_hit_record(HitRecord* record);

typedef struct {
  HitRecord** records;
  size_t size;
  size_t capacity;
} HitableList;



#endif
