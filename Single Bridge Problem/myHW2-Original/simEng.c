/*
 * simEng.c
 *
 *  Created on: Sep 27, 2014
 *      Author: Mostafa
 */

#include "PriorityQ.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


Event* futureEventList = NULL;
double currTime = 0;

void Schedule(double ts, void* data, void (*cb)(void*)) {
	Event* newEvent = (Event*)malloc(sizeof(Event));
	if (futureEventList == NULL) {
		printf("future event list was null, so I make one.\n"); //////////////// to be removed
		futureEventList = makePrioQ();
	}
	if (newEvent == NULL) {
		printf("error in scheduling. There is no memory left"); //////////////// to be removed
		exit(1);
	}
	newEvent->timeStamp = ts;
	newEvent->data = data;
	newEvent->callback = cb;
	newEvent->next = NULL; // it might not be needed.
	addQ(futureEventList, newEvent);
}

void RunSim(void) {
	if (futureEventList == NULL) {
		printf("future event list was null, so I make one.\n");
		futureEventList = makePrioQ();
	}
	while(size(futureEventList) != 0) {
	    Event* currEvent = removeQ(futureEventList);
	    currTime = currEvent->timeStamp;
		//printList(futureEventList); // Just for testing
		currEvent->callback(currEvent->data);
		//free(currEvent);
	}
	printf("I am now out of the while loop of RunSIm:))\n"); //////////////// to be removed
}

double CurrentTime(void) {
    return currTime;
}
