//==================================================================================================================
// Name        : Heap.h
// Author      : Veinstin Furtado
// Version     :
// Copyright   : Your copyright notice
// Description : Implementation of a heap. This heap is built based on Floyd's algorithm.
//====================================================================================================================
#pragma once
#include <unordered_map>
#include <vector>
#include <iostream>

using namespace std;

class Heap { 

public:  
	/*
	* The vector passed into the heap should have unique nodes. The vector_positions are only valid for a vector with unique nodes or the vertex_positions will be messed up
	*/
	unordered_map<int, int> vertex_positions;
	vector<pair<int, int>> heap_vector;//node and key values
	int heap_vector_size;

	Heap(vector<pair<int, int>> inputVector);   
    void build_min_heap(); 
	/*
	 * The min heapify takes in parent node as input
	 */
	void min_heapify(size_t i);
	void bubbleUp(size_t index);
	void bubbleDown(size_t index);
	void insertNodeIntoHeap(pair<int, int> newnodeandkey);
	void deleteNodeFromHeap(size_t indexToRemove);
	size_t getLeftChildPosition(size_t  index);
	size_t getRightChildPosition(size_t  index);
	size_t getParentPosition(size_t index);
	vector<pair<int,int>> getHeapVector();
	size_t getIndexForMinimumValue(size_t index1, size_t index2, size_t index3);
	void swap(size_t index1, size_t index2);
	void printHeap();
	unordered_map<int, int> getMapForVertexPositions();
	void printVertexPositions();
};