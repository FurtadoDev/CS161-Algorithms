#include "Heap.h" 

Heap::Heap(vector<pair<int,int>> inputVector) {
	heap_vector = inputVector;
	build_min_heap();
}

void Heap::build_min_heap() {
	heap_vector_size = size(heap_vector);
	if (heap_vector_size >= 2) {
		size_t lim = (heap_vector_size) / 2;
		for (size_t i = lim; i >= 1; i--) {
			min_heapify(i - 1);
		}
	}
	else if(heap_vector_size == 1){
		vertex_positions[heap_vector[0].first] = 0;
	}
}

void Heap::min_heapify(size_t idx) {
	size_t parentNodeIdx = idx;
	size_t leftChildIdx;
	size_t rightChildIdx;
	size_t minIdx;
	if (idx < heap_vector_size - 1) {// -1 because there should be at least one child for the element to get into the if condition
		leftChildIdx = getLeftChildPosition(parentNodeIdx);
		rightChildIdx = getRightChildPosition(parentNodeIdx);

		if (leftChildIdx < heap_vector_size) {
			if (rightChildIdx < heap_vector_size) { //parent has two child nodes
				//assign positions to the nodes
				vertex_positions[heap_vector[parentNodeIdx].first] = parentNodeIdx;
				vertex_positions[heap_vector[leftChildIdx].first] = leftChildIdx;
				vertex_positions[heap_vector[rightChildIdx].first] = rightChildIdx;
				minIdx = getIndexForMinimumValue(idx, leftChildIdx, rightChildIdx);
				if (minIdx != parentNodeIdx) {
					swap(minIdx, parentNodeIdx);
					min_heapify(minIdx);
				}
			}
			else { //parent only has left child node
				vertex_positions[heap_vector[parentNodeIdx].first] = parentNodeIdx;
				vertex_positions[heap_vector[leftChildIdx].first] = leftChildIdx;
				if (heap_vector[parentNodeIdx].second > heap_vector[leftChildIdx].second)
					swap(parentNodeIdx, leftChildIdx);
			}
		}
	}
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

size_t Heap::getIndexForMinimumValue(size_t index1, size_t index2, size_t index3) {
	int minimumValue;
	size_t minimumIndex;

	minimumValue = heap_vector[index1].second;
	minimumIndex = index1;

	if (heap_vector[index2].second < minimumValue) {
		minimumValue = heap_vector[index2].second;
		minimumIndex = index2;
	}
	if (heap_vector[index3].second < minimumValue) {
		minimumValue = heap_vector[index3].second;
		minimumIndex = index3;
	}
	return minimumIndex;
}

void Heap::swap(size_t index1, size_t index2) {
	pair<int, int> temp;
	temp = heap_vector[index1];
	vertex_positions[heap_vector[index1].first] = index2;
	vertex_positions[heap_vector[index2].first] = index1;
	heap_vector[index1] = heap_vector[index2];
	heap_vector[index2] = temp;
}

void Heap::printHeap() {
	cout << "Heap Values:" << endl;

	for (int i = 0; i < heap_vector_size; i++)
	{
		cout << heap_vector[i].first << " : " << heap_vector[i].second << endl;
	}
	cout << endl;
}

void Heap::deleteNodeFromHeap(size_t indexToRemove) {
	int nodeToRemove = heap_vector[indexToRemove].first;
	size_t parentIndex = getParentPosition(indexToRemove);
	size_t leftChild = getLeftChildPosition(indexToRemove);
	//Step 1: Replace the node with the farthest right node.
	heap_vector[indexToRemove] = heap_vector[heap_vector_size - 1];
	vertex_positions[heap_vector[heap_vector_size - 1].first] = indexToRemove;
	//Step 2: Bubble it up or down to maintain heap property.
	if (indexToRemove == 0) {
		bubbleDown(indexToRemove);
	}
	else {//the index range is from 1 to size-1
		if (heap_vector[indexToRemove].second < heap_vector[parentIndex].second)
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
	
	heap_vector.pop_back();
	heap_vector_size--;
	vertex_positions.erase(nodeToRemove);
}

void Heap::insertNodeIntoHeap(pair<int,int> newnodeandkey) {
	heap_vector.push_back(newnodeandkey);
	heap_vector_size++;
	vertex_positions[newnodeandkey.first] = heap_vector_size-1;

	if (heap_vector_size > 1) {
		size_t parentIndex = getParentPosition(heap_vector_size - 1);
		if (heap_vector[heap_vector_size - 1].second < heap_vector[parentIndex].second) {
			//call the bubble up algorithm
			bubbleUp(heap_vector_size - 1);
		}
	}
}

void Heap::bubbleUp(size_t index) {
	size_t currentNodeIndex = index;
	size_t parentNodeIndex = getParentPosition(currentNodeIndex);

	while (currentNodeIndex >= 1) { //while it has a parent node bubble up : TODO : Check if condition is right 
		if (heap_vector[currentNodeIndex].second < heap_vector[parentNodeIndex].second) {
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
	size_t chosenMinIndex;
	while (leftChildIndex <= heap_vector_size - 1) {//while it has at least one child node bubble down
		if ((leftChildIndex <= heap_vector_size - 1) && (rightChildIndex <= heap_vector_size - 1)) {//if it has two child nodes
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
				vertex_positions[heap_vector[parentNodeIndex].first] = parentNodeIndex;
				break;
			}
		}
		else { //else it has only one child node
			if (this->heap_vector[leftChildIndex].second < this->heap_vector[parentNodeIndex].second) {
				swap(leftChildIndex, parentNodeIndex);
				parentNodeIndex = leftChildIndex;
				leftChildIndex = getLeftChildPosition(parentNodeIndex);
				rightChildIndex = getRightChildPosition(parentNodeIndex);
			}
			else {
				//break if the heap property is already maintained
				vertex_positions[heap_vector[parentNodeIndex].first] = parentNodeIndex;
				break;
			}
		}
	}

}

vector<pair<int,int>> Heap::getHeapVector() {
	return heap_vector;
}

unordered_map<int, int> Heap::getMapForVertexPositions() {
	return vertex_positions;
}

void Heap::printVertexPositions() {
	cout << "Vertex Positions :" << endl;
	for (auto const& pair : vertex_positions) {
		std::cout << "{" << pair.first << ": " << pair.second << "}\n";
	}
	cout << endl;
}