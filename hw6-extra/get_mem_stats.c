// CSE 374
// HW 6
// Chen Bai, Luke Jiang
// 05/15/2018

// This file implements the get_mem_stats function declared in mem.h


#include "mem.h"
#include "mem_impl.h"

void get_mem_stats(uintptr_t* total_size, uintptr_t* total_free,
                   uintptr_t* n_free_blocks) {
  FreeNode * current = front;
  uintptr_t countFreeTotal = 0;
  uintptr_t countFreeBlocks = 0;
  while (current != NULL) {
    countFreeTotal += sizeof(FreeNode) + current->size;
    countFreeBlocks++;
    current = current->next;
  }
  *total_size = systemCallSize;
  *total_free = countFreeTotal;
  *n_free_blocks = countFreeBlocks;
}
