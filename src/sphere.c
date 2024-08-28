#include "vec.h"
#include <math.h>
#include "interval.h"
#include "ray.h"
#include "hitable.h"
#include "sphere.h"

HitRecord* sphere_hit(Sphere sphere, Ray r, Interval ray_interval) {
  Vec3 oc = sub_vec3(sphere.center, r.origin);
  double a = len_sq(r.direction);
  double h = dot(r.direction, oc);
  double c = len_sq(oc) - (sphere.radius * sphere.radius);
  double discriminant = h*h - a*c;
  if (discriminant < 0.0) {
     return no_hits();  
  }

  double root = (h - sqrt(discriminant)) / a;
  if (!interval_surrounds(ray_interval, root)) {
    root = (h + sqrt(discriminant)) / a;
    if (!interval_surrounds(ray_interval, root)) {
      return no_hits();
    }
  } 
  double t = root;
  Vec3 point = ray_at(r, t);
  Vec3 outward_normal = div_vec3(sub_vec3(point, sphere.center), double2vec(sphere.radius));

  bool front_face = dot(r.direction, outward_normal); 
  Vec3 _nrm;
  if (front_face) {
    _nrm = outward_normal;
  } else {
    // if not front face , reverse the faces to inside 
    _nrm = negate_vec3(outward_normal);
  }
  return new_hit_record(point, _nrm, t, front_face, true);  
}

void free_sphere(Sphere* sphere) {
  if(sphere != NULL) {
    free(sphere);
  }
}

