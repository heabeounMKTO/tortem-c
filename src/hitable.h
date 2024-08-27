#ifndef HITABLE_H
#define HITABLE_H
#include "vec.h"
#include <stdlib.h>
#include <stdbool.h>

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

// TODO: calcuate length of hit record list
// on start instead ion like this 
// 𝓭𝔂𝓷𝓪𝓶𝓲𝓬 𝓪𝓻𝓻𝓪𝔂 nonsense
typedef struct {
  HitRecord** records;
  size_t size;
  size_t capacity;
} HitableList;

HitableList* init_hit_record_list(size_t initial_capacity);
bool add_record_to_hitablelist(HitableList* list, HitRecord* record);
void free_hit_record_list(HitableList* list); 

#endif
