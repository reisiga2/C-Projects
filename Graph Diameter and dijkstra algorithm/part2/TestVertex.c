#include <stdio.h>
#include <stdlib.h>
#include "vertex.h"
#include "shortPath.h"
#include "priorityQ.h"
/*
int main(void) {
	void relax(Vertex* u, Vertex* v);
	int dijkstra(Graph* g, int source);
   Graph* gr = makeGraph(5);
   
   Vertex* v1 = makeVertex(1);
   printf("%d\n", v1->id);
   int i;
   int j;
   //for (i = 0; i < gr->N; i++) {
	//   for (j = i + 1; j < gr->N; j++) {
	 //      addToGraph(gr, i, j);
     //  }
  // }

   addToGraph(gr, 0, 1);
   addToGraph(gr, 1, 2);
   addToGraph(gr, 2, 3);
   addToGraph(gr, 3, 4);
   //addToGraph(gr, 4, 0);

   // test the vertex list
   VertexList* vl = (VertexList*)malloc(sizeof(VertexList));
   vl->head = NULL;
   printf("add to vertexList test1 %p\n", vl->head);
   addToVertexList(vl, v1);
   printf("Add to vertexList test 2 :%d\n", vl->head->id);
   Vertex* v2 = makeVertex(2);
   addToVertexList(vl, v2);
   printf("Add to vertexList test 3 :%d\n", vl->head->next->id);
    printf("%d\n", gr->N);
    printf("%d\n" , gr->array[2].head->next->id);
    printf("%d\n" , gr->array[1].head->id);

    printf("----------------------------------------->>>> %d\n",searchVertexList(vl, 2) );
    printf("----------------------------------------->>>> %d\n",searchVertexList(vl, 0) );
    //test the priority queue
    Vertex* v3 = makeVertex(3);
    Vertex* pq =  makePrioQ();
    addQ(pq, v1);
    addQ(pq, v2);
    addQ(pq, v3);
    printList(pq);
    removeQVertex(pq, v3->id);
    printList(pq);
   printf("test the graph to see if it works----------------------");
   int kkk;
   for (kkk = 0; kkk< gr->N; kkk++) {
	   printf("-----------connections of vertex %d\n", kkk);
	   Vertex* temp = gr->array[kkk].head;
	   while(temp != NULL) {
		   printf("%d \n", temp->id);
		   temp = temp->next;
	   }
   }

   printf("-----------------test dijkstra algorthm One by One--------------------------\n");
/////////////////////////////////////////////////////////////////////////////////
// test dijkstra alogrithm part by part

    int source = 0;
    Vertex* pq2 = makePrioQ();
   	VertexList* vl2 = (VertexList*)malloc(sizeof(VertexList));
   	vl2->head = NULL;
   	int N = gr->N;
   	int ii;
   	for (ii = 0; ii < N; ii++) {
   	    Vertex* v = makeVertex(ii);
   		if (ii == source) {
   		    v->distance = 0;
   		}
   		addQ(pq2, v);
   	}
   	printList(pq2);
    while (size(pq2) != 0) {
   	printf("----------------------------------\n");
    Vertex* u = removeQ(pq2);
    printf("this is the vertex removed from pq and added to list %d\n", u->id);
   	addToVertexList(vl2,u);
   	printf("vertex added to list %d\n", u->id);
   	VertexList listU = gr->array[u->id];
   	Vertex* temp = listU.head;
   	printf("this is the first node connected to u %d\n", temp->id);
   	while (temp != NULL) {
   		Vertex* prioQInstance;
   		 if (searchVertexList(vl2, temp->id) == 0) {
		     prioQInstance = removeQVertex(pq2, temp->id);
		     relax(u, prioQInstance);
		     addQ(pq2, prioQInstance);
   		 }
		 printf("--------------Priority q after relax and add----------------\n");
		 printList(pq2);
		 temp = temp->next;
    }
    }
/////////////////////////////////////////////////////////////////
printf("------------------test dijkstra algorithm in full-------------------------\n");
int d = 0;
d = dijkstra(gr, 0);
printf("This is the max distance: %d\n", d);
int diam = 0;
diam = findDiameter(gr);
printf("This is the diameter %d ", diam);
		///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////
   //printf("%d\n", ll->next->id);
   //Vertex* v2 = makeVertex(2);
   //add(ll, v2);
   //printf("%d\n", ll->next->next->id);
   //removeVertex(ll, v1);
   //printf("%d\n", ll->next->id);
   //removeVertex(ll, v2);
  // printf("%p\n", ll->next);
   //Vertex v3 = makeVertex(3);
   //Vertex v4 = makeVertex(4);
   //Vertex v5 = makeVertex(5);
   
   //int i;
   //for (i = 0; i < 5; i++) {
      // add(gr->vertices[i],makeVertex(i + 1));
   //}

return 0;
}   
 */
