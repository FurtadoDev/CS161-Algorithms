/*!
 * @file      Graph.h
 * @brief     Declaration of the Graph class.
 *
 * @author    Veinstin Furtado <vrfurtado@mun.ca>
 * @copyright (c) 2020 Veinstin Furtado. All rights reserved.
 * @license   Apache License, Version 2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not
 * use this file except in compliance with the License.  You may obtain a copy
 * of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations
 * under the License.
 */
#pragma once
#include <iostream>
#include <vector>
#include <list>
using namespace std;

class Graph
{

public:
	int num_vertices;
	int num_edges;
	list<pair<int, int>>* adjList;
	/**
	 * Constructor which takes in the number of vertices and the number of edges in the Graph. An adjacency list is initialized using the number of vertices passed here.
	 *
	 */
	Graph(int num_vertices, int num_edges);

	void addEdge(int u, int v, int w);
};