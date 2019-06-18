/*
Calvin Fernando Tjoeng
CIS 22C
Lab 8
*/

#ifndef LIST_H_
#define LIST_H_

#include <cstddef> //for NULL
#include <iostream>
#include <assert.h>
#include "Order.h"
using namespace std;
 //list stores generic Order, not any specific C++ type
class List {
private:
    struct Node {
        Order data;
        Node* nextnode;
		Node* previousnode;

        Node(Order data) :
                data(data), nextnode(NULL), previousnode(NULL) {
        }
    };

    typedef struct Node* NodePtr;

    NodePtr begin;
    NodePtr end;
    NodePtr iterator;

    int length;

    void reverse(NodePtr node) const;
	//Helper function for the public printReverse() function.
    //Recursively prints the data in a List in reverse.

    bool isSorted(NodePtr node) const;
	//Helper function for the public isSorted() function.
    //Recursively determines whether a list is sorted in ascending order.

	int binarySearch(int low, int high, Order data);
	//Recursively search the list by dividing the search space in half
	//Returns the index of the element, if it is found in the List
	//Returns -1 if the element is not in the List

public:

    /**Constructors and Destructors*/

    List();
    //Default constructor; initializes and empty list
    //Postcondition: the value of data is undefined and nextnode is initialized to NULL
   
	List(const List &list);
	//Copy construcor. Initializes list to have the same elements as another list
	//Postcondition: newly created list is the same as another list

    ~List();
    //Destructor. Frees memory allocated to the list
    //Postcondition: dynamic memory allocated freed, no memory leaks

    /**Accessors*/

    Order getBegin() const; //this function now returns generic data
    //Returns the first element in the list
    //Precondition: the list exists or has been initialized, begin pointer contains data

    Order getEnd() const;
    //Returns the last element in the list
    //Precondition: the list exists or has been initialized, end pointer contains data

    Order getIterator() const;
    //Returns the element currently pointed at by the iterator
    //Precondition: the iterator is pointing at an element in the list

    bool empty() const;
    //Determines whether a list is empty.

    bool offEnd() const;
    //Determines whether the iterator is off the end of the list

    bool isSorted() const;
	//Wrapper function that calls the isSorted helper function to determine whether 
	//a list is sorted in ascending order.
	//We will consider that a list is trivially sorted if it is empty.
	//Therefore, no precondition is needed for this function

    int getLength() const;
    //Returns the size of the list

    int getIndex() const;
	//Indicates the index of the Node where the iterator is currently pointing
	//Nodes are numbered from 1 to size of the list
	//Pre: length != 0
	//Pre: !offEnd()

	int linearSearch(Order data);
	//Searchs the list, element by element, from the start of the List to the end of the List
	//Returns the index of the element, if it is found in the List
	//Calls the above indexing functions in its implementation
	//Returns -1 if the element is not in the List
	//Pre: length != 0

	int binarySearch(Order data);
	//Returns the index where data is located in the List
	//Calls the private helper function binarySearch to perform the search
	//Pre: length != 0
	//Pre: List is sorted (must test on a sorted list)

    /**Manipulation Procedures*/

    void deleteEnd();
    //Removes the value of the last element in the list
    //Precondition: the list exists or has been initialized, end pointer contains data
    //Postcondition: the last element in the list will hold no data

    void deleteBegin();
    //Removes the value of the first element in the list
    //Precondition: the list exists or has been initialized, begin pointer contains data
    //Postcondition: the first element in the list will hold no data

    void insertEnd(Order data);
    //Inserts a new element at the end of the list
    //If the list is empty, the new element becomes both first and last
    //Postcondition: new element will be added at the end of the list

    void insertBegin(Order data); //this function now takes in generic data
    //Inserts a new element at the start of the list
    //If the list is empty, the new element becomes both first and last
    //Postcondition: new element will be added at the start of the list

    void beginIterator();
    //Moves the iterator to the start of the list
    //Precondition: the list exists or has been initialized

    void deleteIterator();
    //Removes the element currently pointed at by the iterator. Iterator then points to NULL.
    //Precondition: the list exists or has been initialized, the iterator is pointing at an element in the list
    //Postcondition: the element which was pointed at by the iterator is no more

    void insertIterator(Order data);
    //Inserts an element after the node currently pointed to by the iterator
    //Precondition: the iterator is pointing at an element in the list
    //Postcondition: a new node is positioned after the position where the iterator is pointing

    void advanceIterator();
    //Moves the iterator up by one node
    //Precondition: the iterator is pointing at an element in the list

    void reverseIterator();
    //Moves the iterator down by one node
    //Precondition: the iterator is pointing at an element in the list

	void advanceToIndex(int index);
	//Moves the iterator to the node whose index number is specified in the parameter
	//Pre: length != 0
	//Pre: index <= length

    /**Additional List Operations*/

    void print() const;
    //Prints the contents of the linked list to the screen separated by a blank space
    //Prints nothing if the list is empty

    void printListCout() const;
    void printON(ostream& os) const;

    void printNumberedList() const;
    //Prints the contents of the linked list to the screen in the format #. <element> followed by a newline

    //bool operator==(const List &list);
	//Tests two lists to determine whether their contents are equal
	//Postcondition: returns true if lists are equal and false otherwise

    void operator=(const List &list);

	void printReverse() const;
	//Wrapper function that calls the reverse helper function to print a list in reverse
	//prints nothing if the List is empty
};

List::List() 
{
    begin = NULL;
    end = NULL;
    iterator = NULL;
    length = 0;
}

List::List(const List &list): length(list.length)
{
    if(list.begin == NULL) //If the original list is empty, make an empty list for this list
    {
        begin = end = iterator = NULL;
    }
    else
    {
        begin = new Node(list.begin->data); //calling Node constructor
        NodePtr temp = list.begin; //set a temporary node pointer to point at the first of the original list
        iterator = begin; //set iterator to point to first node of the new list

        while(temp->nextnode != NULL)
        {

            temp = temp->nextnode; //advance up to the next node in the original list
            iterator->nextnode = new Node(temp->data); //using node constructor to create new node w/ copy of data
            iterator = iterator->nextnode; //advance to this new node

        }

        end = iterator; //Why do I need this line of code?
        iterator = NULL;

    }
    
    length = list.length;
}

List::~List() 
{
    iterator = begin;
    NodePtr temp;
    while (iterator != NULL) {
        temp = iterator->nextnode;
        delete iterator;
        iterator = temp;
    }
}

void List::insertBegin(Order data) 
{
    if(length == 0) {//why is this necessary
        begin = end = new Node(data);
    } else {
        NodePtr N = new Node(data);
        N->nextnode = begin;
        begin->previousnode = N; //Need to update the previous pointer of first to point back at the new node
        begin = N;
    }
    length++;
}

void List::insertEnd(Order data) 
{
    if(length == 0) {//why is this necessary
        begin = end = new Node(data);
    } else {
        NodePtr N = new Node(data);
        end->nextnode = N;
        N->previousnode = end;
        end = N;
    }
    length++;
}

void List::deleteBegin() 
{
    assert(!empty());
    if (length == 1) {
        delete begin;
        begin = end = iterator = NULL;
        length = 0;

    } else {
        begin = begin->nextnode;
        delete begin->previousnode;
        begin->previousnode = NULL;
        length--;
    }
}

void List::deleteEnd() 
{
    assert(!empty());
    if (length == 1) {
        delete end;
        begin = end = iterator = NULL;
        length = 0;

    } else {
        end = end->previousnode;
        delete end->nextnode;
        end->nextnode = NULL;
        length--;
    }
}

void List::deleteIterator() 
{
	assert(!offEnd());
	if (iterator == begin) {
		deleteBegin();
		iterator = NULL;
	}
	else if (iterator == end) {
		deleteEnd();
		iterator = NULL;
	}
	else {
		iterator->nextnode->previousnode = iterator->previousnode;
		iterator->previousnode->nextnode = iterator->nextnode;
		delete iterator;
		iterator = NULL;
		length--;
	}
	
}

void List::insertIterator(Order data) 
{
	assert(!offEnd());
    if(iterator == end) {
        insertEnd(data);
    } else {
        NodePtr N = new Node(data);
        N->nextnode = iterator->nextnode;
        N->previousnode = iterator;
        iterator->nextnode->previousnode = N;
        iterator->nextnode = N;
    	length++;
    }
}

void List::beginIterator() 
{
	assert(!empty());
	iterator = begin;
}

void List::advanceIterator() 
{
	assert(!offEnd());
	iterator = iterator->nextnode;
}

void List::reverseIterator() 
{
	assert(!offEnd());
	iterator = iterator->previousnode;
}

void List::advanceToIndex(int index)
{
	assert(length != 0);
    assert(index <= length);
    beginIterator();
    for(int i = 1; i < index; i++){
        advanceIterator();
    }
}

bool List::empty() const
{
    return length == 0;
}

bool List::offEnd() const
{
    return iterator == NULL;
}

bool List::isSorted() const
{
	return isSorted(begin);
}

bool List::isSorted(NodePtr node) const
{
	NodePtr temp1;
	NodePtr temp2;

	if (node == NULL) {
		return true;
	}
	else {
		temp1 = node;
	}

	if (node->nextnode == NULL) {
		return true;
	}
	else {
		temp2 = node->nextnode;
	}

	while (temp2 != NULL){
		if (temp1->data > temp2->data) {
			return false;
		}
		else {
			temp1 = temp1->nextnode;
			temp2 = temp2->nextnode;
		}
	}
	return true;
}

int List::getLength() const
{
    return length;
}

int List::getIndex() const
{
    assert(length != 0);
    assert(!offEnd());
    NodePtr temp = begin;
    int n = 1;
    while(temp != iterator){
        temp = temp->nextnode;
        n++;
    }
    return n;
}

Order List::getBegin() const
{
	assert(begin != NULL);       
    return begin -> data;
}

Order List::getEnd() const
{       
	assert(end != NULL);
    return end -> data;
}

Order List::getIterator() const
{       
	assert(!offEnd());
    return iterator -> data;
}

void List::print() const
{
    NodePtr temp = begin; //create a temporary 
    while (temp != NULL) {

        cout << temp->data;
        temp = temp->nextnode;

    }
    cout << endl; //What does this do?

}

void List::printListCout() const
{
    NodePtr temp = begin; //create a temporary 
    while (temp != NULL) {

        temp->data.printCout();
        temp = temp->nextnode;

    }
    cout << endl; //What does this do?

}

void List::printON(ostream& os) const{
    NodePtr temp = begin; //create a temporary 
    while (temp != NULL) {

        os << temp->data.getOrderNumber() << " " << temp->data.getShipType() << endl;
        temp = temp->nextnode;

    }
}

void List::printNumberedList() const
{
    NodePtr temp = begin; //create a temporary 
    int i = 1;
    while (temp != NULL) {

        cout << i << ". " << temp->data << endl;
        temp = temp->nextnode;
        i++;

    }
    cout << endl; //What does this do?

}

/*
bool List::operator==(const List& list)
{
    if(length != list.length)
        return false;
    NodePtr temp1 = begin;
    NodePtr temp2 = list.begin;
    while(temp1 != NULL)
    {
        if(temp1->data != temp2->data)
            return false;
        temp1 = temp1->nextnode;
        temp2 = temp2->nextnode;
    }
    return true;
}
*/

void List::reverse(NodePtr node) const
{
    if (node == NULL)
        return;
    cout << node->data << " ";
    reverse(node->previousnode);
}

void List::printReverse() const 
{
    reverse(end);
    cout << endl;
}

int List::linearSearch(Order data)
{
	assert(length != 0);
	beginIterator();
    while(iterator != NULL){
        if(getIterator() == data)
            return getIndex();
        advanceIterator();
    }
    return -1;
}

int List::binarySearch(int low, int high, Order data)
{
	if(high < low) {
        return -1;
	}

    int mid = low + (high-low)/2;
    advanceToIndex(mid);

    if(getIterator() == data) {
        return mid;
    }
    else if (data < getIterator()) {
        return binarySearch(low, mid-1, data);
    } 
    else {
        return binarySearch(mid+1, high, data);
    }
}

int List::binarySearch(Order data)
{
	assert(length != 0);
	assert(isSorted());
	return binarySearch(1, getLength(), data);
}

void List::operator=(const List &list) {
    if(list.begin == NULL) //If the original list is empty, make an empty list for this list
    {
        begin = end = iterator = NULL;
    }
    else
    {
        begin = new Node(list.begin->data); //calling Node constructor
        NodePtr temp = list.begin; //set a temporary node pointer to point at the first of the original list
        iterator = begin; //set iterator to point to first node of the new list

        while(temp->nextnode != NULL)
        {

            temp = temp->nextnode; //advance up to the next node in the original list
            iterator->nextnode = new Node(temp->data); //using node constructor to create new node w/ copy of data
            iterator = iterator->nextnode; //advance to this new node

        }

        end = iterator; //Why do I need this line of code?
        iterator = NULL;

    }
    
    length = list.length;
}


#endif /* LIST_H_ */