#ifndef RAY_H
#define RAY_H
#include "vec.h"

typedef struct {
  Vec3_d origin;
  Vec3_d direction;
} Ray;

Vec3_d orig(Ray r);
Vec3_d dir(Ray r);
Vec3_d ray_at(Ray r, float t);

#endif
