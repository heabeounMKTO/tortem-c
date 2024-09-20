#include "material.h"
#include "utils.h"
#include "vec.h"


Material new_mat(MaterialType mat, Vec3_d color) {
  switch(mat) {
    case METAL:
      Material _mat_met;
      _mat_met.mat_type = METAL;
      _mat_met.metal.albedo = color;
      return _mat_met;
    case LAMBERTIAN:
      Material _mat_lam;
      _mat_lam.mat_type = LAMBERTIAN;
      _mat_lam.lambert.albedo = color;
      return _mat_lam;
    default:
      // crash if u supply some bullshit 
      // material that dont exist
      abort();
  }
}

void determine_material_scatter(Material mat, const Ray r_in,
                                const HitRecord *rec,
                                Vec3_d* attenuation, Ray* scattered) {
  switch(mat.mat_type) {
    case LAMBERTIAN:
      Vec3_d lambert_scatter_dir = vec3d_add(rec->normal, random_unit_vector());      
      // if near zero , give it back >:(
      if (check_vec3d_near_zero(lambert_scatter_dir)) {
        lambert_scatter_dir = rec->normal;
      }
      scattered->origin = rec->p;
      scattered->direction = lambert_scatter_dir;
      *attenuation = mat.lambert.albedo;
      break;
    case METAL:
      Vec3_d metal_scatter_dir = vec3d_reflect(r_in.direction, rec->normal);      
      metal_scatter_dir = vec3d_add(vec3d_unit(metal_scatter_dir), vec3d_mul(vec3d_from_float(mat.metal.fuzz), random_unit_vector()));
      scattered->origin = rec->p;
      scattered->direction = metal_scatter_dir;
      *attenuation = mat.metal.albedo;
      break;
    case DIELECTRIC:
      double ri;
      if (rec->front_face) {
        ri = 1.0/mat.dielectric.index_of_refraction;
      }
      else {
        ri = mat.dielectric.index_of_refraction;
      }
      Vec3_d unit_direction = vec3d_unit(r_in.direction);
      Vec3_d refracted = vec3d_refract(unit_direction, rec->normal, ri);
      scattered->origin = rec->p;
      scattered->direction = refracted;
      *attenuation = vec3d_from_float(1.0);
      break;
    default: 
      abort();
  } 
}
