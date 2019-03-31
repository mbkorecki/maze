#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "stack.h"

Stack newStack(int s)
{
	Stack st;
	st.array = malloc(s * sizeof(Cell));
	assert(st.array != NULL);
	st.top = 0;
	st.size = s;
	return st;
}

void doubleStackSize(Stack *stp)
{
	int newSize = 2 * stp->size;
	stp->array = realloc(stp->array, newSize * sizeof(Cell));
	assert(stp->array != NULL);
	stp->size = newSize;
}

void push(Cell value, Stack *stp)
{
	if (stp->top == stp->size)
	{
		doubleStackSize(stp);
	}
	stp->array[stp->top] = value;
	stp->top++;
}

int isEmptyStack(Stack st)
{
	return (st.top == 0);
}

Cell pop(Stack *stp)
{
	if (isEmptyStack(*stp))
	{
		printf("stack empty\n");
		abort();
	}
	(stp->top)--;
	return (stp->array)[stp->top];
}

void freeStack(Stack st)
{
	free(st.array);
}
