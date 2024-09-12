#include "mt1997.h"

mt_state64 GLOBAL_MT_STATE;

void initialize_state64(mt_state64* state, uint64_t seed) 
{
    uint64_t* state_array = &(state->state_array[0]);
    
    state_array[0] = seed;                          // suggested initial seed = 19650218UL
    
    for (int i=1; i<n; i++)
    {
        seed = f * (seed ^ (seed >> (w-2))) + i;    // Knuth TAOCP Vol2. 3rd Ed. P.106 for multiplier.
        state_array[i] = seed; 
    }
    
    state->state_index = 0;
}

void initialize_state(mt_state* state, uint32_t seed) 
{
    uint32_t* state_array = &(state->state_array[0]);
    
    state_array[0] = seed;                          // suggested initial seed = 19650218UL
    
    for (int i=1; i<n; i++)
    {
        seed = f * (seed ^ (seed >> (w-2))) + i;    // Knuth TAOCP Vol2. 3rd Ed. P.106 for multiplier.
        state_array[i] = seed; 
    }
    
    state->state_index = 0;
}



uint64_t random_uint64(mt_state64* state)
{
    uint64_t* state_array = &(state->state_array[0]);
    int k = state->state_index;      // point to current state location
                                     // 0 <= state_index <= n-1   always
//  int k = k - n;                   // point to state n iterations before
//  if (k < 0) k += n;               // modulo n circular indexing
                                     // the previous 2 lines actually do nothing
                                     //  for illustration only
    
    int j = k - (n-1);               // point to state n-1 iterations before
    if (j < 0) j += n;               // modulo n circular indexing

    uint64_t x = (state_array[k] & UMASK) | (state_array[j] & LMASK);
    
    uint64_t xA = x >> 1;
    if (x & 0x00000001UL) xA ^= a;
    
    j = k - (n-m);                   // point to state n-m iterations before
    if (j < 0) j += n;               // modulo n circular indexing
    
    x = state_array[j] ^ xA;         // compute next value in the state
    state_array[k++] = x;            // update new state value
    
    if (k >= n) k = 0;               // modulo n circular indexing
    state->state_index = k;
    
    uint64_t y = x ^ (x >> u);       // tempering 
             y = y ^ ((y << s) & b);
             y = y ^ ((y << t) & c);
    uint64_t z = y ^ (y >> l);
    
    return z; 
}

uint32_t random_uint32(mt_state* state)
{
    uint32_t* state_array = &(state->state_array[0]);
    int k = state->state_index;      // point to current state location
                                     // 0 <= state_index <= n-1   always
//  int k = k - n;                   // point to state n iterations before
//  if (k < 0) k += n;               // modulo n circular indexing
                                     // the previous 2 lines actually do nothing
                                     //  for illustration only
    
    int j = k - (n-1);               // point to state n-1 iterations before
    if (j < 0) j += n;               // modulo n circular indexing

    uint32_t x = (state_array[k] & UMASK) | (state_array[j] & LMASK);
    
    uint32_t xA = x >> 1;
    if (x & 0x00000001UL) xA ^= a;
    
    j = k - (n-m);                   // point to state n-m iterations before
    if (j < 0) j += n;               // modulo n circular indexing
    
    x = state_array[j] ^ xA;         // compute next value in the state
    state_array[k++] = x;            // update new state value
    
    if (k >= n) k = 0;               // modulo n circular indexing
    state->state_index = k;
    
    uint32_t y = x ^ (x >> u);       // tempering 
             y = y ^ ((y << s) & b);
             y = y ^ ((y << t) & c);
    uint32_t z = y ^ (y >> l);
    
    return z; 
}