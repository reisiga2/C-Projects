#ifndef part2_H_
#define part2_H_
#include"vertex.h"

Graph* CreateGraph(FILE* inFile);
void relax(Vertex* u, Vertex* v);
int dijkstra(Graph* g, int source);
int findDiameter(Graph* g);

#endif
