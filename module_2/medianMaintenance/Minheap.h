//==================================================================================================================
// Name        : Heap.h
// Author      : Veinstin Furtado
// Version     :
// Copyright   : Your copyright notice
// Description : Implementation of a min heap. This heap is built based on Floyd's algorithm.
//====================================================================================================================
#pragma once
#include <unordered_map>
#include <vector>
#include <iostream>

using namespace std;

class Minheap {

public:
	int heap_vector_size;
	vector<int> heap_vector;
	Minheap(vector<int> inputVector);
	void build_heap();
	/*
	 * The min heapify takes in parent node as input
	 */
	void heapify(size_t i);
	void bubbleUp(size_t index);
	void bubbleDown(size_t index);
	void insertNodeIntoHeap(int newnode);
	void deleteNodeFromHeap(size_t indexToRemove);
	size_t getLeftChildPosition(size_t  index);
	size_t getRightChildPosition(size_t  index);
	size_t getParentPosition(size_t index);
	void swap(size_t index1, size_t index2);
	size_t getIndexForMinValue(size_t index1, size_t index2, size_t index3);
	void printHeap();
};
