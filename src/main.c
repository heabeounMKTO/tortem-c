#include "camera.h"
#include "hitable_list.h"
#include "utils.h"
#include "mt1997.h"

int main() {
  // initialize MT1997 state 
  initialize_state64(&GLOBAL_MT_STATE, 19650218UL);
  const int image_width = 512;
  const int image_height = 256;


  Camera* cam = new_cam(image_width, image_height);
  HitableList* world = init_hit_record_list(2); 
  Sphere sphere2 = {.center=new_vec(0.0,-80.0,-1.0), .radius=100.0}; 
  Sphere sphere1 = {.center=new_vec(0.0,0.0,-1.0), .radius=0.5}; 
  Sphere sphere3= {.center=new_vec(1.0,0.0,-1.0), .radius=0.5}; 
  add_sphere_to_hitablelist(world, &sphere2); 
  add_sphere_to_hitablelist(world, &sphere1); 
  add_sphere_to_hitablelist(world, &sphere3); 
  printf("P3\n%d %d\n255\n", cam->image_width, cam->image_height);
  render(cam, *world, 100);
  return 0;
}