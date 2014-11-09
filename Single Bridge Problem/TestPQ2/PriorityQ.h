/*
 * EventNode.h
 *
 *  Created on: Sep 24, 2014
 *      Author: Mostaffa
 */

#ifndef PRIORITYQ_H_
#define PRIOIRTYQ_H_


typedef struct Event {
	double timeStamp;
	struct Event* next;
} Event;

Event* makePrioQ(); // sets memory for an event and sets its fields.
void addFront(Event* pq, double time); // adds an Event to the front of a list
void addQ(Event* prioQ, Event* newEvent); // adds an event to the list based on its priority (timestamp)
Event* removeQ(Event* prioQ); //removes and event with smallest timestamp
int size(Event* pq); // finds the size of the list
void printList(Event* pq); // prints the list

#endif
