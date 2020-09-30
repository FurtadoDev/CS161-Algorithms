#include "Heap.h" 


Heap::Heap(vector<pair<int, int>> inputVector) {
	heap_vector = inputVector;
	heap_vector_size = inputVector.size();
	build_min_heap();
	vertex_positions.reserve(heap_vector_size);
}

void Heap::build_min_heap() {
	//TODO: check to see if the size is more than 1
	size_t lim = heap_vector_size/2;
	for (int i = lim - 1; i >= 0; i--) {
		min_heapify(i);
	}
}

void Heap::build_max_heap() {

}

void Heap::min_heapify(size_t parentIdx) {
	size_t leftChildIdx = getLeftChildPosition(parentIdx);
	size_t rightChildIdx = getRightChildPosition(parentIdx);
	size_t minIdx;

	vertex_positions[heap_vector[parentIdx].first] = parentIdx;
	if (rightChildIdx <= heap_vector_size-1) {//it has both nodes
		vertex_positions[heap_vector[leftChildIdx].first] = leftChildIdx;
		vertex_positions[heap_vector[rightChildIdx].first] = rightChildIdx;
		minIdx = getIndexForMinimumValue(parentIdx, leftChildIdx, rightChildIdx);
		if (minIdx != parentIdx) {
			swap(parentIdx, minIdx);
			min_heapify(minIdx);
		}
	}
	else if (leftChildIdx <= heap_vector_size - 1) {//it only has the left node
		vertex_positions[heap_vector[leftChildIdx].first] = leftChildIdx;
		if (heap_vector[leftChildIdx].second < heap_vector[parentIdx].second) {
			swap(leftChildIdx, parentIdx);
			min_heapify(leftChildIdx);
		}

	}
	else {
		//it has no child nodes : do nothing
	}
}

size_t Heap::getLeftChildPosition(size_t  index) {
	return (index + 1) * 2 - 1;
}

size_t Heap::getRightChildPosition(size_t  index) {
	return (index + 1) * 2;
}

size_t Heap::getParentPosition(size_t index) {
	return floor((index + 1) / 2) - 1;
}

void Heap::swap(size_t index1, size_t index2) {//no duplicate nodes allowed
	vertex_positions[heap_vector[index1].first] = index2;
	vertex_positions[heap_vector[index2].first] = index1;
	pair<int, int> temp = heap_vector[index1];
	heap_vector[index1] = heap_vector[index2];
	heap_vector[index2] = temp;
}



//return the parent index if it is the min else return the min child index
size_t Heap::getIndexForMinimumValue(size_t parentIdx, size_t leftChildIdx, size_t rightChildIdx) {
	int min = heap_vector[parentIdx].second;
	size_t minIdx = parentIdx;

	if (heap_vector[leftChildIdx].second < min) {
		min = heap_vector[leftChildIdx].second;
		minIdx = leftChildIdx;
	}
		
	if (heap_vector[rightChildIdx].second < min) {
		min = heap_vector[rightChildIdx].second;
		minIdx = rightChildIdx;
	}

	return minIdx;
}


void Heap::printHeap() {
	for (int i = 0; i < heap_vector_size; i++) {
		cout << heap_vector[i].first << " : " << heap_vector[i].second << endl;
	}
}

void Heap::printVertexPositions() {
	for (auto it = vertex_positions.begin(); it != vertex_positions.end(); ++it)
		std::cout << "Vertex : " << it->first << " Index : " << it->second << endl;
}

unordered_map<int, int> Heap::getMapForVertexPositions() {
	return vertex_positions;
}

vector<pair<int, int>> Heap::getHeapVector() {
	return heap_vector;
}

void Heap::bubbleUp(size_t childIdx) {
	size_t parentIdx = getParentPosition(childIdx);
	size_t leftChildIdx = getLeftChildPosition(parentIdx);
	size_t rightChildIdx = getRightChildPosition(parentIdx);
	size_t  minIdx;
	//TODO::check to see the size of the heap vector is at least 2 before proceeding/index childIdx argument should be at least 1/it has a parent
	if ((leftChildIdx < heap_vector_size) && (childIdx > 0)) {
		if (rightChildIdx < heap_vector_size) {//parent has two children
			minIdx = getIndexForMinimumValue(parentIdx, leftChildIdx, rightChildIdx);
			if (minIdx != parentIdx) {
				swap(parentIdx, minIdx);
				bubbleUp(parentIdx);
			}
		}
		else {//parent has only the left child
			if (heap_vector[leftChildIdx].second < heap_vector[parentIdx].second) {
				swap(parentIdx, leftChildIdx);
				bubbleUp(parentIdx);
			}
		}
	}
}

void Heap::bubbleDown(size_t parentIdx) {
	min_heapify(parentIdx);
}


void Heap::insertNodeIntoHeap(pair<int, int> newnodeandkey) {
	//increase the size after inserting and assign position
	heap_vector.push_back(newnodeandkey);
	vertex_positions[newnodeandkey.first] = heap_vector_size;
	heap_vector_size++;
	bubbleUp(heap_vector_size-1);
}


void Heap::deleteNodeFromHeap(size_t indexToRemove) {
	//delete from veretex position and reduce the size
	heap_vector.pop_back();
	heap_vector_size--;
	vertex_positions.erase();
}