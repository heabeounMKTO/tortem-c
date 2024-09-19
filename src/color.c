#include "color.h"
#include "hitable.h"
#include "hitable_list.h"
#include "ray.h"
#include "utils.h"
#include "vec.h"
#include <stdbool.h>




// converts double to rgb values for
// setting `apply_curve` to 1 applies ACES tone curve
// setting it to anything other than 1 wont apply anything
// final display on screen
ScreenColor write_color(Vec3_d pixel_color, short int apply_curve) {
  Vec3_d applied_curve;
  if (apply_curve == 1) {
    applied_curve = apply_aces(pixel_color);
  } else {
    applied_curve = pixel_color;
  }
  Interval intensity = {.min = 0.0f, .max = 0.99f};
  int rbyte =
      (int)(255.99f * interval_clamp(intensity, vec3d_x(applied_curve)));
  int gbyte =
      (int)(255.99f * interval_clamp(intensity, vec3d_y(applied_curve)));
  int bbyte =
      (int)(255.99f * interval_clamp(intensity, vec3d_z(applied_curve)));
  ScreenColor color = {rbyte, gbyte, bbyte};
  return color;
}
