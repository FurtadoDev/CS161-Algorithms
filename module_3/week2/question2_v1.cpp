/*!
 * @file      main.cpp
 * @brief     This file contains the 'main' function finds all the connected components in the data set using the bfs technique(using a queue). This is an alternative to the Kruskal's agorithm in solving question 2. Took 7 minutes to run.
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


int num_nodes;
int num_bits;
queue<string> bfs_queue;
unordered_map<string, bool> nodes_explored;
void magic(string str, int i, int changesLeft);

int main() {
	unordered_map<string, bool>::const_iterator got;

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

			got = nodes_explored.find(temp_node); //lookup used filter out the duplicates
			if (got == nodes_explored.end()) {
				nodes_explored[temp_node] = false;
			}
			else {
				//cout << "duplicate node : " << temp_node << endl;
			}

			str_strm.clear();
		}
		myfile.close();
	}
	else {
		cout << "Cannot open file" << endl;
	}



	auto t1 = std::chrono::high_resolution_clock::now();

	int num_connnectedComponents = 0;
	for (auto& it : nodes_explored) {
		if (it.second == false) {//if it is unexplored
			it.second = true;
			bfs_queue.push(it.first);
			num_connnectedComponents++;
			while (!bfs_queue.empty()) {
				string temp = bfs_queue.front();
				bfs_queue.pop();
				magic(temp, num_bits - 1, 1);
				magic(temp, num_bits - 1, 2);
			}
		}
	}

	cout << "The Number of connected components is : " << num_connnectedComponents << endl;

	auto t2 = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::seconds>(t2 - t1).count();
	std::cout << "Duration : " << duration/60 << "minutes" << endl;

	nodes_explored.clear();
	return 0;
}



void magic(string str, int i, int changesLeft) {
	unordered_map<string, bool>::const_iterator got;
	if (changesLeft == 0) {
		got = nodes_explored.find(str);
		if (got != nodes_explored.end()) {
			if (nodes_explored[str]  == false) {
				nodes_explored[str] = true;
				bfs_queue.push(str);
			}
		}
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