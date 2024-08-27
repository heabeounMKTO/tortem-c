#ifndef COLOR_H
#define COLOR_H
#include "vec.h"
#include "ray.h"

typedef struct {
  int r;
  int g; 
  int b;
} ScreenColor;

ScreenColor write_color(Vec3 pixel_color);
Vec3 ray_color(Ray r);

#endif
