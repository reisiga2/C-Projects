/*
 * VertexNode.h
 *
 *  Created on: Sep 24, 2014
 *      Author: Mostafa
 */

#ifndef PRIORITYQ_H_
#define PRIOIRTYQ_H_

#include "vertex.h"

Vertex* makePrioQ(); // sets memory for an Vertex and sets its fields.
void addQ(Vertex* prioQ, Vertex* newVertex); // adds an Vertex to the list based on its priority
Vertex* removeQ(Vertex* prioQ); //removes and Vertex with smallest distance
Vertex* removeQVertex(Vertex* pq, int id); // remove a particular node with a given id from the priority queue.
int size(Vertex* pq); // finds the size of the list
void printList(Vertex* pq); // prints the list

#endif
