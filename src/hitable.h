#ifndef HITABLE_H
#define HITABLE_H
#include "ray.h"
#include "vec.h"

typedef struct {
 Vec3_d p;
 Vec3_d normal;
 double t;
} HitRecord;

HitRecord* new_hit_record(Vec3_d point, Vec3_d normal, double t);
void free_hit_record(HitRecord* record);



#endif
