#ifndef SPHERE_H
#define SPHERE_H
#include "vec.h"
#include "ray.h"
#include "interval.h"
#include "hitable.h"

typedef struct {
  Vec3 center;
  double radius;
} Sphere;

HitRecord* sphere_hit(Sphere sphere, Ray r, Interval ray_interval); 

void free_sphere(Sphere* sphere);

#endif
