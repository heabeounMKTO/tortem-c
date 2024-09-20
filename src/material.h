#ifndef MATERIAL_H
#define MATERIAL_H

#include "vec.h"
#include "hitable.h"
#include "ray.h"

typedef enum {
  METAL,
  LAMBERTIAN
} MaterialType;

typedef struct {
  Vec3_d scatter_dir, albedo;
  double index_of_refraction;
} LambertianMaterial;

typedef struct {
  Vec3_d scatter_dir, albedo;
  double index_of_refraction;
} MetalMaterial;

typedef union {
  MetalMaterial metal;
  LambertianMaterial lambert;
  MaterialType mat_type;
} Material;


bool determine_material_scatter(Material mat,
                                const Ray r,
                                const HitRecord* rec, 
                                Vec3_d attenuation, Ray scattered);

static inline Material new_mat(MaterialType mat) {
  switch(mat) {
    case METAL:
      Material _mat_met;
      _mat_met.mat_type = METAL;
      return _mat_met;
    case LAMBERTIAN:
      Material _mat_lam;
      _mat_lam.mat_type = LAMBERTIAN;
      return _mat_lam;
    default:
      // if u supply some bullshit 
      // material that dont exist
      abort();
  }


}


#endif
