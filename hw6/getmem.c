// CSE 374
// HW 6
// Chen Bai, Luke Jiang
// 23/05/2018

// This file implements the getmem function declared in mem.h

#include "mem.h"
#include "mem_impl.h"

void *getmem(uintptr_t raw_size) {
  check_heap();
  if ((int) raw_size <= 0) {
    return NULL;
  }
  uintptr_t size = to_16_multiple(raw_size);
  if (front == NULL) {
    front = system_call(max(INITIAL_HEAP_SIZE, size));
  }
  FreeNode *prev = NULL;
  FreeNode *curr = front;
  while (curr != NULL && curr->size < size) {
    curr = curr->next;
    if (prev == NULL) {
      prev = front;
    } else {
      prev = prev->next;
    }
  }
  if (curr == NULL) {
    if (size <= INITIAL_HEAP_SIZE) {
      prev->next = system_call(INITIAL_HEAP_SIZE);
    } else {
      prev->next = system_call(size);
    }
    curr = prev->next;
  }
  void *result = (void *) ((uintptr_t) curr + sizeof(FreeNode));
  if (curr->size - size <= SPLIT_THRESHOLD) {
    if (prev != NULL) {
      prev->next = curr->next;
    } else {
      front = curr->next;
    }
  } else {
    uintptr_t old_size = curr->size;
    uintptr_t new_size = old_size - size - sizeof(FreeNode);
    curr->size = size;
    FreeNode *splited = (FreeNode *)
      ((uintptr_t) curr + size + sizeof(FreeNode));
    splited->size = new_size;
    splited->next = curr->next;
    if (prev != NULL) {
      prev->next = splited;
    } else {
      front = splited;
    }
  }
  check_heap();
  return result;
}
