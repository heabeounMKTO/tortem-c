/*
 * vector and vector util functions
 * 
 */
#ifndef VEC_H
#define VEC_H
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

typedef struct {
  double x;
  double y;
  double z;
} Vec3;

void print_vec(Vec3 v);
Vec3 double2vec(double f);
Vec3 negate_vec3(Vec3 v);
Vec3 new_vec(double x, double y, double z);
Vec3 int2vec(int i);
Vec3 add_vec3(Vec3 v1, Vec3 v2);
Vec3 div_vec3(Vec3 v1, Vec3 v2);
Vec3 mul_vec3(Vec3 v1, Vec3 v2);
Vec3 sub_vec3(Vec3 v1, Vec3 v2);
Vec3 unit_vec(Vec3 v);
double dot(Vec3 v1, Vec3 v2);
double len_sq(Vec3 v);
double length(Vec3 v);

bool near_zero(Vec3 v);
Vec3 random_in_unit_sphere();
Vec3 random_unit_vec3_sphere();
Vec3 random_on_hemisphere(Vec3 normal);


#endif
