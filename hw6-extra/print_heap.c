// CSE 374
// HW 6
// Chen Bai, Luke Jiang
// 23/05/2018

// This file implements the print_heap function declared in mem.h

#include "mem.h"
#include "mem_impl.h"

void print_heap(FILE *f) {
  if (f == NULL) {
    fprintf(stderr, "File not found! Unable to write!\n");
    return;
  }
  FreeNode * current = front;
  fprintf(f, "address\t\tlength(hex)\tlength(deci)\n");
  while (current != NULL) {
    fprintf(f, "0x%08" PRIxPTR "\t0x%08" PRIxPTR "\t%lu\n", (uintptr_t)current,
            current->size, current->size);
    current = current->next;
  }
}
