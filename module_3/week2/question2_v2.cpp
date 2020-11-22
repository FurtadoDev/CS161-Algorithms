/*!
 * @file      main.cpp
 * @brief     This file contains the 'main' function which contains a variation of the clustering(Kruskal's) Algorithm to find the number of clusters for question 2. Program execution begins and ends there. The Union Find techique is implemented using weighted uions and path compression.
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
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <chrono>

using namespace std;


int num_nodes = 0;
int num_bits = 0;

unordered_map<string, int> node_nodenumbers;
vector<int> roots;
vector<int> weights;

vector<string> temp_neighbournodes;



void magic(string str, int i, int changesLeft);

int findRoot(int node);
bool fuseDisjointSets(int node1, int node2);

int main() {
	int idx = 1;
	unordered_map<string, int>::const_iterator got;

	int len;
	string line;
	stringstream str_strm;
	ifstream myfile("C:\\Users\\vrfur\\Desktop\\Algorithms.git\\trunk\\module_3\\module_3_datasets\\week2\\clustering_big.txt"); //clustering_big.txt
	if (myfile.is_open())
	{
		getline(myfile, line);
		str_strm << line;
		str_strm >> num_nodes;
		str_strm >> num_bits;
		str_strm.clear();

		while (getline(myfile, line))
		{
			char temp_char;
			string temp_node;

			len = line.length();
			while (line[len - 1] == ' ') { line.erase(--len, 1); } //right trim
			while (line[0] == ' ') { line.erase(0, 1); } //left trim
			str_strm << line; //output the entire line into the string stream
			
			for (int i = 0; i < num_bits; i++) {
				str_strm >> temp_char;
				temp_node = temp_node + temp_char;
			}

			got = node_nodenumbers.find(temp_node); //lookup used filter out the duplicates
			if (got == node_nodenumbers.end()) {
				node_nodenumbers[temp_node] = idx;
				idx++;
			}
			
			str_strm.clear();
		}
		myfile.close();
	}
	else {
		cout << "Cannot open file" << endl;
	}

	roots.reserve(num_nodes+1);
	roots.push_back(0);
	weights.reserve(num_nodes+1);
	weights.push_back(0);
	for (int i = 1; i <= num_nodes; i++) {
		roots.push_back(-1);
	}
	for (int i = 1; i <= num_nodes; i++) {
		weights.push_back(1);
	}

	
	auto t1 = std::chrono::high_resolution_clock::now();
	//Step 1 :for each node in the unordered map generate nodes that are a distance of 1
	//if the generated node exists in the map fuse the nodes
	int num_clusters = node_nodenumbers.size();
	string temp_str;
	int temp_size;
	int temp_nodenumber1;
	int temp_nodenumber2;
	for (auto& it : node_nodenumbers) {
		temp_str = it.first;
		temp_nodenumber1 = it.second;
		magic(temp_str, num_bits - 1, 1);
		temp_size = temp_neighbournodes.size();
		for (int i = 0; i < temp_size; i++) {
			got = node_nodenumbers.find(temp_neighbournodes[i]);
			if (got != node_nodenumbers.end()) {//it does exist
				temp_nodenumber2 = node_nodenumbers[temp_neighbournodes[i]];
				if (fuseDisjointSets(temp_nodenumber1, temp_nodenumber2))
					num_clusters--;
			}
		}
	
		temp_neighbournodes.clear();
	}
	
	//Step 2 :for each node in the undordered map generate nodes that are a distance of 2
	//if the generated node exists in the map fuse the nodes.
	for (auto& it : node_nodenumbers) {
		temp_str = it.first;
		temp_nodenumber1 = it.second;
		magic(temp_str, num_bits - 1, 2);
		temp_size = temp_neighbournodes.size();
		for (int i = 0; i < temp_size; i++) {
			got = node_nodenumbers.find(temp_neighbournodes[i]);
			if (got != node_nodenumbers.end()) {//it does exist
				temp_nodenumber2 = node_nodenumbers[temp_neighbournodes[i]];
				if (fuseDisjointSets(temp_nodenumber1, temp_nodenumber2))
					num_clusters--;
			}
		}

		temp_neighbournodes.clear();
	}

	cout << "The number of clusters is : " << num_clusters << endl;
	auto t2 = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::seconds>(t2 - t1).count();
	std::cout << "Duration : " << duration/60 << " minutes" << endl;

	node_nodenumbers.clear();
	roots.clear();
	weights.clear();
	return 0;
}

void magic(string str, int i, int changesLeft) {
	if (changesLeft == 0) {
		//cout << str << endl;
		temp_neighbournodes.push_back(str);
		return;
	}
	if (i < 0) return;
	// flip current bit
	str[i] = str[i] == '0' ? '1' : '0';
	magic(str, i - 1, changesLeft - 1);
	// undo the flip
	str[i] = str[i] == '0' ? '1' : '0';
	magic(str, i - 1, changesLeft);
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