#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include <iostream>
#include <iomanip>
#include <assert.h>
#include <string>
#include "ListG.h"
#include "Customer.h"
using namespace std;

class HashTable {
public:

    /**Access Functions*/

    int hash(string key);
    //returns the hash value for the given key
    //the hash value is the sum of
    //of the ASCII values of each char in the key
    //% the size the of the table
    //Key for this table: title + author

    int countBucket(int index);
    //counts the number of Books at this index
    //returns the count
    //pre: 0<= index < SIZE

    int searchData(Customer c);
    //Searches for b in the table
    //returns the index at which b is located
    //returns -1 if b is not in the table

    Customer getSelectedCustomer(Customer c);

    /**Manipulation Procedures*/

    void insertData(Customer c);
    //inserts a new book into the table
    //calls the hash function on the key to determine
    //the correct bucket

    void removeData(Customer c);
    //removes b from the table
    //calls the hash function on the key to determine
    //the correct bucket

    /**Additional Functions*/

    void printBucket(int index, ostream& os);
    //Prints all the books at index
    //pre: 0<= index < SIZE
    //Should print according to the following formula:
    //"Printing index <index#>
    //skips two lines
    //Next, prints each book at that index in the format:
    //<title> by <author>
    //$<X.XX>
    //ISBN: <isbn>
    //followed by a blank line

    void printTable(ostream& os);
    //Prints the first book at each index
    //along with a count of the total books
    //at each index by calling count_bucket
    //as a helper function
    //Prints in the format:
    //________________________
    //Bucket: <index>
    //<title> by <author>
    //$<X.XX>
    //ISBN: <isbn>
    //Number of books at this bucket: <number of elements at this index>
    //__________________________

	void printInfoBucket(int index);
    void printInfoTable();

private:
    static const int SIZE = 75;
    ListG<Customer> Table[SIZE];
};

int HashTable::hash(string key)
{
	int value = 0;
	int sum = 0;
	for(int i = 0; i < key.length();i++)
	{
		//add the sum of each ascii value in the key
		sum += (int)key[i];
	}//for
	value = sum % SIZE;
	return value;
}//hash

int HashTable::countBucket(int index)
{
	assert(index>=0);
	assert(index < SIZE);

	//return list size
	return Table[index].getLength();
}//countBucket

int HashTable::searchData(Customer c)
{
	int i = hash(c.getFirstName() + c.getLastName());
	if (!Table[i].empty()){
		if (Table[i].linearSearch(c) != -1){
			return i;
		}
	}

    return -1;
}//searchData

Customer HashTable::getSelectedCustomer(Customer c)
{
	assert(searchData(c) != -1);
	int i = hash(c.getFirstName()+c.getLastName());
	if(!Table[i].empty()){
		int index = Table[i].linearSearch(c);
		if(index != -1){
			Table[i].beginIterator();
			Table[i].advanceToIndex(index);
			return Table[i].getIterator();
		}
	}
	Customer empty;
	return empty;
}//getSelectedCustomer

void HashTable::insertData(Customer c)
{
	int i = hash(c.getFirstName()+c.getLastName());
	Table[i].insertEnd(c);
}//insertData

void HashTable::removeData(Customer c)
{
	int tableIndex = hash(c.getFirstName()+c.getLastName());
	if(Table[tableIndex].getLength() == 0)
	{
		cout << "Customer not found" << endl;
	}//if
	else
	{
		int listIndex = Table[tableIndex].linearSearch(c);
		if(listIndex != -1)
		{
			Table[tableIndex].advanceToIndex(listIndex);
			Table[tableIndex].deleteIterator();
		}//if
		else
		{
			cout << "Customer not found" << endl;
		}//else
	}//else
}//removeData

void HashTable::printBucket(int index, ostream& os)
{
	assert(index < SIZE);
	//Begin iterator
	Table[index].beginIterator();
	while(!Table[index].offEnd())
	{
		Customer customer1 = Table[index].getIterator();

		os << endl << customer1;

		Table[index].advanceIterator();
	}//while
}//printBucket

void HashTable::printTable(ostream& os)
{
	for(int i=0; i < SIZE ; i++){
		if(!Table[i].empty()){
			printBucket(i, os);
		}//else
	}//for
}//printTable

void HashTable::printInfoBucket(int index)
{
	assert(index < SIZE);
	//Begin iterator
	Table[index].beginIterator();
	while(!Table[index].offEnd())
	{
		Customer customer1 = Table[index].getIterator();

		customer1.printInfo();

		Table[index].advanceIterator();
	}//while
}//printBucket

void HashTable::printInfoTable()
{
	for(int i=0; i < SIZE ; i++)
	{
		if(!Table[i].empty())
		{
			printInfoBucket(i);
		}//else
	}//for
}//printTable

#endif /* HASHTABLE_H_ */
