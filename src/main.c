#include "camera.h"
#include "hitable_list.h"
#include "utils.h"
#include "mt1997.h"

int main() {
  // init random seed
  seed_random();
  // Initialize MT1997 state 
  // initialize_state64(&GLOBAL_MT_STATE, 19650218UL);

  Camera* cam = new_cam(512, 256);
  HitableList* world = init_hit_record_list(2); 
  Sphere sphere1 = {.center=new_vec(0.0,0.0,-1.0), .radius=0.5}; 
  Sphere sphere2 = {.center=new_vec(0.0,-98.7,-1.0), .radius=100.0}; 
  add_sphere_to_hitablelist(world, &sphere2); 
  add_sphere_to_hitablelist(world, &sphere1); 
  printf("P3\n%d %d\n255\n", cam->image_width, cam->image_height);
  render(cam, *world, 100, 50);
  return 0;
}
