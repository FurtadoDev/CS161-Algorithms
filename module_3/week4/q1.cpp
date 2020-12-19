/*!
 * @file      knapsack1.cpp
 * @brief     This file contains the solution to the knapsack problem
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

int computeOptimalSoln(int n, int capacity);

int main() {
	int temp_value;
	int temp_weight;

	size_t len = 0;
	string line;
	stringstream str_strm;
	ifstream myfile("C:\\Users\\vrfur\\Desktop\\Algorithms.git\\trunk\\module_3\\module_3_datasets\\week4\\knapsack1.txt");
	if (myfile.is_open())
	{
		getline(myfile, line);
		str_strm << line;
		str_strm >> knapsack_size;
		str_strm >> number_of_items;
		values_weights.reserve(number_of_items+1);
		values_weights.push_back(make_pair(0,0));
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
	int** A = new int* [number_of_items + 1];
	for (int i = 0; i <= number_of_items; i++) {
		A[i] = new int[knapsack_size+1];
	}
	for (int i = 0; i <= number_of_items; i++) {
		for (int j = 0; j <= knapsack_size; j++) {
			A[i][j] = 0;
		}
	}
	/*End : Initializing the 2-D structure*/


	
	

	//Approach 1 : Naive Recursive Implementation
	//cout << "Answer (Naive Recursive Implementation): " << computeOptimalSoln(number_of_items, knapsack_size) << endl;
	
	//Approach 2 : Dynamic Programming 
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
	}
	cout << "Answer (Dynamic Programming Implementation): " << A[number_of_items][knapsack_size] << endl;

	//Print the result matrix for Approach 2
	/*
	for (int i = 0; i <= number_of_items; i++) {
		for (int j = 0; j <= knapsack_size; j++) {
			cout << A[i][j] << " ";

		}
		cout << endl;
	}
	*/

	



	/* Beginning of Clean Up Code */
	for (int i = 0; i <= number_of_items; ++i) {
		delete[] A[i];
	}
	delete[] A;
	values_weights.clear();
	values_weights.shrink_to_fit();
	/* End of Clean Up Code */

	return 0;
}


/*
 *
 * Naive Recursive Implementation : Can be optimized using memoization
 *
*/
int computeOptimalSoln(int n, int capacity) {
	
	if (n == 0 || capacity == 0) {
		return 0;
	}
	else {
		//case 1 : with last item excluded
		//case 2 : with last item included
		if (values_weights[n].second <= capacity) { //weight of the nth item is less than equal to the capacity
			//both cases are possible
			return max(computeOptimalSoln(n - 1, capacity), computeOptimalSoln(n - 1, capacity - values_weights[n].second) + values_weights[n].first);
		}
		else { //weight of the nth item is more than the capacity
			return computeOptimalSoln(n - 1, capacity);
		}
	}
}



