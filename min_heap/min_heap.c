#include "min_heap.h"

#include <stdio.h>

typedef enum { Modified, Unmodified } Modification;

Modification min_heapify_subtree(const int cursor, const size_t sz, heap_element_type *arr);

void min_heapify(const size_t sz, Heap *heap);

Heap new_heap(const size_t capacity) {
    Heap heap = {.arr = malloc(capacity * sizeof(heap_element_type)),
                 .sz = 0,
                 .capacity = capacity};
    return heap;
}

void free_heap(const Heap heap) {
    free(heap.arr);
}

void print_heap(const Heap *heap) {
    for(int i=0;i<heap->sz;i++) {
        printf(print_string, heap->arr[i]); 
    }
    printf("\n");
}

Heap inplace_min_heapify(const size_t sz, heap_element_type *arr) {
    Heap heap = {.arr = arr,
                 .sz = sz,
                 .capacity = sz};
    for(int cursor = (sz - 1) / 2; cursor >= 0; cursor--) {
        min_heapify_subtree(cursor, sz, heap.arr);
    }
    return heap;
}

const static inline int left(const int cursor) {
  return (cursor + 1) * 2 - 1;
}

const static inline int right(const int cursor) {
  return (cursor + 1) * 2;
}

const static inline int up(const int cursor) {
  return (cursor - 1) / 2;
}

typedef enum { Top, Left, Right } Smallest;

Modification min_heapify_subtree(const int cursor, const size_t sz, heap_element_type *arr) {

    heap_element_type smallest = arr[cursor];
    Smallest smallestPos = Top;

    const int leftCursor = left(cursor);
    const int rightCursor = right(cursor);

    //check left
    if (leftCursor < sz && arr[leftCursor] < smallest) {
        smallestPos = Left;
        smallest = arr[leftCursor];
    }

    //check right
    if (rightCursor < sz && arr[rightCursor] < smallest) {
        smallestPos = Right;
        smallest = arr[rightCursor];
    }

    heap_element_type tmp;
    switch (smallestPos) {
        case Left:
            tmp = arr[leftCursor];
            arr[leftCursor] = arr[cursor];
            arr[cursor] = tmp;
            min_heapify_subtree(leftCursor, sz, arr);
            return Modified; //Does this break TCO
        
        case Right:
            tmp = arr[rightCursor];
            arr[rightCursor] = arr[cursor];
            arr[cursor] = tmp;
            min_heapify_subtree(rightCursor, sz, arr);
            return Modified; //Does this break TCO
            
        default://Top
            return Unmodified;
    }
}

bool is_heap_(const int cursor, const Heap *heap) {

    const int left_cursor = left(cursor);
    const int right_cursor = right(cursor);
    
    //left subheap must be non-existant or smaller
    const bool l = left_cursor >= heap->sz || 
           (heap->arr[cursor] <= heap->arr[left_cursor] && is_heap_(left_cursor, heap));

    //right subheap must be non-existant or smaller
    const bool r = right_cursor >= heap->sz ||
           (heap->arr[cursor] <= heap->arr[right_cursor] && is_heap_(right_cursor, heap));

    return l && r;
}

bool is_heap(const Heap *heap) {
    return is_heap_(0, heap);
}

Result insert_heap(Heap *heap, const heap_element_type element) {

    int cursor = heap->sz;

    if(cursor >= heap->capacity) {
        return Too_Full;
    }

    heap->arr[cursor] = element;
    heap->sz++;
    
    Modification modified = Modified;
    do {
        cursor = up(cursor);
        modified = min_heapify_subtree(cursor, heap->sz, heap->arr);
    } while (cursor > 0 && modified == Modified);

    min_heapify_subtree(0, heap->sz, heap->arr);

    return Success;
}


