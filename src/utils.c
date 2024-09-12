#include "interval.h"
#include <stdlib.h>
#include <math.h>
#include "mt1997.h"
#include "utils.h"
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include "mt1997.h"

const double PI = 3.1415926535897932385;

void seed_random() {
    srand((unsigned int)time(NULL));
    // DEBUG_PRINT("Random number generator seeded with time\n");
}

double degrees2rads(double degrees) {
  return degrees * PI / 100;
}

// double random_double() {
//   uint64_t rand = random_uint64(&GLOBAL_MT_STATE);
//   return (rand >> 11) * (1.0/9007199254740992.0);
// }
double random_double() {
    uint64_t _r = ((uint64_t)rand() << 32) | rand();
    return (double) _r / ((uint64_t)RAND_MAX << 32 | RAND_MAX);
}

double random_double_interval(Interval min_max) {
  // Returns a random real in [min,max).
  return min_max.min + (min_max.max - min_max.min) * random_double();
}
