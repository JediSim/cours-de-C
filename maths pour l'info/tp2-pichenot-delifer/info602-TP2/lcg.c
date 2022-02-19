#include "tp2.h"

/*********************************
 * Linear congruential generator
 *********************************/

// global variables
static int64_t LCG_state = 1;
static int64_t LCG_a = 1103515245;
static int64_t LCG_c = 12345;
static int64_t LCG_m = 1lu<<31;

// initialize the current LCG
void LCG_init(int64_t a, int64_t c, int64_t m) {
    LCG_a = a;
    LCG_c = c;
    LCG_m = m;
}

// give the initial seed for the current LCG
void LCG_seed(int64_t seed) {
    LCG_state = seed;
}

// generate the next number
int64_t LCG_random() {
    LCG_state = mod(LCG_state*LCG_a + LCG_c, LCG_m);
    return LCG_state;
}

// display the current LCG
void LCG_show() {
    printf("\n");
    printf("x_n = %"PRId64".x_n-1 + %"PRId64"  (mod %"PRId64")\n", LCG_a, LCG_c, LCG_m);
    /* printf("current state: 0x%"PRIx64"\n", LCG_state); */
}

// look for the period of the current LCG with given seed
// TODO
int LCG_period(int64_t seed);
