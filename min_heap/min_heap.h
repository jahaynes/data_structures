#ifndef HEAP_H
#define HEAP_H

#include "min_heap_generics.h"

#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    heap_element_type *arr;
    size_t sz;
    const size_t capacity;
} Heap;

typedef enum {
    Success,
    Too_Full
} Result;

Heap new_heap(const size_t capacity);

Heap inplace_min_heapify(const size_t sz, heap_element_type *arr);

Result insert_heap(Heap *heap, const heap_element_type element);

bool is_heap(const Heap *heap);

void print_heap(const Heap *heap);

void free_heap(const Heap heap);

#endif
