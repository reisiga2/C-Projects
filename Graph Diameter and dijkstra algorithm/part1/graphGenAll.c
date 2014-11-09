/*
 * graphGen.c
 *
 *  Created on: Oct 16, 2014
 *      Author: Mostafa Reisi
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
// declare the fucntions...
	int pickNode(int* D, int N, int DTotal);
   double* giveProbDist(int* D, int N, int DTotal);
	
	FILE *myGraph;// name of the file to write on

	if (argc != 3) {
	    fprintf(stderr, "there are too many or too few arguments.");
	}
	int N;
	N = atoi(argv[1]);

	int* D = (int*) malloc(sizeof(int)*N);
    // initiate the graph with 5 nodes each has degree on 4;
	int n0 = 5; // number of initial nodes.
	int j = 0;
	for (j = 0; j < n0; j++) {
		D[j] = n0 - 1;
	}
    int DTotal = n0 * (n0 - 1);
    // open the file to write on
    int i = 0;
    int addedTo = 0; // the node that will be picked.
    myGraph = fopen(argv[2], "w"); //open the file
    if (myGraph == NULL) { // check if the file was opened.
        fprintf(stderr, "could not open the file %s\n", argv[2]);
    }
 // print the number of node to the file...
    fprintf (myGraph, "%d\n", N);

 // write to the file the few first nodes that initiated the graph with
    int kk;
    int jj;
    for(kk = 0; kk < n0; kk++){
        for(jj = kk + 1; jj < n0; jj++){
            fprintf (myGraph, "%d %d\n", kk, jj);
        }
    }
    // add new nodes and change the degree and write to the file 
    for (i = n0; i < N; i++) {
    	addedTo = pickNode(D, N, DTotal);
        if(addedTo == -1) {
            fprintf(stderr, "Not possible to connect to a node\n");
        }
    	D[addedTo]++;
    	D[i] = 1;
    	DTotal = DTotal + 2;

    	fprintf (myGraph, "%d %d\n", i, addedTo);
    }
    fclose(myGraph);
    int ii = 0;
    for (ii = 0; ii < N; ii++) {
        printf("%d\n", D[ii]);
    }
    return 0;
}

/*
 * Gives the accumulative probability distribution of the Nodes.
 * @param: D is the vector of the degree of the nodes.
 * @param: N number of Nodes
 * @param DTotal is the sum of the node degrees
 * @return the accumulative probability of selecting a node.
 */
double* giveProbDist(int* D, int N, int DTotal) {
    double* p = (double*) malloc(sizeof(double) * (N +1));
    p[0] = 0;
    int i = 1;
    for (i = 1; i <= N; i++) {
    	p[i] = p[i - 1] + (double) D[i-1]/DTotal;
    }
    return p;
}

/*
 * Gives the node that a new node will be connected to
 * @param: D is the vector of the degree of the nodes.
 * @param: N number of Nodes
 * @param DTotal is the sum of the node degrees
 * @return The node
 */
int pickNode(int* D, int N, int DTotal) {
    int node = 0;
    double* p;
    p = giveProbDist(D, N, DTotal);
    double urand;
    urand = ((double) rand ()) / (((double) RAND_MAX)+1.0);
    int i;
    for (i = 0; i < N; i++) {
        if (p[i] <= urand && urand < p[i+1]) {
    	    node = i;
    	    return node;
    	}
    }
    return -1; // if this happens something goes wrong.
}

