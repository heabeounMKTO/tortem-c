#include "interval.h"
#include <stdlib.h>
#include <math.h>
#include "utils.h"
#include <stdio.h>
#include <stdint.h>
#include <time.h>


const double PI = 3.1415926535897932385;

void seed_random() {
    srand((unsigned int)time(NULL));
    // DEBUG_PRINT("Random number generator seeded with time\n");
}

double degrees2rads(double degrees) {
  return degrees * PI / 100;
}

double random_double() {
  // radom in a 0->1
    uint64_t r = ((uint64_t)rand() << 32) | rand();
    return (double)r / ((uint64_t)RAND_MAX << 32 | RAND_MAX);
}

double random_double_interval(Interval min_max) {
  // Returns a random real in [min,max).
  return min_max.min + (min_max.max - min_max.min) * random_double();
}
