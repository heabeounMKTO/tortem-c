#include "material.h"
#include "lights.h"
#include "ray.h"
#include "texture.h"
#include "utils.h"
#include "vec.h"

void determine_material_scatter(Material mat, const Ray r_in,
                                const HitRecord *rec, Vec3_d *attenuation,
                                Ray *scattered, Vec3_d *emission_value) {
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

    /* if near zero , give it back >:( */
    if (check_vec3d_near_zero(lambert_scatter_dir)) {
      lambert_scatter_dir = rec->normal;
    }
    scattered->origin = rec->p;
    scattered->direction = lambert_scatter_dir;

    /*if no have texture , we fallback*/

    if (mat.lambert.tex->rgb.texture_type == RGB_TEXTURE) {
      *attenuation = mat.lambert.albedo;
    } else {
      if (mat.lambert.tex->checker.texture_type == CHECKER_TEXTURE) {
        *attenuation = checker_texture_determine_color(
            rec->u, rec->v, mat.lambert.tex->checker, rec->p);
      }
    }

    Vec3_d col_a = vec3d_from_float(0.0);
    double intensity_ = 10.0;
    if (mat.lambert.emission.is_on == true) {
      if (mat.lambert.tex->checker.texture_type == CHECKER_TEXTURE) {
        emission_color_from_texture(rec->u,rec->v,  mat.lambert.tex , rec->p,
        &col_a); *emission_value = vec3d_scale(col_a, intensity_);
      } else {
      col_a = vec3d_from_float(1.0);
      *emission_value = vec3d_scale(col_a,intensity_);
      }
    }
  }

  if (mat.dielectric.mat_type == DIELECTRIC) {
    double ri = rec->front_face ? (1.0 / mat.dielectric.index_of_refraction)
                                : mat.dielectric.index_of_refraction;
    Vec3_d unit_direction = vec3d_unit(r_in.direction);

    Vec3_d caustic_offset = vec3d_from_float(0.0);

    double cos_theta =
        fmin(vec3d_dot(vec3d_negate(unit_direction), rec->normal), 1.0);
    double sin_theta = sqrt(1.0 - cos_theta * cos_theta);

    bool cannot_refract = ri * sin_theta > 1.0;

    Vec3_d direction, caustic_attenuation;

    if (cannot_refract || schlicks_approx(cos_theta, ri) > random_double()) {
      direction = vec3d_reflect(unit_direction, rec->normal);
      /* // Reflecting
      double caustic_intensity = fabs(vec3d_dot(unit_direction, rec->normal));
      caustic_offset = vec3d_scale(rec->normal, caustic_intensity * 0.001);
      caustic_attenuation = mat.dielectric.albedo;
      caustic_attenuation.x *= (1.0 + caustic_intensity * 0.1);
      caustic_attenuation.y *= (1.0 + caustic_intensity * 0.1);
      caustic_attenuation.z *= (1.0 + caustic_intensity * 0.1); */
    } else {
      direction = vec3d_refract(unit_direction, rec->normal, ri);

      /* // Refracting
      double caustic_intensity = 1.0 - fabs(vec3d_dot(direction, rec->normal));
      caustic_offset = vec3d_scale(direction, caustic_intensity * 0.02);
      caustic_attenuation = mat.dielectric.albedo;
      caustic_attenuation.x *= (1.0 + caustic_intensity * 0.2);
      caustic_attenuation.y *= (1.0 + caustic_intensity * 0.2);
      caustic_attenuation.z *= (1.0 + caustic_intensity * 0.2); */
    }
    scattered->origin = rec->p;
    // scattered->origin = vec3d_add(rec->p, caustic_offset);
    scattered->direction = direction;

    *attenuation = mat.dielectric.albedo;
    //
    // *attenuation = caustic_attenuation;
  }
}
