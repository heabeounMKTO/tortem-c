#ifndef MATERIAL_H
#define MATERIAL_H

#include "vec.h"
#include "ray.h"
#include <stdbool.h>
#include "hitable.h"

typedef enum {
  METAL,
  LAMBERTIAN,
  DIELECTRIC, // TODO: fix index of refraction bug, causes black
} MaterialType;

typedef struct {
  Vec3_d scatter_dir, albedo;
  double index_of_refraction;
} LambertianMaterial;

typedef struct {
  Vec3_d scatter_dir, albedo;
  double index_of_refraction, fuzz;
} MetalMaterial;

typedef struct {
  Vec3_d scatter_dir, albedo;
  double index_of_refraction;
} DielectricMaterial;

typedef union {
  MetalMaterial metal;
  LambertianMaterial lambert;
  DielectricMaterial dielectric;
  MaterialType mat_type;
} Material;



Material new_mat(MaterialType mat, Vec3_d color); 
void determine_material_scatter(Material mat, const Ray r_in,
                                const HitRecord *rec,
                                Vec3_d* attenuation, Ray* scattered); 


#endif
