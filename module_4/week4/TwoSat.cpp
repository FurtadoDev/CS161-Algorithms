//#pragma comment(linker, "/STACK:2000000")
//#pragma comment(linker, "/HEAP:2000000")

/*!
 * @file      TwoSat.cpp
 * @brief     This file contains the solution of the 2 SAT problem using the scc approach
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
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <list>
#include <unordered_map>
#include <chrono>
#include <ctime>
#include <unordered_set>
#include <stack>


using namespace std;

size_t num_clauses;

struct Clause {
	bool remove;
	int literal1;
	int literal2;
};

vector<Clause> clauses;



unordered_map<int, vector<int>> adjacencyList_forward;
unordered_map<int, vector<int>> adjacencyList_reverse;
unordered_set<int> explored;
stack<int> finished_vertices_increasing_order; //the topmost element finished the fastest(this is for the reverse graph)


void dfs_reverse(int node);
void dfs_forward(int node);

bool satScc();

unordered_set<int> scc_vertices_temp;

int main()
{
	
	int temp_literal1;
	int temp_literal2;
	size_t len;
	string line;
	stringstream str_strm;
	ifstream myfile("C:\\Users\\vrfur\\Desktop\\Algorithms.git\\trunk\\module_4\\module_4_datasets\\week4\\test.txt"); //2sat6.txt
	if (myfile.is_open())
	{
		getline(myfile, line);
		str_strm << line;
		str_strm >> num_clauses;
		clauses.reserve(num_clauses);
		str_strm.clear();

		while (getline(myfile, line))
		{
			len = line.length();
			while (line[len - 1] == ' ') { line.erase(--len, 1); } //right trim
			while (line[0] == ' ') { line.erase(0, 1); } //left trim
			str_strm << line; //output the entire line into the string stream
			str_strm >> temp_literal1;
			str_strm >> temp_literal2;
			Clause temp_clause = {false, temp_literal1, temp_literal2};
			clauses.push_back(temp_clause);
			str_strm.clear();
		}
		myfile.close();
	}
	else {
		std::cout << "Cannot open file" << endl;
	}

	std::cout << "The last element is " << clauses[num_clauses - 1].literal1 << "  " << clauses[num_clauses - 1].literal2 << endl;


	auto start = std::chrono::system_clock::now();

	size_t num_reductions = 250;	 //TODO :: change before running as required
	for (size_t i = 1; i <= num_reductions; i++) {
		
		unordered_map<int, vector<size_t>> literal_positions;
		for (size_t j = 0; j < num_clauses; j++) {
			if (clauses[j].remove == false) {
				literal_positions[clauses[j].literal1].push_back(j);
				literal_positions[clauses[j].literal2].push_back(j);
			}
		}

		unordered_map<int, vector<size_t>>::const_iterator got;
		for (size_t k = 0; k < num_clauses; k++) {
			
			if (clauses[k].remove == false) {
				int literal1 = clauses[k].literal1;
				int literal2 = clauses[k].literal2;
				got = literal_positions.find(-literal1);
				if (got == literal_positions.end()) {
					//mark all the positions with literal1 as to delete
					for (size_t l = 0; l < literal_positions[literal1].size(); l++) {
						size_t idx1 = literal_positions[literal1][l];
						clauses[idx1].remove = true;
					}
					literal_positions[literal1].clear();
					literal_positions.erase(literal1);
				}
				got = literal_positions.find(-literal2);
				if (got == literal_positions.end()) {
					//mark all the positions with literal2 as to delete
					for (size_t m = 0; m < literal_positions[literal2].size(); m++) {
						size_t idx2 = literal_positions[literal2][m];
						clauses[idx2].remove = true;
					}
					literal_positions[literal2].clear();
					literal_positions.erase(literal2);
				}
			}

		}
		for (auto& it : literal_positions) {
			it.second.clear();
		}
		literal_positions.clear();
	}

	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	std::cout << "No of seconds taken for reduction : " << elapsed_seconds.count() << endl;



	size_t count_clauses = 0;
	for (size_t i = 0; i < num_clauses; i++) {
		if (clauses[i].remove == false) {
			temp_literal1 = clauses[i].literal1;
			temp_literal2 = clauses[i].literal2;
			
			adjacencyList_forward[-temp_literal1].push_back(temp_literal2);
			adjacencyList_forward[-temp_literal2].push_back(temp_literal1);
			adjacencyList_forward[temp_literal2];
			adjacencyList_forward[temp_literal1];
			
			adjacencyList_reverse[temp_literal2].push_back(-temp_literal1);
			adjacencyList_reverse[temp_literal1].push_back(-temp_literal2);
			adjacencyList_reverse[-temp_literal1];
			adjacencyList_reverse[-temp_literal2];

			count_clauses++;
		}
	}
	cout << "the no of clauses after reduction is " << count_clauses << endl;

	if (count_clauses == 0) {

		cout << "The assignment is satisfiable." << endl;

	}
	else {


		unordered_set<int> literals;
		for (size_t i = 0; i < num_clauses; i++) {
			if (clauses[i].remove == false) {
				literals.insert(clauses[i].literal1);
				literals.insert(clauses[i].literal2);
				cout << clauses[i].literal1 << "        " << clauses[i].literal2 << endl;
			}
		}
		cout << "the no of literals after reduction is " << literals.size() << endl;
		literals.clear();
		clauses.clear();
		cout << "Initalization for the forward and reverse adjacency lists are complete" << endl;


		cout << "Size of the forward ajacency list is " << adjacencyList_forward.size() << endl;
		cout << "Size of the reverse adjacency list is " << adjacencyList_reverse.size() << endl;


		/*
		int temp_from_node;
		int temp_to_node;
		size_t len1;
		string line1;
		stringstream str_strm1;
		ifstream myfile1("C:\\Users\\vrfur\\Desktop\\Algorithms.git\\trunk\\module_4\\module_4_datasets\\week4\\adj_test.txt");
		if (myfile1.is_open())
		{
			while (getline(myfile1, line1))
			{
				len1 = line1.length();
				while (line1[len1 - 1] == ' ') { line1.erase(--len1, 1); } //right trim
				while (line1[0] == ' ') { line1.erase(0, 1); } //left trim
				str_strm1 << line1; //output the entire line into the string stream
				str_strm1 >> temp_from_node;
				str_strm1 >> temp_to_node;
				adjacencyList_forward[temp_from_node].push_back(temp_to_node);
				adjacencyList_forward[temp_to_node];
				adjacencyList_reverse[temp_to_node].push_back(temp_from_node);
				adjacencyList_reverse[temp_from_node];

				str_strm1.clear();
			}
			myfile1.close();
		}
		else {
			std::cout << "Cannot open file" << endl;
		}*/



		//1. Run dfs on the reverse graph
		unordered_set<int>::iterator explored_itr;
		for (auto& it : adjacencyList_reverse) {
			explored_itr = explored.find(it.first);
			if (explored_itr == explored.end()) { //not explored
				dfs_reverse(it.first);
			}
		}

		//2. clear the explored set
		explored.clear();


		//3. Run dfs on the forward graph by
		size_t scc_count = 0;
		bool sat = false;
		while (!finished_vertices_increasing_order.empty()) {
			int top_node = finished_vertices_increasing_order.top();
			finished_vertices_increasing_order.pop();
			explored_itr = explored.find(top_node);
			if (explored_itr == explored.end()) { //not explored yet
				cout << top_node << endl;
				scc_count++;
				dfs_forward(top_node);
				sat = satScc();
				if (!sat)
					break;
			}
			scc_vertices_temp.clear();
		}
		scc_vertices_temp.clear();

		explored.clear();

		cout << "The no of sccs in the graph are : " << scc_count << endl;


		if (sat) {
			cout << "The assignment is satisfiable." << endl;
		}
		else {
			cout << "The assignment is not satisfiable." << endl;
		}


		/* TEST CODE
		size_t temp_vector_size;
		for (auto& it : adjacencyList_forward) {
			temp_vector_size = it.second.size();
			if (temp_vector_size == 0) {
				cout << it.first << " has no outgoing edges" << endl;
			}
		}
		for (auto& it : adjacencyList_reverse) {
			temp_vector_size = it.second.size();
			if (temp_vector_size == 0) {
				cout << it.first << " has no outgoing edges" << endl;
			}
		}*/
		
	}
	
	
	//clear the adjacency lists
	for (auto& it : adjacencyList_forward) {
		it.second.clear();
	}
	for (auto& it : adjacencyList_reverse) {
		it.second.clear();
	}
	adjacencyList_forward.clear();
	adjacencyList_reverse.clear();

	return 0;
}


void dfs_reverse(int node) {
	unordered_set<int>::iterator itr;
	size_t vector_size;
	itr = explored.find(node);
	if (itr == explored.end()) { //not explored yet
		explored.insert(node); //mark it as explored
		vector_size = adjacencyList_reverse[node].size();
		for (size_t i = 0; i < vector_size; i++) {
			/*
			itr = explored.find(adjacencyList_reverse[node][i]);
			if (itr == explored.end()) { //not explored yet
				explored.insert(adjacencyList_reverse[node][i]);
				dfs_reverse(adjacencyList_reverse[node][i]);
			}*/
			dfs_reverse(adjacencyList_reverse[node][i]);
		}
		finished_vertices_increasing_order.push(node);
	}
}



void dfs_forward(int node) {
	unordered_set<int>::iterator itr;
	size_t vector_size;
	itr = explored.find(node);
	if (itr == explored.end()) { //not explored yet
		explored.insert(node); //mark it as explored
		scc_vertices_temp.insert(node);
		vector_size = adjacencyList_forward[node].size();
		for (size_t i = 0; i < vector_size; i++) {
			dfs_forward(adjacencyList_forward[node][i]);
		}
	}
}


bool satScc() {
	
	unordered_set<int>::iterator itr;
	for (const auto& node : scc_vertices_temp) {
		itr = scc_vertices_temp.find(-node);
		if (itr != scc_vertices_temp.end()) { //that means the node and it's negation are present in the same scc
			return false;
		}
	}
	return true;
}