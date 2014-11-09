/*
 * main.c
 *
 *  Created on: Oct 27, 2014
 *      Author: Mostaffa
 */
#include <stdio.h>
#include<stdlib.h>
#include "vertex.h"
#include "priorityQ.h"
#include "shortPath.h"

int main(int argc, char* argv[]) {
	// declare function
	Graph* CreateGraph(FILE* inFile);
	int dijkstra(Graph* g, int source);
	int findDiameter(Graph* g);
    // open the file to read a graph from
	FILE* graphFile =  fopen(argv[1], "r");
    // check that there are not too many arguments
	if (argc != 2) {
    	fprintf(stderr, "There are too many arguments for main function");
    }
	Graph* myGraph = CreateGraph(graphFile); // initialize the graph
	printf("%d\n", myGraph->N); // check if correct number of nodes read from file
	int d = 0;
	d = dijkstra(myGraph, 0); // calculate the maximum of the minimum distance...
	printf("This is the max distance from node 0 to other nodes: %d\n", d);
	int diam = 0;
	diam = findDiameter(myGraph); // find the diameter.
	printf("This is the diameter of the graph %d ", diam);
    return 0;
}
