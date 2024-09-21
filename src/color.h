#include "material.h"
#include "utils.h"
#include "vec.h"
#include <stdlib.h>
#include "ray.h"
#include <stdbool.h>
#include "hitable_list.h"
#include "hitable.h"
#define PRIMARIES 6.8e-7f
#define SCATTER_STRENGTH 0.25
#define PI 3.14159265358979323846
#define SCATTER_STRENGTH 0.25
#define MIE_COEFFICIENT 0.005
#define MIE_DIRECTIONAL_G 0.8
#define RAYLEIGH_COEFFICIENT 0.0000075
#define PRIMARIES 6.8e-7f
#define SUN_INTENSITY 20.0
#define TURBIDITY 1.0


typedef struct {
  short int r,g,b;
} ScreenColor;

static inline Vec3_d calculate_nishita(Vec3_d ray_dir, Vec3_d sun_dir) {
  double cos_theta = vec3d_dot(ray_dir, sun_dir);
  double ray_length = 1.0 / (vec3d_y(ray_dir) + 0.1);
  
  Vec3_d rayleigh_sum, mie_sum;
  double sample_step = ray_length / SAMPLES_PER_PIXEL;
  double current_sample_pos = 0.0;

  for (int i = 0; i < SAMPLES_PER_PIXEL; i++) {
        double height = ray_dir.y * current_sample_pos;
        double density = exp(-height * SCATTER_STRENGTH) * sample_step;
        
        rayleigh_sum = vec3d_add(rayleigh_sum, vec3d_new(density / PRIMARIES, density / (PRIMARIES * PRIMARIES), density / (PRIMARIES * PRIMARIES * PRIMARIES)));
        mie_sum = vec3d_add(mie_sum, vec3d_new(density, density, density));
        
        current_sample_pos += sample_step;
    }
      Vec3_d rayleigh = vec3d_scale(rayleigh_sum, RAYLEIGH_COEFFICIENT * TURBIDITY);
    Vec3_d mie = vec3d_scale(mie_sum, MIE_COEFFICIENT * TURBIDITY);
    
    double rayleigh_phase = 3.0 / (16.0 * PI) * (1.0 + cos_theta * cos_theta);
    double mie_phase = 3.0 / (8.0 * PI) * ((1.0 - MIE_DIRECTIONAL_G * MIE_DIRECTIONAL_G) * (1.0 + cos_theta * cos_theta)) / 
                       ((2.0 + MIE_DIRECTIONAL_G * MIE_DIRECTIONAL_G) * pow(1.0 + MIE_DIRECTIONAL_G * MIE_DIRECTIONAL_G - 2.0 * MIE_DIRECTIONAL_G * cos_theta, 1.5));
    
    Vec3_d total_scatter = vec3d_add(
        vec3d_scale(rayleigh, rayleigh_phase),
        vec3d_scale(mie, mie_phase)
    );
    
    return vec3d_scale(total_scatter, SUN_INTENSITY);

}



static inline Vec3_d calculate_sky_color(Vec3_d ray_dir, Vec3_d sun_dir) {
  Vec3_d nishita_color = calculate_nishita(ray_dir, sun_dir);

  double a = 0.5 * (vec3d_y(ray_dir), 1.0);
  Vec3_d gradient_color = vec3d_add(
    vec3d_scale(vec3d_from_float(1.0), (1.0 - a)),
    vec3d_scale(vec3d_new(0.5, 0.7, 1.0), a)
  );

  double blend = vec3d_y(ray_dir) * 0.000001 + 0.000001;
  return vec3d_add(
    vec3d_scale(nishita_color, blend),
    vec3d_scale(gradient_color, 1.0-blend)
  );
}

static inline Vec3_d ray_color(const Ray r, HitableList* world, int depth) {
  if (depth <= 0) {
    return vec3d_from_float(0.0);
  }
  HitRecord* rec = (HitRecord*)malloc(sizeof(HitRecord));
  Interval _inv = interval_new(0.001, INFINITY);
  Ray scattered;
  Vec3_d attenuation;
  bool check_w = check_world_hits(world, r, _inv, rec, &attenuation, &scattered); 

  if (check_w) {
    Vec3_d temp_raycol = ray_color(scattered, world, depth-1);
    Vec3_d final =vec3d_mul(temp_raycol, attenuation);
    // printf("FINAL COLOR HIT:");
    // vec3d_print(final);
    free_hit_record(rec);
    return final;
  }
  else {
    free_hit_record(rec);
    Vec3_d unit_dir = vec3d_unit(r.direction);
    double a = 0.5 * (vec3d_y(unit_dir) + 1.0);
    Vec3_d final_color = vec3d_mul(vec3d_from_float(1.0 - a), vec3d_new(1.0, 1.0, 1.0)); 
    final_color = vec3d_add(final_color, vec3d_mul(vec3d_from_float(a), vec3d_new(0.5, 0.7, 1.0)));
   // Vec3_d sun_dir = vec3d_unit(vec3d_new(0.0, 1.0, 1.0));
   //  Vec3_d final_color = calculate_sky_color(unit_dir, sun_dir);
    return final_color;
  }
}



static inline Vec3_d apply_aces(Vec3_d col) {
  double a = 2.34;
  double b = 0.03;
  double c = 2.43;
  double d = 0.59;
  double e = 0.14;

  double _r = (vec3d_x(col) * (a * vec3d_x(col) + b)) /
              (vec3d_x(col) * (c * vec3d_x(col) + d) + e);
  double _g = (vec3d_y(col) * (a * vec3d_y(col) + b)) /
              (vec3d_y(col) * (c * vec3d_y(col) + d) + e);
  double _b = (vec3d_z(col) * (a * vec3d_z(col) + b)) /
              (vec3d_z(col) * (c * vec3d_z(col) + d) + e);
  Vec3_d _applied = vec3d_new(_r, _g, _b);
  return _applied;
}

static inline ScreenColor write_color(Vec3_d pixel_color, short int apply_curve) {
  Vec3_d applied_curve;
  if (apply_curve == 1) {
    applied_curve = apply_aces(pixel_color);
  } else {
    applied_curve = pixel_color;
  }
  const Interval intensity = {.min = 0.0f, .max = 0.99f};
  const int rbyte =
      (short int)(255.99f * interval_clamp(intensity, vec3d_x(applied_curve)));
  const int gbyte =
      (short int)(255.99f * interval_clamp(intensity, vec3d_y(applied_curve)));
  const int bbyte =
      (short int)(255.99f * interval_clamp(intensity, vec3d_z(applied_curve)));
  ScreenColor color = {rbyte, gbyte, bbyte};
  return color;
}

