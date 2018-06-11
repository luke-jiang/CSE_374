// CSE 374
// HW 6
// Chen Bai, Luke Jiang
// 15/05/2018

// This file implements the getmem function declared in mem.h

#include "mem.h"
#include "mem_impl.h"

void *getmem(uintptr_t raw_size) {
  check_heap();
  if (raw_size < 0) {
    return NULL;
  }
  uintptr_t size = to_16_multiple(raw_size);
  if (front == NULL) {
    front = system_call(INITIAL_HEAP_SIZE);
    search_front = front;
  }
  FreeNode *prev = search_front;
  FreeNode *curr = prev->next;
  int end_search = 0;
  while (end_search == 0) {
    if (curr == NULL) {
      curr = front;
      prev = NULL;
    }
    if (curr->size >= size) {
      break;
    }
    if (curr == search_front) {
      end_search = 1;
    }
    prev = curr;
    curr = curr->next;
  }
  if (end_search) {
    FreeNode *end = front;
    while (end->next != NULL) {
      end = end->next;
    }
    if (size <= INITIAL_HEAP_SIZE) {
      end->next = system_call(INITIAL_HEAP_SIZE);
    } else {
      end->next = system_call(size);
    }
    prev = end;
    curr = end->next;
  }
  void *result = (void *) ((uintptr_t) curr + sizeof(FreeNode));
  if (curr->size - size <= SPLIT_THRESHOLD) {
    if (prev != NULL) {
      prev->next = curr->next;
      search_front = prev;
    } else {
      front = curr->next;
      search_front = front;
    }
  } else {
    uintptr_t old_size = curr->size;
    uintptr_t new_size = old_size - size - sizeof(FreeNode);
    curr->size = size;
    FreeNode *splited = (FreeNode *) ((uintptr_t) curr +
                          size + sizeof(FreeNode));
    splited->size = new_size;
    splited->next = curr->next;
    if (prev != NULL) {
      prev->next = splited;
      search_front = prev;
    } else {
      front = splited;
      search_front = front;
    }
  }
  check_heap();
  return result;
}
