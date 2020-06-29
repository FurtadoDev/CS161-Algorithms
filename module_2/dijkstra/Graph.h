#pragma once
#include <iostream>
#include <vector>
#include <list>
using namespace std;

class Graph
{

public:
	int num_vertices;
	list<pair<int, int>>* adjList;

	Graph(int num_vertices);

	void addEdge(int u, int v, int w);
};

