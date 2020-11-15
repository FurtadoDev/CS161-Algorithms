/*!
 * @file      main.cpp
 * @brief     This file contains the 'main' function which contains the implementation of the clustering(Kruskal's) Algorithm using the Union Find Data Structure. Program execution begins and ends there. The Union Find techique is implemented using weighted uions and path compression.
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
#include <functional>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <fstream>
#include <unordered_map>


using namespace std;

struct edge{
	int left_node;
	int right_node;
	int weight;
};

vector<struct edge> edges;
int num_nodes;
int num_edges;
int maxSpacing;
std::vector<int> roots;
std::vector<int> weights;

void merge_sort(int leftIndex, int rightIndex);
void merge(int leftIndex, int midIndex, int rightIndex);
int findRoot(int node);
bool fuseDisjointSets(int node1, int node2);

int main() {
	num_edges = 0;
	num_nodes = 0;
	int maxSpacing = 0;
	int temp_node1 = 0;
	int temp_node2 = 0;
	int temp_edgeweight = 0;
	struct edge temp_edge;
	int len;
	string line;
	stringstream str_strm;
	ifstream myfile("C:\\Users\\vrfur\\Desktop\\Algorithms.git\\trunk\\module_3\\module_3_datasets\\week2\\clustering1.txt"); //clustering1.txt
	if (myfile.is_open())
	{
		getline(myfile, line);
		str_strm << line;
		str_strm >> num_nodes;
		str_strm.clear();

		while (getline(myfile, line))
		{
			len = line.length();
			while (line[len - 1] == ' ') { line.erase(--len, 1); } //right trim
			while (line[0] == ' ') { line.erase(0, 1); } //left trim
			str_strm << line; //output the entire line into the string stream
			str_strm >> temp_node1;
			str_strm >> temp_node2;
			str_strm >> temp_edgeweight;
			temp_edge.left_node = temp_node1;
			temp_edge.right_node = temp_node2;
			temp_edge.weight = temp_edgeweight;
			edges.push_back(temp_edge);
			num_edges++;
			str_strm.clear();
		}
		myfile.close();
	}
	else {
		cout << "Cannot open file" << endl;
	}
	//cout << "The size of edges vector is : "<< edges.size() << endl;
	//cout << "The last edge is : " << edges[edges.size() - 1].left_node << " : " << edges[edges.size() - 1].right_node << " : " << edges[edges.size() - 1].weight << endl;
	


	/*
	*
	* START OF DRIVER CODE
	*
	*/
	roots.reserve(num_nodes + 1); //ignore the 0th position
	weights.reserve(num_nodes + 1); //ignore the 0th position
	for (int i = 0; i <= num_nodes; i++) {
		roots.push_back(-1);
	}
	for (int i = 0; i <= num_nodes; i++) {
		weights.push_back(1);//or use an unordered_map instead
	}
	merge_sort(0,num_edges-1); //sort the edges in ascending order according to their weights
	
	/*
	for (int i = 0; i < num_edges; i++) {
		cout << edges[i].left_node << " : " << edges[i].right_node << " : " << edges[i].weight << endl;
	}
	
	cout << "Selected Edges(Kruskal's Min Spanning Tree Alg.) : " << endl;
	for (int i = 0; i < num_edges; i++) {
		if (fuseDisjointSets(edges[i].left_node, edges[i].right_node)) {
			cout << edges[i].left_node << " : " << edges[i].right_node << " : " << edges[i].weight << endl;
		}
	}
	**/

	
	int num_clusters = num_nodes;
	int i = 0;
	while (num_clusters != 4) {
		if (fuseDisjointSets(edges[i].left_node, edges[i].right_node)) {
			num_clusters--;
		}
		i++;
	}

	bool createsCycle = true;
	while (createsCycle) {
		int root1 = findRoot(edges[i].left_node);
		int root2 = findRoot(edges[i].right_node);
		if (root1 != root2) {//they are not in thhe same cluste
			createsCycle = false;
			maxSpacing = edges[i].weight;
		}
		i++;
	}
	
	
	//max spacing for the first question is the min distance between nodes in different clusters
	cout << "Max spacing of the algorithm is : " << maxSpacing << endl;
	roots.clear();
	weights.clear();
	/*
	*
	* END OF DRIVER CODE
	*
	*/
	edges.clear();
	






	/*TEST CODE FOR MERGE SORT FOR EDGES*/
	/*
	struct edge four;
	struct edge one;
	struct edge eight;
	struct edge ten;
	struct edge six;
	struct edge three;
	struct edge seven;
	struct edge two;
	struct edge nine;
	struct edge nine_1;
	struct edge one_1;
	struct edge one_2;
	four.weight = 4;
	one.weight = 1;
	eight.weight = 8;
	ten.weight = 10;
	six.weight = 6;
	three.weight = 3;
	seven.weight = 7;
	two.weight = 2;
	nine.weight = 9;
	
	nine_1.weight = 9;
	one_1.weight = 1;
	one_2.weight = 1;
	edges.push_back(four); edges.push_back(one); edges.push_back(eight); edges.push_back(ten);
	edges.push_back(six); edges.push_back(three); edges.push_back(seven); edges.push_back(two);
	edges.push_back(nine); 
	edges.push_back(nine_1); edges.push_back(one_1); edges.push_back(one_2);
	merge_sort(0, edges.size()-1);

	for (int i = 0; i < edges.size(); i++) {
		cout << edges[i].weight << endl;
	}
	*/
	return 0;
}


void merge_sort(int leftIndex, int rightIndex) {
	int midIndex = ((rightIndex + leftIndex) / 2);
	if (leftIndex < rightIndex) {
		merge_sort(leftIndex, midIndex);
		merge_sort(midIndex + 1, rightIndex);
		merge(leftIndex, midIndex, rightIndex);
	}
}

void merge(int leftIndex, int midIndex, int rightIndex) {
	int tempvectorSize = (rightIndex - leftIndex) + 1;
	vector<struct edge> tempVector;
	tempVector.reserve(tempvectorSize);
	int idx1 = leftIndex;
	int idx2 = midIndex + 1;
	while ((idx1 <= midIndex) && (idx2 <= rightIndex)) {
		if (edges[idx1].weight < edges[idx2].weight) {
			tempVector.push_back(edges[idx1]);
			idx1++;
		}/*
		else {
			tempVector.push_back(edges[idx2]);
			idx2++;
		}*/
		else if(edges[idx1].weight > edges[idx2].weight){
			tempVector.push_back(edges[idx2]);
			idx2++;
		}
		else {
			tempVector.push_back(edges[idx1]);
			tempVector.push_back(edges[idx2]);
			idx1++;
			idx2++;
		}
		
	}

	while (idx1 <= midIndex) {
		tempVector.push_back(edges[idx1]);
		idx1++;
	}

	while (idx2 <= rightIndex) {
		tempVector.push_back(edges[idx2]);
		idx2++;
	}

	//copy into the original vector here
	for (int i = 0; i < tempvectorSize; i++) {
		edges[leftIndex] = tempVector[i];
		leftIndex++;
	}
	tempVector.clear();
}



int findRoot(int node) {
	if (roots[node] == -1) return node; // At root
	roots[node] = findRoot(roots[node]);
	return roots[node];
}


bool fuseDisjointSets(int node1, int node2) {
	int root1 = findRoot(node1);
	int root2 = findRoot(node2);
	if (root1 != root2) {//if root1 and root2 are in the same, that would create a cycle
		int weight1 = weights[node1];
		int weight2 = weights[node2];
		if (weight1 < weight2) {
			roots[root1] = root2;
			weights[root2] += weight1;
		}
		else if (weight2 < weight1) {
			roots[root2] = root1;
			weights[root1] += weight2;
		}
		else {//changing the root of either is ok if the weights are equal.
			roots[root1] = root2;
			weights[root2] += weight1;
		}
		return true;
	}
	return false;
}

