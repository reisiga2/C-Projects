#include<stdio.h>
#include<stdlib.h>
#include "vertex.h"


Vertex* makeVertex(int id) {
    Vertex* v = (Vertex*) malloc(sizeof(Vertex));
	if (v == NULL) {
	    fprintf(stderr, "there is not enough memory for making a vertex");
	}
	v->next = NULL;
	v->id = id;
	v->distance = 9999999;
	v->previous = -1;
    return v;
}

Graph* makeGraph(int n) {
    Graph* gr = (Graph*)malloc(sizeof(Graph));
    gr->N = n;
    gr->array = (VertexList*) malloc(sizeof(VertexList) * n);
	int i;
	for (i = 0; i < n; i++) {
	    gr->array[i].head = NULL;
	}
    return gr;	
}

void addToVertexList(VertexList* vl, Vertex* v) {
    if (vl->head == NULL) {
        vl->head = v;
    } else {
	    Vertex* temp = vl->head;
        while(temp->next != NULL) {
		    temp = temp->next;
		}
		temp->next = v;
	}	
}

int searchVertexList(VertexList* vl, int id) {
    Vertex* temp = vl->head;
	while (temp != NULL) {
	   if (temp->id == id) {
	       return 1;
		}
        temp = temp->next;		
	}
	return 0;
}

void addToGraph(Graph* gr, int s, int d) {
    Vertex* source = makeVertex(s);
    Vertex* dest = makeVertex(d);

    //connect source to dest
    dest->next = gr->array[s].head; // add the dest to the top of the linked list
    gr->array[s].head = dest; // change the head to the new node that is just added.

    //connect dest to source
    source->next = gr->array[d].head; // add the source node to the top of linked list related to dest
    gr->array[d].head = source;
}



