#include "hitable_list.h"
#include "sphere.h"
#include "hitable.h"
#include "vec.h"
#include "interval.h"


HitableList* init_hit_record_list(size_t initial_capacity) {
  HitableList* list = (HitableList*)malloc(sizeof(HitableList));
  if (list == NULL) {
    return NULL;
  }
  list->spheres = (Sphere**)malloc(initial_capacity * sizeof(Sphere*));
  if (list->spheres==NULL) {
    free(list);
    return NULL;
  }
  list->size = 0;
  list->capacity = initial_capacity;
  return list;
}


bool add_sphere_to_hitablelist(HitableList *list, Sphere* sphere) {
  if (list->size == list->capacity) {
    size_t new_capacity = list->capacity * 2;

    // resize that bih
    Sphere** new_records = (Sphere**)realloc(list->spheres, new_capacity * sizeof(Sphere*));
    if(new_records==NULL) {
      return false;
    }
    list->spheres = new_records;
    list->capacity=new_capacity;
  }
  list->spheres[list->size++] = sphere;
  return true;
}

// free young thung :0
void free_hit_record_list(HitableList* list) {
    if (list == NULL) return;
    for (size_t i = 0; i < list->size; i++) {
        free_sphere(list->spheres[i]);  
  }
    free(list->spheres);  
    free(list);           
}

HitRecord* check_world_hits(HitableList* world, Ray r, Interval ray_interval) {
  // init a dummy record 
  HitRecord* hit_rec = new_hit_record(new_vec(0.0,0.0,0.0),
                                      new_vec(0.0,0.0,0.0), 
                                      0.0, 
                                      false, 
                                      false);
  double closest_so_far = ray_interval.max;

  // this is probably inefficient as fuck
  // but this is what i can come up with so 
  for (size_t i = 0; i < world->size; i++) {
    Sphere* sphere_ = world->spheres[i];
    HitRecord* hit = sphere_hit(*sphere_, r,interval_new(ray_interval.min, closest_so_far));
    if (hit->is_hit) {
      closest_so_far = hit->t;
      hit_rec = hit;
    }
    free_hit_record(hit);
  }
  return hit_rec;
}
