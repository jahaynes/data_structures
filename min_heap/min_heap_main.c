#include "min_heap.h"
#include <stdio.h>

int main(int argc, char** argv) {

    heap_element_type arr[] = {3,4,11,5,3,7,6,4,8,56,32,65,2,43,55,12};

    int sz = sizeof(arr) / sizeof(heap_element_type);

    Heap heap = inplace_min_heapify(sz, arr);

    print_heap(&heap);
    printf("%d\n", is_heap(&heap));

    return 0;
}
