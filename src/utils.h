#ifndef INTERVAL_H
#define INTERVAL_H

#include <stdbool.h>

typedef struct {
  double min;
  double max;
} Interval;

Interval interval_new(double min, double max);
bool interval_surrounds(Interval interval, double x);
float interval_clamp(Interval interval, double threshold);
float interval_sizeof(Interval interval);

#endif

