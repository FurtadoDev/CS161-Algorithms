// testDijkstra.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include <list>
#include <utility>
#include <iostream>     // std::cout
#include <algorithm>    // std::make_heap, std::pop_heap, std::push_heap, std::sort_heap
#include <vector>       // std::vector


using namespace std;

//TODO: no of vertices should be 1 more since there is no zero vertex in our dataset
class Graph {

	int num_vertices;
	list<pair<int, int>>* adjList;
	public:
		Graph(int num_vertices);
		
		void addEdge(int u, int v, int w);
};

Graph::Graph(int num_vertices)
{
	this->num_vertices = num_vertices;
	this->adjList = new list<pair<int, int>>[num_vertices];
}

void Graph::addEdge(int u, int v, int w) {
	this->adjList[u].push_back(make_pair(v,w));
	this->adjList[v].push_back(make_pair(u,w));
}

class Heap {

	public:
		std::vector<int> heapVector;
		int heapVector_size;
		Heap(vector<int> vertices);
		void bubbleUp(size_t index);
		void bubbleDown(size_t index);
		void swap(size_t index1, size_t index2);
		size_t getIndexForMinimumValue(int index1, int index2, int index3);
		size_t  getLeftChildPosition(size_t  index);
		size_t  getRightChildPosition(size_t  index);
		size_t getParentPosition(size_t index);
		void deleteNodeFromHeap(size_t indexToRemove);
};

Heap::Heap(vector<int> vertices) {
	this->heapVector = vertices;
	std::make_heap(begin(this->heapVector), end(this->heapVector), std::greater<int>{});
	this->heapVector_size = size(heapVector);
}

void Heap::deleteNodeFromHeap(size_t indexToRemove) {
	size_t parentIndex = getParentPosition(indexToRemove);
	size_t leftChild = getLeftChildPosition(indexToRemove);
	//Step 1: Replace the node with the farthest right node.
	heapVector[indexToRemove] = heapVector[heapVector_size - 1];
	//Step 2: Bubble it up or down to maintain heap property.
	if (indexToRemove == 0) {
		bubbleDown(indexToRemove);
	}
	else {//the index range is from 1 to size-1
		if (heapVector[indexToRemove] < heapVector[parentIndex])
		{
			//call the bubble up algorithm
			bubbleUp(indexToRemove);
		}
		else {
			//call the bubble down algorithm
			bubbleDown(indexToRemove);
		}
	}
	//pop_heap(begin(myheap), end(myheap), std::greater<int>{});
	heapVector.pop_back();
	heapVector_size--;
}

void Heap::bubbleUp(size_t index) {
	size_t currentNodeIndex = index;
	size_t parentNodeIndex = getParentPosition(currentNodeIndex);

	while (currentNodeIndex >= 1) { //while it has a parent node bubble up : TODO : Check if condition is right 
		if (heapVector[currentNodeIndex] < heapVector[parentNodeIndex]) {
			//swap and update the current node index and the parent nodeindex
			swap(currentNodeIndex, parentNodeIndex);
			currentNodeIndex = parentNodeIndex;
			parentNodeIndex = getParentPosition(currentNodeIndex);
		}
		else {
			break;
		}
	}
}

void Heap::bubbleDown(size_t index) {
	size_t parentNodeIndex = index;
	size_t leftChildIndex = getLeftChildPosition(parentNodeIndex);
	size_t rightChildIndex = getRightChildPosition(parentNodeIndex);
	//size_t heap_size = size(heapVector);
	size_t chosenMinIndex;
	while (leftChildIndex <= heapVector_size - 1) {//while it has at least one child node bubble down
		if ((leftChildIndex <= heapVector_size - 1) && (rightChildIndex <= heapVector_size - 1)) {//if it has two child nodes
			//swap if the minimum index is not the parent 
			chosenMinIndex = getIndexForMinimumValue(parentNodeIndex, leftChildIndex, rightChildIndex);
			if (chosenMinIndex != parentNodeIndex) {
				swap(parentNodeIndex, chosenMinIndex);
				parentNodeIndex = chosenMinIndex;
				leftChildIndex = getLeftChildPosition(parentNodeIndex);
				rightChildIndex = getRightChildPosition(parentNodeIndex);
			}
			else {
				//break if the heap property is already maintained
				break;
			}
		}
		else { //else it has only one child node
			if (this->heapVector[leftChildIndex] < this->heapVector[parentNodeIndex]) {
				swap(leftChildIndex, parentNodeIndex);
				parentNodeIndex = leftChildIndex;
				leftChildIndex = getLeftChildPosition(parentNodeIndex);
				rightChildIndex = getRightChildPosition(parentNodeIndex);
			}
			else {
				//break if the heap property is already maintained
				break;
			}
		}
	}
}

void Heap::swap(size_t index1, size_t index2) {
	int temp;
	temp = heapVector[index1];
	heapVector[index1] = heapVector[index2];
	heapVector[index2] = temp;
}

size_t Heap::getIndexForMinimumValue(int index1, int index2, int index3) {
	int minimumValue;
	size_t minimumIndex;

	minimumValue = heapVector[index1];
	minimumIndex = index1;

	if (heapVector[index2] < minimumValue) {
		minimumValue = heapVector[index2];
		minimumIndex = index2;
	}
	if (heapVector[index3] < minimumValue) {
		minimumValue = heapVector[index3];
		minimumIndex = index3;
	}
	return minimumIndex;
}

size_t  Heap::getLeftChildPosition(size_t  index) {
	return ((index + 1) * 2) - 1;
}

size_t  Heap::getRightChildPosition(size_t  index) {
	return (index + 1) * 2;
}

size_t Heap::getParentPosition(size_t index) {
	return floor((index - 1) / 2);
}

int main()
{
	vector<int> vertices;
	//vertices = {1, 5, 6, 9, 11, 8, 15, 17, 21};
	vertices = {1, 9, 22, 17, 11, 33, 27, 21, 19};

	Heap hp(vertices);
	for (int number : hp.heapVector)
	{
		std::cout << number << ' ';
	}

	cout << endl;
	
	//variables for bookkeeping
	size_t indexToRemove = 5;
	hp.deleteNodeFromHeap(indexToRemove);

	cout << "Final Result :" << endl;
	for (int number : hp.heapVector)
	{
		std::cout << number << ' ';
	}

}

