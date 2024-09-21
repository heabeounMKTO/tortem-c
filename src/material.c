#include "material.h"
#include "ray.h"
#include "utils.h"
#include "vec.h"



void determine_material_scatter(Material mat, const Ray r_in,
                                const HitRecord *rec, Vec3_d *attenuation,
                                Ray *scattered) {
  if (mat.metal.mat_type == METAL) {

    Vec3_d metal_scatter_dir = vec3d_reflect(r_in.direction, rec->normal);
    metal_scatter_dir = vec3d_add(
        vec3d_unit(metal_scatter_dir),
        vec3d_mul(vec3d_from_float(mat.metal.fuzz), random_unit_vector()));
    scattered->origin = rec->p;
    scattered->direction = metal_scatter_dir;
    *attenuation = mat.metal.albedo;
  }

  if (mat.lambert.mat_type == LAMBERTIAN) {
    Vec3_d lambert_scatter_dir = vec3d_add(rec->normal, random_unit_vector());
    // if near zero , give it back >:(
    if (check_vec3d_near_zero(lambert_scatter_dir)) {
      lambert_scatter_dir = rec->normal;
    }
    scattered->origin = rec->p;
    scattered->direction = lambert_scatter_dir;
    *attenuation = mat.lambert.albedo;
  }

  if (mat.dielectric.mat_type == DIELECTRIC) {
    double ri = rec->front_face ? (1.0 / mat.dielectric.index_of_refraction)
                                : mat.dielectric.index_of_refraction;
    Vec3_d unit_direction = vec3d_unit(r_in.direction);

    double cos_theta =
        fmin(vec3d_dot(vec3d_negate(unit_direction), rec->normal), 1.0);
    double sin_theta = sqrt(1.0 - cos_theta * cos_theta);

    bool cannot_refract = ri * sin_theta > 1.0;

    Vec3_d direction;
    if (cannot_refract || schlicks_approx(cos_theta,ri) > random_double()) {
      direction = vec3d_reflect(unit_direction, rec->normal);
      // printf("Reflecting\n");
    } else {
      direction = vec3d_refract(unit_direction, rec->normal, ri);
      // printf("Refracting\n");
    }
    scattered->origin = rec->p;
    scattered->direction = direction;
    *attenuation = mat.dielectric.albedo;
  }
}
