//============================================================================
// Name        : countingInversions.cpp
// Author      : Veinstin Furtado
// Version     :
// Copyright   : Your copyright notice
// Description : Counting inversions in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <fstream>

using namespace std;

vector<int> input_vector;

long long int inversion_count = 0;

void merge_sort(int leftIndex, int rightIndex);

void merge(int leftIndex,int midIndex,int rightIndex);

//Driver Code
int main() {
	string line;
	int temp;
	ifstream myfile ("C:\\Users\\veins\\OneDrive\\Desktop\\data_set_week2.txt");
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

	int vector_length = (input_vector.size())-1;
	merge_sort(0,vector_length);
	cout << "no of inversions " << inversion_count << endl;
	return 0;
}

//recursive function to divide the inputs into single(sorted) elements followed by a merge
void merge_sort(int leftIndex, int rightIndex){
	int midIndex = 0;
	if(leftIndex < rightIndex){
		midIndex = (leftIndex+rightIndex)/2;
		merge_sort(leftIndex,midIndex);
		merge_sort(midIndex+1,rightIndex);
		merge(leftIndex,midIndex,rightIndex);
	}
}

void merge(int leftIndex,int midIndex, int rightIndex){
	int helperArray[(rightIndex-leftIndex)+1];
	int i = 0;
	int j = leftIndex;
	int k = midIndex+1;
	while(j <= midIndex && k <= rightIndex){
		if(input_vector[j] < input_vector[k]){
			helperArray[i] = input_vector[j];
			i++;
			j++;
		}else if(input_vector[k] < input_vector[j]){
			helperArray[i] = input_vector[k];
			i++;
			k++;
			/*
			 * Code To Count Inversions
			 *
			 */
			inversion_count = inversion_count + ((midIndex-j)+1);
		}else{
			helperArray[i] = input_vector[j];
			i++;
			j++;
		}
	}

	//If the elements on the left have exhausted
	if((j > midIndex) && (k <= rightIndex)){
		while(k <= rightIndex){
			helperArray[i] = input_vector[k];
			i++;
			k++;
		}
	}

	//If the elements on the right have exhausted
	if((j <= midIndex) && (k > rightIndex)){
		while(j <= midIndex){
			helperArray[i] = input_vector[j];
			i++;
			j++;
		}
	}

	//Copy elements from the helperArray to the original vector
	for (int elem : helperArray){
		input_vector[leftIndex] = elem;
		leftIndex++;
	}

}


