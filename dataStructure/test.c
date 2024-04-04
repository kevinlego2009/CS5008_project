#include <stdio.h>
#include <stdlib.h>
#include "heapq.h"


// Include or copy your corrected min_heap and node structures and functions here

int main() {
    // Create a min heap
    min_heap_t *heap = create_minHeap();
    if (heap == NULL) {
        printf("Failed to create a min heap.\n");
        return -1;
    }

    // Create and insert nodes into the heap
    double f_values[] = {5.1, 3.3, 4.7, 2.2, 9.8, 1.0};
    unsigned int rows[] = {0, 1, 2, 3, 4, 5};
    unsigned int columns[] = {5, 4, 3, 2, 1, 0};

    size_t num_nodes = sizeof(f_values) / sizeof(f_values[0]);
    for (size_t i = 0; i < num_nodes; i++) {
        node_t *node = create_node(f_values[i], rows[i], columns[i]);
        if (!heap_push(heap, node)) {
            printf("Failed to push node with f_value: %f\n", node->f_value);
            free(node); // Ensure to free node if not successfully pushed
        }
        // The heap now owns the node, so don't free it here
    }

    // Pop nodes from the heap and print their values
    printf("Popping nodes from the heap:\n");
    while (heap->size > 0) {
        node_t *node = heap_pop(heap);
        if (node != NULL) {
            printf("Node - f_value: %f, Row: %u, Column: %u\n", node->f_value, node->row, node->column);
            // If you change heap_pop to return a copy, you need to free the node here
            // free(node);
        }
    }

    int i = 8;
    int j = 1;
    // use the min_heap initialize the open list (cells to be visited) with the start cell
    min_heap_t* open_list = create_minHeap();
    // put the src into a node
    node_t *temp = create_node(1.0, 8, 2);
    //push the scr into heap
    heap_push(open_list, temp);

    node_t *temp2 = create_node(2.0, 3, 4);
    //push the scr into heap
    heap_push(open_list, temp2);
    node_t *p = heap_pop(open_list);
        
        //#################
        //#################
        //#################
    // Mark the poped cell as visited
    //something wrong after I pop the heap, i and j numbers are weird
    i = p->row;
    printf("%d\n", i);
    j = p->column;
    printf("%d\n", j);

    // Free the heap
    free_heap(heap);

    return 0;
}