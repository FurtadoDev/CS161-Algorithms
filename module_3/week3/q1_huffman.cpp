/*!
 * @file      q1_huffman.cpp
 * @brief     This file contains the implementation of the huffmans algorithm using two queues(linear runnning time) which is a better alternative to the implementation using a heap.
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



using namespace std;


struct symbol {
	int value;
	int freq;
	struct symbol* left_symbol;
	struct symbol* right_symbol;
	int minCodeLength;
	int maxCodeLength;
};
vector<struct symbol> symbols;
queue<struct symbol*> queue1;
queue<struct symbol*> queue2;
int num_symbols;

struct symbol* getSymbolWithMinFrequency();
void merge(struct symbol* s1, struct symbol* s2);
void free_tree(struct symbol* symbol);

int main() {
	int symbol = 1;
	int weight;

	int len;
	string line;
	stringstream str_strm;
	ifstream myfile("C:\\Users\\vrfur\\Desktop\\Algorithms.git\\trunk\\module_3\\module_3_datasets\\week3\\huffman.txt"); 
	if (myfile.is_open())
	{
		getline(myfile, line);
		str_strm << line;
		str_strm >> num_symbols;
		str_strm.clear();

		while (getline(myfile, line))
		{
			len = line.length();
			while (line[len - 1] == ' ') { line.erase(--len, 1); } //right trim
			while (line[0] == ' ') { line.erase(0, 1); } //left trim
			str_strm << line; //output the entire line into the string stream
			str_strm >> weight;
			
			struct symbol temp;
			temp.value = symbol;
			temp.freq = weight;
			temp.left_symbol = nullptr;
			temp.right_symbol = nullptr;
			temp.minCodeLength = 0;
			temp.maxCodeLength = 0;
			symbols.push_back(temp);

			symbol++;
			str_strm.clear();
		}
		myfile.close();
	}
	else {
		cout << "Cannot open file" << endl;
	}



	//TODO :: reserve size for symbols before initialization
	//Step 1 : Sort the input(ascending order)
	sort(symbols.begin(), symbols.end(), [](struct symbol lhs, struct symbol rhs) {
		return lhs.freq < rhs.freq;
	});

	//Step 2 :: Copy over the contents of the sorted vector to a queue
	for (int i = 0; i < num_symbols; i++) {

		struct symbol* temp = (struct symbol*)malloc(sizeof(struct symbol));
		
		temp->value = symbols[i].value;
		temp->freq = symbols[i].freq;
		temp->left_symbol = nullptr;
		temp->right_symbol = nullptr;
		temp->minCodeLength = 0;
		temp->maxCodeLength = 0;
		queue1.push(temp);
	}
	symbols.clear();
	symbols.shrink_to_fit();

	//Step 3 :: While queue1 is not emplty or queue2 is not empty
	struct symbol* min1 = nullptr;
	struct symbol* min2 = nullptr;
	while (!queue1.empty() || !queue2.empty()) {
		min1 = getSymbolWithMinFrequency();
		min2 = getSymbolWithMinFrequency();

		if(min2 != nullptr)
			merge(min1, min2);
	}
	

	cout << "Min code Length : " << min1->minCodeLength << endl;
	cout << "Max code Length : " << min1->maxCodeLength << endl;

	//Step 4 :: Clean up the tree
	free_tree(min1);

	return 0;
}



struct symbol* getSymbolWithMinFrequency() {
	
	struct symbol* min = nullptr;
	
	if (!queue1.empty() && !queue2.empty()) {
		if (queue1.front()->freq < queue2.front()->freq) {
			min = queue1.front();
			queue1.pop();
		}
		else {
			min = queue2.front();
			queue2.pop();
		}
	}
	else if(!queue1.empty() && queue2.empty()){
		min = queue1.front();
		queue1.pop();
	}
	else if(queue1.empty() && !queue2.empty()){
		min = queue2.front();
		queue2.pop();
	}
	else {//case : where both queues are empty
		return nullptr;
	}
	
	return min;
}

/*For each merge, add the count for min merges and max merges : Intuition could be wrong*/
void merge(struct symbol  *s1, struct symbol *s2) {
	
	struct symbol* parent = (struct symbol*)malloc(sizeof(struct symbol));
	parent->value = 0;
	parent->freq = s1->freq + s2->freq;
	parent->left_symbol = s1;
	parent->right_symbol = s2;
	parent->minCodeLength = 1 + min(parent->left_symbol->minCodeLength, parent->right_symbol->minCodeLength);
	parent->maxCodeLength = 1 + max(parent->left_symbol->maxCodeLength, parent->right_symbol->maxCodeLength);

	queue2.push(parent);
}


void free_tree(struct symbol* symbol) {
	if (symbol != nullptr) {
		free_tree(symbol->left_symbol);
		free_tree(symbol->right_symbol);
		free(symbol);
	}
}





