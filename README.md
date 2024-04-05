# CS5008_project

This is the final project of 24Spring CS5008, createed by: Kevin Yu, Danny Liao, and Mingzhe Ou

# A* Algorithm Implementation

This repository contains an implementation of the A* (A-star) algorithm, a popular pathfinding algorithm used in various fields, including robotics, video games, and artificial intelligence.

## About A* Algorithm

A* is a heuristic search algorithm that finds the shortest path between a given start node and a target node in a weighted graph. It is widely used due to its efficiency and optimality under certain conditions. The algorithm combines elements of both uniform cost search and greedy best-first search.

### Key Features:
- **Admissibility**: A* guarantees to find the shortest path if certain conditions are met, including the admissibility of the heuristic function used.
- **Completeness**: A* is complete if the search space is finite.
- **Optimality**: A* is optimal if the heuristic function is admissible and the cost function is non-negative.

## Project Structure

- **`astar.c`**: Contains the implementation of the A* algorithm.
- **`heapq.h`**: Contains the data structure to make A* easier to implement.
- **`README.md`**: This file, providing an overview of the project and algorithm.

## Usage

To use the A* algorithm in your project:

1. Create a graph representation of your problem domain in the main function in "astar.c".
2. Define heuristic functions and cost functions as needed. (currently using the Euclidean approach)
3. Compile and run!
