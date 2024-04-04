// This is a self-implementation of data structures that will
// be used in our CS5008 final project, A* algorithm in particular.
// Written by: Da-En, Yu

#ifndef HEAPQ_H
#define HEAPQ_H

// This is the node structure that minimum heap contains.
// A node has three attributes:
//     1. f_value of the cell
//     2. row of the cell
//     3. column of the cell
typedef struct node
{
    double f_value;
    unsigned int row;
    unsigned int column;
} node_t;

// This is the minimum heap structure.
// A minimum heap has two attributes:
//     1. an array of nodes
//     2. the size of the minimum heap
typedef struct min_heap
{
    node_t *heap;
    size_t size;
} min_heap_t;

// Function declarations
min_heap_t *create_minHeap();
node_t *create_node(double, unsigned int, unsigned int);
void free_heap(min_heap_t *);
int heap_push(min_heap_t *, node_t *);
node_t heap_pop(min_heap_t *);
void heapify(min_heap_t *);

// This is the constructor of a min_heap_t
min_heap_t *create_minHeap()
{
    min_heap_t *new_heap = (min_heap_t *)malloc(sizeof(min_heap_t));
    if (new_heap == NULL)
    {
        printf("Memory allocation failed for min_heap_t.\n");
        return NULL;
    }

    new_heap->heap = NULL;
    new_heap->size = 0;

    return new_heap;
}

// This is the constructor of a node_t
node_t *create_node(double f, unsigned int r, unsigned int c)
{
    node_t *new_node = (node_t *)malloc(sizeof(node_t));
    if (new_node == NULL)
    {
        printf("Memory allocation failed for node_t.\n");
        return NULL;
    }

    new_node->f_value = f;
    new_node->row = r;
    new_node->column = c;

    return new_node;
}

// Free the heapq including all the nodes inside
void free_heap(min_heap_t *h)
{
    if (h == NULL)
        return;

    // Free each individual node
    for (size_t i = 0; i < h->size; i++)
    {
        free(&(h->heap[i]));
    }

    // Free the min_heap_t structure
    free(h);
}

// Pushing a node to the minimum heap
// This function returns 1 upon success, 0 when fail.
inline int heap_push(min_heap_t *h, node_t *new_node)
{
    if (h == NULL || new_node == NULL)
        return 0;

    // Increase the size of the heap
    h->size++;

    // Reallocate memory to increase the size of the heap
    h->heap = (node_t *)realloc(h->heap, h->size * sizeof(node_t));
    if (h->heap == NULL)
    {
        printf("Memory allocation failed for heap push operation.\n");
        exit(1);
    }

    // Add the new node to the end of the heap
    h->heap[h->size - 1] = *new_node;

    heapify(h);
    return 1;
}

// Popping a node from the minimum heap
// This function returns a node with the minimum f_value
// If the heap is NULL or empty, NULL is returned
node_t heap_pop(min_heap_t *h) {
    if (h == NULL || h->size == 0)
        return (node_t){-1, 0, 0}; // Return an invalid node

    // Copy the minimum node
    node_t min_node = h->heap[0];

    // Replace the first node with the last node and shrink the heap
    h->heap[0] = h->heap[h->size - 1];
    h->size--;
    h->heap = (node_t *)realloc(h->heap, h->size * sizeof(node_t));

    if (h->heap == NULL && h->size > 0) {
        printf("Memory allocation failed for heap pop operation.\n");
        exit(1);
    }

    heapify(h);
    return min_node; // Return the copied node
}

// This is the heapify function of the minimum heap
inline void heapify(min_heap_t *h)
{
    // Start from the last non-leaf node and move up to the root
    for (int i = (h->size - 1) / 2; i >= 0; i--)
    {
        int parent = i;
        int smallest = parent;

        // Find the smallest among parent, left child, and right child
        while (1)
        {
            int left_child = 2 * parent + 1;
            int right_child = 2 * parent + 2;

            if (left_child < h->size && h->heap[left_child].f_value < h->heap[smallest].f_value)
                smallest = left_child;
            if (right_child < h->size && h->heap[right_child].f_value < h->heap[smallest].f_value)
                smallest = right_child;

            // If the smallest node is the parent, stop
            if (smallest == parent)
                break;

            // Swap parent with smallest child
            node_t temp = h->heap[parent];
            h->heap[parent] = h->heap[smallest];
            h->heap[smallest] = temp;

            // Move down to the smallest child
            parent = smallest;
        }
    }
}


#endif