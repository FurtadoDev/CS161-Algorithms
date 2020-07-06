//============================================================================
// Name        : MedianMaintenance.cpp
// Author      : Veinstin Furtado
// Version     :
// Copyright   : Your copyright notice
// Description : Median Maintenance Algorithm using min and max heaps in C++, Ansi-style
//============================================================================
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <fstream>
#include "Minheap.h"
#include "Maxheap.h"

using namespace std;



int main() {
	int linenumber = 0;
	vector<int> heapvector;
	Minheap minheap(heapvector);
	Maxheap maxheap(heapvector);
	int sumOfMedians  = 0;
	int median = 0;

	string line;
	int temp;
	ifstream myfile("C:\\Users\\veins\\OneDrive\\Desktop\\Algorithms.git\\trunk\\module_2\\module_2_datasets\\median_maintenance_data_set.txt"); //median_maintenance_data_set
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			temp = stoi(line, nullptr, 10);
			//Call the Driver code for the Median Maintenance Algorithm
			if ((maxheap.heap_vector_size == 0) || temp < maxheap.heap_vector[0]) { //if the number is lesser than the biggest(topmost) element in the max heap, insert it in the max heap
					maxheap.insertNodeIntoHeap(temp);
					if ((maxheap.heap_vector_size - minheap.heap_vector_size) > 1) {
						minheap.insertNodeIntoHeap(maxheap.heap_vector[0]);
						maxheap.deleteNodeFromHeap(0);
					}
			}
			else if ((minheap.heap_vector_size == 0) || temp > minheap.heap_vector[0]) { //if the number is more than the smallest(topmost) element of the min heap, insert it in the min heap
					minheap.insertNodeIntoHeap(temp);
					if ((minheap.heap_vector_size - maxheap.heap_vector_size) > 1) {
						maxheap.insertNodeIntoHeap(minheap.heap_vector[0]);
						minheap.deleteNodeFromHeap(0);
					}
			}
			else { //else you can put it in either heap(i chose the max heap)
				maxheap.insertNodeIntoHeap(temp);
				if ((maxheap.heap_vector_size - minheap.heap_vector_size) > 1) {
					minheap.insertNodeIntoHeap(maxheap.heap_vector[0]);
					maxheap.deleteNodeFromHeap(0);
				}
			}
			
			if ((maxheap.heap_vector_size % 2 == 0) && (minheap.heap_vector_size % 2 == 0)) { //both are even
				median = maxheap.heap_vector[0];
			}

			if ((maxheap.heap_vector_size % 2 != 0) && (minheap.heap_vector_size % 2 != 0)) { //both are odd
				median = maxheap.heap_vector[0];
			}

			if ((maxheap.heap_vector_size % 2 == 0) && (minheap.heap_vector_size % 2 != 0)) { //max heap size is even and min heap size is odd
				if (maxheap.heap_vector_size > minheap.heap_vector_size)
					median = maxheap.heap_vector[0];
				else
					median = minheap.heap_vector[0];
			}

			if ((maxheap.heap_vector_size % 2 != 0) && (minheap.heap_vector_size % 2 == 0)) { //max heap size is odd and min heap size is even
				if (maxheap.heap_vector_size > minheap.heap_vector_size)
					median = maxheap.heap_vector[0];
				else
					median = minheap.heap_vector[0];
			}
			sumOfMedians += median;
		}

		myfile.close();
	}
	else {
		cout << "Unable to open file";
	}

	cout << "Final Result : " << sumOfMedians%10000 << endl;

	return 0;
}