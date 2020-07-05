#pragma once
#include <unordered_map>
#include <vector>
#include <iostream>

using namespace std;
class Maxheap
{
public:
	int heap_vector_size;
	vector<int> heap_vector;
	Maxheap(vector<int> inputVector);
	void build_heap();
	void bubbleUp(size_t index);
	void bubbleDown(size_t index);
	void insertNodeIntoHeap(int newnode);
	void deleteNodeFromHeap(size_t indexToRemove);
	size_t getLeftChildPosition(size_t  index);
	size_t getRightChildPosition(size_t  index);
	size_t getParentPosition(size_t index);
	void swap(size_t index1, size_t index2);
	size_t getIndexForMaxValue(size_t index1, size_t index2, size_t index3);
	void printHeap();
};

