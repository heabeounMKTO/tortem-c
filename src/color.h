#include "vec.h"
#include <stdio.h>


typedef struct {
  int r,g,b;
} ScreenColor;


ScreenColor write_color(Vec3 pixel_color, short int apply_curve);
Vec3 apply_aces(Vec3 col);
