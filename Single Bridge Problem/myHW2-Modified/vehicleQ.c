/*
 * vehicleQ.c
 *
 *  Created on: Sep 30, 2014
 *      Author: Mostaffa
 */
#include<stdio.h>
#include <stdlib.h>
#include "vehicleQ.h"


void insert(Vehicle** head, Vehicle** tail, Vehicle* veh) {
	veh->next = NULL;
	if (*head == NULL) {
		*head = veh;
		*tail = veh;
	}
	else {
		(*tail)->next = veh;
		*tail = veh;
	}
}
Vehicle* delete(Vehicle** head, Vehicle** tail) {
	Vehicle* veh;
	if (*head == NULL) {
		printf("the queue is empty when attempting to remove from the vehicle queue");
		exit(1);
	}
	    veh = *head;
	    *head = veh->next;
	if (*head == NULL)
        *tail = NULL;
	return (veh);
}
/*
int isEmpty(Vehicle** head) {
	return (head == NULL);
}

void printQ(Vehicle** head) {
	    while (! isEmpty(*head)) {
    	printf("%d---id is---", head->id);
    	*head = head->next;
    }
}*/

