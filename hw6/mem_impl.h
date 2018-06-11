// CSE 374
// HW 6
// Chen Bai, Luke Jiang
// 23/05/2018

// This is the interface that declares helper functions and
// variables for implementing the memory manager package.


#ifndef _MEM_IMPL_H_
#define _MEM_IMPL_H_

#include <inttypes.h>
#include <stdlib.h>
#include <assert.h>

// FreeNode data structure in free list
typedef struct FreeNode {
  struct FreeNode *next;    // pointer to the next list
  uintptr_t size;           // size excluding node's size
} FreeNode;

#define SPLIT_THRESHOLD 32
#define INITIAL_HEAP_SIZE 10000

// the front of the free list.
extern FreeNode *front;
// total bytes allocated via system call malloc.
extern uintptr_t systemCallSize;

// Check that the current free list satisfies the following
// properties:
// -blocks are ordered with strictly increasing memory address.
// -block sizes are positive numbers and are larger than the
//         smallest possible block.
// -blocks do not overlap.
// -blocks are not touching.
// If free list violates one of these properties, the program
// terminates. Else, it returns silently.
void check_heap();

// allocate size + sizeof(FreeNode) bytes via system call and create a
// FreeNode at the beginning of the block. Return the address of FreeNode.
FreeNode *system_call(uintptr_t size);

// return a multiple of 16 that is closest to raw_size.
uintptr_t to_16_multiple(uintptr_t raw_size);

// check if prev and its next node are located contiguously on the heap and
// merge the two blocks if so.
void combine(FreeNode *prev);

// return the larger parameter.
uintptr_t max(uintptr_t a, uintptr_t b);

#endif
