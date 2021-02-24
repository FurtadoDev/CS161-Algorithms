/*!
 * @file      all_pairs_shortest_path.cpp
 * @brief     This file contains the implementation of the Bellman-Held-Karp algorithm for the Travelling Salesman Problem
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



 /*!
  * INSTRUCTIONS
  * @brief     Change the value of the const n before running this program. It should be set to the number of citites
  *
  * @author    Veinstin Furtado <vrfurtado@mun.ca>
  * @copyright (c) 2020 Veinstin Furtado. All rights reserved.
  * @license   Apache License, Version 2.0
  *
  */




#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <stdlib.h> 
#include <stdio.h>  
#include<cmath>
#include <bitset>
#include <iomanip>



using namespace std;

size_t num_cities;
pair<double, double>* city_coordinates;


double getDist(size_t city_num_one, size_t city_num_two);

int main() {
	double temp_x;
	double temp_y;
	int city_number = 0;
	size_t len = 0;
	string line;
	stringstream str_strm;
	ifstream myfile("C:\\Users\\vrfur\\Desktop\\Algorithms.git\\trunk\\module_4\\module_4_datasets\\week2\\tsp.txt"); //tsp.txt
	if (myfile.is_open())
	{
		getline(myfile, line);
		str_strm << line;
		str_strm >> num_cities;
		city_coordinates = (pair<double, double>*)malloc(num_cities * sizeof(pair<double, double>));
		str_strm.clear();
		int i = 0;
		while (getline(myfile, line))
		{
			len = line.length();
			while (line[len - 1] == ' ') { line.erase(--len, 1); } //right trim
			while (line[0] == ' ') { line.erase(0, 1); } //left trim
			str_strm << line; //Output the entire line into the string stream
			str_strm >> temp_x;
			str_strm >> temp_y;
			city_coordinates[i] = make_pair(temp_x, temp_y);
			str_strm.clear();
			i++;
		}
		myfile.close();
	}
	else {
		cout << "Cannot open file" << endl;
	}




	const size_t n = 13; //Change this when choosing to solve a portion at a time
	unordered_map<size_t, vector<bitset<n>>> sub_problems;
	unordered_map<bitset<n>, size_t> row_no;
	size_t num_rows = pow(2, n - 1) - 1;
	size_t num_cols = n - 1;
	double** A = (double**)malloc(num_rows * sizeof(double*));
	for (size_t i = 0; i < num_rows; i++) {
		A[i] = (double*)malloc((n - 1) * sizeof(double));
	}
	for (size_t i = 0; i < num_rows; i++) {
		for (size_t j = 0; j < num_cols; j++) {
			A[i][j] = numeric_limits<double>::infinity();
		}
	}
	size_t start = pow(2, n - 1) + 1;
	size_t end = pow(2, n) - 1;
	bitset<n> temp_bitset;
	size_t row_num = 0;
	for (size_t i = start; i <= end; i++) {
		temp_bitset = bitset<n>(i);
		sub_problems[temp_bitset.count()].push_back(temp_bitset);
		row_no[temp_bitset] = row_num;
		//cout << temp_bitset << "	:	" << row_num << endl;
		row_num++;
	}

	//Solve the base case(not optimal)
	temp_bitset = bitset<n>(pow(2, n - 1));
	bitset<n> temp_bitset_second;
	for (size_t j = 1; j < n; j++) {
		temp_bitset_second = (temp_bitset >> j) | temp_bitset;
		//cout << temp_bitset_second << endl;
		row_num = row_no[temp_bitset_second];
		A[row_num][j - 1] = getDist(0, j);
	}

	//Solve all other sub-problems
	size_t temp_vector_size;
	size_t row_num_second;
	double min;
	temp_bitset_second = bitset<n>(start - 1);
	bitset<n> temp_bitset_third;
	for (size_t s = 3; s <= n; s++) {
		temp_vector_size = sub_problems[s].size();
		for (size_t t = 0; t < temp_vector_size; t++) {
			temp_bitset = sub_problems[s][t];
			//solve for each choice of ultimate vertex possible in the bitset
			for (size_t j = 1; j < n; j++) {
				if (((temp_bitset_second >> j) & temp_bitset) != bitset<n>(0)) {//if the jth(starting from the left) bit is set
					row_num = row_no[temp_bitset];
					temp_bitset_third = (~(temp_bitset_second >> j) & temp_bitset); //make the jth bit 0
					row_num_second = row_no[temp_bitset_third];
					//Solve for the best possible solution for A[row_num][j-1]
					min = numeric_limits<double>::infinity();
					for (size_t k = 1; k < n; k++) {
						if (((temp_bitset_second >> k) & temp_bitset_third) != bitset<n>(0)) {//if the kth(starting from the left) bit is set
							if ((A[row_num_second][k - 1] + getDist(j, k)) < min)
								min = A[row_num_second][k - 1] + getDist(j, k);
						}
					}
					A[row_num][j - 1] = min;
				}
			}
		}
	}


	//Get the Optimum cost tour
	temp_bitset = bitset<n>(end);
	row_num = row_no[temp_bitset];
	double optimum_tour_cost = numeric_limits<double>::infinity();
	for (size_t j = 1; j < n; j++) {
		if (A[row_num][j - 1] + getDist(0, j) < optimum_tour_cost)
			optimum_tour_cost = A[row_num][j - 1] + getDist(0, j);
	}


	cout << "The Optimum tour cost is(double) " << optimum_tour_cost << endl;
	cout << "The Optimum tour cost is(int) " << (int)optimum_tour_cost << endl;

	
	/* CODE USED WHILE BREAKING UP SUBPROBLEMS INTO SNALLER CHUNKS
	double temp = getDist(0,1);
	cout << "The distance between city 0 and  1 is " <<  temp << endl;
	optimum_tour_cost = optimum_tour_cost + 14662 - (2* temp);
	cout << "Final Answer(double) : " << optimum_tour_cost << endl;
	cout << "Final Answer(int) : " << (int)optimum_tour_cost << endl;*/

	//Free up memory
	for (size_t i = 0; i < num_rows; i++) {
		free(A[i]);
	}
	free(A);
	free(city_coordinates);
	for (auto it = sub_problems.begin(); it != sub_problems.end(); ++it) {
		sub_problems[it->first].clear();
	}
	sub_problems.clear();
	row_no.clear();

	cout << "End of program." << endl;
	return 0;
}





double getDist(size_t city_num_one, size_t city_num_two) {
	pair<double, double> pair1 = city_coordinates[city_num_one];
	pair<double, double> pair2 = city_coordinates[city_num_two];

	return sqrt(pow(pair1.first - pair2.first, 2) + pow(pair1.second - pair2.second, 2));
}