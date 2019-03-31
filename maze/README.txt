Maze is a simple, in-terminal maze game. It is written in C with the help of ncurses library (which you need if you want to run it). To run the game compile it (eg. Using the provided makefile) and call it ./maze n with n being one of 3 available modes. 0 is a regular mode in which you need to reach the end of the maze. Modes 1 and 2 are graphical demonstration of depth first search and breadth first search algorithms respectively solving the maze.

In mode 0 use WSAD keys to move and q to quit the game. The players is denoted by an X symbol and the end of the maze by an E symbol. The visited parts of the maze are denoted by dots.

The size of the maze is that of the terminal window so if you want a bigger challenge just make the window bigger. 

The maze is created in a random manner and the creation process is visualised immediately after the game start. This can take a long time for a larger maze but can be toggled off by commenting out lines 36 and 37 in file maze.c. 

Below the maze the current number of moves is displayed as well as the way found by DFS and BFS algorithms (BFS will always show the optimal path, DFS might show a longer path).