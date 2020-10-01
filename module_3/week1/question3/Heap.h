#pragma once
/*!
 * @file      Heap.h
 * @brief     Declaration of the Heap class.
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
#include <unordered_map>
#include <vector>
#include <iostream>

using namespace std;

class Heap {

public:
	/*
	* The vector passed into the heap should have unique nodes. The vector_positions are only valid for a vector with unique nodes or the vertex_positions will be messed up
	*/

	//map representing positions of different nodes within the heap vector
	unordered_map<int, int> vertex_positions;

	//vector of node-key values which is to be maintained as a heap
	vector<pair<int, int>> heap_vector;

	//size of the heap vector
	int heap_vector_size;

	/**
	 * Constructor which takes in a vector and initializes a heap
	 *
	 */
	Heap(vector<pair<int, int>> inputVector);

	/**
	 * Build a heap from the vector assined while calling the constructor
	 *
	 * @returns void
	 */
	void build_min_heap();
	
	/**
	 * Bubble a node up the heap based on it's key value
	 *
	 * @returns void
	 */
	void bubbleUp(size_t childIdx);
	
	/**
	 * Bubble a node down the heap based on it's key value
	 *
	 * @returns void
	 */
	void bubbleDown(size_t index);

	/**
	 * Given the pair repesenting a node-key value, insert it into the heap_vector while maintaining the heap property
	 *
	 * @returns void
	 */
	void insertNodeIntoHeap(pair<int, int> newnodeandkey);

	/**
	 * Given the index of an element, remove the element from the heap
	 *
	 * @returns void
	 */
	void deleteNodeFromHeap(size_t indexToRemove);

	/**
	 * Given the index of an element, return index of the left child of an element
	 *
	 * @returns a size_t value representing an index value
	 */
	size_t getLeftChildPosition(size_t  index);

	/**
	 * Given the index of an element, return index of the right child of the element
	 *
	 * @returns a size_t value representing an index value
	 */
	size_t getRightChildPosition(size_t  index);

	/**
	 * Given the index of an element, return index of the parent of an element
	 *
	 * @returns a size_t value representing an index value
	 */
	size_t getParentPosition(size_t index);

	/**
	 * Return the vector representing the heap
	 *
	 * @returns a vector
	 */
	vector<pair<int, int>> getHeapVector();

	/**
	 * Returns the parent index if the key of it's node is minimum, 
	 * else returns the index of the node with the minimum key
	 *
	 * @returns an index value representing the position with the lowest key value for it's node
	 */
	size_t getIndexForMinimumValue(size_t index1, size_t index2, size_t index3);

	/**
	 * Swap the contents of two positions in the heap vector
	 *
	 * @returns void
	 */
	void swap(size_t index1, size_t index2);

	/**
	 * Print the node-key values from the heap_vector
	 *
	 * @returns void
	 */
	void printHeap();

	/**
	 * Return the map representing node-position values
	 *
	 * @returns an unordered_map representing positions for nodes
	 */
	unordered_map<int, int> getMapForVertexPositions();

	/**
	 * Print the positions of each of the nodes in the heap_vector
	 *
	 * @returns void
	 */
	void printVertexPositions();
};
