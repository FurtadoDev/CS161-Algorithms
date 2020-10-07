/*!
 * @file      main.cpp
 * @brief     This file contains the 'main' function which contains the implementation of the Prim's algorithm. Program execution begins and ends there.
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
#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>      // std::stringstream, std::stringbuf
#include <fstream>
#include <algorithm>
#include "Heap.h"
#include "Graph.h"

using namespace std;

int main()
{
	/*
	vector<pair<int,int>> temp;
	temp.push_back(make_pair(6, 7));
	temp.push_back(make_pair(7, 8));
	temp.push_back(make_pair(8, 9));
	temp.push_back(make_pair(9, 10));
	temp.push_back(make_pair(10, 11));
	temp.push_back(make_pair(11, 12));
	temp.push_back(make_pair(12, 13));

	temp.push_back(make_pair(0,1));
	temp.push_back(make_pair(1, 2));
	temp.push_back(make_pair(2, 3));
	temp.push_back(make_pair(3, 4));
	temp.push_back(make_pair(4, 5));
	temp.push_back(make_pair(5, 6));


	if (std::binary_search(temp.begin(), temp.end(), make_pair(50,11)))
		std::cout << "found!\n"; else std::cout << "not found.\n";

	Heap hp(temp);
	hp.deleteNodeFromHeap(0);
	hp.deleteNodeFromHeap(5);
	hp.deleteNodeFromHeap(3);
	hp.insertNodeIntoHeap(make_pair(0,1));
	hp.insertNodeIntoHeap(make_pair(6, 7));

	cout << "Heap Values - " << endl;
	hp.printHeap();
	cout << "Vertex Positions - " << endl;
	hp.printVertexPositions();

	hp.heap_vector.clear();
	hp.vertex_positions.clear();
	*/

	
	int num_vertices;
	int num_edges;
	int temp_u;
	int temp_v;
	int temp_w;
	int len;
	string line;
	stringstream str_strm;
	ifstream myfile("C:\\Users\\vrfur\\Desktop\\Algorithms.git\\trunk\\module_3\\module_3_datasets\\week1\\edges.txt"); //edges_test.txt
	if (myfile.is_open())
	{
		getline(myfile, line);
		str_strm << line;
		str_strm >> num_vertices;
		str_strm >> num_edges;
		str_strm.clear();
		Graph g(num_vertices, num_edges);

		while (getline(myfile, line))
		{
			len = line.length();
			while (line[len - 1] == ' ') { line.erase(--len, 1); } //right trim
			while (line[0] == ' ') { line.erase(0, 1); } //left trim
			str_strm << line; //output the entire line into the string stream
			str_strm >> temp_u;
			str_strm >> temp_v;
			str_strm >> temp_w;
			g.addEdge(temp_u, temp_v, temp_w);
			str_strm.clear();
		}
		myfile.close();
		
		
		
		/*Start of Test Code for Inititialization*/
		/*
		cout << "No of vertices : " << num_vertices << endl;
		cout << "No of edges : " << num_edges << endl;
		for(int i = 1; i <= num_vertices; i++){
		std::list<pair<int, int>>::iterator it;
		cout << "Node No : " << i << endl;
 			for (it = g.adjList[i].begin(); it != g.adjList[i].end(); it++) {
				cout << it->first << " : " << it->second << endl;
			}
		}
		*/
		/*End of Test Code for Initialization*/


		
		/*Start Of Driver Code*/
		long long int answer = 0;
		std::unordered_map<int, int> visitedNodes; //TODO: clear this in the end
		visitedNodes.reserve(num_vertices);
		visitedNodes[1] = 1;
		std::list<pair<int, int>>::iterator it;
		vector<pair<int, int>> init_heap; //TODO: clear this in the end
		for (it = g.adjList[1].begin(); it != g.adjList[1].end(); it++) {
			init_heap.push_back(make_pair(it->first, it->second));
		}
		Heap hp(init_heap); //TODO: clear this in the end and everything inside including vertex positions
		pair<int, int> extractedNode_temp;
		while (hp.heap_vector_size > 0) {
			extractedNode_temp = hp.heap_vector[0];
			hp.deleteNodeFromHeap(0);
			visitedNodes[extractedNode_temp.first] = 1;
			answer += extractedNode_temp.second;

			//find all the neighbours of of the extracted node
			for (it = g.adjList[extractedNode_temp.first].begin(); it != g.adjList[extractedNode_temp.first].end(); it++) {
				if (visitedNodes.find(it->first) == visitedNodes.end()) {//the neighbour does not exist in V
					if (hp.vertex_positions.find(it->first) == hp.vertex_positions.end()) {//the neighbour does not exist in V-x
						hp.insertNodeIntoHeap(make_pair(it->first, it->second));
					}
					else {//the neighbour exists in V-X
						int idx = hp.vertex_positions[it->first]; //position in the hea[
						if (hp.heap_vector[idx].second > it->second) {
							hp.deleteNodeFromHeap(idx);
							hp.insertNodeIntoHeap(make_pair(it->first,it->second));
						}
					}
				}
			}
			
		}
		/*End Of Driver Code*/

		/*Start of Code to free memory*/
		visitedNodes.clear();
		hp.heap_vector.clear();
		hp.heap_vector.shrink_to_fit();
		g.adjList->clear();
		/*End of Code to free memory*/

		cout << "The final answer is : " << answer << endl;
	}
	else {
		cout << "Cannot open file" << endl;
	}
	

	return 0;
}



