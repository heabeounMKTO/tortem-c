#ifndef TORTEM_UTILS_H
#define TORTEM_UTILS_H
#include <math.h>
#include <stdlib.h>
#include "interval.h"


void seed_random();
double degrees2rads(double degrees);
double random_double(); 
double random_double_interval(Interval min_max); 
#endif
