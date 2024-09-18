#include "vec.h"
#include <stdio.h>
#include "ray.h"

typedef struct {
  short int r,g,b;
} ScreenColor;

Vec3_d ray_color(Ray r);
Vec3_d apply_aces(Vec3_d col);
ScreenColor write_color(Vec3_d pixel_color, short int apply_curve);
