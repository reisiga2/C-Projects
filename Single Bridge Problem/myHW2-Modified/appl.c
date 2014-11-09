/*

 * appl.c
 *
 *  Created on: Sep 27, 2014
 *      Author: Mostafa
 */

// simulation parameters
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "vehicleQ.h"
#include "simEng.h"

#define DB	1  //Flag set to 1 to print debugging statements
#define nbRate 10.0 //arrival rate of northbound vehicles
#define sbRate 10.0 //arrival rate of southbound vehicles
#define enterTime 2.0 // time that takes a vehicle enter the bridge
#define compTime 30.0 // total time that take for a vehicle to enter and traverse the bridge

// state variables for the system
clock_t StartTime, EndTime;
double simDuration = 14400;  // maximum time that the simulation runs in seconds.
int nDepN = 0; // total number of Departures for North
int nDepS = 0;  // total number of Departures for south
int bridgeState = 0; // set the value to 1 for north direction and 2 for south direction and zero for empty.
double totalWaitTimeNorth = 0;
double totalWaitTimeSouth = 0;
int nAtNorthEnt = 0;
int nAtSouthEnt = 0;
int numOnBridge = 0;
int numOfEvents = 0;

int numOutOfQNorth = 0; // counts how many vehicles got out of the north queue,
                        // it will be incremented when a vehicle deleted from queue. it will be reset when the bridge status chage
int numOutOfQSouth = 0; // counts how many vehicles got out of the north queue
int maxExitQ = 10; // maximum number of vehicles that are allowed to exit a queue
//////////////////////////////////////////////////////
// initiate queue on the south and north
/////////////////////////////////////////////////////

Vehicle* southHead = NULL;
Vehicle* southTail = NULL;
Vehicle* northHead = NULL;
Vehicle* northTail = NULL;

//////////////////////////////////////////////////
// Event data structures
//////////////////////////////////
 typedef enum {ARRIVAL_NORTH, ARRIVAL_SOUTH, DONEENTER_NORTH, DONEENTER_SOUTH, DEPARTURE_NORTH, DEPARTURE_SOUTH} EventType;
 typedef struct EventData {
    EventType TypeOfEvent;
    union {
    	struct {
    		int vehID; // Id assigned to the arrival vehicle
    		int direction; // direction is assigned to arriving vehicle
    	} vehicleArrival;
    	struct {
    		Vehicle* veh;
    	} doneEntering;
    	struct {
    		Vehicle* v;
    	} vehicleDeparture;
    } EventParam;
} EventData;

////////////////////////////////////////////////////////////
// function prototypes
///////////////////////////////////////////////
 void arrivalNorth(EventData *e);		// car arrival event
 void arrivalSouth(EventData *e);
 void doneEnteringSouth(EventData *e);	// car entrance event
 void doneEnteringNorth(EventData *e);
 void departureNorth(EventData *e);		// car departure event
 void departureSouth(EventData *e);
 double randExp(double m);
//////////////////////////////////////////////////////////////////////////
 ////////////////////////////////////////////////////////////////////
/*
 * generates a random number from an exponential distribution.
 * It considers the direction of the vehicle and uses
 * its corresponding average interarrival time.
 */
 double randExp(double m) {
	 double urand;
	 urand = ((double) rand ()) / (((double) RAND_MAX)+1.0);
	 return (-m * log(1.0 - urand));
 }

 ///////////////////////////////////////////////////////////////////////////////
 /*
  * generate a vehicle based on the input data,
  * schedule next arrival on the same direction of the bridge,
  * schedule the time when the vehicle finish entering the bridge, or
  * put the vehicle in its corresponding queue.
  */
 void arrivalNorth(EventData *e) {
    EventData* data; // data that will be used to schedule other events.
	Vehicle* v; // vehicle that will be arrived
    double ts; // timestamp

    if (e->TypeOfEvent != ARRIVAL_NORTH) { // give an error if the event type does not match
    	fprintf (stderr, "Unexpected event type in Arrival north\n");
    	exit(1);
    }

    if (DB) printf ("ArrivalEventNorth: time=%f, VehID=%d\n", CurrentTime(), e->EventParam.vehicleArrival.vehID);

    // increase the number of events.
    numOfEvents++;

    // set the memory for a vehicle
    v = (Vehicle*) malloc(sizeof(Vehicle));
    if (v == NULL) {
    	printf("No more memory for a vehicle");
    	exit(1);
    }

     // set the vehicles information
    v->id = e->EventParam.vehicleArrival.vehID;
    v->direction = e->EventParam.vehicleArrival.direction;
    v->next = NULL; // set the next vehicle to NULL since it will be added to the end of the queue if any.

    //add to the number of vehicles at the bridge entrance.
    nAtNorthEnt++;

    // if there is still time left schedule a new arrival.

	data = (EventData*) malloc(sizeof(EventData));
	if (data == NULL) {
		printf("There is no space for an event data");
		exit(1);
	}
	data->TypeOfEvent = ARRIVAL_NORTH;
	data->EventParam.vehicleArrival.vehID = e->EventParam.vehicleArrival.vehID + 1;
	ts = CurrentTime() + randExp(nbRate);
	if (ts < simDuration) {
	    Schedule(ts, data, (void *) arrivalNorth); // schedule a new arrival
    }
    // schedule vehicle entrance if there is nothing on the bridge.
    if (bridgeState == 0) { // might need to change.
        bridgeState = 1;
    	v->startWait = CurrentTime();
    	v->endWait = CurrentTime(); //calculates the end wait time.
    	data = (EventData*) malloc(sizeof(EventData)); // initiate data to pass to schedule function.
    	if (data == NULL) {
    	 	printf("There is no space for an event data");
    	 	exit(1);
    	 }
 		 data->TypeOfEvent = DONEENTER_NORTH;
 		 data->EventParam.doneEntering.veh = v;
 		 ts = CurrentTime() + enterTime;
 		 if (ts < simDuration) {
 		     Schedule(ts, data, (void*) doneEnteringNorth);
 		 }
     } else {
    	 v->startWait = CurrentTime();
    	 insert(&northHead, &northTail, v);
     }
     free(e); // free the memory for the input
}
////////////////////////////////////////////////////////////////////////////////////////
/*
 * schedule an arrival for southbound and add vehicles to queue.
 * generate a vehicle based on the input data,
 * schedule next arrival on the same direction of the bridge,
 * schedule the time when the vehicle finish entering the bridge, or
 * put the vehicle in its corresponding queue.
 */

 void arrivalSouth(EventData *e) {
    EventData* data;
 	Vehicle* v;
    double ts;

    if (e->TypeOfEvent != ARRIVAL_SOUTH) { // give an error if the event type does not match
     	fprintf (stderr, "Unexpected event type in Arrival south\n");
     	exit(1);
     }
    if (DB) printf ("ArrivalEventSouth: time=%f, VehID=%d\n", CurrentTime(), e->EventParam.vehicleArrival.vehID);

    // increase the number of events.
       numOfEvents++;

     // set the memory for a vehicle
     v = (Vehicle*) malloc(sizeof(Vehicle));
     if (v == NULL) {
     	printf("No more memory for a vehicle");
     	exit(1);
     }

     // set the vehicles information
     v->id = e->EventParam.vehicleArrival.vehID;
     v->direction = e->EventParam.vehicleArrival.direction;
     v->startWait = 0; // just for initiating and will change later
     v->endWait = 0;
     v->next = NULL; // set the next vehicle to NULL since it will be added to the end of the queue if any.


     //add to the number of vehicles at the bridge southern entrance.
     nAtSouthEnt++;

     // if there is still time left schedule a new arrival.

 		data = (EventData*) malloc(sizeof(EventData));
 	if (data == NULL) {
 		printf("There is no space for an event data");
 		exit(1);
 	}
 	data->TypeOfEvent = ARRIVAL_SOUTH;
 	data->EventParam.vehicleArrival.vehID = e->EventParam.vehicleArrival.vehID + 1;
 	ts = CurrentTime() + randExp(sbRate);
 	if (ts < simDuration) {
 	    Schedule(ts, data, (void *) arrivalSouth); // schedule a new arrival
 	}
 	// schedule a done Entering if bridge is empty
    if (bridgeState == 0) {
        bridgeState = 2;
     	v->startWait = CurrentTime();
        v->endWait = CurrentTime(); //calculates the end wait time.
  		data = (EventData*) malloc(sizeof(EventData));
  		if (data == NULL) {
  		    printf("There is no space for an event data");
  			exit(1);
  		}
  		data->TypeOfEvent = DONEENTER_SOUTH;
  		data->EventParam.doneEntering.veh = v;
  		ts = CurrentTime() + enterTime;
  		if (ts < simDuration) {
  		    Schedule(ts, data, (void*) doneEnteringSouth);
  		}
     } else {
     	v->startWait = CurrentTime();
     	insert(&southHead, &southTail, v);
      }
      free(e); // free the memory for the input
 }
//////////////////////////////////////////////////////////////////////////////
 ////////////////////////////////////////////////////////////////////////////
 //////////////////////////////////////////////////////////////////////////////

/*
 * get an event data for the north side, and schedule a departure event. Also if there is any
 * vehicle on the line, it schedule its entrance.
 */
 void doneEnteringNorth(EventData *e) {

	EventData* data;
	Vehicle* v;
    double ts;

    if (e->TypeOfEvent != DONEENTER_NORTH) { // give an error if the event type does not match
    	fprintf (stderr, "Unexpected event type in doneEntering North\n");
    	exit(1);
    }
    if (DB) printf ("DoneEnteringNorth: time=%f, VehID=%d\n", CurrentTime(), e->EventParam.doneEntering.veh->id);

    numOfEvents++; // add to number of events.
    nAtNorthEnt--; //subtract from the number of vehicles at the bridge entrance.
    numOnBridge++; // add to number of vehicles on the bridge.


	// schedule departure event
	data = (EventData*) malloc (sizeof(EventData));
	if (data == NULL) {
		fprintf(stderr, "malloc error. No space for event data\n");
		exit(1);
	}
    // schedule a departure for the vehicle that finished entering the bridge.
	data->TypeOfEvent = DEPARTURE_NORTH;
	data->EventParam.vehicleDeparture.v = e->EventParam.doneEntering.veh;
	ts = CurrentTime() + (compTime - enterTime);
	if (ts < simDuration) {
	    Schedule(ts, data, (void *) departureNorth);
	}

	// if there is any vehicle behind the current vehicle (in the same group), schedule its entrance.
	if (nAtNorthEnt > 0 && numOutOfQNorth < maxExitQ) {
		printf("start removing from north queue\n");
		v = delete(&northHead, &northTail);
		numOutOfQNorth++;
		v->endWait = CurrentTime(); // vehicle has been served.

 		data = (EventData*) malloc(sizeof(EventData));
 		if (data == NULL) {
 			printf("There is no space for an event data");
 			exit(1);
 		}

		data->TypeOfEvent = DONEENTER_NORTH;
		data->EventParam.doneEntering.veh = v;
		ts = CurrentTime() + enterTime;
		if (ts < simDuration) {
		    Schedule(ts, data, (void*) doneEnteringNorth);
		}
   	}
 }
 /*
  * get an event data for the south side, and schedule a departure event. Also if there is any
  * vehicle on the line, it schedule its entrance.
  */
void doneEnteringSouth(EventData *e) {
    EventData* data;
 	Vehicle* v;
    double ts;

    if (e->TypeOfEvent != DONEENTER_SOUTH) { // give an error if the event type does not match
        fprintf (stderr, "Unexpected event type in doneEntering south\n");
     	exit(1);
     }
    if (DB) printf ("DoneEnteringSouth: time=%f, VehID=%d\n", CurrentTime(), e->EventParam.doneEntering.veh->id);
    numOfEvents++; // add to number of events.
    nAtSouthEnt--;  //subtract from the number of vehicles at the bridge entrance.
    numOnBridge++; // add to number of vehicles on the bridge.

 	// schedule departure event
 	data = (EventData*) malloc (sizeof(EventData));
 	if (data == NULL) {
 		fprintf(stderr, "malloc error. No space for event data\n");
 		exit(1);
 	}
 	data->TypeOfEvent = DEPARTURE_SOUTH;
 	data->EventParam.vehicleDeparture.v = e->EventParam.doneEntering.veh;
 	ts = CurrentTime() + (compTime - enterTime);
 	if (ts < simDuration) {
 	    Schedule(ts, data, (void *) departureSouth);
 	}

 	// if there is any vehicle in the group, schedule its entrance.
 	if (nAtSouthEnt > 0 && numOutOfQSouth < maxExitQ) {
 		printf("start removing from south queue\n");
 		v = delete(&southHead, &southTail);
 		numOutOfQSouth++;
 		v->endWait = CurrentTime();
 		data = (EventData*) malloc(sizeof(EventData));

 		if (data == NULL) {
 			printf("There is no space for an event data");
 			exit(1);
 		}
 		data->TypeOfEvent = DONEENTER_SOUTH;
 		data->EventParam.doneEntering.veh = v;
 		ts = CurrentTime() + enterTime;
 		if (ts < simDuration) {
 		    Schedule(ts, data, (void*) doneEnteringSouth);
 		}
    }
}
///////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
 ////////////////////////////////////////////////////////////////////////////////////
 /*
 * remove a vehicle from the bridge
 * changes the status of the bridge
 * schedule entrance of the other vehicles waiting at the bridge.
 *
 */
 void departureNorth (EventData *e) {

	EventData* data;
	Vehicle* v;
	double ts;

	nDepN++; // add to number of vehicles that departed

    if (e->TypeOfEvent != DEPARTURE_NORTH ) { // give an error if the event type does not match
	     	fprintf (stderr, "Unexpected event type in departure north\n");
	     	exit(1);
	     }
	if (DB) printf ("Departure North: time=%f, VehID=%d\n", CurrentTime(), e->EventParam.vehicleDeparture.v->id);
	numOfEvents++; // add to number of events.
	numOnBridge--; // reduce the number of vehicles on the bridge by 1;

	if (numOnBridge == 0) {
	    if (nAtSouthEnt > 0) {
		bridgeState = 2;
		numOutOfQSouth = 0; // reset the value of the number of vehicles exit the queue
		v = delete(&southHead, &southTail);
		v->endWait = CurrentTime();
		data = (EventData*) malloc(sizeof(EventData));
		if (data == NULL) {
			printf("There is no space for an event data");
			exit(1);
		}
		data->TypeOfEvent = DONEENTER_SOUTH;
		data->EventParam.doneEntering.veh = v;
		ts = CurrentTime() + enterTime;
		if (ts < simDuration) {
		    Schedule(ts, data, (void*) doneEnteringSouth);
		}

	} else if (nAtNorthEnt > 0) {
		bridgeState = 1;
		numOutOfQNorth = 0;
		v = delete(&northHead, &northTail);
		v->endWait = CurrentTime();
		data = (EventData*) malloc(sizeof(EventData));
		if (data == NULL) {
			printf("There is no space for an event data");
			exit(1);
		}
	  	data->TypeOfEvent = DONEENTER_NORTH;
		data->EventParam.doneEntering.veh = v;
		ts = CurrentTime() + enterTime;
		if (ts < simDuration) {
		    Schedule(ts, data, (void*) doneEnteringNorth);
		}
	} else {
		bridgeState = 0;
		numOutOfQNorth = 0;
		numOutOfQSouth = 0;
	}
	}
	totalWaitTimeNorth += (e->EventParam.vehicleDeparture.v->endWait) - (e->EventParam.vehicleDeparture.v->startWait);
	free(e->EventParam.vehicleDeparture.v);
	free(e);
 }
 /*
* remove a vehicle from the bridge
* changes the status of the bridge
* schedule entrance of the other vehicles waiting at the bridge.
*/
 void departureSouth (EventData *e) {

	 EventData* data;
	 Vehicle* v;
	 double ts;

	 nDepS++; // add to number of vehicles that departed

	 if (e->TypeOfEvent != DEPARTURE_SOUTH ) { // give an error if the event type does not match
	     	fprintf (stderr, "Unexpected event type in departure south\n");
	     	exit(1);
	     }
	 if (DB) printf ("Departure South: time=%f, VehID=%d\n", CurrentTime(), e->EventParam.vehicleDeparture.v->id);

	numOfEvents++; // add to number of events.
	numOnBridge--; // reduce the number of vehicles on the bridge by 1;

	if (numOnBridge == 0) {
		 // reset the value of the number of vehicles exit the queue
	    if (nAtNorthEnt > 0) {
	    	numOutOfQNorth = 0;
			bridgeState = 1;
			v = delete(&northHead, &northTail);
			v->endWait = CurrentTime();
			data = (EventData*) malloc(sizeof(EventData));
			if (data == NULL) {
				printf("There is no space for an event data");
				exit(1);
			}
			data->TypeOfEvent = DONEENTER_NORTH;
			data->EventParam.doneEntering.veh = v;
			ts = CurrentTime() + enterTime;
			if (ts < simDuration) {
			    Schedule(ts, data, (void*) doneEnteringNorth);
				}
		} else if (nAtSouthEnt > 0) {
			numOutOfQSouth = 0;
			bridgeState = 2;
			v = delete(&southHead, &southTail);
			v->endWait = CurrentTime();
		 	data = (EventData*) malloc(sizeof(EventData));
		 	if (data == NULL) {
		 		printf("There is no space for an event data");
		 		exit(1);
		 	}
			data->TypeOfEvent = DONEENTER_SOUTH;
			data->EventParam.doneEntering.veh = v;
			ts = CurrentTime() + enterTime;
			if (ts < simDuration) {
			    Schedule(ts, data, (void*) doneEnteringSouth);
			}
			} else {
				bridgeState = 0;
				numOutOfQSouth = 0;
				numOutOfQNorth = 0;
			}
		}
	totalWaitTimeSouth += (e->EventParam.vehicleDeparture.v->endWait) - (e->EventParam.vehicleDeparture.v->startWait);
	free(e->EventParam.vehicleDeparture.v);
	free(e);
 }

///////////////////////////////////////////////////////////////
// this is the main function
//////////////////////////////////////////////////////
 int main(void) {
	 EventData* dataNorth;
	 EventData* dataSouth;
	 double tsN;
	 double tsS;


	 // initial for north side
	 dataNorth = (EventData*)malloc(sizeof(EventData));
	 if(dataNorth == NULL) {
		 printf("There is no memory left for initiating the fist data");
		 exit(1);
	 }
	 dataNorth->TypeOfEvent = ARRIVAL_NORTH;
	 dataNorth->EventParam.vehicleArrival.direction = 1;
	 dataNorth->EventParam.vehicleArrival.vehID = 0;
	 tsN = randExp(nbRate);
	 Schedule(tsN, dataNorth, (void *) arrivalNorth);

	 // initial for south side
	 dataSouth = (EventData*)malloc(sizeof(EventData));
	 if(dataSouth == NULL) {
		 printf("There is no memory left for initiating the fist data");
		 exit(1);
	 }
	 dataSouth->TypeOfEvent = ARRIVAL_SOUTH;
	 dataSouth->EventParam.vehicleArrival.direction = 2;
	 dataSouth->EventParam.vehicleArrival.vehID = 0;
	 tsS = randExp(sbRate);
	 Schedule(tsS, dataSouth, (void *) arrivalSouth);

	printf ("Single lane bridge problem\n");

	StartTime = clock();
	RunSim(); // start the simulation
	EndTime = clock();

	printf ("Total waiting time on North= %f\n", totalWaitTimeNorth);
	printf ("Total waiting time on South= %f\n", totalWaitTimeSouth);
	printf ("Average waiting time on North= %f\n", totalWaitTimeNorth/(double)nDepN);
	printf ("Average waiting time on South= %f\n", totalWaitTimeSouth/(double)nDepS);
	printf ("total number of events = %d \n", numOfEvents);

	return 0;
 }


