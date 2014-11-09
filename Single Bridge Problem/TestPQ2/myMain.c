/*
 * myMain.c
 *
 *  Created on: Oct 1, 2014
 *      Author: Mostaffa
 */
#include "PriorityQ.h"
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include <time.h>

double RandExp(double M)
{
	double urand;	// uniformly distributed random number [0,1)
	urand = ((double) rand ()) / (((double) RAND_MAX)+1.0);	// avoid value 1.0
	return (-M * log(1.0-urand));
}
/*
 * put N elements in the priority Q.
*/
void fillPQ(Event* pq, int N) {
	int i;
	for (i = 0; i < N ; i++) {
		Event* e = (Event*) malloc(sizeof(Event));
		e->timeStamp = RandExp(10);
		addQ(pq, e);
	}
}

int main(void) {
	clock_t startTime;
	clock_t endTime;
	// declare the function

	printf("Start making the priority Queue\n");
	Event* pq = makePrioQ();
	fillPQ(pq, 10000);
    //printList(pq); // print the priority queue*/

	// Now remove and add (a series of holds)
	int i;
	int iteration = 1000000;
    startTime = clock();
	for (i = 1; i < iteration; i++) {
		Event* e0 = (Event*) malloc(sizeof(Event));
		Event* e = removeQ(pq);
		double ts = e->timeStamp;
		e0->timeStamp = ts + RandExp(1);
		addQ(pq, e0);
	}
	printList(pq);
	endTime = clock();
    double duration = (double)endTime - (double)startTime;
    printf("total duration%f\n", duration);
    printf("average time%f\n", duration/iteration);

return 0;
}
