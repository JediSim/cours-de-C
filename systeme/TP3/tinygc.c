// REY PICHENOT


/****
 * info507: système d'exploitation
 * TP2
 * Pierre Hyvernat
 ***/

#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <stdarg.h>

#define WORD_SIZE 4

/*
 * verbosity level
 */
int VERBOSE = 0;

/*
 * type for "raw" addresses
 * ``void*`` is not appropriate because C fordids pointer arithmetic on
 * ``void*``...
 */
typedef char *address_t;

/*
 * type of linked lists
 *
 * Note that because pointers are aligned, the field ``in_use`` could be put
 * in the least significant bit of ``start``!
 */
typedef struct cell {
    address_t start;
    size_t size;
    char in_use;
    struct cell *next;
} cell_t;

/*
 * prototypes
 */
void print_list(cell_t * list);
void insert_BLOCKS(address_t start, size_t size);

void *GC_malloc(size_t size);
void mark_BLOCK(address_t v);
void mark_region(address_t start, address_t end);
void mark_from_heap();
void mark_from_stack();

void GC_collect();

void DEBUG(int v, char *format, ...);

/*
 * GLOBAL variable containing the list of user allocated blocks
 */
cell_t *BLOCKS = NULL;

/*
 * GLOBAL variable containing the address of the start of the stack (this
 * needs to be initialized in ``main``.
 */
address_t STACK_START;

/*
 * display an ASCII representation of a linked list of blocks
 */
void print_list(cell_t * list)
{
    fprintf(stderr, "  +-------+--------------+----------+------+\n");
    fprintf(stderr, "  | index |   address    |   size   | used |\n");
    fprintf(stderr, "  +-------+--------------+----------+------+\n");
    
    cell_t *p;
    int index = 0;
    for (p = list; p != NULL; p = p->next) {
        fprintf(stderr, "  |  %03i  |  %10p  |  %6lu  |  %c   |\n",
                        index,
                        p->start,
                        p->size,
                        p->in_use+48);
        index++;
    }

    fprintf(stderr, "  +-------+--------------+----------+------+\n");
}

/*
 * special malloc that calls system's malloc and records the corresponding
 * blocks inside global variable ``BLOCKS``
 */
void *GC_malloc(size_t size)
{
    // TODO
    address_t x;

    x = (address_t)malloc(size);
    insert_BLOCKS(x,size);
    return (void*)x;
}

/*
 * mark the block containing address ``v`` as used
 */
void mark_BLOCK(address_t v)
{
    cell_t *p;
    for (p = BLOCKS; p != NULL; p = p->next) {
        // if the address ``v`` is inside the block, mark it as used
        if ((v >= p->start) && (v <= p->start + p->size)) {
            p->in_use = 1;
            return;
        }
    }
}

/*
 * mark blocks from a memory region
 */
void mark_region(address_t start, address_t end)
{
    address_t p = NULL;                // pointer to memory
    address_t v = NULL;                // value at pointer p

    for (p = start; p < end; p += WORD_SIZE) {
        v = *(address_t*)p;       // WARNING!!!
        mark_BLOCK(v);
    }
}

/*
 * mark blocks referenced from the stack,
 */
void mark_from_stack()
{
    int i;
    address_t end = (address_t)&i;
    mark_region(end,STACK_START);
    return;
}

/*
 * look at the stack and heap for references to user allocated blocks, and
 * free all the blocks that were not referenced
 */
void GC_collect()
{
    // unmark all blocks
    cell_t *p;
    for (p = BLOCKS; p != NULL; p = p->next) {
        p->in_use = 0;
    }

    // mark blocks referenced from stack
    mark_from_stack();

    // mark blocks referenced from heap
    // TODO

    // Le heap c'esst une pile avec tous les trucs malloc

    // free all unused blocks
    cell_t *tmp;
    p = BLOCKS;
    cell_t *prev = NULL;
    while (p != NULL) {
        if (p->in_use == 0) {
            free(p->start);
            if (prev == NULL) {        // first element
                BLOCKS = p->next;
                // NOTE: do not set prev, it should remain NULL
            } else {
                prev->next = p->next;
            }
            tmp = p->next;
            free(p);
            p = tmp;
        } else {
            prev = p;
            p = p->next;
        }
    }
}

void test(){
    cell_t* c1 = GC_malloc(WORD_SIZE*sizeof(char*));
    cell_t* c2 = GC_malloc(WORD_SIZE*sizeof(char*));
    cell_t* c3 = GC_malloc(WORD_SIZE*sizeof(char*));

    fprintf(stderr,"%10p\n",c1);
    fprintf(stderr,"%10p\n",c2);

    fprintf(stderr,"%10p\n",c3);

    GC_collect();
    print_list(BLOCKS);

    c3 = NULL;
    // mark_from_stack();

    GC_collect();
    // mark_from_stack();
    print_list(BLOCKS);
}

/***************************************************************************
 ***   ``main`` function   *************************************************
 ***************************************************************************/
int main(int argc, char **argv)
{
    // TODO
    // printf("coucou");
    int i;
    STACK_START = (address_t)&i;

    // get first command line argument for verbosity
    if (argc > 1) {
        VERBOSE = atoi(argv[1]);
        printf("VERBOSE = %i\n", VERBOSE);
    }
    // tests
    // TODO
    test();

    return 0;
}

/***************************************************************************
 ***************************************************************************
 ***   DO NOT MODIFY FOLLOWING FUNCTIONS   *********************************
 ***************************************************************************
 ***************************************************************************/

/*
 * display debug messages:
 * ``DEBUG`` takes a first argument giving the verbosity level at which the
 * message is displayed
 * the remaining arguments are interpreted as for the standard ``printf``
 * function...
 *
 * Note: the global variable ``VERBOSE`` is initialized in ``main`` as the
 * value of the first argument ``argv[1]``.
 */
void DEBUG(int v, char *format, ...)
{
    va_list args;
    if (v <= VERBOSE) {
        va_start(args, format);
        vfprintf(stderr, format, args);
        va_end(args);
    }
}

/*
 * insert a new cell into the global variable ``BLOCKS``
 */
void insert_BLOCKS(address_t start, size_t size)
{
    cell_t *c = malloc(sizeof(cell_t));
    c->start = start;
    c->size = size;
    c->next = NULL;
    c->in_use = 0;

    if (BLOCKS == NULL) {
        // initialize BLOCKS list if necessary
        BLOCKS = c;
    } else if (c->start < BLOCKS->start) {
        // insert in first position
        c->next = BLOCKS;
        BLOCKS = c;
    } else {
        // otherwise, look for position just before the new cell
        cell_t *p;
        for (p = BLOCKS; p->next != NULL; p = p->next) {
            if (p->next->start > c->start) {
                break;
            }
        }
        c->next = p->next;
        p->next = c;
    }
}
