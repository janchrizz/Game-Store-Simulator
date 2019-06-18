/*
Calvin Fernando Tjoeng
CIS 22C
Lab 8
*/

#ifndef LISTG_H_
#define LISTG_H_

#include <cstddef> //for NULL
#include <iostream>
#include <assert.h>
using namespace std;

template <class listGdata> //listG stores generic listGdata, not any specific C++ type
class ListG {
private:
    struct Node {
        listGdata data;
        Node* nextnode;
		Node* previousnode;

        Node(listGdata data) :
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
    //Recursively prints the data in a ListG in reverse.

    bool isSorted(NodePtr node) const;
	//Helper function for the public isSorted() function.
    //Recursively determines whether a listG is sorted in ascending order.

	int binarySearch(int low, int high, listGdata data);
	//Recursively search the listG by dividing the search space in half
	//Returns the index of the element, if it is found in the ListG
	//Returns -1 if the element is not in the ListG

public:

    /**Constructors and Destructors*/

    ListG();
    //Default constructor; initializes and empty listG
    //Postcondition: the value of data is undefined and nextnode is initialized to NULL
   
	ListG(const ListG &listG);
	//Copy construcor. Initializes listG to have the same elements as another listG
	//Postcondition: newly created listG is the same as another listG

    ~ListG();
    //Destructor. Frees memory allocated to the listG
    //Postcondition: dynamic memory allocated freed, no memory leaks

    /**Accessors*/

    listGdata getBegin() const; //this function now returns generic data
    //Returns the first element in the listG
    //Precondition: the listG exists or has been initialized, begin pointer contains data

    listGdata getEnd() const;
    //Returns the last element in the listG
    //Precondition: the listG exists or has been initialized, end pointer contains data

    listGdata getIterator() const;
    //Returns the element currently pointed at by the iterator
    //Precondition: the iterator is pointing at an element in the listG

    bool empty() const;
    //Determines whether a listG is empty.

    bool offEnd() const;
    //Determines whether the iterator is off the end of the listG

    bool isSorted() const;
	//Wrapper function that calls the isSorted helper function to determine whether 
	//a listG is sorted in ascending order.
	//We will consider that a listG is trivially sorted if it is empty.
	//Therefore, no precondition is needed for this function

    int getLength() const;
    //Returns the size of the listG

    int getIndex() const;
	//Indicates the index of the Node where the iterator is currently pointing
	//Nodes are numbered from 1 to size of the listG
	//Pre: length != 0
	//Pre: !offEnd()

	int linearSearch(listGdata data);
	//Searchs the listG, element by element, from the start of the ListG to the end of the ListG
	//Returns the index of the element, if it is found in the ListG
	//Calls the above indexing functions in its implementation
	//Returns -1 if the element is not in the ListG
	//Pre: length != 0

	int binarySearch(listGdata data);
	//Returns the index where data is located in the ListG
	//Calls the private helper function binarySearch to perform the search
	//Pre: length != 0
	//Pre: ListG is sorted (must test on a sorted listG)

    /**Manipulation Procedures*/

    void deleteEnd();
    //Removes the value of the last element in the listG
    //Precondition: the listG exists or has been initialized, end pointer contains data
    //Postcondition: the last element in the listG will hold no data

    void deleteBegin();
    //Removes the value of the first element in the listG
    //Precondition: the listG exists or has been initialized, begin pointer contains data
    //Postcondition: the first element in the listG will hold no data

    void insertEnd(listGdata data);
    //Inserts a new element at the end of the listG
    //If the listG is empty, the new element becomes both first and last
    //Postcondition: new element will be added at the end of the listG

    void insertBegin(listGdata data); //this function now takes in generic data
    //Inserts a new element at the start of the listG
    //If the listG is empty, the new element becomes both first and last
    //Postcondition: new element will be added at the start of the listG

    void beginIterator();
    //Moves the iterator to the start of the listG
    //Precondition: the listG exists or has been initialized

    void deleteIterator();
    //Removes the element currently pointed at by the iterator. Iterator then points to NULL.
    //Precondition: the listG exists or has been initialized, the iterator is pointing at an element in the listG
    //Postcondition: the element which was pointed at by the iterator is no more

    void insertIterator(listGdata data);
    //Inserts an element after the node currently pointed to by the iterator
    //Precondition: the iterator is pointing at an element in the listG
    //Postcondition: a new node is positioned after the position where the iterator is pointing

    void advanceIterator();
    //Moves the iterator up by one node
    //Precondition: the iterator is pointing at an element in the listG

    void reverseIterator();
    //Moves the iterator down by one node
    //Precondition: the iterator is pointing at an element in the listG

	void advanceToIndex(int index);
	//Moves the iterator to the node whose index number is specified in the parameter
	//Pre: length != 0
	//Pre: index <= length

    /**Additional ListG Operations*/

    void print() const;
    //Prints the contents of the linked listG to the screen separated by a blank space
    //Prints nothing if the listG is empty

    void printNumberedListG() const;
    //Prints the contents of the linked listG to the screen in the format #. <element> followed by a newline

    bool operator==(const ListG &listG);
	//Tests two listGs to determine whether their contents are equal
	//Postcondition: returns true if listGs are equal and false otherwise

	void printReverse() const;
	//Wrapper function that calls the reverse helper function to print a listG in reverse
	//prints nothing if the ListG is empty
};

template <class listGdata>
ListG<listGdata>::ListG() 
{
    begin = NULL;
    end = NULL;
    iterator = NULL;
    length = 0;
}

template <class listGdata>
ListG<listGdata>::ListG(const ListG &listG): length(listG.length)
{
    if(listG.begin == NULL) //If the original listG is empty, make an empty listG for this listG
    {
        begin = end = iterator = NULL;
    }
    else
    {
        begin = new Node(listG.begin->data); //calling Node constructor
        NodePtr temp = listG.begin; //set a temporary node pointer to point at the first of the original listG
        iterator = begin; //set iterator to point to first node of the new listG

        while(temp->nextnode != NULL)
        {

            temp = temp->nextnode; //advance up to the next node in the original listG
            iterator->nextnode = new Node(temp->data); //using node constructor to create new node w/ copy of data
            iterator = iterator->nextnode; //advance to this new node

        }

        end = iterator; //Why do I need this line of code?
        iterator = NULL;

    }
    
    length = listG.length;
}

template <class listGdata>
ListG<listGdata>::~ListG() 
{
    iterator = begin;
    NodePtr temp;
    while (iterator != NULL) {
        temp = iterator->nextnode;
        delete iterator;
        iterator = temp;
    }
}

template <class listGdata>
void ListG<listGdata>::insertBegin(listGdata data) 
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

template <class listGdata>
void ListG<listGdata>::insertEnd(listGdata data) 
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

template <class listGdata>
void ListG<listGdata>::deleteBegin() 
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

template <class listGdata>
void ListG<listGdata>::deleteEnd() 
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

template <class listGdata>
void ListG<listGdata>::deleteIterator() 
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

template <class listGdata>
void ListG<listGdata>::insertIterator(listGdata data) 
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

template <class listGdata>
void ListG<listGdata>::beginIterator() 
{
	assert(!empty());
	iterator = begin;
}

template <class listGdata>
void ListG<listGdata>::advanceIterator() 
{
	assert(!offEnd());
	iterator = iterator->nextnode;
}

template <class listGdata>
void ListG<listGdata>::reverseIterator() 
{
	assert(!offEnd());
	iterator = iterator->previousnode;
}

template <class listGdata>
void ListG<listGdata>::advanceToIndex(int index)
{
	assert(length != 0);
    assert(index <= length);
    beginIterator();
    for(int i = 1; i < index; i++){
        advanceIterator();
    }
}

template <class listGdata>
bool ListG<listGdata>::empty() const
{
    return length == 0;
}

template <class listGdata>
bool ListG<listGdata>::offEnd() const
{
    return iterator == NULL;
}

template <class listGdata>
bool ListG<listGdata>::isSorted() const
{
	return isSorted(begin);
}

template <class listGdata>
bool ListG<listGdata>::isSorted(NodePtr node) const
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

template <class listGdata>
int ListG<listGdata>::getLength() const
{
    return length;
}

template<class listGdata>
int ListG<listGdata>::getIndex() const
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

template <class listGdata>
listGdata ListG<listGdata>::getBegin() const
{
	assert(begin != NULL);       
    return begin -> data;
}

template <class listGdata>
listGdata ListG<listGdata>::getEnd() const
{       
	assert(end != NULL);
    return end -> data;
}

template <class listGdata>
listGdata ListG<listGdata>::getIterator() const
{       
	assert(!offEnd());
    return iterator -> data;
}

template <class listGdata>
void ListG<listGdata>::print() const
{
    NodePtr temp = begin; //create a temporary 
    while (temp != NULL) {

        cout << temp->data;
        temp = temp->nextnode;

    }
    cout << endl; //What does this do?

}

template <class listGdata>
void ListG<listGdata>::printNumberedListG() const
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

template <class listGdata>
bool ListG<listGdata>::operator==(const ListG& listG)
{
    if(length != listG.length)
        return false;
    NodePtr temp1 = begin;
    NodePtr temp2 = listG.begin;
    while(temp1 != NULL)
    {
        if(temp1->data != temp2->data)
            return false;
        temp1 = temp1->nextnode;
        temp2 = temp2->nextnode;
    }
    return true;
}

template <class listGdata>
void ListG<listGdata>::reverse(NodePtr node) const
{
    if (node == NULL)
        return;
    cout << node->data << " ";
    reverse(node->previousnode);
}

template<class listGdata>
void ListG<listGdata>::printReverse() const 
{
    reverse(end);
    cout << endl;
}

template <class listGdata>
int ListG<listGdata>::linearSearch(listGdata data)
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

template <class listGdata>
int ListG<listGdata>::binarySearch(int low, int high, listGdata data)
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

template <class listGdata>
int ListG<listGdata>::binarySearch(listGdata data)
{
	assert(length != 0);
	assert(isSorted());
	return binarySearch(1, getLength(), data);
}

#endif /* LISTG_H_ */