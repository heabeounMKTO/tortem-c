#include <stdbool.h>
#include "utils.h"


Interval interval_new(float min, float max) {
  Interval interval = {.min=min, .max=max};
  return interval;
}
float interval_sizeof(Interval interval) {
  return interval.max - interval.min;
}

float interval_clamp(Interval interval, float num) {
  if (num < interval.min) {
    return interval.min;
  } 
  if (num > interval.max) {
    return interval.max;
  }
  return num;
}

bool interval_surrounds(Interval interval, float x) {
  return interval.min < x && x < interval.max;
}
