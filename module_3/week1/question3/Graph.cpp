#include "Graph.h"

Graph::Graph(int num_vertices, int num_edges)
{
	this->num_vertices = num_vertices;
	this->num_edges = num_edges;
	this->adjList = new list<pair<int, int>>[num_vertices+1]; //not using the 0th position to make things simpler
}

void Graph::addEdge(int u, int v, int w) {
	this->adjList[u].push_back(make_pair(v, w));
	this->adjList[v].push_back(make_pair(u, w));
}