//==================================================================================================================
// Name        : TwoSum.cpp
// Author      : Veinstin Furtado
// Version     :
// Copyright   : Your copyright notice
// Description : Two Sum problem using hash-tables, Ansi-style
// References	: Tim Roughgarden, "Algorithms Illuminated - Part 2"
//====================================================================================================================
#include <utility>
#include <iostream> 
#include <sstream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <cstring>
#include <cstdlib>
#include <unordered_map>
#include <map>
#include <unordered_set>


using namespace std;
vector<long long int>* v;

void make_unique(vector<long long int>* v, int vector_size);
int computeNumberOfTargetValues(vector<long long int>* sortedVector);

int main() {
	int INPUT_SIZE = 1000000;
	v = new vector<long long int>(INPUT_SIZE);
	int idx = 0;

	
	int len;
	string line;
	stringstream str_strm;
	ifstream myfile("C:\\Users\\vrfur\\Desktop\\Algorithms.git\\trunk\\module_2\\module_2_datasets\\algo1-programming_prob-2sum.txt"); //algo1-programming_prob-2sum.txt
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			len = line.length();
			while (line[len - 1] == ' ') { line.erase(--len, 1); } //right trim
			while (line[0] == ' ') { line.erase(0, 1); } //left trim
			str_strm << line; //output the entire line into the string stream
			long long int temp_int;
			str_strm >> temp_int;
			//cout << temp_int << endl;
			v->operator[](idx) = temp_int;
			idx++;
			str_strm.clear();
		}
	}
	else {
		cout << "Cannot open file" << endl;
	}

	cout << "First Element Before Sort sub-routine : " << v->operator[](0) << endl;
	cout << "Last Element Before Sort sub-routine : " << v->operator[](INPUT_SIZE-1) << endl;
	std::sort(v->begin(), v->end());
	cout << "Initial size after sorting: " << v->size() << endl;
	make_unique(v, INPUT_SIZE);
	cout << "Final size after removing duplicates: " << v->size() << endl;
	cout << "The number of target values are : " << computeNumberOfTargetValues(v) << endl;
	v->clear();
	v->shrink_to_fit();
	
	return 0;
}


void make_unique(vector<long long int> *v, int vector_size) {
	long long int* first = &v->operator[](0);
	long long int* result = &v->operator[](0);
	long long int* last = &(v->operator[](vector_size-1));
	int pos = 0;
	while (++first != last+1) {

		if (*first == *result)
			continue;

		pos++;
		if (++result != first)
			*result = std::move(*first);
	}
	v->erase(v->begin()+pos+1, v->end());
}


int computeNumberOfTargetValues(vector<long long int>* sortedVector) {
	unordered_set<long long int> targetValues;
	long long int sum = 0;
	int sum_target = 0;
	int lhs = 0;
	int rhs = sortedVector->size() - 1;
	while (lhs < rhs) {
		sum = sortedVector->operator[](lhs) + sortedVector->operator[](rhs);
		if (sum > 10000) {
			rhs--;
		}
		else if (sum < -10000) {
			lhs++;
		}
		else {
			if (targetValues.find(sum) == targetValues.end()) {
				targetValues.insert(sum);
				sum_target++;
			}
			lhs++;
		}
	}
	return sum_target;
}