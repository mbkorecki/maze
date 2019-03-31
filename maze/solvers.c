#include "solvers.h"

int dfsSolver(int *mazeGrid[], int maxX, int maxY, int draw)
{
	Stack stack = newStack(100);
	int visited[maxX][maxY];

	for (int i = 0; i < maxX; i++)
	{
		for (int j = 0; j < maxY; j++)
		{
			visited[i][j] = 0;
		}
	}
  
	Cell position;
	position.x = 1;
	position.y = 1;
	position.visited = 0;

	int goalX = maxX - 2;
	int goalY = maxY - 2;

	push(position, &stack);

	while (position.x != goalX || position.y != goalY)
	{
		if (draw == 1)
		{
			usleep(5000);
			if (rand()%2)
				mvprintw(position.y, position.x, "0");
			else
				mvprintw(position.y, position.x, "1");
			refresh();
		}
		position = pop(&stack);

		if (position.x + 1 < maxX && mazeGrid[position.x + 1][position.y] == 1)
		{
			Cell nextPosition = position;
			nextPosition.x++;
			nextPosition.visited++;
			if (visited[nextPosition.x][nextPosition.y] != 1)
				push(nextPosition, &stack);
		}
		if (position.x - 1 > 0 && mazeGrid[position.x - 1][position.y] == 1)
		{
			Cell nextPosition = position;
			nextPosition.x--;
			nextPosition.visited++;
			if (visited[nextPosition.x][nextPosition.y] != 1)
				push(nextPosition, &stack);
		}
		if (position.y + 1 < maxY && mazeGrid[position.x][position.y + 1] == 1)
		{
			Cell nextPosition = position;
			nextPosition.y++;
			nextPosition.visited++;
			if (visited[nextPosition.x][nextPosition.y] != 1)
				push(nextPosition, &stack);
		}
		if (position.y - 1 > 0 && mazeGrid[position.x][position.y - 1] == 1)
		{
			Cell nextPosition = position;
			nextPosition.y--;
			nextPosition.visited++;
			if (visited[nextPosition.x][nextPosition.y] != 1)
				push(nextPosition, &stack);
		}
		visited[position.x][position.y] = 1;
	}
	freeStack(stack);
	return position.visited;
}




int bfsSolver(int *mazeGrid[], int maxX, int maxY, int draw)
{
	Queue queue = newQueue(100);
	int visited[maxX][maxY];

	for (int i = 0; i < maxX; i++)
	{
		for (int j = 0; j < maxY; j++)
		{
			visited[i][j] = 0;
		}
	}
  
	Cell position;
	position.x = 1;
	position.y = 1;
	position.visited = 0;

	int goalX = maxX - 2;
	int goalY = maxY - 2;

	enqueue(position, &queue);

	while ((position.x != goalX || position.y != goalY) && !isEmptyQueue(queue))
	{
		if (draw == 2)
		{
			usleep(5000);
			if (rand()%2)
				mvprintw(position.y, position.x, "0");
			else
				mvprintw(position.y, position.x, "1");
			refresh();
		}
		position = dequeue(&queue);

		if (position.x + 1 < maxX && mazeGrid[position.x + 1][position.y] == 1)
		{
			Cell nextPosition = position;
			nextPosition.x++;
			nextPosition.visited++;
			if (visited[nextPosition.x][nextPosition.y] != 1)
				enqueue(nextPosition, &queue);
		}
		if (position.x - 1 > 0 && mazeGrid[position.x - 1][position.y] == 1)
		{
			Cell nextPosition = position;
			nextPosition.x--;
			nextPosition.visited++;
			if (visited[nextPosition.x][nextPosition.y] != 1)
				enqueue(nextPosition, &queue);
		}
		if (position.y + 1 < maxY && mazeGrid[position.x][position.y + 1] == 1)
		{
			Cell nextPosition = position;
			nextPosition.y++;
			nextPosition.visited++;
			if (visited[nextPosition.x][nextPosition.y] != 1)
				enqueue(nextPosition, &queue);
		}
		if (position.y - 1 > 0 && mazeGrid[position.x][position.y - 1] == 1)
		{
			Cell nextPosition = position;
			nextPosition.y--;
			nextPosition.visited++;
			if (visited[nextPosition.x][nextPosition.y] != 1)
				enqueue(nextPosition, &queue);
		}
		visited[position.x][position.y] = 1;
	}
	freeQueue(queue);
	return position.visited;
}
