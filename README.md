# Sudoku-Solver
Sudoku solver using QT
## Introduction
Two algorithms are implemented to solve sudoku problems, which **are depth-first search** (**DFS**) and **Dancing Links X** (**DLX**).
### DFS
DFS tries possible numbers for each blank spot on the board, and recursively tries the remaining blank spots. If the algorithm fails at a certain blank spot, it will backtrack to the previous position and continue to run. The algorithm will run until it finds a solution.

Since solutions are not easy to find in some specific cases, it will take a long time to run the algorithm, just like DFS will walk into many dead ends when finding a way out of a maze.
### DLX
DLX will take less time than DFS algorithm to solve this problem, using a data structure called [**dancing links**](https://en.wikipedia.org/wiki/Dancing_Links).
