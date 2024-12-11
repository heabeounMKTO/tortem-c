#ifndef TEXTURE_H
#define TEXTURE_H

#include "vec.h"
#include <math.h>


// image textures are for later
typedef enum {
  RGB_TEXTURE,
  CHECKER_TEXTURE,
  IMAGE_TEXTURE
} TextureType;

typedef struct {
  TextureType texture_type;  
  double inv_scale;
  Vec3_d odd, even; 
} CheckerTexture;

typedef struct {
  TextureType texture_type;  
  Vec3_d color;
} RgbTexture;

typedef union {
  CheckerTexture checker;
  RgbTexture rgb; 
} Texture;



static inline CheckerTexture checker_texture_new(const Vec3_d color1,
                                                 const Vec3_d color2 ,
                                                 const double scale) {
  return (CheckerTexture) {.inv_scale=scale,  .odd=color1 ,.even=color2, .texture_type=CHECKER_TEXTURE}; 
}



static inline Vec3_d checker_texture_determine_color(double u ,
                                                     double v, 
                                            const CheckerTexture checker_texture,
                                                     const Vec3_d input_point) {
  int x_int = (int) (floor(checker_texture.inv_scale * input_point.x)); 
  int y_int = (int) (floor(checker_texture.inv_scale * input_point.y)); 
  int z_int = (int) (floor(checker_texture.inv_scale * input_point.z)); 
  bool is_even = (x_int + y_int + z_int) % 2 == 0;
  return is_even ? checker_texture.even : checker_texture.odd; 
}




#endif
