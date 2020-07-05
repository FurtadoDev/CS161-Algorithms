#include "Maxheap.h"

Maxheap::Maxheap(vector<int> inputVector) {
	heap_vector = inputVector;
	build_heap();
}

size_t  Maxheap::getLeftChildPosition(size_t  index) {
	return ((index + 1) * 2) - 1;
}

size_t  Maxheap::getRightChildPosition(size_t  index) {
	return (index + 1) * 2;
}

size_t Maxheap::getParentPosition(size_t index) {
	return floor((index - 1) / 2);
}

void Maxheap::swap(size_t index1, size_t index2) {
	int temp;
	temp = heap_vector[index1];
	heap_vector[index1] = heap_vector[index2];
	heap_vector[index2] = temp;
}


void Maxheap::build_heap() {
	heap_vector_size = size(heap_vector);
	if (heap_vector_size >= 2) { //if the size of the heap is less than 2(eg. 1), it is already a heap. If it is 0, there is nothing to heapify.
		size_t lim = (heap_vector_size) / 2;
		for (size_t i = lim; i >= 1; i--) {
			//pass the parent node to heapify
			bubbleDown(i - 1);
		}
	}
}


size_t Maxheap::getIndexForMaxValue(size_t index1, size_t index2, size_t index3) {
	//think about what happens if two or three values are the same. : either index could be the minimum Index
	int maxValue = heap_vector[index1];
	size_t maxIndex = index1;
	if (heap_vector[index2] > maxValue) {
		maxValue = heap_vector[index2];
		maxIndex = index2;
	}
	if (heap_vector[index3] > maxValue) {
		maxValue = heap_vector[index3];
		maxIndex = index3;
	}
	return maxIndex;
}

void Maxheap::bubbleDown(size_t parentIndex) {
	size_t leftChildIndex = getLeftChildPosition(parentIndex);
	size_t rightChildIndex = getRightChildPosition(parentIndex);
	size_t indexHoldingMaximum;
	if (leftChildIndex <= heap_vector_size - 1) {//if it has at least one child(left child)
		if (rightChildIndex <= heap_vector_size - 1) {//if it has a right child(so it has two children)
			indexHoldingMaximum = getIndexForMaxValue(parentIndex, leftChildIndex, rightChildIndex);
			if (indexHoldingMaximum != parentIndex) {
				swap(parentIndex, indexHoldingMaximum);
				bubbleDown(indexHoldingMaximum);
			}
		}
		else {//it has only one child
			if (heap_vector[leftChildIndex] > heap_vector[parentIndex]) {
				swap(leftChildIndex, parentIndex);
				//TODO is no need to call bubbleDown here since we've reached the end of the tree
			}
		}
	}
}

//the vector should already be a min heap for bubble up to work
void Maxheap::bubbleUp(size_t childIndex) {
	size_t parentIndex;
	size_t leftChildIndex;
	size_t rightChildIndex;
	size_t indexHoldingMaximum;
	if (childIndex >= 1) {//The fact that we are inside this if statement confirms that we have at least one child(left child) below the parent. This is why the if condition below is commented
		parentIndex = getParentPosition(childIndex);
		leftChildIndex = getLeftChildPosition(parentIndex);
		rightChildIndex = getRightChildPosition(parentIndex);
		//if (leftChildIndex <= heap_vector_size-1) {//it has at least one child(i.e., the left child)
		if (rightChildIndex <= heap_vector_size - 1) {//it has a left child and a right child
			indexHoldingMaximum = getIndexForMaxValue(parentIndex, leftChildIndex, rightChildIndex);
			if (indexHoldingMaximum != parentIndex) {
				swap(indexHoldingMaximum, parentIndex);
				bubbleUp(parentIndex);
			}
		}
		else {//it only has a left child
			if (heap_vector[leftChildIndex] > heap_vector[parentIndex]) {
				swap(leftChildIndex, parentIndex);
				bubbleUp(parentIndex);
			}
		}
		//}
	}
}

void Maxheap::insertNodeIntoHeap(int newnode) {
	heap_vector.push_back(newnode);
	heap_vector_size++;
	bubbleUp(heap_vector_size - 1);
}

void Maxheap::deleteNodeFromHeap(size_t indexToRemove) {
	heap_vector[indexToRemove] = heap_vector[heap_vector_size - 1];
	heap_vector.pop_back();
	heap_vector_size--;

	size_t parentIndex;
	size_t leftChildIndex;
	//Bubble up or down and rearrange the heap
	if (heap_vector_size >= 2) {//call the bubble up or bubble down functions only if there are at least 2 elements in the heap
		if (indexToRemove == 0) {
			//call the bubble down algorithm
			bubbleDown(indexToRemove);
		}
		else {
			parentIndex = getParentPosition(indexToRemove);
			if (heap_vector[indexToRemove] > heap_vector[parentIndex]) {
				bubbleUp(indexToRemove);
			}
			else {
				bubbleDown(indexToRemove);
			}
		}
	}
}

void Maxheap::printHeap() {
	for (auto i = heap_vector.begin(); i != heap_vector.end(); ++i) {
		cout << *i << endl;
	}
}
