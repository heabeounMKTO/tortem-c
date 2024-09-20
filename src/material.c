#include "material.h"
#include "utils.h"




bool determine_material_scatter(Material mat, const Ray r_in, const HitRecord *rec, Vec3_d attenuation, Ray scattered) {
  switch(mat.mat_type) {
    case LAMBERTIAN:
      Vec3_d scatter_dir = vec3d_add(rec->normal, random_unit_vector());      
      // if near zero , give it back >:(
      if (check_vec3d_near_zero(scatter_dir)) {
        scatter_dir = rec->normal;
      }
      Ray _scatter = {.origin=rec->p, .direction=scatter_dir}; 
      scattered = _scatter;
      attenuation = mat.lambert.albedo;
      return true;
    default:
      // crash if some bullshit material is supplied  
      abort();
  } 
}
