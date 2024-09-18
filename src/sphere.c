#include "sphere.h"
#include <math.h>
#include <stdbool.h>
#include "vec.h"
#include "hitable.h"





bool hit(Sphere sphere, Ray r, double t_min, double t_max, HitRecord* rec) {
  Vec3_d oc = vec3d_sub(sphere.center , r.origin); 
  double a = vec3d_dot(r.direction, r.direction);
  double h = vec3d_dot(r.direction, oc);
  double c = vec3d_dot(oc,oc) - sphere.radius*sphere.radius;
  double disc = h * h -  a * c;
  if (disc < 0.0) {
    return false;
  }

  double sqrtd = sqrt(disc);
  double root = (h - sqrtd) / a;
  if (root <= t_min || t_max <= root) {
    root = (h + sqrtd) / a;
    if (root <= t_min || t_max <= root) {
      return false;
    }
  }
  rec->t = root;
  rec->p = ray_at(r, root);
  Vec3_d outward_normal = (vec3d_sub(rec->p, sphere.center), vec3d_from_float(sphere.radius));
  set_front_face(rec, r, outward_normal);
  return true;
}
