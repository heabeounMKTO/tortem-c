#ifndef SPHERE_H
#define SPHERE_H
#include "hitable.h"
#include "vec.h"
#include "ray.h"
#include <stdbool.h>
#include "utils.h"
#include "material.h"
#include "bvh_aabb.h"


typedef struct {
  Vec3_d center;
  double radius;
  Material sphere_mat;
  BvhAABB bounding_box;
} Sphere;

bool sphere_hit(Sphere* sphere, Ray r, Interval interval, HitRecord* rec);

// todo add bbox calculation
static inline Sphere new_sphere(Vec3_d sphere_pos, 
                                Material sphere_material, 
                                double sphere_radius) {
  Vec3_d r_vec = vec3d_from_float(sphere_radius);
  BvhAABB bounding_box = new_bvh_from_vecpair(vec3d_sub(sphere_pos, r_vec), vec3d_add(sphere_pos, r_vec)); 
  return (Sphere){
                   .center = sphere_pos, 
                   .radius = sphere_radius, 
                   .sphere_mat=sphere_material,
                   .bounding_box = bounding_box
                  };
}

#endif
