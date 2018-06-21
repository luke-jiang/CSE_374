// CSE 374
// HW 6
// Chen Bai, Luke Jiang
// 15/05/2018

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
    front = system_call(INITIAL_HEAP_SIZE);
    search_front = front;
    end_of_memory = (uintptr_t) front + front->size + sizeof(FreeNode);
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
    add_tag(curr, FREE);
    Tag *begin_tag = (Tag *) ((uintptr_t) curr - sizeof(Tag));
    begin_tag->size = end_of_memory;
    end_of_memory = (uintptr_t) curr + curr->size + sizeof(FreeNode);
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
    add_tag(curr, IN_USE);
  } else {
    uintptr_t old_size = curr->size;
    uintptr_t new_size = old_size - size - 2 * sizeof(FreeNode);
    curr->size = size;
    add_tag(curr, IN_USE);
    FreeNode *splited = (FreeNode *) ((uintptr_t) curr +
                         size + 2 * sizeof(FreeNode));
    splited->size = new_size;
    splited->next = curr->next;
    add_tag(splited, FREE);
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
