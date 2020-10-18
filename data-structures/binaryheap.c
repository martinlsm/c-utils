#include "binaryheap.h"

#include <errno.h>

static const size_t INIT_CAPACITY = 16;

struct BinaryHeap {
  void *data;
  size_t elem_size;
  size_t size;
  size_t capacity;
  int (*comp)(void*, void*);
};

int binary_heap_create(BinaryHeap **heap, size_t elem_size, int (*comp)(void*, void*)) {
  if (heap == NULL || elem_size == 0) {
    return EINVAL;
  }

  *heap = malloc(sizeof(BinaryHeap));
  if (*heap == NULL) {
    return ENOMEM;
  }

  (*heap)->data = malloc(elem_size * INIT_CAPACITY);
  if ((*heap)->data == NULL) {
    free(heap);
    *heap = NULL;
    return ENOMEM;
  }

  (*heap)->elem_size = elem_size;
  (*heap)->size = 0;
  (*heap)->capacity = INIT_CAPACITY;
  (*heap)->comp = comp;

  return 0;
}

int binary_heap_destroy(BinaryHeap **heap) {
  if (heap == NULL) {
	  return EINVAL;
  }

  free((*heap)->data);
  free(*heap);
  *heap = NULL;

  return 0;
}

int binary_heap_insert(BinaryHeap *heap, void *data) {
  return 0;
}

int binary_heap_peek(BinaryHeap *heap, void **data) {
  if (heap == NULL || heap->size == 0 || data == NULL) {
    return EINVAL;
  }

  *data = heap->data;

  return 0;
}

int binary_heap_pop(BinaryHeap *heap) {
  return 0;
}
