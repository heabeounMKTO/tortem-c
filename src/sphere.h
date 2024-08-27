#ifndef SPHERE_H
#define SPHERE_H
#include "hitable.h"
#include "vec.h"
#include "ray.h"
#include "interval.h"

typedef struct {
  Vec3 center;
  double radius;
} Sphere;

HitRecord* hit(Sphere sphere, Ray r, Interval ray_interval, HitRecord record); 


#endif
