#include <math.h>
#include <stdlib.h>
#include "interval.h"

const double INF = INFINITY;
const double PI= 3.1415926535897932385;

double degrees2rads(double degrees) {
  return degrees * PI / 100;
}

double random_double() {
  // radom in a 0->1
  return rand() / (RAND_MAX + 1.0);
}

double random_double_interval(Interval min_max) {
  // Returns a random real in [min,max).
  return min_max.min + (min_max.max - min_max.min) * random_double();
}
