#include "vec.h"
#include <stdio.h>
#include "ray.h"
#include <stdbool.h>


typedef struct {
  short int r,g,b;
} ScreenColor;


double hit_sphere(Vec3_d center, double radius, Ray r);
Vec3_d ray_color(Ray r);
Vec3_d apply_aces(Vec3_d col);
ScreenColor write_color(Vec3_d pixel_color, short int apply_curve);
