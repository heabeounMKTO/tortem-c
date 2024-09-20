#ifndef SPHERE_H
#define SPHERE_H
#include "hitable.h"
#include "vec.h"
#include "ray.h"
#include <stdbool.h>
#include "utils.h"
#include "material.h"

typedef struct {
  Vec3_d center;
  double radius;
  Material sphere_mat;
} Sphere;

bool sphere_hit(Sphere* sphere, Ray r, Interval interval, HitRecord* rec);

static inline Sphere new_sphere(Vec3_d sphere_pos, Material sphere_material, double sphere_radius) {
  Sphere _sph = {.center = sphere_pos, .radius = sphere_radius, .sphere_mat=sphere_material};
  return _sph;
}

#endif
