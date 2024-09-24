#ifndef HB_VEC_H
#define HB_VEC_H
#include <stdio.h>
#include <math.h>

typedef struct {
  float x,y,z;
} Vec3;

typedef struct {
 double x,y,z;
} Vec3_d;



static inline Vec3 vec3_new(float x, float y, float z) {
 Vec3 v ={ .x=x, .y=y, .z=z };
  return v;
}

 static inline Vec3_d vec3d_new(double x, double y, double z) {
  Vec3_d v = { x ,y ,z };
  return v;
}


// f32 opps
void vec3_print(Vec3 v);
float vec3_lengthsq( Vec3 v);  Vec3 vec3_from_float(float f); 
Vec3 vec3_from_int(int i); 
Vec3 vec3_add(Vec3 v1, Vec3 v2); 
Vec3 vec3_sub(Vec3 v1, Vec3 v2);
Vec3 vec3_mul(Vec3 v1, Vec3 v2);
Vec3 vec3_div(Vec3 v1, Vec3 v2);
Vec3 vec3_negate(Vec3 v); 
float vec3_dot(Vec3  v1, Vec3 v2); 
Vec3 vec3_cross(Vec3 v1, Vec3 v2);
float vec3_length(Vec3 v); 
Vec3 vec3_unit(Vec3 v); 
Vec3 vec3_scale(Vec3 v, float t); 
float vec3x(Vec3 v); 
float vec3y(Vec3 v); 
float vec3z(Vec3 v);

/// f64 opps
double vec3d_lengthsq( Vec3_d v);
void vec3d_print(Vec3_d v); 
Vec3_d vec3d_add(Vec3_d v1, Vec3_d v2);
Vec3_d vec3d_from_float(double f);
Vec3_d vec3d_cross(Vec3_d v1, Vec3_d v2); 
Vec3_d vec3d_from_int(int i);
Vec3_d vec3d_sub(Vec3_d v1, Vec3_d v2);
Vec3_d vec3d_mul(Vec3_d v1, Vec3_d v2);
Vec3_d vec3d_div(Vec3_d v1, Vec3_d v2); 
Vec3_d vec3d_negate(Vec3_d v) ;
double vec3d_dot(Vec3_d  v1, Vec3_d v2);
double vec3d_length(Vec3_d v);
Vec3_d vec3d_scale(Vec3_d v, double t);
Vec3_d vec3d_unit(Vec3_d v);
Vec3_d vec3d_reflect(Vec3_d v, Vec3_d n);
Vec3_d vec3d_refract(Vec3_d uv, Vec3_d n, double etai_over_etat); 
double vec3d_x(Vec3_d v);
double vec3d_y(Vec3_d v);
double vec3d_z(Vec3_d v); 

#endif
