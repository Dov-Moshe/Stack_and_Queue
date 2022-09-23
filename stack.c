#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "element.h"
#include "stack.h"


/******************
* Function Name: initStack
* Input: None
* Output: Stack*
* Function Operation: The function create struct by dynamic allocation, create stack inside by dynamic allocation,
					and return pointer to struct
******************/

Stack* initStack() {

	// create the stack
	Stack* stack = malloc(sizeof(Stack));
	if (stack == NULL) {
		printf("Heap memory error!\nFile: %s; Function: %s;\n", __FILE__, __func__);
		return NULL;
	}

	// create the content 
	stack->content = malloc(sizeof(Element));
	if (stack->content == NULL) {
		printf("Heap memory error!\nFile: %s; Function: %s;\n", __FILE__, __func__);
		free(stack);
		return NULL;
	}

	// update of size and topIndex
	stack->topIndex = -1;
	stack->size = 1;

	return stack;
}

/******************
* Function Name: destroyStack
* Input: Stack*
* Output: None
* Function Operation: The function releases the allocated memory
******************/

void destroyStack(Stack* stack) {
	free(stack->content);
	free(stack);
}

/******************
* Function Name: isStackEmpty
* Input: None
* Output: None
* Function Operation: The function return if the stack is empty or not
******************/

int isStackEmpty(Stack* stack) {

	if (stack->topIndex == -1)
		return 1;
	else
		return 0;
}

/******************
* Function Name: lenOfStack
* Input: Stack*
* Output: int
* Function Operation: The function return the number of elements that in the stack
******************/

int lenOfStack(Stack* stack) {

	return stack->topIndex+1;
}

/******************
* Function Name: capacityOfStack
* Input: Stack*
* Output: int
* Function Operation: The function return the size of the stack
******************/

int capacityOfStack(Stack* stack) {

	return stack->size;
}

/******************
* Function Name: push
* Input: Stack*, Element
* Output: None
* Function Operation: The function gets element, push it to the stack, and increase the allocation size if necessary
******************/

void push(Stack* stack, Element element) {

		assert(stack->size > stack->topIndex + 1);

		stack->topIndex++;
		stack->content[stack->topIndex] = element;

		if (stack->size == stack->topIndex + 1) {

			// to increase the allocation, and seve it in temp pinter for case the allocation dosen't succeed 
			Element* temp = realloc(stack->content, stack->size * 2);

			if (temp == NULL)
				printf("Heap memory error!\nFile: %s; Function: %s;\n", __FILE__, __func__);
			else {
				stack->size = stack->size * 2;
				stack->content = temp;
			}
		}
}

/******************
* Function Name: pop
* Input: Stack*
* Output: Element
* Function Operation: The function takes out the element that in the top of the stack,
					decreases the allocation size if necessary and return the element
******************/

Element pop(Stack* stack) {

	if (stack->size / 2 == stack->topIndex + 1) {

		Element* temp = realloc(stack->content, stack->size / 2);

		if (temp == NULL)
			printf("Heap memory error!\nFile: %s; Function: %s;\n", __FILE__, __func__);
		else {
			stack->size = stack->size / 2;
			stack->content = temp;
		}
	}

	Element element = stack->content[stack->topIndex];
	stack->topIndex--;

	return element;
}

/******************
* Function Name: top
* Input: Stack*
* Output: Element
* Function Operation: The function return the element that in the top of the stack, but not takes it out
******************/

Element top(Stack* stack) {

	return stack->content[stack->topIndex];
}

/******************
* Function Name: printStack
* Input: Stack*
* Output: None
* Function Operation: The function prints the elements that in the stack
******************/

void printStack(Stack* stack) {

	for (int i = stack->topIndex; i >= 0; i--) {
		Element c = stack->content[i];
		printf("%d: ", i+1);
		printElement(c);
		printf("\n");
	}
}