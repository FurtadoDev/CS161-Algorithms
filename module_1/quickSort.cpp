//============================================================================
// Name        : quickSort.cpp
// Author      : Veinstin Furtado
// Version     :
// Copyright   : Your copyright notice
// Description : QuickSort in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

vector<int> input_vector;
int pivot;
int count_comparisons = 0;
int count_comparisons1 = 0;
int sub_vectorLength = 0;
void recursiveCall(int leftIndex, int rightIndex);
int partition(int leftIndex, int rightIndex);
void swap(int index1, int index2);




int main() {

	string line;
	int temp;
	ifstream myfile ("C:\\Users\\veins\\OneDrive\\Desktop\\data_set_week3.txt");
	if (myfile.is_open())
	{
	   while (getline(myfile,line))
	   {
		 temp = stoi(line,nullptr,10);
		 input_vector.push_back(temp);
	   }
	   myfile.close();
	}
	else{
	   cout << "Unable to open file";
	}

	recursiveCall(0, input_vector.size() - 1);
	cout << "Total number of comparisons : " << count_comparisons << endl; // prints the number of comparisons
	cout << "Total number of comparisons1 : " << count_comparisons1 << endl;
	for(unsigned int i = 0; i < input_vector.size(); i++){
		cout << input_vector[i] << endl;
	}
	return 0;
}


void recursiveCall(int leftIndex, int rightIndex){
	//Step 1 : Partition the array
	//Step 2 : Call itself recursively
	if(leftIndex < rightIndex){
		sub_vectorLength = (rightIndex - leftIndex) + 1;
		count_comparisons = count_comparisons + (sub_vectorLength - 1);
		int i = partition(leftIndex, rightIndex);
		recursiveCall(leftIndex, i-2);
		recursiveCall(i, rightIndex);
	}
}
void swap(int index1, int index2){
	if((index2 - index1) > 0){// if the indexes are the same, no swap would be required
		int temp = input_vector[index1];
		input_vector[index1] = input_vector[index2];
		input_vector[index2] = temp;
	}
}

int getMedianIndex(int startIndex, int lastIndex){
	int length = (lastIndex - startIndex) + 1;
	int middle_element;
	int middleIndex;
	if(length%2 == 0){
		middleIndex = startIndex + ((length/2) -1);
		middle_element = input_vector[middleIndex];
	}else{
		middleIndex = startIndex + (length/2);
		middle_element = input_vector[middleIndex];
	}

	if(((input_vector[startIndex] > input_vector[middleIndex]) && (input_vector[startIndex] < input_vector[lastIndex])) || ((input_vector[startIndex] > input_vector[lastIndex]) && (input_vector[startIndex] < input_vector[middleIndex]))){
			return startIndex;
	}
	if(((input_vector[middleIndex] > input_vector[startIndex]) && (input_vector[middleIndex] < input_vector[lastIndex])) || ((input_vector[middleIndex] > input_vector[lastIndex]) && (input_vector[middleIndex] < input_vector[startIndex]))){
			return middleIndex;
	}
	if(((input_vector[lastIndex] > input_vector[startIndex]) && (input_vector[lastIndex] < input_vector[middleIndex])) || ((input_vector[lastIndex] > input_vector[middleIndex]) && (input_vector[lastIndex] < input_vector[startIndex]))){
			return lastIndex;
	}
}
int partition(int leftIndex, int rightIndex){
	count_comparisons1 = count_comparisons1 + (rightIndex-leftIndex) + 1 - 1;

	//Choose pivot depending on the question
	swap(leftIndex, getMedianIndex(leftIndex, rightIndex));
	//swap(leftIndex,rightIndex);

	pivot = input_vector[leftIndex]; //choose a pivot according to the pivoting rule in the question
	int i = leftIndex + 1;
	for(int j = leftIndex+1; j <= rightIndex; j++){
		if(input_vector[j] < pivot){
			swap(i,j);
			i++;
		}
	}
	swap(leftIndex,i-1);
	return i;
}


