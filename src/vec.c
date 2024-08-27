#include <math.h>
#include "vec.h"
#include <stdio.h>
#include "utils.h"

void print_vec(Vec3 v) {
  printf("vec: %f %f %f\n", v.x, v.y, v.z);
}

Vec3 div_vec3(Vec3 v1, Vec3 v2) {
    Vec3 result;
    if (v2.x != 0.0) {
        result.x = v1.x / v2.x;
    } else {
        result.x = 0.0; // Handle division by zero as needed
    }
    if (v2.y != 0.0) {
        result.y = v1.y / v2.y;
    } else {
        result.y = 0.0; // Handle division by zero as needed
    }
    if (v2.z != 0.0) {
        result.z = v1.z / v2.z;
    } else {
        result.z = 0.0; // Handle division by zero as needed
    }
    return result;
} 

Vec3 new_vec(double x, double y, double z) {
  Vec3 fuck = { x, y,z };
  return fuck;
}
Vec3 negate_vec3(Vec3 v) {
  Vec3 neg = { -v.x, -v.y, -v.z };
  return neg;
}

Vec3 sub_vec3(Vec3 v1, Vec3 v2) {
  Vec3 res =  { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
  return res;
}

Vec3 add_vec3(Vec3 v1, Vec3 v2) {
  Vec3 res =  { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
  return res;
}

Vec3 mul_vec3(Vec3 v1, Vec3 v2) {
  Vec3 res = { v1.x*v2.x, v1.y*v2.y, v1.z*v2.z };
  return res;
}

double length(Vec3 v) {
  return sqrt(len_sq(v));
}

double len_sq(Vec3 v) {
  return v.x*v.x + v.y*v.y + v.z*v.z;
}

double dot(Vec3 v1, Vec3 v2) {
  return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

Vec3 unit_vec(Vec3 v) {
  double len = length(v);
  Vec3 vec = { len, len ,len }; 
  return div_vec3(v, vec);
}

Vec3 int2vec(int i) {
  Vec3 vec = { (double) i, (double) i, (double) i };
  return vec;
}

Vec3 random_vec3(Interval _range) {
  Vec3 vec = { random_double_interval(_range), random_double_interval(_range), random_double_interval(_range) };
  return vec;
}


Vec3 random_in_unit_sphere() {
  while(true) {
    Interval _interval = {.min=-1.0, .max=1.0};
    Vec3 p = random_vec3(_interval);
    if(len_sq(p) < 1.0) {
      return p;
    }
  }
}


Vec3 random_unit_vec3_sphere() {
  return unit_vec(random_in_unit_sphere());
}

Vec3 random_on_hemisphere(Vec3 normal) {
  Vec3 on_unit_sphere = random_unit_vec3_sphere();
  if (dot(on_unit_sphere, normal) > 0.0) {
    return on_unit_sphere;
  } else {
    return negate_vec3(on_unit_sphere);
  }
}

Vec3 double2vec(double f) {
  Vec3 vec = { f, f, f };
  return vec;
}
