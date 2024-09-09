#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include "sort.h"

void swap(void* const elem1, void* const elem2, const size_t elem_size);

void sort(void *base, size_t num, size_t size, int (*compare) (const void *, const void *))
{
    //TODO - implement
}

#define SWAP_HELP(ELEM1, ELEM2, TYPE, OFFSET)                              \
    do {                                                                   \
        TYPE temp = *(TYPE*)((char*)ELEM1 + OFFSET);                       \
        *(TYPE*)((char*)ELEM1 + OFFSET) = *(TYPE*)((char*)ELEM2 + OFFSET); \
        *(TYPE*)((char*)ELEM2 + OFFSET) = temp;                            \
        OFFSET += sizeof(TYPE);                                            \
    } while(0)

void swap(void* const elem1, void* const elem2, const size_t elem_size) 
{
    assert(elem1);
    assert(elem2);


    size_t swapped_size = 0;

    while(swapped_size + 8 < elem_size)
        SWAP_HELP(elem1, elem2, int64_t, swapped_size);


    if (swapped_size + 4 < elem_size)
        SWAP_HELP(elem1, elem2, int32_t, swapped_size);

    if (swapped_size + 2 < elem_size)
        SWAP_HELP(elem1, elem2, int16_t, swapped_size);

    if (swapped_size + 1 < elem_size)
        SWAP_HELP(elem1, elem2, int8_t, swapped_size);
}