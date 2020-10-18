#ifndef BINARYHEAP_H
#define BINARYHEAP_H

#include <stdlib.h>

typedef struct BinaryHeap BinaryHeap;

int binary_heap_create(BinaryHeap **heap, size_t elem_size, int (*comp)(void*, void*));
int binary_heap_destroy(BinaryHeap **heap);
int binary_heap_insert(BinaryHeap *heap, void *data);
int binary_heap_peek(BinaryHeap *heap, void **data);
int binary_heap_pop(BinaryHeap *heap);

#endif
