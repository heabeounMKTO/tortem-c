#ifndef RAY_H
#define RAY_H
#include "vec.h"

typedef struct {
  Vec3 origin;
  Vec3 direction;
} Ray;



Vec3 orig(Ray r);
Vec3 dir(Ray r);
Vec3 ray_at(Ray r, double t);
#endif
