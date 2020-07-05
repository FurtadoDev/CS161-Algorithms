#include <iostream>
#include "Minheap.h"
#include "Maxheap.h"

using namespace std;

int main() {
	cout << "I will overcome." << endl;
	vector<int> myHeap;
	myHeap.push_back(9);
	myHeap.push_back(14);
	myHeap.push_back(5);
	myHeap.push_back(4);
	myHeap.push_back(8);
	myHeap.push_back(12);
	myHeap.push_back(1);
	myHeap.push_back(7);
	myHeap.push_back(10);
	Minheap minhp(myHeap);

	minhp.deleteNodeFromHeap(0);
	minhp.deleteNodeFromHeap(2);
	minhp.insertNodeIntoHeap(20);
	minhp.insertNodeIntoHeap(30);
	minhp.deleteNodeFromHeap(2);
	minhp.printHeap();


	return 0;
}