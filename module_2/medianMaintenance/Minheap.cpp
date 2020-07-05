#include "Minheap.h" 


Minheap::Minheap(vector<int> inputVector) {
	heap_vector = inputVector;
	build_heap();
}

size_t  Minheap::getLeftChildPosition(size_t  index) {
	return ((index + 1) * 2) - 1;
}

size_t  Minheap::getRightChildPosition(size_t  index) {
	return (index + 1) * 2;
}

size_t Minheap::getParentPosition(size_t index) {
	return floor((index - 1) / 2);
}

void Minheap::swap(size_t index1, size_t index2) {
	int temp;
	temp = heap_vector[index1];
	heap_vector[index1] = heap_vector[index2];
	heap_vector[index2] = temp;
}

void Minheap::build_heap() {
	heap_vector_size = size(heap_vector);
	if (heap_vector_size >= 2) { //if the size of the heap is less than 2(eg. 1), it is already a heap. If it is 0, there is nothing to heapify.
		size_t lim = (heap_vector_size) / 2;
		for (size_t i = lim; i >= 1; i--) {
			//pass the parent node to heapify
			//heapify(i - 1);
			bubbleDown(i - 1);
		}
	}
}


/*
* Left Incomplete. Will complete if I get some genius idea
*/
void Minheap::heapify(size_t parentIndex) {
	size_t leftChildIndex = getLeftChildPosition(parentIndex);
	size_t rightChildIndex = getRightChildPosition(parentIndex);
	size_t minimumIndex;
	//the fact that heapify is called confirms that we got at a left child for sure.
	if (rightChildIndex <= heap_vector_size - 1) {//if it has a right child
		minimumIndex = getIndexForMinValue(parentIndex, leftChildIndex, rightChildIndex);
		if (minimumIndex != parentIndex) {
			//TODO: call the bubble down algorithm to bubble down the parent node towards the bottom
		}
	}
	else {//it has a left child only
		if (heap_vector[leftChildIndex] < heap_vector[parentIndex]) {
			//TODO: call the bubble down algorithm to bubble down the parent node towards the bottom
		}
	}
}

size_t Minheap::getIndexForMinValue(size_t index1, size_t index2, size_t index3) {
	//think about what happens if two or three values are the same. : either index could be the minimum Index
	int minValue = heap_vector[index1];
	size_t minIndex = index1;
	if (heap_vector[index2] < minValue) {
		minValue = heap_vector[index2];
		minIndex = index2;
	}
	if (heap_vector[index3] < minValue) {
		minValue = heap_vector[index3];
		minIndex = index3;
	}
	return minIndex;
}

void Minheap::bubbleDown(size_t parentIndex) {
	size_t leftChildIndex = getLeftChildPosition(parentIndex);
	size_t rightChildIndex = getRightChildPosition(parentIndex);
	size_t indexHoldingMinimum;
	if (leftChildIndex <= heap_vector_size - 1) {//if it has at least one child(left child)
		if (rightChildIndex <= heap_vector_size - 1) {//if it has a right child(so it has two children)
			indexHoldingMinimum = getIndexForMinValue(parentIndex, leftChildIndex, rightChildIndex);
			if (indexHoldingMinimum != parentIndex) {
				swap(parentIndex, indexHoldingMinimum);
				bubbleDown(indexHoldingMinimum);
			}
		}
		else {//it has only one child
			if (heap_vector[leftChildIndex] < heap_vector[parentIndex]) {
				swap(leftChildIndex, parentIndex);
				//there is no need to call bubbleDown here since we've reached the end of the tree
			}
		}
	}
}

//the vector should already be a min heap for bubble up to work
void Minheap::bubbleUp(size_t childIndex) {
	size_t parentIndex;
	size_t leftChildIndex;
	size_t rightChildIndex;
	size_t indexHoldingMinimum;
	if (childIndex >= 1) {//The fact that we are inside this if statement confirms that we have at least one child(left child) below the parent. This is why the if condition below is commented
		parentIndex = getParentPosition(childIndex);
		leftChildIndex = getLeftChildPosition(parentIndex);
		rightChildIndex = getRightChildPosition(parentIndex);
		//if (leftChildIndex <= heap_vector_size-1) {//it has at least one child(i.e., the left child)
		if (rightChildIndex <= heap_vector_size - 1) {//it has a left child and a right child
			indexHoldingMinimum = getIndexForMinValue(parentIndex, leftChildIndex, rightChildIndex);
			if (indexHoldingMinimum != parentIndex) {
				swap(indexHoldingMinimum, parentIndex);
				bubbleUp(parentIndex);
			}
		}
		else {//it only has a left child
			if (heap_vector[leftChildIndex] < heap_vector[parentIndex]) {
				swap(leftChildIndex, parentIndex);
				bubbleUp(parentIndex);
			}
		}
		//}
	}
}

void Minheap::insertNodeIntoHeap(int newnode) {
	heap_vector.push_back(newnode);
	heap_vector_size++;
	bubbleUp(heap_vector_size - 1);
}

void Minheap::deleteNodeFromHeap(size_t indexToRemove) {
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
			if (heap_vector[indexToRemove] < heap_vector[parentIndex]) {
				bubbleUp(indexToRemove);
			}
			else {
				bubbleDown(indexToRemove);
			}
		}
	}
}

void Minheap::printHeap() {
	for (auto i = heap_vector.begin(); i != heap_vector.end(); ++i) {
		cout << *i << endl;
	}
}
