#include "tp2.h"

/**********************************
 * Linear Feedback Shift Register
 **********************************/

// global variables: state for LFSR
static word LFSR_state = 1; // LFSR state
static word LFSR_taps = 0;  // LFSR taps, given by the "1" bits in LFSR_taps
static int LFSR_size = 0;   // state size, in bits
static unsigned char LFSR_table[64]
= {                           // this table contains the indices of the taps
    0, 0, 0, 0, 0, 0, 0, 0, // for exemple, for b_n = b_{n-1} + b_{n-7}
    0, 0, 0, 0, 0, 0, 0, 0, // the table is [1,7]
    0, 0, 0, 0, 0, 0, 0, 0, // the rest of the table is unused
    0, 0, 0, 0, 0, 0, 0, 0, // (LFSR_size is 7 in this case)
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0
};

// initialize the current LFSR
void LFSR_init(word taps)
{
    int n = 0;
    LFSR_taps = taps;
    for (int i = 0; i < 64; i++) {
        if (BIT(i, taps) == 1) {
            LFSR_table[n] = i + 1;
            n++;
        }
    }
    if (n > 0) {
        LFSR_size = LFSR_table[n - 1];
    }
}

// give the initial seed for the current LFSR
// NOTE: do not use a seed of 0!
void LFSR_seed(word seed) { LFSR_state = seed; }

// generate the next bit
int LFSR_random_bit()
{
    int bit = 0;
    int i = -1;
    do {
        i++;
        bit ^= LFSR_state >> (LFSR_table[i] - 1);
    } while (LFSR_table[i] != LFSR_size);
    bit &= 1;
    LFSR_state = ((LFSR_state << 1) | bit) & ((1 << LFSR_size) - 1);
    return bit;
}

// display the current LFSR
void LFSR_show()
{
    printf("\n");
    if (LFSR_taps == 0) {
        printf("b_n = 0\n");
        printf("(taps: '')\n ");
        printf("\n");
        /* printf("current state: 0x0 ('')\n"); */
        return;
    }

    printf("b_n = b_n-%d ", LFSR_table[0]);
    int i = 0;
    while (LFSR_table[i] != LFSR_size) {
        i++;
        printf("+ b_n-%d ", LFSR_table[i]);
    }
    printf("(taps: ");
    print_bin(LFSR_taps, LFSR_size);
    printf(")\n");
    printf("\n");
    /* printf("current state: 0x%" PRIx64 " (", LFSR_state); */
    /* print_bin(LFSR_state, LFSR_size); */
    /* printf(")\n"); */
    /* printf("\n"); */
}

// look for the period of the current LFSR with given seed
// TODO
int LFSR_period(word seed);
