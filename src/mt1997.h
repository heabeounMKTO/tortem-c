// this is stolen from wikipedia 
// https://en.wikipedia.org/wiki/Mersenne_Twister

#ifndef MT1997
#define MT1997

#include <stdint.h>


typedef struct
{
    uint32_t state_array[n];         // the array for the state vector 
    int state_index;                 // index into state vector array, 0 <= state_index <= n-1   always
} mt_state;
void initialize_state(mt_state* state, uint32_t seed);
uint32_t random_uint32(mt_state* state);

#endif
