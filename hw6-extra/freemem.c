// CSE 374
// HW 6
// Chen Bai, Luke Jiang
// 15/05/2018

// This file implements the freemem function declared in mem.h

#include "mem_impl.h"
#include "mem.h"

void freemem(void* p) {
  check_heap();
  if (!p) return;
  FreeNode *block = (FreeNode *) ((uintptr_t) p - sizeof(FreeNode));
  add_tag(block, FREE);
  if (block < front) {
    block->next = front;
    front = block;
    combine(front);
  } else {
    Tag *prev_tag = (Tag *) ((uintptr_t) block - sizeof(Tag));
    if (is_beginning_tag(prev_tag)) {
      prev_tag = (Tag *) prev_tag->size;
    }
    FreeNode *prev_node = (FreeNode *) ((uintptr_t) prev_tag -
                            prev_tag->size - sizeof(Tag));
    while (prev_node > front && !is_free_tag(prev_tag)) {
      prev_tag = (Tag *) ((uintptr_t) prev_node - sizeof(Tag));
      if (is_beginning_tag(prev_tag)) {
        prev_tag = (Tag *) prev_tag->size;
      }
      prev_node = (FreeNode *) ((uintptr_t) prev_tag -
                                 prev_tag->size - sizeof(Tag));
    }
    block->next = prev_node->next;
    prev_node->next = block;
    combine(block);
    combine(prev_node);
  }
  check_heap();
}
