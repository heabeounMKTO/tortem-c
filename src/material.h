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
/// INITILAIZES A LAMBERT MF MAT, 
/// WITH A RGB TEXTURE AS DEFAULT
static inline Material new_lambert_mat(Vec3_d color) {
  Texture rgb_tex = (Texture) {.rgb= {.color = color, .texture_type=RGB_TEXTURE}};
  return (Material) {
    .lambert={ .albedo=color, 
      .mat_type=LAMBERTIAN,
      .tex= &rgb_tex} 
    };
}


static inline Material new_lambert_mat_from_texture(Texture* texture)
{
  return (Material) {
    .lambert={.tex=texture, .mat_type=LAMBERTIAN}
  };
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
                                Vec3_d* attenuation, Ray* scattered, Vec3_d* emission_value); 


/// adds  texture to materials
///
/// not sure if i  should add it to dialetrics, 
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

/// turns a object into a light , if enable
///
static inline void mat_enable_emit(Material* input_material) {
  if (input_material->lambert.emission.is_on == false) {
    input_material->lambert.emission.is_on = true; 
    input_material->lambert.emission.emission_color = vec3d_from_float(1.0);
  } 
}


#endif
