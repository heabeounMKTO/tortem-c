#ifndef INTERVAL_H
#define INTERVAL_H

#include <stdbool.h>

typedef struct {
  float min;
  float max;
} Interval;

Interval interval_new(float min, float max);
bool interval_surrounds(Interval interval, float x);
float interval_clamp(Interval interval, float threshold);
float interval_sizeof(Interval interval);

#endif

