#ifndef MATERIAL_H
#define MATERIAL_H

#include "vec.h"
#include "ray.h"
#include <stdbool.h>
#include "hitable.h"

typedef enum {
  METAL,
  LAMBERTIAN,
  DIELECTRIC, 
} MaterialType;

typedef struct {
  Vec3_d scatter_dir, albedo;
  MaterialType mat_type;
} LambertianMaterial;

typedef struct {
  Vec3_d scatter_dir, albedo;
  double fuzz;
  MaterialType mat_type;
} MetalMaterial;

typedef struct {
  Vec3_d scatter_dir, albedo;
  double index_of_refraction;
  MaterialType mat_type;
} DielectricMaterial;

typedef union {
  MetalMaterial metal;
  LambertianMaterial lambert;
  DielectricMaterial dielectric;
} Material;



static inline Material new_metal_mat(Vec3_d color, double fuzz) {
  Material _matmetal ={ .metal= { .albedo=color, 
                                                 .scatter_dir=vec3d_from_float(0.0),
                                                 .fuzz=fuzz ,.mat_type=METAL }};


  return _matmetal; 
}

static inline Material new_lambert_mat(Vec3_d color) {
  return (Material) {
    .lambert={ .albedo=color, .mat_type=LAMBERTIAN
  }};
}
/// ior = index of refraction
///
/// Read more `https://en.wikipedia.org/wiki/List_of_refractive_indices`
static inline Material new_dialectric_mat(Vec3_d color, double ior) {
  return (Material) {
    .dielectric={
      .albedo=color,
      .index_of_refraction=ior,
      .mat_type=DIELECTRIC
    }
  };
}

void determine_material_scatter(Material mat, const Ray r_in,
                                const HitRecord *rec,
                                Vec3_d* attenuation, Ray* scattered); 


#endif
