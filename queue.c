#include <stdio.h>
#include <stdlib.h>
#include "element.h"
#include "stack.h"
#include "queue.h"


/******************
* Function Name: initQueue
* Input: None
* Output: Queue*
* Function Operation: The function create struct with two pointers by dynamic allocation,
					calling to function "initStack" to create two struct by dynamic allocation,
					create stack inside by dynamic allocation, and return pointer to struct
******************/

Queue* initQueue() {

	Queue* queue = malloc(sizeof(Queue));
	if (queue == NULL) {
		printf("Heap memory error!\nFile: %s; Function: %s;\n", __FILE__, __func__);
		return NULL;
	}
	queue->s1 = initStack();
	if (queue->s1 == NULL) {
		free(queue);
		printf("Heap memory error!\nFile: %s; Function: %s;\n", __FILE__, __func__);
		return NULL;
	}
	queue->s2 = initStack();
	if (queue->s2 == NULL) {
		free(queue);
		printf("Heap memory error!\nFile: %s; Function: %s;\n", __FILE__, __func__);
		return NULL;
	}

	return queue;
}

/******************
* Function Name: destroyQueue
* Input: Queue*
* Output: None
* Function Operation: The function releases the allocated memory
******************/

void destroyQueue(Queue* queue) {

	destroyStack(queue->s1);
	destroyStack(queue->s2);
	free(queue);
}

/******************
* Function Name: isQueueEmpty
* Input: Queue*
* Output: int
* Function Operation: The function return if the both stacks are empty or not
******************/

int isQueueEmpty(Queue* queue) {

	if (isStackEmpty(queue->s1) && isStackEmpty(queue->s2))
		return 1;
	else
		return 0;
}

/******************
* Function Name: lenOfQueue
* Input: Queue*
* Output: int
* Function Operation: The function return the number of elements that in the queue
******************/

int lenOfQueue(Queue* queue) {

	return queue->s1->topIndex + queue->s2->topIndex + 2;
}

/******************
* Function Name:
* Input: None
* Output: None
* Function Operation: The function return the size of the both stacks
******************/

int capacityOfQueue(Queue* queue) {

	return queue->s1->size + queue->s2->size;
}

/******************
* Function Name: enqueue
* Input: Queue*, Element
* Output: None
* Function Operation: The function gets element and push it to the queue
******************/

void enqueue(Queue* queue, Element element) {

	push(queue->s1, element);
}

/******************
* Function Name: stackToStack
* Input: Queue*
* Output: None
* Function Operation: The function moves the elements from one stack to other stack,
					by calling to functions "pop" and "push"
******************/

void stackToStack(Queue* queue) {

	if (isStackEmpty(queue->s2)) {

		for (int i = queue->s1->topIndex; i >= 0; i--) {
			Element element = pop(queue->s1);
			push(queue->s2, element);
		}
	}
}

/******************
* Function Name: dequeue
* Input: Queue*
* Output: Element
* Function Operation: the functin takes element out from the top of the queue, and full the stack 's2' if si empty
******************/

Element dequeue(Queue* queue) {

	stackToStack(queue);

	return pop(queue->s2);
}

/******************
* Function Name: peek
* Input: Queue*
* Output: Element
* Function Operation: he function return the element that in the top of the queue, but not takes it out
******************/

Element peek(Queue* queue) {

	stackToStack(queue);

	return top(queue->s2);
}