#include "hitable.h"
#include "vec.h"
#include <stdlib.h>
#include <stdbool.h>

HitRecord* new_hit_record(Vec3 point, Vec3 normal, double t, bool front_face, bool is_hit) {
  HitRecord* record = (HitRecord*)malloc(sizeof(HitRecord));
  record->point = point;
  record->normal = normal;
  record->t = t;
  record->front_face = front_face;
  record->is_hit = is_hit;
  return record;
}

HitRecord* no_hits() {
  HitRecord* record = new_hit_record(new_vec(0.0,0.0,0.0), new_vec(0.0,0.0,0.0), -1.0, false, false); 
  return record;
}

void free_hit_record(HitRecord* record) {
  // avoid double free's lmao
  if (record != NULL) {
    free(record);
  }
}

HitableList* init_hit_record_list(size_t initial_capacity) {
  HitableList* list = (HitableList*)malloc(sizeof(HitableList));
  if (list == NULL) {
    return NULL;
  }
  list->records = (HitRecord**)malloc(initial_capacity * sizeof(HitRecord*));
  if (list->records==NULL) {
    free(list);
    return NULL;
  }
  list->size = 0;
  list->capacity = initial_capacity;
  return list;
}


bool add_record_to_hitablelist(HitableList *list, HitRecord *record) {
  if (list->size == list->capacity) {
    size_t new_capacity = list->capacity * 2;

    // resize that bih
    HitRecord** new_records = (HitRecord**)realloc(list->records, new_capacity * sizeof(HitRecord*));
    if(new_records==NULL) {
      return false;
    }
    list->records = new_records;
    list->capacity=new_capacity;
  }
  list->records[list->size++] = record;
  return true;
}

void free_hit_record_list(HitableList* list) {
    if (list == NULL) return;

    for (size_t i = 0; i < list->size; i++) {
        free_hit_record(list->records[i]);      }

    free(list->records);  
    free(list);           
}

