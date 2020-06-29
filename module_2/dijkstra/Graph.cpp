#include "Graph.h"

Graph::Graph(int num_vertices)
{
	this->num_vertices = num_vertices;
	this->adjList = new list<pair<int, int>>[num_vertices];
}

void Graph::addEdge(int u, int v, int w) {
	this->adjList[u].push_back(make_pair(v, w));
	//this->adjList[v].push_back(make_pair(u, w)); PIECE OF ADVICE : DON'T GET AHEAD OF YOURSELF
}
