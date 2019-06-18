/*
 * Chaitanya Galivanche
 * CIS 22C, Class Project
 * June 16th, 2017
 * PriorityQueue.h
 *
 */
#ifndef PRIORITYQUEUE_H_
#define PRIORITYQUEUE_H_
#include <vector>
#include <algorithm> //for reverse function
#include "assert.h"
#include "Order.h"

using namespace std;

class PriorityQueue {
	private:
		vector<Order> Orders;
		//This Priority Queue is implemented using a vector. The vector is kept as a field of the PQ as opposed to being passed in as
		//a parameter to the PQ functions.

		vector<Order> ShippedOrders;
		//In order to have a record of all completed Orders, shipped Orders will be transferred to the ShippedOrders vector. At the end of
		//the main program, this vector can be written to an output file using the printShipped function.

		int size;
		//Separate variable to keep track of the PQ size, since Orders[0] will not be used. This is especially useful for the
		//SortOrders/HeapSort function.

		void helpInsertOrder(int index);
		//Private helper function for the InsertOrder/HeapInsert function.

	public:
		PriorityQueue();
		//Instantiates a new PQ


		/** Manipulation functions **/
		void heapify(int index);
		//Recursively swaps an out-of-place Order to its correct place in the PQ.

		void buildHeap();
		//Utilizes the Heapify function to convert the entire Orders vector into a valid max-heap/PQ.

		void insertOrder(Order key);
		//HeapInsert function.
		//
		//Inserts a new Order into the PQ and swaps it to its correct place.

		void insertEnd(Order key);
		//Alternate insert function that inserts every new element to the end of the Orders vector.
		//
		//IMPORTANT: This should be used when the PQ is first being filled with values from the input file.
		//It is more efficient to sort an unordered vector/array through buildHeap than it is to
		//call InsertOrder on every element.

		void insertShipped(Order key);

		void sortOrders();
		//HeapSort function.
		//
		//Sorts the Orders vector from highest Order priority to lowest Order priority.

		void shipTopOrder();
		//Pre - Orders vector cannot be empty (excludes Orders[0]).
		//Moves the highest priority Order from the Orders vector to the ShippedOrders vector.

		void removeOrder(Order key);
		//Pre - Order must exist in the PQ before it is removed
		//Removes the specified Order from the PQ. Useful for handling cancelled orders.


		/** Access functions **/
		int searchOrder(Order key) const;
		//Uses a linear search through the Orders vector to find a specified Order.
		//Returns the index of the Order if found, otherwise it returns -1

		Order getSelectedOrder(Order key);

		int searchShippedOrder(Order key) const;
		//Uses a linear search through the Orders vector to find a specified Order.
		//Returns the index of the Order if found, otherwise it returns -1

		Order getSelectedShippedOrder(Order key);

		Order getTopOrder() const;
		//Pre - Orders vector cannot be empty (excludes Orders[0]).
		//Returns the highest priority Order.

		int getSize() const;
		//Returns how many elements there are in the PQ.

		bool isEmpty() const;
		//Returns whether or not the PQ is empty.


		/** Additional functions **/
		void print(ostream& out) const;
		//Print function that displays all the elements of the PQ to the specified output.

		void printShipped(ostream& out) const;
		//Print function that displays all the elements of the ShippedOrders vector to the specified output.

		void printPQCout();
		//Print function that displays all the elements of the PQ to the specified output.

		void printShippedPQCout();
		//Print function that displays all the elements of the ShippedOrders vector to the specified output.
};

PriorityQueue::PriorityQueue() {
	Order empty;
	Orders.push_back(empty); //not using the first element (a.k.a Orders[0]) of the vector, so a dummy Order is inserted
	size = 0;
}

void PriorityQueue::heapify(int index) {
	assert(index >= 1 && index <= size); //index must be the location of a valid Order in the PQ.
	int index_of_max = index; //Assume the highest priority Order is at the current index
	int left = (index * 2); //left child = Orders[2i]
	int right = (index * 2) + 1; //right child = Orders[2i + 1]
	if (left <= size && Orders[left] > Orders[index]) {
		index_of_max = left;
	}
	if (right <= size && Orders[right] > Orders[index_of_max]) {
		index_of_max = right;
	}
	if (index != index_of_max) {
		Order temp = Orders[index]; //swap values in Orders[index] and Orders[index_of_max]
		Orders[index] = Orders[index_of_max];
		Orders[index_of_max] = temp;
		heapify(index_of_max); //recursive heapify call
	}
}

void PriorityQueue::buildHeap() {
	int n = size;
	for (int i = n/2; i >= 1; i--) { //start at floor(n/2), floor function is not required because i is an int
		heapify(i);
	}
}

void PriorityQueue::helpInsertOrder(int index) {
	while (index > 1 && Orders[index/2] < Orders[index]) { //Parent = Orders[floor(index/2)]
		Order temp = Orders[index]; //swap parent and child values
		Orders[index] = Orders[index/2];
		Orders[index/2] = temp;
		index = index/2;
	}
}

void PriorityQueue::insertOrder(Order key) {
	Orders.push_back(key);
	size++;
	helpInsertOrder(size); //move the newly inserted key to its correct place in PQ, Orders[size] now points to this new last element
}

void PriorityQueue::insertEnd(Order key) {
	Orders.push_back(key);
	size++;
}

void PriorityQueue::insertShipped(Order key) {
	ShippedOrders.push_back(key);
}

void PriorityQueue::sortOrders() {
	int n = size;
	for (int i = n; i > 1; i--) { //stops at index 2
		Order temp = Orders[1]; //swap values first and last element (last element index is decremented by one every loop cycle)
		Orders[1] = Orders[i];
		Orders[i] = temp;
		size--; //need to decrement size to prevent heapify call from swapping with the "disconnected" values
		heapify(1);
	}
	size = n; //Restore the PQ size after sorting
	reverse(Orders.begin()+1, Orders.end()); //From <algorithm> library, reverses the elements to display the highest priority orders first.
											 //Less efficient, but this way the main heapSort algorithm isn't touched
}

void PriorityQueue::shipTopOrder() {
	assert(!isEmpty());
	Orders[1].Ship(); //set shipped flag in the Order
	Orders[1].printCout();
	ShippedOrders.push_back(Orders[1]); //Add the shipped order (first element) to the ShippedOrders vector
	Orders.erase(Orders.begin()+1); //Delete the shipped order and shift over remaining elements
	size--;
}

void PriorityQueue::removeOrder(Order key) {
	int index = searchOrder(key);
	assert(index != -1);
	Orders.erase(Orders.begin()+index);
	size--;
}

int PriorityQueue::searchOrder(Order key) const {
	for (int i = 1; i <= size; i++) {
		if (Orders[i] == key) {
			return i;
		}
	}
	return -1;
}

Order PriorityQueue::getSelectedOrder(Order key){
	assert(searchOrder(key) != -1);
	for (int i = 1; i <= size; i++) {
		if (Orders[i] == key) {
			return Orders[i];
		}
	}
	Order empty;
	return empty;
}

int PriorityQueue::searchShippedOrder(Order key) const {
	for (int i = 1; i <= ShippedOrders.size(); i++) {
		if (ShippedOrders[i] == key) {
			return i;
		}
	}
	return -1;
}

Order PriorityQueue::getSelectedShippedOrder(Order key){
	assert(searchShippedOrder(key) != -1);
	for (int i = 1; i <= ShippedOrders.size(); i++) {
		if (ShippedOrders[i] == key) {
			return ShippedOrders[i];
		}
	}
	Order empty;
	return empty;
}

Order PriorityQueue::getTopOrder() const {
	assert(!isEmpty());
	return Orders[1];
}

int PriorityQueue::getSize() const {
	return size;
}

bool PriorityQueue::isEmpty() const {
	return (size == 0);
}

void PriorityQueue::print(ostream& out) const {
	if (size > 0){
		for (int i = 1; i < size; i++) { //start from index 1 -> size, ignore Orders[0] element
			out << Orders[i] << endl;
		}
		out << Orders[size];
	}
}

void PriorityQueue::printShipped(ostream& out) const {
	int n = ShippedOrders.size();
	if (n > 0)
	{
		for (int i = 0; i < n-1; i++) {
			out << ShippedOrders[i] << endl;
		}
		out << ShippedOrders[n-1];
	}
}

void PriorityQueue::printPQCout() {
	for (int i = 1; i <= size; i++) { //start from index 1 -> size, ignore Orders[0] element
		Orders[i].printCout();
	}
}

void PriorityQueue::printShippedPQCout() {
	int n = ShippedOrders.size();
	for (int i = 0; i < n; i++) {
		ShippedOrders[i].printCout();
	}
}

#endif /* PRIORITYQUEUE_H_ */
