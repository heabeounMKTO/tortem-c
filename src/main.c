#include <stdio.h>
#include "vec.h"
#include "color.h"


int main() {
  int image_width = 256;
  int image_height = 256;

  printf("P3\n %i %i\n255\n", image_width, image_height); 
  for (int j = 0; j < image_height; j++) {
    for (int i =0; i < image_width; i++) {
      float r = (float) i / (float) (image_width-1); 
      float g = (float) j / (float) (image_height-1);
      float b = 0.0f;
      Vec3 final_color = vec3_new(r, g,b); 
      ScreenColor _sc = write_color(final_color, 1);
      printf("%i %i %i\n", _sc.r , _sc.g , _sc.b);
    }
  }
}
