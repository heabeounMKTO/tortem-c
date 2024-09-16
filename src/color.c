#include "vec.h"
#include "utils.h"
#include "color.h"


// TODO: refactor into SIMD 
Vec3 apply_aces(Vec3 col) {
    float a = 2.34;
    float b = 0.03;
    float c= 2.43;
    float d= 0.59;
    float e = 0.14;
  
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
  int rbyte = (int) (255.999f * interval_clamp(intensity, vec3x(applied_curve)));
  int gbyte = (int) (255.999f * interval_clamp(intensity, vec3y(applied_curve)));
  int bbyte = (int) (255.999f * interval_clamp(intensity, vec3z(applied_curve)));
  ScreenColor color = { rbyte, gbyte, bbyte };
  return color ;
}
