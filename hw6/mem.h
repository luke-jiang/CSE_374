// CSE 374
// HW 6
// Chen Bai, Luke Jiang
// 23/05/2018

// This is the public interface for the memory management package

#ifndef _MEM_H_
#define _MEM_H_

#include <inttypes.h>
#include <stdio.h>

// Return a pointer to a new block of storage with at least size
// bytes of memory. The returned pointer has an address of a
// multiple of 16. The value size must be greater than 0. If size
// is not positive or getmem cannot satisfy the result, return
// NULL.
void *getmem(uintptr_t size);

// Free the block pointed by p. If p is NULL, the function has no
// effect. If p is not the value returned by getmem, the function's
// behavior is undefined.
void freemem(void *p);

// Store statistics about the current state of memory manager.
// total_size stores total amount of storage in bytes acquired by
//        the memory manager so far.
// total_free stores total amount of storage in bytes that is
//        currently stored on the free list.
// n_free/blocks stores the amount of blocks in the current free
//        list.
void get_mem_stats(uintptr_t* total_size, uintptr_t* total_free,
                   uintptr_t* n_free_blocks);

// Takes a file pointer as parameter. Append a formatted listing
// on the file showing the blocks of the free list. Each line
// describes one block including the address and the length of the
// block.
void print_heap(FILE * f);


#endif
