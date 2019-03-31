#ifndef MAZE_H
#define MAZE_H

#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "stack.h"

void initMaze(int *maxX, int *maxY);
void drawMaze(int *mazeWalls[], int maxX, int maxY);
void customBox(int maxX, int maxY);
void makeMaze(Cell current, Cell *maze[], Stack *cellStack, int *mazeWalls[], int maxX, int maxY, int *unvisted);
int neighbours(int x, int y, int *mazeWalls[]);
void freeMaze(Cell *maze[], int *mazeWalls[], int maxX);

#endif

            
