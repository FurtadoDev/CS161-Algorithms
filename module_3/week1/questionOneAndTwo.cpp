//==================================================================================================================
// Name        : questionOneAndTwo.cpp
// Author      : Veinstin Furtado
// Version     :
// Copyright   : Your copyright notice
// Description : Greedy algorithm that schedules jobs in decreasing order of the difference (weight - length) and decreasing order of ratios (weight/length), Ansi-style
// References  : Tim Roughgarden, "Algorithms Illuminated - Part 3"
//====================================================================================================================

#include <iostream>     // std::cout
#include <functional>   // std::plus
#include <algorithm>    // std::transform
#include <iostream>
#include <sstream>
#include <fstream>
#include <unordered_map>

using namespace std;


typedef struct {
	long long int job_weight;
	long long int job_length;
	long long int strategy;
} aTuple;


vector<aTuple> *jobs;
void merge_sort(int l, int r);
void merge(int l, int mid, int r);

int main() {
	int idx = 0;
	int temp_int;
	int vector_size = 0;
	long long int sum = 0;
	long long int comp_time = 0;
	int len;
	string line;
	stringstream str_strm;
	ifstream myfile("C:\\Users\\vrfur\\Desktop\\Algorithms.git\\trunk\\module_3\\module_3_datasets\\week1\\jobs.txt"); //jobs.txt
	if (myfile.is_open())
	{
		getline(myfile, line);
		str_strm << line;
		str_strm >> vector_size;
		str_strm.clear();
		jobs = new vector<aTuple>(vector_size);

		while (getline(myfile, line))
		{
			aTuple theTuple;
			len = line.length();
			while (line[len - 1] == ' ') { line.erase(--len, 1); } //right trim
			while (line[0] == ' ') { line.erase(0, 1); } //left trim
			str_strm << line; //output the entire line into the string stream
			str_strm >> temp_int;
			theTuple.job_weight = temp_int;
			str_strm >> temp_int;
			theTuple.job_length = temp_int;
			theTuple.strategy = (theTuple.job_weight) - (theTuple.job_length); //change the strategy according to the question
			jobs->operator[](idx) = theTuple;
			idx++;
			str_strm.clear();
		}
			myfile.close();
	}
	else {
		cout << "Cannot open file" << endl;
	}


	merge_sort(0, vector_size-1);
	for (int i = 0; i < vector_size; i++) {
		comp_time = comp_time + (jobs->operator[](i).job_length);
		sum = sum + ((jobs->operator[](i).job_weight) * comp_time);
		/*
		cout << jobs->operator[](i).job_weight << endl;
		cout << jobs->operator[](i).job_length << endl;
		cout << jobs->operator[](i).strategy << endl;
		cout << endl;
		*/
	}
	cout << "Answer : " << sum << endl;
	
	delete jobs;
	return 0;
}


void merge_sort(int l, int r) {
	int mid;
	if (l < r) {
		mid = (l+r) / 2;
		merge_sort(l, mid);
		merge_sort(mid+1, r);
		merge(l, mid, r);
	}
}

void merge(int l, int mid, int r) {
	vector<aTuple>* temp = new vector<aTuple>(r-l+1);
	int ptr1 = l;
	int ptr2 = mid + 1;
	int idx = 0;
	while (ptr1 <= mid && ptr2 <= r) {
		if (jobs->operator[](ptr1).strategy < jobs->operator[](ptr2).strategy) {
			temp->operator[](idx) = jobs->operator[](ptr2);
			ptr2++;
			idx++;
		}
		else if (jobs->operator[](ptr1).strategy > jobs->operator[](ptr2).strategy) {
			temp->operator[](idx) = jobs->operator[](ptr1);
			ptr1++;
			idx++;
		}
		else {// the strategy values are equal. check weights to break the tie
			if (jobs->operator[](ptr1).job_weight < jobs->operator[](ptr2).job_weight) {
				temp->operator[](idx) = jobs->operator[](ptr2);
				idx++;
				ptr2++;
			}
			else if (jobs->operator[](ptr1).job_weight > jobs->operator[](ptr2).job_weight) {
				temp->operator[](idx) = jobs->operator[](ptr1);
				idx++;
				ptr1++;
			}
			else {// the weights are also equal. So in order to break the tie, we need to select the shorter job
				if (jobs->operator[](ptr1).job_length < jobs->operator[](ptr2).job_length) {
					temp->operator[](idx) = jobs->operator[](ptr1);
					idx++;
					ptr1++;
				}
				else if (jobs->operator[](ptr1).job_length > jobs->operator[](ptr2).job_length) {
					temp->operator[](idx) = jobs->operator[](ptr2);
					idx++;
					ptr2++;
				}
				else {//the strategy, weights and lengths are all equal so choose either any job.
					temp->operator[](idx) = jobs->operator[](ptr1);
					idx++;
					ptr1++;
				}
			}
		}
	}

	while (ptr2 <= r) {
		temp->operator[](idx) = jobs->operator[](ptr2);
		idx++;
		ptr2++;
	}
	while (ptr1 <= mid) {
		temp->operator[](idx) = jobs->operator[](ptr1);
		idx++;
		ptr1++;
	}

	idx = 0;
	for (int i = l; i <= r; i++) {
		jobs->operator[](i) = temp->operator[](idx);
		idx++;
	}
	delete temp;
}
