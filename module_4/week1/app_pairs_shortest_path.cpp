/*!
 * @file      all_pairs_shortest_path.cpp
 * @brief     This file contains the implementation of the all-pairs-shortest-path problem using Floyd-Warshall's algorithm 
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


#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <stdlib.h> 
#include <stdio.h>  




using namespace std;

int Y_SIZE; //represents the node subset k
int Z_SIZE; //represents source vertex v
int X_SIZE; //represents destination vertex w

int num_vertices;
int num_edges;
unordered_map<int, unordered_map<int, int>> adjList;

int getOffset(int k, int from, int to);
pair<bool, int> getWeightIfEdgeExists(int from, int to);
int floyd_warshall_subroutine();

int main() {
		
	unordered_map<int, int>::iterator it;
	
	int temp_v;
	int temp_w;
	int temp_wt;

	size_t len = 0;
	string line;
	stringstream str_strm;
	ifstream myfile("C:\\Users\\vrfur\\Desktop\\Algorithms.git\\trunk\\module_4\\module_4_datasets\\week1\\g1.txt");
	if (myfile.is_open())
	{
		getline(myfile, line);
		str_strm << line;
		str_strm >> num_vertices;
		str_strm >> num_edges;
		adjList.reserve(num_vertices);

		Y_SIZE = num_vertices + 1; 
		X_SIZE = num_vertices;
		Z_SIZE = num_vertices;
		
		str_strm.clear();
		while (getline(myfile, line))
		{
			len = line.length();
			while (line[len - 1] == ' ') { line.erase(--len, 1); } //right trim
			while (line[0] == ' ') { line.erase(0, 1); } //left trim
			str_strm << line; //Output the entire line into the string stream
			str_strm >> temp_v;
			str_strm >> temp_w;
			str_strm >> temp_wt;
			
			//TODO::what if temp_v source does not exist?? : Working without this todo
			it = adjList[temp_v].find(temp_w);
			if (it == adjList[temp_v].end()) { //the destination does not exist
				adjList[temp_v][temp_w] = temp_wt;
			}else {//else it exists. update if new weight is lower(this condtion takes care of parallel edges)
				if (adjList[temp_v][temp_w] > temp_wt) {
					adjList[temp_v][temp_w] = temp_wt;//new temp_wt
				}
			}
			
			str_strm.clear();
		}
		myfile.close();
	}
	else {
		cout << "Cannot open file" << endl;
	}

	
	int min = floyd_warshall_subroutine();
	if (min == 0) {
		cout << "Negative Cycle Exists." << endl;
	}
	else {
		cout << "The shortest path among all paths is : " << min << endl;
	}

	
	//Free memory
	for (auto i = adjList.begin(); i != adjList.end(); i++) {
		adjList[i->first].clear();
	}
	adjList.clear();

	cout << "End of program. " << endl;
	return 0;
}


pair<bool, int> getWeightIfEdgeExists(int v, int w) {
	
	unordered_map<int, unordered_map<int, int>>::iterator it1;
	unordered_map<int, int>::iterator it2;

	it1 = adjList.find(v);
	if (it1 != adjList.end()) { //the vertex v exists as a source vertex
		it2 = adjList[v].find(w);
		if (it2 != adjList[v].end()) {// the destination node w exists
			return make_pair(true, adjList[v][w]);
		}else {// the destination node does not exist
			return make_pair(false, 0);
		}
	}
	
	return make_pair(false,0);
}


int getOffset(int k, int v, int w) {
	//v and w cannot be less than 1
	return k * (Z_SIZE * X_SIZE) + ((v - 1) * X_SIZE) + (w - 1);
}

int floyd_warshall_subroutine() {
	double* A = (double*)malloc(2 * Z_SIZE * X_SIZE * sizeof(double));
	pair<bool, int> isExists;

	/*Initialization Code : Initialize the 0th row*/
	for (int v = 1; v <= Z_SIZE; v++) {
		for (int w = 1; w <= X_SIZE; w++) {
			if (v == w) {
				A[getOffset(0, v, w)] = 0;
			}
			else {
				isExists = getWeightIfEdgeExists(v, w);
				if (isExists.first) {
					A[getOffset(0, v, w)] = isExists.second;
				}
				else {
					A[getOffset(0, v, w)] = std::numeric_limits<double>::infinity();
				}
			}
		}
	}


	/*Floyd-Warshall Algorithm*/
	for (int k = 1; k < Y_SIZE; k++) {
		for (int v = 1; v <= Z_SIZE; v++) {
			for (int w = 1; w <= X_SIZE; w++) {
				
				if (k % 2 == 0) {//old values are in the 1st row
					A[getOffset(0,v,w)] = min(A[getOffset(1,v,w)], A[getOffset(1,v,k)] + A[getOffset(1,k,w)]);
				}
				else {//old values are in the 0th row
					A[getOffset(1,v,w)] = min(A[getOffset(0, v, w)], A[getOffset(0, v, k)] + A[getOffset(0, k, w)]);
				}

			}
		}
	}


	

	/*Negative Cycle Detection*/
	for (int v = 1; v < X_SIZE; v++) {
		if (num_vertices%2 == 0) {//check the Oth row for negative cycle
			if (A[getOffset(0, v, v)] < 0) {
				free(A);
				return 0;
			}
		}else {//check the 1st row for negative cycle
			if (A[getOffset(1, v, v)] < 0) {
				free(A);
				return 0;
			}
		}
	}

	/*Return minimum shortest path*/
	int min = INT_MAX;
	for (int v = 1; v <= Z_SIZE; v++) {
		for (int w = 1; w < X_SIZE; w++) {
			if (v != w) {
				if (num_vertices % 2 == 0) {//check the Oth row for the answers
					if (A[getOffset(0, v, w)] < min) {
						min = A[getOffset(0, v, w)];
					}
				}else {//check the 1st row for the answers
					if (A[getOffset(1, v, w)] < min) {
						min = A[getOffset(1, v, w)];
					}
				}
			}
		}
	}


	free(A);
	return min;
}