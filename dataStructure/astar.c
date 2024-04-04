//gcc -o astar astar.c -lm
#include <stdio.h>
#include <stdlib.h>
#include <math.h>    // For sqrt
#include <float.h>
#include <stdbool.h>
#include <string.h>  // For memset
#include "heapq.h"

#define ROW 9
#define COL 10

// Cell struct
typedef struct {
    int parent_i, parent_j;
    double f, g, h;
} Cell;

// Check if a cell is valid (within the grid)
bool is_valid(int row, int col) {
    return (row >= 0) && (row < ROW) && (col >= 0) && (col < COL);
}

// Check if a cell is unblocked
bool is_unblocked(int grid[][COL], int row, int col) {
    return grid[row][col] == 1;
}

// Check if a cell is the destination
bool is_destination(int row, int col, int dest[]) {
    return row == dest[0] && col == dest[1];
}

// Calculate the heuristic value of a cell (Euclidean distance to destination)
double calculate_h_value(int row, int col, int dest[]) {
    return sqrt((row - dest[0]) * (row - dest[0]) + (col - dest[1]) * (col - dest[1]));
}

// Function to trace the path from the source to destination
void trace_path(Cell cell_details[][COL], int dest[]) {
    printf("The Path is ");
    int row = dest[0];
    int col = dest[1];

    int path[ROW * COL][2]; // To store the path
    int path_index = 0; // Path index
    while (!(cell_details[row][col].parent_i == row && cell_details[row][col].parent_j == col)) {
        path[path_index][0] = row;
        path[path_index][1] = col;
        path_index++;

        int temp_row = cell_details[row][col].parent_i;
        int temp_col = cell_details[row][col].parent_j;
        row = temp_row;
        col = temp_col;
    }

    path[path_index][0] = row;
    path[path_index][1] = col;

    for (int i = path_index; i >= 0; i--) {
        printf("-> (%d,%d) ", path[i][0], path[i][1]);
    }
    printf("\n");
}

// A* Search Algorithm
void a_star_search(int grid[][COL], int src[], int dest[]) {
    // check if src and dest are valid
    if (!is_valid(src[0], src[1]) || !is_valid(dest[0], dest[1])) {
        printf("Source or destination is invalid\n");
        return;
    }

    // check if src or dest is blocked
    if (!is_unblocked(grid, src[0], src[1]) || !is_unblocked(grid, dest[0], dest[1])) {
        printf("Source or the destination is blocked\n");
        return;
    }

    // check if src is at dest
    if (is_destination(src[0], src[1], dest)) {
        printf("We are already at the destination\n");
        return;
    }

    // create closed_list to mark block already walked
    bool closed_list[ROW][COL];
    //memset set all the element in closed_list as false
    memset(closed_list, false, sizeof(closed_list));
    // cell_details stores f g h valuses and the parent block
    Cell cell_details[ROW][COL];

    // initialize cell_details, set all value to inf and parent to [-1][-1]
    int i, j;
    for (i = 0; i < ROW; i++) {
        for (j = 0; j < COL; j++) {
            cell_details[i][j].f = FLT_MAX;
            cell_details[i][j].g = FLT_MAX;
            cell_details[i][j].h = FLT_MAX;
            cell_details[i][j].parent_i = -1;
            cell_details[i][j].parent_j = -1;
        }
    }

    // set i and j to the src, and initialize all values
    // parent of src is itself so trace path can identify
    i = src[0], j = src[1];
    cell_details[i][j].f = 0.0;
    cell_details[i][j].g = 0.0;
    cell_details[i][j].h = 0.0;
    cell_details[i][j].parent_i = i;
    cell_details[i][j].parent_j = j;

    // use the min_heap initialize the open list (cells to be visited) with the start cell
    min_heap_t* open_list = create_minHeap();
    // put the src into a node
    node_t* temp = create_node(0.0, i, j);
    //push the scr into heap
    heap_push(open_list, temp);
    
    // Initialize the flag for whether destination is found
    bool found_dest = false;

    // Main loop of A* search algorithm
    while (open_list->size > 0) {
        // Pop the cell with the smallest f value from the open list
        node_t* p = heap_pop(open_list);
        
        //#################
        //#################
        //#################
        // Mark the poped cell as visited
        //something wrong after I pop the heap, i and j numbers are weird
        i = p->row;
        printf("%d\n", i);
        j = p->column;
        printf("%d\n", j);
        closed_list[i][j] = true;

        // Process all 8 successors of this cell
        int new_i, new_j;
        double g_new, h_new, f_new;
        //iterate though the 8 neighbour of the current block
        //check each cell if they are detination
        //If not dest, update values
        for (int add_i = -1; add_i <= 1; add_i++) {
            for (int add_j = -1; add_j <= 1; add_j++) {
                // continue if i=0 && j=0, the current cell
                if (i == 0 && j == 0){
                    continue;
                }
                //new i and j are the current neighbour cell
                new_i = i + add_i;
                new_j = j + add_j;
                // If the successor is valid, unblocked, and not visited
                if (is_valid(new_i, new_j) && !closed_list[new_i][new_j] && is_unblocked(grid, new_i, new_j)) {
                    // If the cell is destination
                    if (is_destination(new_i, new_j, dest)) {
                        // Set the parent of the destination cell
                        cell_details[new_i][new_j].parent_i = i;
                        cell_details[new_i][new_j].parent_j = j;
                        printf("The destination cell is found\n");
                        trace_path(cell_details, dest);
                        found_dest = true;
                        return;
                    //
                    } else {
                        // calculate the new f value
                        g_new = cell_details[i][j].g + 1.0; // this might need improve, since Euclidean 
                        h_new = calculate_h_value(new_i, new_j, dest);
                        f_new = g_new + h_new;

                        // If the cell is not visited or the f_new value is smaller, 
                        // meaning going this way result in shorter rout
                        // add to open list and update detail
                        if (cell_details[new_i][new_j].f == FLT_MAX || cell_details[new_i][new_j].f > f_new) {
                            // Add the cell to the open list
                            node_t* temp = create_node(f_new, new_i, new_j);
                            heap_push(open_list, temp);

                            // Update the details of this cell
                            cell_details[new_i][new_j].f = f_new;
                            cell_details[new_i][new_j].g = g_new;
                            cell_details[new_i][new_j].h = h_new;
                            cell_details[new_i][new_j].parent_i = i;
                            cell_details[new_i][new_j].parent_j = j;
                        }
                    }
                }
            }
        }


    }

    if (!found_dest) {
        printf("Failed to find the destination cell\n");
    }
}

int main() {
    int grid[ROW][COL] = {
        {1, 0, 1, 1, 1, 1, 0, 1, 1, 1},
        {1, 1, 1, 0, 1, 1, 1, 0, 1, 1},
        {1, 1, 1, 0, 1, 1, 0, 1, 0, 1},
        {0, 0, 1, 0, 1, 0, 0, 0, 0, 1},
        {1, 1, 1, 0, 1, 1, 1, 0, 1, 0},
        {1, 0, 1, 1, 1, 1, 0, 1, 0, 0},
        {1, 0, 0, 0, 0, 1, 0, 0, 0, 1},
        {1, 0, 1, 1, 1, 1, 0, 1, 1, 1},
        {1, 1, 1, 0, 0, 0, 1, 0, 0, 1}
    };

    int src[] = {8, 0};
    int dest[] = {0, 0};

    a_star_search(grid, src, dest);

    return 0;
}
