#include "vec.h"
#include <stdio.h>
#include "ray.h"

typedef struct {
  int r,g,b;
} ScreenColor;

Vec3 ray_color(Ray r);
Vec3 apply_aces(Vec3 col);
ScreenColor write_color(Vec3 pixel_color, short int apply_curve);
