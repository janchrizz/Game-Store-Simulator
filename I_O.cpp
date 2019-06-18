/*
Calvin Fernando Tjoeng
Team #8
Topic: FPS Games
I/O file
 */

#include <iostream>
#include <fstream>
#include <string>
#include "Customer.h"
#include "Game.h"
#include "Order.h"
#include "PriorityQueue.h"
#include "BST.h"
#include "HashTable.h"
#include "List.h"
#include "Login.h"

using namespace std;

void customerMainMenu();
void employeeMainMenu();
void billingInformation(string& firstName, string& lastName, string& address, string& city, string& state, int& zip);
void shippingMethod();
void printProduct(BST<Game>& tree);

int main(){
	int response;
	int onCounter;
	string gameTitle;
	string gameDeveloper;
	double price;
	string strTemp;
	string firstName;
	string lastName;
	string address;
	string city;
	string state;
	int zip;
	Login Lo;
	string pass;
	string P_change;
	Game temp;
	BST<Game> primaryTree; // sorted by primary key
	BST<Game> secondaryTree; // sorted by secondary key
	HashTable customers;
	PriorityQueue OrdersQueue;
	ifstream fileIn;
	ofstream fileOut;

	fileIn.open("orders.txt");
	if (fileIn.peek() != std::ifstream::traits_type::eof()){
		while (!fileIn.eof()){
			Order tempO;
			int tempI;
			fileIn >> tempI;
			tempO.setOrderNumber(tempI);
			fileIn >> tempI;
			tempO.setShipType(tempI);
			fileIn >> tempI;
			if (tempI == 1){
				tempO.Ship();
			}
			Game tempG;
			double tempD;
			fileIn.ignore();
			getline(fileIn, strTemp);
			tempG.setTitle(strTemp);
			getline(fileIn, strTemp);
			tempG.setDeveloper(strTemp);
			getline(fileIn, strTemp);
			tempG.setPublisher(strTemp);
			getline(fileIn, strTemp);
			tempG.setDate(strTemp);
			fileIn >> tempD;
			tempG.setPrice(tempD);
			fileIn >> tempI;
			tempG.setSingleplayer(tempI);
			fileIn >> tempI;
			tempG.setMultiplayer(tempI);
			fileIn.ignore();
			getline(fileIn, strTemp);
			tempG.setPlatform(strTemp);
			fileIn.ignore();
			tempO.setGame(tempG);
			OrdersQueue.insertEnd(tempO);
		}
		OrdersQueue.buildHeap();
		OrdersQueue.sortOrders();
	}
	fileIn.close();
	fileIn.clear();

	fileIn.open("customers.txt");
	if (fileIn.peek() != std::ifstream::traits_type::eof()){
		fileIn.ignore();
		while (!fileIn.eof()){
			int tempI;
			getline(fileIn, firstName);
			getline(fileIn, lastName);
			getline(fileIn, address);
			getline(fileIn, city);
			getline(fileIn, state);
			fileIn >> zip;
			Customer tempC;
			tempC.setFirstName(firstName);
			tempC.setLastName(lastName);
			tempC.setAddress(address);
			tempC.setCity(city);
			tempC.setState(state);
			tempC.setZip(zip);
			fileIn >> tempI;
			for (int i = 0; i < tempI; ++i){
				int tempI2, tempI3;
				Order tempO, tempO2;
				fileIn >> tempI2;
				fileIn >> tempI3;
				tempO.setOrderNumber(tempI2);
				tempO.setShipType(tempI3);
				int index1 = OrdersQueue.searchOrder(tempO);
				int index2 = OrdersQueue.searchShippedOrder(tempO);
				if (index1 != -1){
					tempO2 = OrdersQueue.getSelectedOrder(tempO);
				}
				if (index2 != -1){
					tempO2 = OrdersQueue.getSelectedShippedOrder(tempO);
				}
				tempC.addOrder(tempO2);
			}
			fileIn.ignore();
			fileIn.ignore();
			customers.insertData(tempC);
		}
	}
	fileIn.close();
	fileIn.clear();

	OrdersQueue.buildHeap();

	fileIn.open("products.txt");
	while (!fileIn.eof()){
		Game tempG;
		double tempD;
		int tempI;
		getline(fileIn, strTemp);
		tempG.setTitle(strTemp);
		getline(fileIn, strTemp);
		tempG.setDeveloper(strTemp);
		getline(fileIn, strTemp);
		tempG.setPublisher(strTemp);
		getline(fileIn, strTemp);
		tempG.setDate(strTemp);
		fileIn >> tempD;
		tempG.setPrice(tempD);
		fileIn >> tempI;
		tempG.setSingleplayer(tempI);
		fileIn >> tempI;
		tempG.setMultiplayer(tempI);
		fileIn.ignore();
		getline(fileIn, strTemp);
		tempG.setPlatform(strTemp);
		fileIn.ignore();
		primaryTree.insertDataPrimary(tempG);
		secondaryTree.insertDataSecondary(tempG);
	}
	fileIn.close();
	fileIn.clear();

	fileIn.open("orderNumberCounter.txt");
	if (!fileIn.eof()) {
		fileIn >> onCounter;
	}
	else {
		onCounter = 0;
	}
	fileIn.close();
	fileIn.clear();

	cout << "Welcome to [FPS Game Store]!\n\n"; // enter a name of our store in the square bracket.
	cout << "Please specify yourself:\n";
	cout << "1. A customer\n";
	cout << "2. An employee\n";
	cout << "0. Quit\n\n";

	cout << "Please enter the number of your desired option: ";
	cin >> response;
	cout << endl;

	while (response != 1 && response != 2 && response != 0){
		cout << "Invalid number!\n";
		cout << "Please enter a valid response: ";
		cin >> response;
		cout << endl;
	}

	if (response == 1){ // Customer
		while (response != 0){
			customerMainMenu();
			cin >> response;
			cout << endl;

			while (response != 1 && response != 2 && response != 3 && response != 4 && response != 0){
				cout << "Invalid number!\n";
				cout << "Please enter a valid response: ";
				cin >> response;
				cout << endl;
			}
			cin.ignore();

			if (response == 0){ // Quit
				break;
			}
			else if (response == 1){ // Search for a product
				cout << "Please select the following options:\n";
				cout << "1. Search by the title of the game\n";
				cout << "2. Search by the developer of the game\n\n";

				cout << "Please enter the number of your desired response: ";
				cin >> response;

				while (response != 1 && response != 2){
					cout << "Invalid number!\n";
					cout << "Please enter a valid response: ";
					cin >> response;
					cout << endl;
				}
				cin.ignore();

				if (response == 1){
					cout << "Please enter the title of the game: ";
					getline(cin, gameTitle);
					temp.setTitle(gameTitle);

					while (!primaryTree.searchPrimary(temp)){
						cout << endl << "The game you searched for is not available in our store!\n";
						cout << "Please enter the valid title of the game or enter \"0\" to cancel: ";
						getline(cin, gameTitle);

						if (gameTitle == "0"){
							break;
						}

						temp.setTitle(gameTitle);
					}

					if (gameTitle != "0"){
						cout << gameTitle << " is available in our store!\n\n";
						Game g1 = primaryTree.searchAndGrabPrimary(temp);
						g1.printGameInfo();
					}
				}
				else {
					cout << "Please enter the developer of the game: ";
					getline(cin, gameDeveloper);
					temp.setDeveloper(gameDeveloper);

					while (!secondaryTree.searchSecondary(temp)){
						cout << "The developer you searched for is not available in our store!\n";
						cout << "Please enter the valid developer of the game or enter \"0\" to cancel: ";
						getline(cin, gameDeveloper);

						if (gameDeveloper == "0"){
							break;
						}

						temp.setDeveloper(gameDeveloper);
					}

					if (gameDeveloper != "0"){
						cout << gameDeveloper << " has a game in our store!\n\n";
						Game g1 = secondaryTree.searchAndGrabSecondary(temp);
						g1.printGameInfo();
					}
				}
			}
			else if (response == 2){ // List the database of FPS games available
				cout << "Please select the following options:\n";
				cout << "1. Sort by the title of the games\n"; // the primary key
				cout << "2. Sort by the developer of the games\n\n"; // the secondary key

				cout << "Please enter the number of your desired option: ";
				cin >> response;
				cout << endl;

				while (response != 1 && response != 2){
					cout << "Invalid number!\n";
					cout << "Please enter a valid response: ";
					cin >> response;
					cout << endl;
				}

				if (response == 1){ // primary key
					printProduct(primaryTree);
				}
				else { // secondary key
					printProduct(secondaryTree);
				}
			}
			else if (response == 3){ // Place an order
				cout << "Please enter the title of the game: ";
				getline(cin, gameTitle);
				cout << "Please enter the developer of the game: ";
				getline(cin, gameDeveloper);
				cout << endl;
				temp.setTitle(gameTitle);
				temp.setDeveloper(gameDeveloper);
				if (!primaryTree.search(temp)){
					cout << gameTitle << " is not available in our store!\n\n";
				}
				else {
					Game chosen = primaryTree.searchAndGrab(temp);

					cout << "Here is the detail of the game you looked for:\n\n";
					chosen.printGameInfo();

					// This part is necessary though
					billingInformation(firstName, lastName, address, city, state, zip);
					shippingMethod();
					cin >> response;
					cout << endl;

					while (response != 1 && response != 2 && response != 3){
						cout << "Invalid number!\n";
						cout << "Please enter a valid response: ";
						cin >> response;
						cout << endl;
					}

					Customer tempC, tempC2;
					tempC.setFirstName(firstName);
					tempC.setLastName(lastName);
					tempC.setAddress(address);
					tempC.setCity(city);
					tempC.setState(state);
					tempC.setZip(zip);

					int index = customers.searchData(tempC);

					if (index != -1){
						tempC2 = customers.getSelectedCustomer(tempC);
						customers.removeData(tempC);

						Order tempO;
						onCounter++;
						tempO.setOrderNumber(onCounter);
						tempO.setGame(chosen);
						tempO.setShipType(response);
						tempC2.addOrder(tempO);

						customers.insertData(tempC2);
						OrdersQueue.insertOrder(tempO);
					}
					else {
						Order tempO;
						onCounter++;
						tempO.setOrderNumber(onCounter);
						tempO.setGame(chosen);
						tempO.setShipType(response);
						tempC.addOrder(tempO);

						customers.insertData(tempC);
						OrdersQueue.insertOrder(tempO);
					}
					cout << "Your order has been placed. Thank you for your purchase!\n\n";
				}
			}
			else { // View purchases
				cout << "Please enter your first name: ";
				getline(cin, firstName);
				cout << "Please enter your last name: ";
				getline(cin, lastName);

				Customer tempC;
				tempC.setFirstName(firstName);
				tempC.setLastName(lastName);

				if (customers.searchData(tempC) == -1){
					cout << "You have not purchased anything.\n\n";
				}
				else {
					Customer tempC2 = customers.getSelectedCustomer(tempC);
					List tempLO = tempC2.getOrders();

					cout << "Your purchases:\n\n";
					tempLO.printListCout();
				}
			}
		}

		cout << "Thank you for visiting [FPS Games Store]! Please come back later!\n\n";

		fileOut.open("customers.txt");
		customers.printTable(fileOut);
		fileOut.close();
		fileOut.clear();

		fileOut.open("orders.txt");
		OrdersQueue.print(fileOut);
		OrdersQueue.printShipped(fileOut);
		fileOut.close();
		fileOut.clear();

		fileOut.open("products.txt");
		primaryTree.inOrderPrint(fileOut);
		fileOut.close();
		fileOut.clear();

		fileOut.open("orderNumberCounter.txt");
		fileOut << onCounter;
		fileOut.close();
		fileOut.clear();

		exit(-1);
	}
	else if (response == 2){
		// Employee
		cout <<"Please enter the program password: "; cin >> pass;
		while(Lo.compare_password(pass)==false)
		{
			cout<<"Your password is incorrect."<<endl<<"Please enter again: "; cin >> pass;

		}
		cout <<endl;
		while (response != 0){
			employeeMainMenu();
			cin >> response;
			cout << endl;

			while (response != 1 && response != 2 && response != 3 && response != 4 && response != 5 && response != 6&& response != 7 && response != 0){
				cout << "Invalid number!\n";
				cout << "Please enter a valid response: ";
				cin >> response;
				cout << endl;
			}
			cin.ignore();

			if (response == 0){ // Quit
				break;
			}
			else if (response == 1){ // Search for a customer
				cout << "Please enter the first name of the customer: ";
				getline(cin, firstName);
				cout << "Please enter the last name of the customer: ";
				getline(cin, lastName);

				Customer tempC;
				tempC.setFirstName(firstName);
				tempC.setLastName(lastName);

				while (customers.searchData(tempC) == -1){
					cout << "There is no customer called " << firstName << " " << lastName << "!\n";
					cout << "Please enter another first name of the customer or enter \"0\" to cancel: ";
					getline(cin, firstName);

					if (firstName == "0"){
						break;
					}

					cout << "Please enter the last name of the customer: ";
					getline(cin, lastName);
					tempC.setFirstName(firstName);
					tempC.setLastName(lastName);
				}

				if (firstName != "0"){
					Customer tempC2 = customers.getSelectedCustomer(tempC);

					cout << "The customer called " << firstName << " " << lastName << " is a customer in our store!\n";
					cout << "Below is the complete information about " << firstName << " " << lastName << ":\n";
					tempC2.printInfo();
				}
			}
			else if (response == 2){ // Display customer information
				cout << "Customers information:\n\n";
				customers.printInfoTable();
			}
			else if (response == 3){ // View orders
				cout << "Orders:" << endl;
				cout << "========" << endl;
				OrdersQueue.sortOrders();
				OrdersQueue.printPQCout();
				OrdersQueue.buildHeap();
				cout << "Orders that you shipped:" << endl;
				cout << "========================" << endl;
				OrdersQueue.printShippedPQCout();
				cout << endl;
			}
			else if (response == 4){ // Ship an order
				if (OrdersQueue.getSize() == 0){
					cout << "There is no more order to be shipped\n\n";
				}
				else {
					cout << "The topmost priority order is being shipped!\n\n";
					cout << "Here are the order details: " << endl << endl;
					OrdersQueue.shipTopOrder();
				}
			}
			else if (response == 5){ // List the database of FPS games available
				cout << "Please select the following options:\n";
				cout << "1. Sort by the title of the games\n"; // the primary key
				cout << "2. Sort by the developer of the games\n\n"; // the secondary key

				cout << "Please enter the number of your desired option: ";
				cin >> response;
				cout << endl;

				while (response != 1 && response != 2){
					cout << "Invalid number!\n";
					cout << "Please enter a valid response: ";
					cin >> response;
					cout << endl;
				}

				if (response == 1){ // primary key
					printProduct(primaryTree);
				}
				else { // secondary key
					printProduct(secondaryTree);
				}
			}
			else if (response == 6){ // Add a new game
				Game newGame;

				cout << "Please enter the title of the game: ";
				getline(cin, gameTitle);
				newGame.setTitle(gameTitle);
				cout << "Please enter the developer of the game: ";
				getline(cin, gameDeveloper);
				newGame.setDeveloper(gameDeveloper);
				cout << "Please enter the publisher of the game: ";
				getline(cin, strTemp);
				newGame.setPublisher(strTemp);
				cout << "Please enter the release date of the game: ";
				getline(cin, strTemp);
				newGame.setDate(strTemp);
				cout << "Please enter the price of the game: ";
				cin.sync();
				cin >> price;
				newGame.setPrice(price);
				cout << "Singleplayer? (Y/N): ";
				getline(cin, strTemp);
				cin >> strTemp;
				if (strTemp == "Y" || strTemp == "y"){
					newGame.setSingleplayer(1);
				}
				else {
					newGame.setSingleplayer(0);
				}
				cout << "Multiplayer? (Y/N): ";
				cin >> strTemp;
				if (strTemp == "Y" || strTemp == "y"){
					newGame.setMultiplayer(1);
				}
				else {
					newGame.setMultiplayer(0);
				}
				getline(cin, strTemp);
				cout << "Please enter the platform of the game: ";
				getline(cin, strTemp);
				newGame.setPlatform(strTemp);
				cout << endl;

				primaryTree.insertDataPrimary(newGame);
				secondaryTree.insertDataSecondary(newGame);

				cout << gameTitle << " has been added!\n\n";
			}
			else { // Remove a game
				cout << "Please enter the title of the game: ";
				getline(cin, gameTitle);
				cout << "Please enter the developer of the game: ";
				getline(cin, gameDeveloper);
				cout << endl;

				Game gameTemp;
				gameTemp.setTitle(gameTitle);
				gameTemp.setDeveloper(gameDeveloper);

				if (primaryTree.search(gameTemp)){
					primaryTree.removeData(gameTemp);
					secondaryTree.removeData(gameTemp);

					cout << gameTitle << " has been removed!\n\n";
				}
				else {
					cout << gameTitle << " is not available here!\n\n";
				}
			}
		}

		cout << "Thank you for visiting [FPS Games Store]! Please come back later!\n\n";

		fileOut.open("customers.txt");
		customers.printTable(fileOut);
		fileOut.close();
		fileOut.clear();

		fileOut.open("orders.txt");
		OrdersQueue.print(fileOut);
		fileOut << endl;
		OrdersQueue.printShipped(fileOut);
		fileOut.close();
		fileOut.clear();

		fileOut.open("products.txt");
		primaryTree.inOrderPrint(fileOut);
		fileOut.close();
		fileOut.clear();

		fileOut.open("orderNumberCounter.txt");
		fileOut << onCounter;
		fileOut.close();
		fileOut.clear();

		exit(-1);
	}
	else { // Quit
		cout << "Thank you for visiting [FPS Games Store]! Please come back later!\n\n";
		exit(-1);
	}

	return 0;
}

void customerMainMenu(){
	cout << "What do you wish to do?\n";
	cout << "1. Search for a product\n";
	cout << "2. List the database of FPS games available\n";
	cout << "3. Place an order\n";
	cout << "4. View purchases\n";
	cout << "(Enter 0 or any non-integer string to quit).\n\n";

	cout << "Please enter the number of your desired option: ";
}

void employeeMainMenu(){
	cout << "What do you wish to do?\n";
	cout << "1. Search for a customer\n";
	cout << "2. Display customer information\n";
	cout << "3. View orders\n";
	cout << "4. Ship an order\n";
	cout << "5. List the database of FPS games available\n";
	cout << "6. Add a new game\n";
	cout << "7. Remove a game\n";
	cout << "(Enter 0 or any non-integer string to quit).\n\n";

	cout << "Please enter the number of your desired option: ";
}

void billingInformation(string& firstName, string& lastName, string& address, string& city, string& state, int& zip){
	cout << "Please enter your preferred billing address below:\n";
	cout << "First name: ";
	getline(cin, firstName);
	cout << "Last name: ";
	getline(cin, lastName);
	cout << "Street name: ";
	getline(cin, address);
	cout << "City: ";
	getline(cin, city);
	cout << "State: ";
	getline(cin, state);
	cout << "Zip code: ";
	cin >> zip;
	cout << endl;
}

void shippingMethod(){
	cout << "Please select the preferred shipping method:\n";
	cout << "1. Standard shipping\n";
	cout << "2. Rush shipping\n";
	cout << "3. Overnight shipping\n\n";

	cout << "Please enter the number of your desired option: ";
}

void printProduct(BST<Game>& tree){
	cout << "There are " << tree.size() << " products in this store:\n\n";
	tree.printInfo();
}
