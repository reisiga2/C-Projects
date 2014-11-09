/*
 * simEng.h
 *
 *  Created on: Sep 27, 2014
 *      Author: Mostafa
 */

#ifndef SIMENG_H_
#define SIMENG_H_

void Schedule(double ts, void* data, void (*cb)(void*));
void RunSim(void);
double CurrentTime(void);

#endif /* SIMENG_H_ */
