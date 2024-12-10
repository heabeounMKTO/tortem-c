#ifndef SPHERE_H
#define SPHERE_H
#include "hitable.h"
#include <math.h>
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
   return (Sphere){.center = sphere_pos, .radius = sphere_radius, .sphere_mat=sphere_material};
}


// constant position for sphere UV's
static inline void sphere_get_uv_for_hit_rec(const Vec3_d point, HitRecord* input_record) {
  double theta = acos(-point.y); 
  double phi = atan2(-point.z, point.z) + 3.14; 
  input_record->u = phi / (6.28); // 2 pi, lazy mfs edition (it might not end well) 
  input_record->v = theta / 3.14;
}

#endif
