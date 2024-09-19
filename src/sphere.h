#ifndef SPHERE_H
#define SPHERE_H
#include "hitable.h"
#include "vec.h"
#include "ray.h"
#include <stdbool.h>
#include "utils.h"

typedef struct {
  Vec3_d center;
  double radius;
} Sphere;

bool sphere_hit(Sphere* sphere, Ray r, Interval interval, HitRecord* rec);


#endif
