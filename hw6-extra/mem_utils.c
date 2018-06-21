// CSE 374
// HW 6
// Chen Bai, Luke Jiang
// 15/05/2018

// This file contains implementations of helper functions declared
// in mem_impl.h for the memory management package.

#include "mem_impl.h"

FreeNode *front = NULL;
FreeNode *search_front = NULL;
uintptr_t systemCallSize = 0;
uintptr_t end_of_memory = 0;

void check_heap() {
  if (front == NULL) {
    return;
  }
  FreeNode* current = front;
  uintptr_t old;
  uintptr_t new;
  while (current != NULL && current->next != NULL) {
    assert(current->size >= sizeof(FreeNode));  // #2
    old = (uintptr_t) current;
    uintptr_t oldTotal = current->size + old + 2 * sizeof(FreeNode);
    current = current->next;
    uintptr_t newStart = (uintptr_t) current;
    assert(oldTotal < newStart);  // #3, #4
    new = (uintptr_t) current;
    assert(old < new);  // #1
  }
}

uintptr_t to_16_multiple(uintptr_t raw_size) {
  if (raw_size % 16 == 0) {
    return (raw_size / 16) * 16;
  }
  return (1 + raw_size / 16) * 16;
}

FreeNode *system_call(uintptr_t size) {
  Tag *begin_tag = (Tag *) malloc(3 * sizeof(FreeNode) + size);
  systemCallSize += 3 * sizeof(FreeNode) + size;
  FreeNode *result = (FreeNode *) ((uintptr_t) begin_tag + sizeof(Tag));
  result->size = size;
  result->next = NULL;
  begin_tag->size = (uintptr_t) NULL;
  begin_tag->state = BEGIN_TAG;
  add_tag(result, FREE);
  return result;
}

void combine(FreeNode *prev) {
  if (prev == NULL || prev->next == NULL) return;
  FreeNode *curr = prev->next;
  if ((uintptr_t) curr == (uintptr_t) prev +
                           prev->size + 2 * sizeof(FreeNode)) {
    prev->size += curr->size + 2 * sizeof(FreeNode);
    prev->next = curr->next;
    add_tag(prev, 1);
    if (curr == search_front) {
      search_front = prev;
    }
  }
}

uintptr_t max(uintptr_t a, uintptr_t b) {
  return a > b ? a : b;
}

void add_tag(FreeNode *node, uintptr_t state) {
  if (node != NULL) {
    Tag *tag = (Tag *) ((uintptr_t) node + node->size + sizeof(FreeNode));
    tag->size = node->size;
    tag->state = state;
  }
}

int is_beginning_tag(Tag *prev_tag) {
  return prev_tag->state == BEGIN_TAG;
}

int is_free_tag(Tag *tag) {
  return tag->state == FREE;
}
