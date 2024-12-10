/// TODO: REFACTOR MATERIAL UNION 
/// TO A STRUCT WITH ENUM AND UNION STRUCT

#ifndef MATERIAL_H
#define MATERIAL_H

#include "vec.h"
#include "ray.h"
#include <stdbool.h>
#include "hitable.h"
#include "texture.h"
#include "lights.h"


typedef enum {
  METAL,
  LAMBERTIAN,
  DIELECTRIC, 
} MaterialType;




typedef struct {
  Texture* tex;
  Vec3_d scatter_dir, albedo;
  MaterialType mat_type;
  Emission emission;
} LambertianMaterial;

typedef struct {
  Texture* tex;
  Vec3_d scatter_dir, albedo;
  double fuzz;
  MaterialType mat_type;
  Emission emission;
} MetalMaterial;

typedef struct {
  Texture tex;
  Vec3_d scatter_dir, albedo;
  double index_of_refraction;
  MaterialType mat_type;
  Emission emission;
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


/// adds  texture to materials
/// not sure if i  should add it to dialetrics 
/// i should add checking whether or not there is already 
/// a material present but idk (foreshadowing perhaps)
static inline void mat_add_tex(Material* input_material, Texture* input_texture) {
  
  if (input_material->lambert.mat_type == LAMBERTIAN) {
    input_material->lambert.tex = input_texture;
  }
  if (input_material->metal.mat_type == METAL) {
    input_material->metal.tex = input_texture;
  }
}


static inline void mat_make_emissive() {

}


#endif
