// CSE 374
// HW 6
// Chen Bai, Luke Jiang
// 23/05/2018

// This file contains implementations of helper functions declared
// in mem_impl.h for the memory management package.

#include "mem_impl.h"

FreeNode *front = NULL;
uintptr_t systemCallSize = 0;

void check_heap() {
  if (front == NULL) {
    return;
  }
  FreeNode* current = front;
  uintptr_t old = (uintptr_t) current;
  uintptr_t new;
  while (current != NULL && current->next != NULL) {
    assert(current->size >= sizeof(FreeNode));   // #2
    uintptr_t oldTotal = current->size + old + sizeof(FreeNode);
    current = current->next;
    uintptr_t newStart = (uintptr_t) current;
    assert(oldTotal < newStart);   // #3, #4
    new = (uintptr_t) current;
    assert(old < new);   // #1
  }
}

uintptr_t to_16_multiple(uintptr_t raw_size) {
  if (raw_size % 16 == 0) {
    return (raw_size / 16) * 16;
  }
  return (1 + raw_size / 16) * 16;
}

FreeNode *system_call(uintptr_t size) {
  FreeNode *result = (FreeNode *) malloc(sizeof(FreeNode) + size);
  result->size = size;
  result->next = NULL;
  systemCallSize += sizeof(FreeNode) + size;
  return result;
}

void combine(FreeNode *prev) {
  if (prev == NULL || prev->next == NULL) return;
  FreeNode *curr = prev->next;
  if ((uintptr_t) curr == (uintptr_t) prev + prev->size + sizeof(FreeNode)) {
    prev->size += curr->size + sizeof(FreeNode);
    prev->next = curr->next;
  }
}

uintptr_t max(uintptr_t a, uintptr_t b) {
  return a > b ? a : b;
}
