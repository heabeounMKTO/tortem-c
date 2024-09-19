#ifndef INTERVAL_H
#define INTERVAL_H


#include <stdlib.h>
#include <stdbool.h>


// Two numbers with extra steps
typedef struct {
  double min;
  double max;
} Interval;

Interval interval_new(double min, double max);
bool interval_surrounds(Interval interval, double x);
double interval_clamp(Interval interval, double threshold);
double interval_sizeof(Interval interval);

static inline double random_double() {
  return rand() / (double) (RAND_MAX) + 1.0;
}

static inline double random_interval(double min, double max) {
  return min + (max-min) * random_double();
}


#endif

