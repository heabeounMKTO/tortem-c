/* probably need a `emission_set_intensity` idk */
#ifndef LIGHTS_H
#define LIGHTS_H
#include <stdbool.h>
#include "vec.h"
#include "texture.h"


/// i maybe should add this to `material` or something idk
typedef struct {
  bool is_on;
  double intensity;
  Vec3_d emission_color;
} Emission;

static inline void emission_color_from_texture(double u , double v , 
                                               const Texture* texture, 
                                               const Vec3_d input_point, 
                                               Vec3_d* col) {
  if (texture->checker.texture_type == CHECKER_TEXTURE){
    *col = checker_texture_determine_color(u, v, texture->checker, input_point);
  }
}


#endif
