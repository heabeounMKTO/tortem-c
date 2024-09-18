#include <stdbool.h>
#include "utils.h"


Interval interval_new(double min, double max) {
  Interval interval = {.min=min, .max=max};
  return interval;
}
double interval_sizeof(Interval interval) {
  return interval.max - interval.min;
}

double interval_clamp(Interval interval, double num) {
  if (num < interval.min) {
    return interval.min;
  } 
  if (num > interval.max) {
    return interval.max;
  }
  return num;
}

bool interval_surrounds(Interval interval, double x) {
  return interval.min < x && x < interval.max;
}
