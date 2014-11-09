#ifndef vertex_H_
#define vertex_H_
// the structure vertex has one field next

typedef struct Vertex {
   int distance;
   int previous;
   int id;
   struct Vertex* next;
} Vertex;

typedef struct VertexList {
	struct Vertex* head;
} VertexList;

typedef struct Graph {
    int N;
	struct VertexList* array;
} Graph;


Graph* makeGraph(int n); // initiates a graph with n vertices.
Vertex* makeLinkedList(); // sets memory for the the head of the linked list
Vertex* makeVertex(int id); // allocates memory for a vertex with a give id
int searchVertexList(VertexList* vl, int id);
void addToVertexList(VertexList* vl, Vertex* v);
void addToGraph(Graph* gr, int s, int d); //adds as new vertex to the linked list
//void removeFromGraph(Graph gr, Vertex* ll, Vertex* v); // removes vertex v from the list

#endif
