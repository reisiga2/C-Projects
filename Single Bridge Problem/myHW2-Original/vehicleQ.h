/*
 * vehicleQ.h
 *
 *  Created on: Sep 30, 2014
 *      Author: Mostaffa
 */

#ifndef VEHICLEQ_H_
#define VEHICLEQ_H_

typedef struct Vehicle {
	int id;
	int direction; // equals 1 if it travels to north and 2 if travels to south.
	double startWait;
	double endWait;
	struct Vehicle* next;
} Vehicle;

void insert(Vehicle** head, Vehicle** tail, Vehicle* veh);
Vehicle* delete(Vehicle** head, Vehicle** tail);
//int isEmpty(Vehicle** head);
//void printQ(Vehicle** head);


#endif /* VEHICLEQ_H_ */
