#ifndef HITABLE_LIST_H
#define HITABLE_LIST_H
#include "sphere.h"
#include "hitable.h"
#include "ray.h"
#include "interval.h"

// TODO: calcuate length of hit record list
// on start instead, cos ion like this 
// 🎀 𝒹𝓎𝓃𝒶𝓂𝒾𝒸 𝒶𝓇𝓇𝒶𝓎 🎀 nonsense
typedef struct {
  Sphere** spheres;
  size_t size;
  size_t capacity;
} HitableList;

HitRecord* check_world_hits(HitableList* world, Ray r, Interval ray_interval);
HitableList* init_hit_record_list(size_t initial_capacity);
bool add_sphere_to_hitablelist(HitableList* list, Sphere* sphere);
void free_hit_record_list(HitableList* list); 

#endif
