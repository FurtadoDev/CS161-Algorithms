/*!
 * @file      q2_mwis.cpp
 * @brief     This file contains the solution to the maximum-weight independent set problem using dynamic programming
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
#include <queue>
#include <unordered_set>



using namespace std;

size_t num_vertices = 0;
vector<int> weights;

int main() {

	int temp_weight;

	size_t len = 0;
	string line;
	stringstream str_strm;
	ifstream myfile("C:\\Users\\vrfur\\Desktop\\Algorithms.git\\trunk\\module_3\\module_3_datasets\\week3\\mwis.txt"); //mwis
	if (myfile.is_open())
	{
		getline(myfile, line);
		str_strm << line;
		str_strm >> num_vertices;
		str_strm.clear();

		weights.reserve(num_vertices+1); //ignoring the 0th position for ease of use.
		weights.push_back(0);

		while (getline(myfile, line))
		{
			len = line.length();
			while (line[len - 1] == ' ') { line.erase(--len, 1); } //right trim
			while (line[0] == ' ') { line.erase(0, 1); } //left trim
			str_strm << line; //output the entire line into the string stream
			str_strm >> temp_weight;

			weights.push_back(temp_weight);

			str_strm.clear();
		}
		myfile.close();
	}
	else {
		cout << "Cannot open file" << endl;
	}

	size_t vector_size = weights.size();

	
	vector<int> mwis;
	mwis.reserve(num_vertices + 1);
	mwis.push_back(0);
	mwis.push_back(weights[1]);

	for (size_t i = 2; i < vector_size; i++) {
		mwis.push_back(max(mwis[i - 1], mwis[i - 2] + weights[i]));
	}

	cout << "Max Weight is : " << mwis[vector_size - 1] << endl;

	size_t i = vector_size-1;
	unordered_set<size_t> vertices_included;
	while (i >= 2) {
		
		if (mwis[i - 1] > mwis[i - 2] + weights[i]) {
			i = i - 1;
		}else {
			vertices_included.insert(i);
			i = i - 2;
		}
		
		if (i == 1) {
			vertices_included.insert(i);
			break;
		}

	}
	

	
	int myArray[8] = { 1, 2, 3, 4, 17, 117, 517,997 };
	for (int i = 0; i < 8; i++) {
		unordered_set<size_t>::const_iterator got = vertices_included.find(myArray[i]);
		if (got == vertices_included.end())
			cout << "0";
		else
			cout << "1";
	}
	cout << endl;
	
	
	
	vertices_included.clear();
	mwis.clear();
	mwis.shrink_to_fit();
	weights.clear();
	weights.shrink_to_fit();

	return 0;
}