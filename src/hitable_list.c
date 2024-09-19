#include "hitable_list.h"
#include <stdlib.h>
#include "hitable.h"
#include "utils.h"


HitableList* init_hit_record_list(size_t initial_capacity) {
  HitableList* list = (HitableList*)malloc(sizeof(HitableList) * initial_capacity);
  // If malloc fail , we bail
  if (list == NULL) {
    return NULL;
  }
  return list; 
}

bool check_world_hits(HitableList* world, Ray r, Interval interval, HitRecord* hit_rec) {
  HitRecord* temp_rec = malloc(sizeof(HitRecord)); // Empty  
  bool hit_anything = false;
  double closest_so_far = interval.max;
  for (size_t i = 0; i < world->size; i++) {
    Sphere* _sph = world->spheres[i];
    if (sphere_hit(_sph, r, interval_new(interval.min, closest_so_far), temp_rec)) {
      hit_anything=true;
      closest_so_far=temp_rec->t;
      hit_rec->normal = temp_rec->normal;
      hit_rec->front_face = temp_rec->front_face;
      hit_rec->t = temp_rec->t;
      hit_rec->p = temp_rec->p;
    } 
  }
  free_hit_record(temp_rec);
  return hit_anything;
}
