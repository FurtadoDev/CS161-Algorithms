//==================================================================================================================
// Name        : dijkstra.cpp
// Author      : Veinstin Furtado
// Version     :
// Copyright   : Your copyright notice
// Description : Dijkstra's shortest path algorithm in C++ (Heap Based Implementation), Ansi-style
// References	: Tim Roughgarden, "Algorithms Illuminated - Part 2"
//====================================================================================================================
#include <list>
#include <utility>
#include <iostream> 
#include <sstream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <regex>

#include <string>
#include <cstring>
#include <cstdlib>
#include <unordered_map>
#include <limits>
#include "Heap.h"
#include "Graph.h"

using namespace std; 

/* When nodes are put into the graph their node values are reduced by 1.
*/
int main() { 
	//int num_vertices = 9; // For test file
	int num_vertices = 200;
	

	Graph g(num_vertices);
	int len;
	string line;
	stringstream str_strm;
	ifstream myfile("C:\\Users\\veins\\OneDrive\\Desktop\\Algorithms.git\\trunk\\module_2\\module_2_datasets\\data_set_week2.txt"); //data_set_week2/test/test1
	int from_node;
	int to_node;
	int weight;
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			len = line.length();
			while (line[len - 1] == ' ') { line.erase(--len, 1); } //right trim
			while (line[0] == ' ') { line.erase(0, 1); } //left trim
			str_strm << line; //output the entire line into the string stream
			string temp_str;
			int temp_int;
			str_strm >> from_node;
			//cout << from_node << " ";
			//cout << endl;
			while (str_strm >> temp_str) {
				std::string delimiter = ",";
				int pos = temp_str.find(delimiter);
				to_node = stoi(temp_str.substr(0, pos));
				temp_str.erase(0, pos + delimiter.length());
				weight = stoi(temp_str.substr(0, std::string::npos));
				//cout << from_node << ":" <<to_node << ":" << weight << "  ";
				g.addEdge(from_node - 1, to_node, weight);
			}
			//cout << endl;
			str_strm.clear();
		}
	}
	else {
		cout << "Cannot open file" << endl;
	}



	//Initialize the heap with all of node 1's neighbours
	int extracted_node;
	vector<pair<int,int>> temp;
	list<pair<int, int>>::iterator i;
	list<pair<int, int>>::iterator j;
	int computed_key;
	size_t indexToRemove;
	int new_shortestPath;
	for (i = g.adjList[0].begin(); i != g.adjList[0].end(); ++i)
	{
		temp.push_back(make_pair(i->first,i->second));
	}
	Heap hp(temp);
	//erase temp here

	unordered_map<int, int> shortestPaths;
	shortestPaths[1] = 0;
	int loop_number = 1;

	while (hp.heap_vector_size != 0) {
		//Step 1: Extract the topmost node from the heap
		extracted_node = hp.heap_vector[0].first; //extracted node
		shortestPaths[extracted_node] = hp.heap_vector[0].second; //extracted node's weight
		hp.deleteNodeFromHeap(0);

		//cout << "Loop Number : " << loop_number << endl;
		//loop_number++;
		//Print the heap here
		//hp.printHeap();

		//Step 2: For all of the extracted node's neighbours
		for (i = g.adjList[extracted_node - 1].begin(); i != g.adjList[extracted_node - 1].end(); ++i) { //extracted node's neighbours
			auto search = shortestPaths.find(i->first);
			if (search == shortestPaths.end()) { //Filter out the neighbours that are not in V
				computed_key = shortestPaths[extracted_node] + i->second;
				search = hp.vertex_positions.find(i->first);
				if (search == hp.vertex_positions.end()) { //it doesn't exist in V-X
					//insert the node into the heap with the computed new key
					hp.insertNodeIntoHeap(make_pair(i->first, computed_key));
				}
				else {
					//update the key(if required) for the node with the computed new key
					indexToRemove = hp.vertex_positions[i->first];
					if (hp.heap_vector[indexToRemove].second > computed_key) {
						hp.deleteNodeFromHeap(indexToRemove);
						hp.insertNodeIntoHeap(make_pair(i->first, computed_key));
					}

				}
			}

			//Print heap here
			//hp.printHeap();
			//cout << "Vertex Position : " << endl;
			//hp.printVertexPositions();
		}
	}

	for (auto& it : shortestPaths) {
		cout << "Vertex :" << it.first << " Shortest Path :" << it.second << endl;
	}
	
}

//TODO: when you choose a vertex take into consideration the case where two nodes share the same key



