#include "hitable_list.h"
#include "hitable.h"
#include "material.h"
#include "utils.h"
#include <stdlib.h>

HitableList *init_hit_record_list(size_t initial_capacity) {
  HitableList *list =
      (HitableList *)malloc(sizeof(HitableList) * initial_capacity);
  // If malloc fail , we bail
  if (list == NULL) {
    return NULL;
  }
  return list;
}

bool check_world_hits(HitableList* world, 
                      Ray r,Interval interval, 
                      HitRecord* hit_rec, 
                      Vec3_d* attenuation, Ray* scattered) 
{
  bool hit_anything = false;
  double closest_so_far = interval.max;
  for (size_t i = 0; i < world->size; i++) {
    Sphere *_sph = world->spheres[i];
    if (sphere_hit(_sph, r, interval_new(interval.min, closest_so_far),
                   hit_rec)) {
      hit_anything = true;
      closest_so_far = hit_rec->t;
      determine_material_scatter(_sph->sphere_mat, r,hit_rec, attenuation, scattered);
    }
  }
  return hit_anything;
}
