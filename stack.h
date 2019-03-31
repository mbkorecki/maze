#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef struct Cell
{
	int x, y;
	int visited;
}Cell;

typedef struct Stack
{
	Cell *array;
	int top;
	int size;
}Stack;

Stack newStack(int s);
void doubleStackSize(Stack *stp);
void push(Cell value, Stack *stp);
int isEmptyStack(Stack st);
Cell pop(Stack *stp);
void freeStack(Stack st);

#endif
