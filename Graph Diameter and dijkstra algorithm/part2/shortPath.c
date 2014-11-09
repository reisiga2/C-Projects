#include<stdio.h>
#include<stdlib.h>
#include "vertex.h"
#include "priorityQ.h"

/*
* uses a file to read the edges of a graph and record the graph in memory using linked list.
* @param a FILE to read from
* @return gives out a graph that stored in a adjacency list
*/
Graph* CreateGraph(FILE* inFile) {

    int N;
    int i;
    int j;
    if (fscanf(inFile, "%d", &i) == 1) {
	    N = i;
    }
	Graph* gr = makeGraph(N);
	while (fscanf(inFile, "%d %d", &i, &j) == 2) {
        addToGraph(gr, i, j);
    }
    return gr;	
}

/*
* Does the relaxation for two vertices.
*/
void relax(Vertex* u, Vertex* v) {
    if ( u->distance + 1 < v->distance) {
	    v->distance = u->distance + 1;
        v->previous = u->id;
	}
}
/*
* calculates the shortest distance between the source and every other node in the graph,
* and returns the maximum shortest distance from the source.
* 
*/
int dijkstra(Graph* g, int source) {
    Vertex* pq = makePrioQ();
	VertexList* vl = (VertexList*)malloc(sizeof(VertexList)); // a list to keep vertices removed from priority queue.
	vl->head = NULL;
	int N = g->N;
	int i;
	// add all the nodes to the priority queue.
	for (i = 0; i < N; i++) {
	    Vertex* v = makeVertex(i);
		if (i == source) {
		    v->distance = 0;
		}
		addQ(pq, v);
	}
	// while the priority queue is not empty remove from it and add the removed to a list.
	while (size(pq) != 0) {
	    Vertex* u = removeQ(pq);
	    addToVertexList(vl,u);
	    // find nodes connected to the the removed node and if needed relax them.
	    VertexList listU = g->array[u->id]; // the list that keep the removed vertices.
	    Vertex* temp = listU.head;
	    while (temp != NULL) {
	    	Vertex* prioQInstance;
	   		 if (searchVertexList(vl, temp->id) == 0) { // check if the vertex is still in prioQ.
			     prioQInstance = removeQVertex(pq, temp->id);
			     relax(u, prioQInstance);
			     addQ(pq, prioQInstance);
	   		 }
	   	temp = temp->next;
	    }
	}
	// find the maximum shortest path from the source node.
	Vertex* temp2 = vl->head;
	int max = temp2->distance;
	while (temp2->next != NULL) {
	   if (temp2->next->distance > max) {
	      	max = temp2->next->distance;
	   }
	   temp2 =temp2->next;
	}
	return max;
}

/*
* finds the diameter of the graph.
* @param Graph
* @return diameter of the graph
*/
int findDiameter(Graph* g) {
    int N = g->N;
    int i;
    int max = 0;
    for (i = 0; i < N; i ++) {
    	int temp = dijkstra(g, i);
    	if (temp > max) {
    		max = temp;
    	}
    }
    return max;
}

