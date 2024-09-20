#include "material.h"
#include "utils.h"


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

bool determine_material_scatter(Material mat, const Ray r_in,
                                const HitRecord *rec,
                                Vec3_d* attenuation, Ray* scattered) {
  switch(mat.mat_type) {
    case LAMBERTIAN:
      Vec3_d lambert_scatter_dir = vec3d_add(rec->normal, random_unit_vector());      
      // if near zero , give it back >:(
      if (check_vec3d_near_zero(lambert_scatter_dir)) {
        lambert_scatter_dir = rec->normal;
      }
      Ray _scatter_lambert = {.origin=rec->p, .direction=lambert_scatter_dir}; 
      scattered = &_scatter_lambert;
      attenuation = &mat.lambert.albedo;
      return true;
    case METAL:
      // metal is reflected therefore reflect func
      Vec3_d metal_scatter_dir = vec3d_reflect(r_in.direction, rec->normal);      
      Ray _scatter_metal = {.origin=rec->p, .direction=metal_scatter_dir}; 
      scattered = &_scatter_metal;
      attenuation = &mat.metal.albedo;
      return true;
    default:
      return false;
  } 
}
