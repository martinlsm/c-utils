#include "binaryheap.h"

#include <errno.h>

static const size_t INIT_CAPACITY = 16;

struct BinaryHeap {
  void **data;
  size_t size;
  size_t capacity;
  int (*comp)(void*, void*);
};

static size_t get_parent(size_t i);

int binary_heap_create(BinaryHeap **heap, int (*comp)(void*, void*)) {
  if (heap == NULL) {
    return EINVAL;
  }

  *heap = malloc(sizeof(BinaryHeap));
  if (*heap == NULL) {
    return ENOMEM;
  }

  (*heap)->data = malloc(INIT_CAPACITY * sizeof(void*));
  if ((*heap)->data == NULL) {
    free(heap);
    *heap = NULL;
    return ENOMEM;
  }

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
  if (heap == NULL) {
    return EINVAL;
  }

  heap->size += 1;
  // TODO: Realloc
  // if (heap->size == heap->capacity) {
  //
  // }

  if (heap->size == 1) {
    heap->data[0] = data;

    return 0;
  }

  // Sift up.
  size_t i = heap->size;
  while (i > 0 && heap->comp(heap->data[get_parent(i)], data) > 0) {
    heap->data[i] = heap->data[get_parent(i)];
    i = get_parent(heap->size);
  }

  heap->data[i] = data;

  return 0;
}

int binary_heap_peek(BinaryHeap *heap, void **data) {
  if (heap == NULL || heap->size == 0 || data == NULL) {
    return EINVAL;
  }

  *data = *heap->data;

  return 0;
}

int binary_heap_pop(BinaryHeap *heap) {
  (void) heap;
  return 0;
}

static size_t get_parent(size_t i) {
  return (i - 1) / 2;
}
