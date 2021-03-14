//#pragma comment(linker, "/STACK:2000000")
//#pragma comment(linker, "/HEAP:2000000")

/*!
 * @file      tsp_nn.cpp
 * @brief     This file contains the solution of the travelling salesman problem using Nearest neighbout heuristic(which uses the KD-tree)
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
#include <unordered_set>
#include "Kdtree.h"

using namespace std;


vector<pair<size_t, pair<double, double>>> dataset;
size_t num_cities;

int main()
{
    /*TEST CODE
	vector<pair<size_t, pair<double, double>>> dataset1;
    dataset1.reserve(6);
    dataset1.push_back(make_pair(1, make_pair(7, 2)));
    dataset1.push_back(make_pair(2, make_pair(5, 4)));
    dataset1.push_back(make_pair(3, make_pair(2, 3)));
    dataset1.push_back(make_pair(4, make_pair(4, 7)));
    dataset1.push_back(make_pair(5, make_pair(9, 6)));
    dataset1.push_back(make_pair(6, make_pair(8, 1)));
	*/
	/*TEST CODE
	vector<pair<size_t, pair<double, double>>> dataset2;
	dataset2.reserve(6);
	dataset2.push_back(make_pair(1, make_pair(2,3)));
	dataset2.push_back(make_pair(2, make_pair(1,5)));
	dataset2.push_back(make_pair(3, make_pair(4,2)));
	dataset2.push_back(make_pair(4, make_pair(4,5)));
	dataset2.push_back(make_pair(5, make_pair(3,3)));
	dataset2.push_back(make_pair(6, make_pair(4,4)));
    */

	
    size_t city_no;
	double temp_x_coordinate;
	double temp_y_coordinate;
	int len;
	string line;
	stringstream str_strm;
	ifstream myfile("C:\\Users\\vrfur\\Desktop\\Algorithms.git\\trunk\\module_4\\module_4_datasets\\week3\\test.txt"); //nn.txt
	if (myfile.is_open())
	{
		getline(myfile, line);
		str_strm << line;
		str_strm >> num_cities;
		dataset.reserve(num_cities);
		str_strm.clear();

		while (getline(myfile, line))
		{
			len = line.length();
			while (line[len - 1] == ' ') { line.erase(--len, 1); } //right trim
			while (line[0] == ' ') { line.erase(0, 1); } //left trim
			str_strm << line; //output the entire line into the string stream
            str_strm >> city_no;
			str_strm >> temp_x_coordinate;
			str_strm >> temp_y_coordinate;
			dataset.push_back(make_pair(city_no,make_pair(temp_x_coordinate, temp_y_coordinate)));
			str_strm.clear();
		}
		myfile.close();
	}
	else {
		cout << "Cannot open file" << endl;
	}
	
		
	/*Beginning of TSP-algorithm*/
	double final_answer = 0;
	Kdtree* tsp_tree = new Kdtree(dataset);
	Kdtree::Node* input_node = tsp_tree->first_city;
	tsp_tree->visited_vertices.insert(tsp_tree->first_city->index);
	
	size_t i = dataset.size();
	while (i >= 2) {
		tsp_tree->recurse(input_node, tsp_tree->parent_node, 0);
		
		input_node = tsp_tree->best_city_current;
		tsp_tree->visited_vertices.insert(tsp_tree->best_city_current->index);
		
		final_answer = final_answer + tsp_tree->best_distance_current;
		i--;
	}

	final_answer = final_answer + tsp_tree->getDist(tsp_tree->first_city->data_point, tsp_tree->best_city_current->data_point);
	cout << "The Final Distance is : " << (int)final_answer << endl;

	delete tsp_tree;
    return 0;
}