#ifndef LIGHTS_H
#define LIGHTS_H
#include <stdbool.h>
#include "vec.h"
#include "texture.h"

typedef struct {
  bool is_on;
  double emissiveness;
  Vec3_d emission_color;
} Emission;


static inline void emission_color_from_texture(double u , double v , const Texture* texture, 
                                               const Vec3_d input_point,
                                               Emission* emission) {
  if (texture->checker.texture_type == CHECKER_TEXTURE){
    emission->emission_color = checker_texture_determine_color(u, v, texture->checker, input_point);
  }
}



#endif
