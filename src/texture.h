#ifndef TEXTURE_H
#define TEXTURE_H


#include "vec.h"
typedef struct {
  Vec3_d color;
} Texture;

typedef struct {
  double inv_scale;
  Texture odd, even; 
} CheckerTexture;

static inline CheckerTexture checker_texture_new( Vec3_d color1, Vec3_d color2 , double scale) {
  CheckerTexture _ct = {.inv_scale=scale,  .odd.color=color1 ,.even.color=color2}; 
  return _ct;
}

#endif
