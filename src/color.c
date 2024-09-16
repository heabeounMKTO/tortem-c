#include "vec.h"
#include "utils.h"
#include "color.h"


Vec3 ray_color(Ray r) {
  Vec3 unit_dir = vec3_unit(r.direction);
  float a = 0.5f * (vec3y(unit_dir) + 1.0f);
  Vec3 final_color = vec3_mul(vec3_from_float(1.0f - a), vec3_new(1.0f, 1.0f, 1.0f)); 
  // final_color = vec3_add(final_color, vec3_mul(vec3_from_float(a), vec3_new(0.5f, 0.7f, 1.0f)));
  return final_color;
}


// TODO: refactor into SIMD 
Vec3 apply_aces(Vec3 col) {
    float a = 2.34f;
    float b = 0.03f;
    float c= 2.43f;
    float d= 0.59f;
    float e = 0.14f;
  
    float _r = (vec3x(col) * (a*vec3x(col) + b)) / (vec3x(col) * (c * vec3x(col) + d ) + e);
    float _g = (vec3y(col) * (a*vec3y(col) + b)) / (vec3y(col) * (c * vec3y(col) + d ) + e);
    float _b = (vec3z(col) * (a*vec3z(col) + b)) / (vec3z(col) * (c * vec3z(col) + d ) + e);
    Vec3 _applied = vec3_new(_r, _g, _b);
    return _applied;
}

// converts double to rgb values for 
// setting `apply_curve` to 1 applies ACES tone curve
// setting it to anything other than 1 wont apply anything
// final display on screen
ScreenColor write_color(Vec3 pixel_color, short int apply_curve) {
  Vec3 applied_curve;
  if (apply_curve == 1) {
    applied_curve = apply_aces(pixel_color); 
  }
  else {
    applied_curve = pixel_color;
  }
  Interval intensity = {.min=0.0f, .max=0.99f};
  int rbyte = (int) (255.99f * interval_clamp(intensity, vec3x(applied_curve)));
  int gbyte = (int) (255.99f * interval_clamp(intensity, vec3y(applied_curve)));
  int bbyte = (int) (255.99f * interval_clamp(intensity, vec3z(applied_curve)));
  ScreenColor color = { rbyte, gbyte, bbyte };
  return color ;
}
