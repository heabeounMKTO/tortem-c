#ifndef HITABLE_LIST_H
#define HITABLE_LIST_H
#include "hitable.h"
#include "sphere.h"
#include <stdlib.h>
#include "utils.h"

// 🎀 𝒹𝓎𝓃𝒶𝓂𝒾𝒸 𝒶𝓇𝓇𝒶𝓎 🎀
typedef struct {
  Sphere** spheres;
  size_t size;
  size_t capacity;
} HitableList;

HitableList* init_hit_record_list(size_t initial_capacity);
bool add_record_to_hitablelist(HitableList* list, HitRecord* record);
// will change to object later idk
bool check_world_hits(HitableList* world, 
                      Ray r,Interval interval, 
                      HitRecord* hit_rec, 
                      Vec3_d* attenuation, Ray* scattered);
void free_hit_record_list(HitableList* list); 


// fuck it
static inline bool add_sphere_to_hitablelist(HitableList *list, Sphere* sphere) {
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

#endif
