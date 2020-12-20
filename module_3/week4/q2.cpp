/*!
 * @file      knapsack_big.cpp
 * @brief     This file contains the solution to the knapsack problem for a big dataset
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

int knapsack_size;
int number_of_items;
vector<pair<int, int>> values_weights;


int main() {
	int temp_value;
	int temp_weight;

	size_t len = 0;
	string line;
	stringstream str_strm;
	ifstream myfile("C:\\Users\\vrfur\\Desktop\\Algorithms.git\\trunk\\module_3\\module_3_datasets\\week4\\knapsack_big.txt");
	if (myfile.is_open())
	{
		getline(myfile, line);
		str_strm << line;
		str_strm >> knapsack_size;
		str_strm >> number_of_items;
		values_weights.reserve(number_of_items + 1);
		values_weights.push_back(make_pair(0, 0));
		str_strm.clear();
		while (getline(myfile, line))
		{
			len = line.length();
			while (line[len - 1] == ' ') { line.erase(--len, 1); } //right trim
			while (line[0] == ' ') { line.erase(0, 1); } //left trim
			str_strm << line; //Output the entire line into the string stream
			str_strm >> temp_value;
			str_strm >> temp_weight;

			values_weights.push_back(make_pair(temp_value, temp_weight));
			//cout << temp_value << " : " << temp_weight << endl;
			str_strm.clear();
		}
		myfile.close();
	}
	else {
		cout << "Cannot open file" << endl;
	}




	/*Begin : Initializing the 2-D structure*/
	int** A = new int* [number_of_items + 1 + 1];
	for (int i = 0; i <= 1; i++) {
		A[i] = new int[knapsack_size + 1];
	}
	for (int i = 0; i <= 1; i++) {
		for (int j = 0; j <= knapsack_size; j++) {
			A[i][j] = 0;
		}
	}
	/*End : Initializing the 2-D structure*/
	

	int vi = 0;
	int si = 0;
	for (int i = 1; i <= number_of_items; i++) {
		for (int j = 1; j <= knapsack_size; j++) {
			vi = values_weights[i].first;
			si = values_weights[i].second;
			if (si <= j) {
				A[i][j] = max(A[i - 1][j], A[i - 1][j - si] + vi);
			}
			else {
				A[i][j] = A[i - 1][j];
			}
		}
		delete[] A[i-1];
		A[i+1] = new int[knapsack_size + 1];
	}
	
	delete[] A[number_of_items + 1];
	cout << "Answer : " << A[number_of_items][knapsack_size] << endl;
	delete[] A[number_of_items];
	delete[] A;
	values_weights.clear();
	values_weights.shrink_to_fit();

	return 0;
}



