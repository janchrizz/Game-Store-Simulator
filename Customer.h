#ifndef CUSTOMER_H_
#define CUSTOMER_H_

#include <iostream>
#include <cstdlib>
#include "List.h"
#include "Order.h"
using namespace std;

class Customer {
private:
	string first_name; //id used to login. unique
	string last_name; //nickname, changeable
	string address; //billingAddress
	string city; //balance of money
	string state;
	int zip;
	List orders;

public:
	Customer();
	Customer(const Customer& cust);
	string getFirstName() const;
	string getLastName() const;
	string getAddress() const;
	string getCity() const;
	string getState() const;
	int getZip() const;
	List getOrders();
	int getSizeofOrders() const;

	void setFirstName(string first);
	void setLastName(string last);
	void setAddress(string add);
	void setCity(string c);
	void setState(string st);
	void setZip(int z);

	void addOrder(Order ord);
	void removeOrder(Order ord);
	void printOrder() const;
	void printInfo() const;
	friend ostream& operator<<(ostream& os, const Customer& c);
	bool operator<(const Customer& c);
	bool operator>(const Customer& c);
	bool operator==(const Customer& c);
	void operator=(const Customer& cust);
};

Customer::Customer() {
	first_name = "";
	last_name = "";
	address = "";
	city = "";
	state = "";
	zip = 0;
}
Customer::Customer(const Customer& cust) {
	first_name = cust.first_name;
	last_name = cust.last_name;
	address = cust.address;
	city = cust.city;
	state = cust.state;
	zip = cust.zip;
	orders = cust.orders;
}

string Customer::getFirstName() const {
	return first_name;
}
string Customer::getLastName() const {
	return last_name;
}
string Customer::getAddress() const {
	return address;
}
string Customer::getCity() const {
	return city;
}
string Customer::getState() const {
	return state;
}
int Customer::getZip() const {
	return zip;
}
List Customer::getOrders() {
	return orders;
}
int Customer::getSizeofOrders() const{
	return orders.getLength();
}

void Customer::setFirstName(string first) {
	first_name = first;
}
void Customer::setLastName(string last) {
	last_name = last;
}
void Customer::setAddress(string add) {
	address = add;
}
void Customer::setCity(string c) {
	city = c;
}
void Customer::setState(string st) {
	state = st;
}
void Customer::setZip(int z) {
	zip = z;
}

void Customer::addOrder(Order ord)
{
	orders.insertEnd(ord);
}

void Customer::removeOrder(Order ord)
{
	int a = 0;
	a = orders.linearSearch(ord);
	if (a != -1){
		orders.advanceToIndex(a);
		orders.deleteIterator();
	}
}

void Customer::printOrder() const
{
	if(orders.empty())
	cout << "No orders" << endl;
else
	orders.printNumberedList();
}

void Customer::printInfo() const
{
	cout << "Name: " << first_name << " " << last_name << endl;
	cout << "Address: " << address << ", " << city << ", " << state << " " << zip << endl << endl;
}//printInfo

ostream& operator<<(ostream& os, const Customer& c)
{
	int length = c.orders.getLength();
	os << c.first_name << endl << c.last_name << endl << c.address << endl << c.city << endl << c.state << endl << c.zip << endl;
	os << length << endl;
	c.orders.printON(os);
	return os;
}

bool Customer::operator==(const Customer& c)
{
    return (last_name == c.last_name && first_name== c.first_name);
}//operator==

bool Customer::operator<(const Customer& c)
{
	if(last_name == c.last_name)
	{
		if(first_name == c.first_name)
		{
			return false;
		}
	}
	return(last_name < c.last_name);
}

bool Customer::operator>(const Customer& c)
{
	if(last_name == c.last_name)
	{
		if(first_name == c.first_name)
		{
			return false;
		}
	}
	return(last_name > c.last_name);
}

void Customer::operator=(const Customer& cust) {
	first_name = cust.first_name;
	last_name = cust.last_name;
	address = cust.address;
	city = cust.city;
	state = cust.state;
	zip = cust.zip;
	orders = cust.orders;
}

#endif /* CUSTOMER_H_ */
