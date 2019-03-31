#include "maze.h"

void initMaze(int *ptrX, int *ptrY)
{
	int maxX, maxY;
	getmaxyx(stdscr, maxY, maxX);
	
	if (!(maxY % 2))
		--maxY;
	else
		maxY -= 2;
	if (!(maxX % 2))
		--maxX;

	for (int i = 0; i < maxY; i++)
	{
		if (!(i % 2))
			mvhline(i, 0, ACS_HLINE, maxX);
	}
	for (int i = 0; i < maxX; i++)
	{
		if (!(i % 2))
			mvvline(0, i, ACS_VLINE, maxY);
	}
	customBox(maxX, maxY);
	refresh();
	*ptrX = maxX;
	*ptrY = maxY;
}

void makeMaze(Cell current, Cell *maze[], Stack *cellStack, int *mazeWalls[], int maxX, int maxY, int *unvisited)
{
	current.visited++;
	while (*unvisited > 0)
	{
		usleep(2500);
		refresh();
		
		int neighbours = 0;
		int moves[4];
		--(*unvisited);

		if (((current.y + 2) < maxY) && (maze[current.x][current.y + 2].visited == 0))
		{
			moves[neighbours] = 1;
			neighbours++;
		}
		if (((current.y - 2) > 0) && (maze[current.x][current.y - 2].visited == 0))
		{
			moves[neighbours] = 2;
			neighbours++;
		}
		if (((current.x + 2) < maxX) && (maze[current.x + 2][current.y].visited == 0))
		{
			moves[neighbours] = 3;
			neighbours++;
		}
		if (((current.x - 2) > 0) && (maze[current.x - 2][current.y].visited == 0))
		{
			moves[neighbours] = 4;
			neighbours++;
		}
		if (neighbours != 0)
		{
			push(current, cellStack);
			int nextMove = moves[rand() % neighbours];
			switch (nextMove)
			{
			case 1:
				mvprintw(current.y + 1, current.x, " ");
				maze[current.x][current.y + 2].visited++;
				mazeWalls[current.x][current.y + 1] = 1;
				makeMaze(maze[current.x][current.y + 2], maze, cellStack, mazeWalls, maxX, maxY, unvisited);
				break;
			case 2:
				mvprintw(current.y - 1, current.x, " ");
				maze[current.x][current.y - 2].visited++;
				mazeWalls[current.x][current.y - 1] = 1;
				current = maze[current.x][current.y - 2];
				break;
			case 3:
				mvprintw(current.y, current.x + 1, " "); // for the version which draws the labirynth in real time
				maze[current.x + 2][current.y].visited++;
				mazeWalls[current.x + 1][current.y] = 1;
				current = maze[current.x + 2][current.y];
				break;
			case 4:
				mvprintw(current.y, current.x - 1, " ");
				maze[current.x - 2][current.y].visited++;
				mazeWalls[current.x - 1][current.y] = 1;
				current = maze[current.x - 2][current.y];
				break;
			}
		}
		else if (!isEmptyStack(*cellStack))
		{
			current = pop(cellStack);
		}
	}
}

void drawMaze(int *mazeWalls[], int maxX, int maxY)
{
	for (int i = 0; i < maxX ; i++)
	{
		if (mazeWalls[i][1] == 0)
			mvaddch(0, i, ACS_TTEE);
		else if (mazeWalls[i][maxY - 2] == 0)
			mvaddch(maxY - 1, i, ACS_BTEE);
	}

	for (int i = 0; i < maxY ; i++)
	{
		if (mazeWalls[1][i] == 0)
			mvaddch(i, 0, ACS_LTEE);
		else if (mazeWalls[maxX - 2][i] == 0)
			mvaddch(i, maxX - 1, ACS_RTEE);
	}

	mvaddch(maxX - 1, maxY - 1, ACS_LRCORNER);
	mvaddch(maxY - 1, 0, ACS_LLCORNER);
	mvaddch(0, maxX - 1, ACS_URCORNER);
	mvaddch(0, 0, ACS_ULCORNER);


	for (int i = 1; i < maxX - 1 ; i++)
	{
		for (int j = 1; j < maxY - 1; j++)
		{
			if (mazeWalls[i][j] == 0)
			{

				if (mazeWalls[i - 1][j] == 0 || mazeWalls[i + 1][j] == 0)
					mvaddch(j, i, ACS_HLINE);
				else if (mazeWalls[i][j - 1] == 0 || mazeWalls[i][j + 1] == 0)
					mvaddch(j, i, ACS_VLINE);

				if (mazeWalls[i][j - 1] == 0 && mazeWalls[i][j + 1] == 0 &&
				    mazeWalls[i + 1][j] == 0 && mazeWalls[i - 1][j] == 0)
					mvaddch(j, i, ACS_PLUS);
				else if (mazeWalls[i][j + 1] == 0 && mazeWalls[i + 1][j] == 0 &&
				         mazeWalls[i][j - 1] == 0)
					mvaddch(j, i, ACS_LTEE);
				else if (mazeWalls[i][j + 1] == 0 && mazeWalls[i - 1][j] == 0 &&
				         mazeWalls[i][j - 1] == 0)
					mvaddch(j, i, ACS_RTEE);
				else if (mazeWalls[i - 1][j] == 0 && mazeWalls[i + 1][j] == 0 &&
				         mazeWalls[i][j + 1] == 0)
					mvaddch(j, i, ACS_TTEE);
				else if (mazeWalls[i - 1][j] == 0 && mazeWalls[i + 1][j] == 0 &&
				         mazeWalls[i][j - 1] == 0)
					mvaddch(j, i, ACS_BTEE);
				else if (mazeWalls[i - 1][j] == 0 && mazeWalls[i][j - 1] == 0)
					mvaddch(j, i, ACS_LRCORNER);
				else if (mazeWalls[i + 1][j] == 0 && mazeWalls[i][j - 1] == 0)
					mvaddch(j, i, ACS_LLCORNER);
				else if (mazeWalls[i - 1][j] == 0 && mazeWalls[i][j + 1] == 0)
					mvaddch(j, i, ACS_URCORNER);
				else if (mazeWalls[i + 1][j] == 0 && mazeWalls[i][j + 1] == 0)
					mvaddch(j, i, ACS_ULCORNER);
			}
		}
	}
}

void customBox(int maxX, int maxY)
{
	mvhline(0, 0, ACS_HLINE, maxX);
	mvhline(maxY - 1, 0, ACS_HLINE, maxX);

	mvvline(0, maxX - 1, ACS_VLINE, maxY);
	mvvline(0, 0, ACS_VLINE, maxY);

	mvaddch(0, 0, ACS_ULCORNER);
	mvaddch(0, maxX - 1, ACS_URCORNER);
	mvaddch(maxY - 1, 0, ACS_LLCORNER);
	mvaddch(maxY - 1, maxX - 1, ACS_LRCORNER);
}


int neighbours(int x, int y, int *mazeWalls[])
{
	return (mazeWalls[x][y - 1] + mazeWalls[x][y + 1] + mazeWalls[x + 1][y] + mazeWalls[x - 1][y]) > 2;
}


void freeMaze(Cell *maze[], int *mazeWalls[], int maxX)
{
	for (int i = 0; i < maxX; i++)
	{
		free(maze[i]);
		free(mazeWalls[i]);
	}
}
