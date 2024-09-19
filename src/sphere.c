#include "sphere.h"
#include <math.h>
#include <stdbool.h>
#include "utils.h"
#include "vec.h"
#include "hitable.h"

bool sphere_hit(Sphere* sphere, Ray r, Interval interval, HitRecord* rec) {
  Vec3_d oc = vec3d_sub(sphere->center , r.origin); 
  double a = vec3d_dot(r.direction, r.direction);
  double h = vec3d_dot(r.direction, oc);
  double c = vec3d_dot(oc,oc) - sphere->radius*sphere->radius;
  double disc = h * h -  a * c;
  if (disc < 0.0) {
    return false;
  }
  double sqrtd = sqrt(disc);
  double root = (h - sqrtd) / a;
  if (!interval_surrounds(interval, root)) {
    root = (h + sqrtd) / a;
    if (!interval_surrounds(interval, root)) {
      return false;
    }
  }
  rec->t = root;
  rec->p = ray_at(r, root);
  Vec3_d outward_normal = vec3d_div(vec3d_sub(rec->p, sphere->center), vec3d_from_float(sphere->radius));
  set_front_face(rec, r, outward_normal);
  return true;
}
