// this is stolen from wikipedia 
// https://en.wikipedia.org/wiki/Mersenne_Twister

#include <stdint.h>
#ifndef MT1997_H
#define MT1997_H
#define n 624
#define m 397
#define w 32
#define r 31
#define UMASK (0xffffffffUL << r)
#define LMASK (0xffffffffUL >> (w-r))
#define a 0x9908b0dfUL
#define u 11
#define s 7
#define t 15
#define l 18
#define b 0x9d2c5680UL
#define c 0xefc60000UL
#define f 1812433253UL


typedef struct
{
    uint32_t state_array[n];         // the array for the state vector 
    int state_index;                 // index into state vector array, 0 <= state_index <= n-1   always
} mt_state;

typedef struct
{
    uint64_t state_array[n];         // the array for the state vector 
    int state_index;                 // index into state vector array, 0 <= state_index <= n-1   always
} mt_state64;

extern mt_state64 GLOBAL_MT_STATE;

void initialize_state64(mt_state64* state, uint64_t seed); 
void initialize_state(mt_state* state, uint32_t seed);
uint32_t random_uint32(mt_state* state);
uint64_t random_uint64(mt_state64* state);



#endif
