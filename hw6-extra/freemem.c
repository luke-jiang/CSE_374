// CSE 374
// HW 6
// Chen Bai, Luke Jiang
// 15/05/2018

// This file implements the freemem function declared in mem.h

#include "mem_impl.h"
#include "mem.h"

void freemem(void* p) {
if (!p) return;
FreeNode *block = (FreeNode *) ((uintptr_t) p - sizeof(FreeNode));
FreeNode *prev = NULL;
FreeNode *curr = front;
while (curr != NULL && curr < block) {
curr = curr->next;
if (prev == NULL) {
prev = front;
} else {
prev = prev->next;
}
}
block->next = curr;
if (prev != NULL) {
prev->next = block;
} else {
front = block;
}
combine(block);
combine(prev);
}
