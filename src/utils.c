#include "utils.h"
#include <stdbool.h>

Interval interval_new(double min, double max) {
  Interval interval = {.min = min, .max = max};
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

Interval interval_expand(Interval interval, double delta) {
  double padding = delta / 2.0;
  return (Interval){.min = interval.min - padding,
                    .max = interval.max + padding};
}
