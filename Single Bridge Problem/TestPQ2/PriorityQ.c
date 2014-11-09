/*
 * PriorityQ.c
 *
 *  Created on: Sep 23, 2014
 *      Author: Mostafa
 */
#include<stdio.h>
#include <stdlib.h>
#include "PriorityQ.h"


Event* makePrioQ() {
	Event* pq = (Event*)malloc(sizeof(Event)); // allocates memory for a dummy node.
	if (pq == NULL) {
		printf("ERROR! out of memory");
		exit(1);
	}
	pq->next = NULL;
	pq->timeStamp = 0;
	return pq;
}

void addQ(Event* pq, Event* newEvent) {
    Event* temp = pq;
	while (temp->next != NULL && (newEvent->timeStamp > temp->next->timeStamp)) {
    		temp = temp->next;
   	}
    newEvent->next = temp->next; // set the next event of the new event
    temp->next = newEvent; // set the new event as the next field of its previous event
    //free(temp);
}


Event* removeQ(Event* pq) {
	if (pq->next == NULL) { // checks if the list is empty or not. if the list is empty then there is nothing to remove.
		printf("Queue is empty");
		exit(1);
	} else {
		Event* temp = pq->next;
		pq->next = temp->next;
		temp->next = NULL;
		return temp;
	}
}

int size(Event* pq) {
    int size = 0;
    while(pq->next != NULL) {
    	pq = pq->next;
    	size = size + 1;
    }
    return size; // size of the list.
}

void printList(Event* pq) {

    while(pq->next != NULL) {
    	pq = pq->next;
    	printf("%f\n", pq->timeStamp);
    }
}



