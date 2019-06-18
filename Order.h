/*
 * Chaitanya Galivanche
 * CIS 22C, Class Project
 * June 16th, 2017
 * Order.h
 *
 */
#ifndef ORDER_H_
#define ORDER_H_
#include "Game.h"
#include <vector>
#include <ostream>

using namespace std;


class Order {
private:
	bool shipped;
	int ordernumber;
	Game fps;
	int shiptype; //1 = standard, 2 = rushed, 3 = overnight
public:
	Order();
	Order(int on, int st);

	void setOrderNumber(int on);
	int getOrderNumber() const;

	void setShipType(int st);
	int getShipType() const;

	void setGame(Game g);
	Game getGames();

	void Ship();
	bool isShipped() const;

	void printCout();
	bool operator==(const Order& order) const;
	bool operator<(const Order& order) const;
	bool operator>(const Order& order) const;
	friend ostream& operator<<(ostream& os, const Order& order);
};

Order::Order() {
	shipped = false;
	ordernumber = -1;
	shiptype = -1;
}

Order::Order(int on, int st) {
	shipped = false;
	ordernumber = on;
	shiptype = st;
}

void Order::setOrderNumber(int on) {
	ordernumber = on;
}

int Order::getOrderNumber() const {
	return ordernumber;
}

void Order::setShipType(int st) {
	shiptype = st;
}

int Order::getShipType() const {
	return shiptype;
}

void Order::setGame(Game g) {
	fps = g;
}

Game Order::getGames() {
	return fps;
}

void Order::Ship() {
	shipped = true;
}

bool Order::isShipped() const {
	return shipped;
}

void Order::printCout(){
	cout << "Order Number: " << ordernumber << endl;
	cout << "Shipping Type: ";
	switch(shiptype) {
		case 1:
			cout << "Standard";
			break;
		case 2:
			cout << "Rushed";
			break;
		case 3:
			cout << "Overnight";
			break;
	}
	cout << endl << "Shipped: ";
	if (!shipped){
		cout << "No";
	}
	else {
		cout << "Yes";
	}
	cout << endl;
	fps.printGameInfo();
}

bool Order::operator==(const Order& Order) const {
    return (shiptype == Order.shiptype && ordernumber == Order.ordernumber);
}

bool Order::operator<(const Order& Order) const {
   if (shiptype < Order.shiptype) {
	   return true;
   }
   else if (shiptype == Order.shiptype) { //if both shipping types are the same, check the order numbers
	   if (ordernumber > Order.ordernumber) { //Higher order number = lower priority
		   return true;
	   }
	   else { //if ordernumber == Order.ordernumber OR ordernumber < Order.ordernumber
		   return false;
	   }
   }
   return false; //if shiptype > Order.shiptype
}

bool Order::operator>(const Order& Order) const {
	if (shiptype > Order.shiptype) {
		   return true;
	}
	else if (shiptype == Order.shiptype) { //if both shipping types are the same, check the order numbers
		if (ordernumber < Order.ordernumber) { //Lower order number = higher priority
			return true;
		}
		else { //if ordernumber == Order.ordernumber OR ordernumber > Order.ordernumber
			return false;
		}
	}
	return false; //if shiptype < Order.shiptype
}

ostream& operator<<(ostream& os, const Order& Order) {
	os << Order.ordernumber << endl << Order.shiptype << endl;
	if (!Order.shipped){
		os << "0" << endl;
	}
	else {
		os << "1" << endl;
	}
	os << Order.fps;
	return os;
}

#endif /* ORDER_H_ */
