#ifndef SPHERE_H
#define SPHERE_H
#include "hitable.h"
#include "vec.h"
#include "ray.h"
#include <stdbool.h>

typedef struct {
  Vec3_d center;
  double radius;
} Sphere;


bool hit(Sphere sphere, Ray r, double t_min, double t_max, HitRecord* rec);


#endif
