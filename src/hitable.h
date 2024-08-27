#ifndef HITABLE_H
#define HITABLE_H
#include "vec.h"
#include <stdlib.h>
#include <stdbool.h>
#include "ray.h"
#include "interval.h"

typedef struct {
  Vec3 point;
  Vec3 normal;
  double t;
  bool front_face;
  bool is_hit;
} HitRecord;

HitRecord* new_hit_record(Vec3 point, Vec3 normal, double t,bool front_face, bool is_hit); 
HitRecord* no_hits();
void free_hit_record(HitRecord* record);

// // TODO: calcuate length of hit record list
// // on start instead, cos ion like this 
// // 🎀 𝒹𝓎𝓃𝒶𝓂𝒾𝒸 𝒶𝓇𝓇𝒶𝓎 🎀 nonsense
// typedef struct {
//   Sphere** spheres;
//   size_t size;
//   size_t capacity;
// } HitableList;

// HitRecord* check_world_hits(HitableList* world, Ray r, Interval ray_interval);
// HitableList* init_hit_record_list(size_t initial_capacity);
// bool add_record_to_hitablelist(HitableList* list, Sphere* sphere);
// void free_hit_record_list(HitableList* list); 

#endif
