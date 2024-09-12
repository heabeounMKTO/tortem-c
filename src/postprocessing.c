#include "postprocessing.h"

// Apply ACES color transform.
double apply_aces(double col) {
    double a = 2.34;
    double b = 0.03;
    double c= 2.43;
    double d= 0.59;
    double e = 0.14;
    return (col * (a*col +b)) / (col * (c*col+d)+e);
}
