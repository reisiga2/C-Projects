/*
 * PriorityQ.c
 *
 *  Created on: Sep 23, 2014
 *      Author: Mostafa
 */
#include<stdio.h>
#include <stdlib.h>
#include "priorityQ.h"
#include "vertex.h"

Vertex* makePrioQ() {
	Vertex* pq = (Vertex*)malloc(sizeof(Vertex)); // allocates memory for a dummy node.
	if (pq == NULL) {
		printf("ERROR! out of memory");
		exit(1);
	}
	pq->next = NULL;
	pq->distance = 0;
	return pq;
}

void addQ(Vertex* pq, Vertex* newVertex) {
    Vertex* temp = pq;
	while (temp->next != NULL && (newVertex->distance > temp->next->distance)) {
    		temp = temp->next;
   	}
    newVertex->next = temp->next; // set the next event of the new event
    temp->next = newVertex; // set the new event as the next field of its previous event
    //free(temp);
}


Vertex* removeQ(Vertex* pq) {
	if (pq->next == NULL) { // checks if the list is empty or not. if the list is empty then there is nothing to remove.
		printf("Queue is empty");
		exit(1);
	} else {
		Vertex* temp = pq->next;
		pq->next = temp->next;
		temp->next = NULL;
		return temp;
	}
}

Vertex* removeQVertex(Vertex* pq, int id) {
	if (pq->next == NULL) {
		printf("Queue is empty");
		exit(1);
	} else {
		Vertex* temp = pq;
		while (temp->next != NULL && temp->next->id != id) {
			temp = temp->next;
		}
		if (temp->next == NULL) {
		    fprintf(stderr, "No such a vertex in priority queue");
		    exit(1);
		} else {
			Vertex* nextOfCurr = temp->next;
			temp->next = nextOfCurr->next;
			nextOfCurr->next = NULL;
			return nextOfCurr;
		}
	}
	return NULL;
}

int size(Vertex* pq) {
    int size = 0;
    while(pq->next != NULL) {
    	pq = pq->next;
    	size = size + 1;
    }
    return size; // size of the list.
}

void printList(Vertex* pq) {

    while(pq->next != NULL) {
    	pq = pq->next;
    	printf("%d, %d\n", pq->id, pq->distance);
    }
}



