#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "solvers.h"
#include "maze.h"

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("Usage: ./maze n, where n can be 0 (no drawing), 1 (draw dfs path) or 2 (draw bfs path), \n");
		return 1;
	}
	
	initscr();
	noecho();
	curs_set(FALSE);
	int x = 1, y = 1;
	int maxX;
	int maxY;
	
	initMaze(&maxX, &maxY);
	
	WINDOW *win;
	win = newwin(2, maxX, maxY, 0);
	wrefresh(win);

	Cell *maze[maxX];
	int *mazeWalls[maxX];

	for (int i = 0; i < maxX; i++)
	{
		maze[i] = malloc(maxY * sizeof(Cell));
		mazeWalls[i] = malloc(maxY * sizeof(int));
	}

	for (int i = 0; i < maxX; i += 1)
	{
		for (int j = 0; j < maxY; j += 1)
		{
			mazeWalls[i][j] = 0;
			maze[i][j].visited = 0;
		}
	}

	for (int i = 1; i < maxX; i += 2)
	{
		for (int j = 1; j < maxY; j += 2)
		{
			mazeWalls[i][j] = 1;
			maze[i][j].x = i;
			maze[i][j].y = j;
		}
	}
	int unvisited = (maxX * maxY) / 2;

	time_t t;
	srand((unsigned) time(&t));

	Stack cellStack = newStack((maxX / 2) * (maxY / 2));

	int startingX = rand() % (maxX - 1);
	int startingY = rand() % (maxY - 1);
	if (!(startingX % 2))
		startingX++;
	if (!(startingY % 2))
		startingY++;
	
	makeMaze(maze[startingX][startingY], maze, &cellStack, mazeWalls, maxX, maxY, &unvisited);
	mvprintw(y, x, "X");
	mvprintw(maxY - 2, maxX - 2, "E");
	drawMaze(mazeWalls, maxX, maxY);
	refresh();

	for (int i = 1; i < maxX; i += 1)
	{
		for (int j = 1; j < maxY; j += 1)
		{
			maze[i][j].visited = 0;
			maze[i][j].x = i;
			maze[i][j].y = j;
		}
	}

	freeStack(cellStack);

	int moves = 0;
	int dfsPath = dfsSolver(mazeWalls, maxX, maxY, *argv[1] - '0');
	int bfsPath = bfsSolver(mazeWalls, maxX, maxY, *argv[1] - '0');
	
	int c = getch();

	mvprintw(y, x, "X");
	while (mazeWalls[x][y] && c != 'q')
	{
		mvprintw(maxY, 1, "MOVES:%d", moves);
		mvprintw(maxY, 20, "DFS:%d", dfsPath);
		mvprintw(maxY, 30, "BFS:%d", bfsPath);

		mvprintw (y, x, ".");

		if (c == 'a' && x > 1 && mazeWalls[x - 1][y])
		{
			x--;
			moves++;
		}
		else if (c == 'w' && y > 1 && mazeWalls[x][y - 1])
		{
			y--;
			moves++;
		}
		else if (c == 's' && y < maxY - 2 && mazeWalls[x][y + 1])
		{
			y++;
			moves++;
		}
		else if (c == 'd' && x < maxX - 2 && mazeWalls[x + 1][y])
		{
			x++;
			moves++;
		}
		else if (!neighbours(x, y, mazeWalls))
		{
			mvprintw(y, x, "X");
			c = getch();
		}
		if (neighbours(x, y, mazeWalls))
		{
			mvprintw(y, x, "X");
			c = getch();
			mvprintw(y, x, ".");
		}

		if (x == maxX - 2 && y == maxY - 2)
		{
			freeMaze(maze, mazeWalls, maxX);
			endwin();
			printf("YOU WIN! MOVES: %d\n", moves);
			return 1;
		}
		mvprintw(y, x, "X");
		refresh();
	}
	freeMaze(maze, mazeWalls, maxX);
	endwin();
	printf("YOU LOSE!\n");
	return 0;
}
