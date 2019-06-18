#ifndef GAME_H_
#define GAME_H_

#include <iostream>
#include <cstdlib>
using namespace std;

class Game {
private:
	string title;
	string gameDeveloper;
	string gamePublisher;
	string date;
	double price;
	int singleplayer;
	int multiplayer;
	string platform;

public:
	Game();
	string getTitle() const;
	string getGameDeveloper() const;
	string getGamePublisher() const;
	string getDate() const;
	double getPrice() const;
	int getSingleplayer() const;
	int getMultiplayer() const;
	string getPlatform() const;

	void setTitle(string t);
	void setDeveloper(string gd);
	void setPublisher(string gp);
	void setDate(string c);
	void setPrice(double p);
	void setSingleplayer(int sp);
	void setMultiplayer(int mp);
	void setPlatform(string pl);

	void printGameInfo() const;
	friend ostream& operator<<(ostream& os, const Game& c);
	bool operator<(const Game& c);
	bool operator>(const Game& c);
	bool operator==(const Game& c);
	bool operator<=(const Game& c);
	bool operator>=(const Game& c);

};

Game::Game() {
	title = "";
	gameDeveloper = "";
	gamePublisher = "";
	date = "";
	price = 0.0;
	singleplayer = 0;
	multiplayer = 0;
	platform = "";
}

string Game::getGameDeveloper() const {
	return gameDeveloper;
}
string Game::getTitle() const {
	return title;
}
string Game::getGamePublisher() const {
	return gamePublisher;
}
string Game::getDate() const {
	return date;
}
double Game::getPrice() const{
	return price;
}
int Game::getSingleplayer() const {
	return singleplayer;
}
int Game::getMultiplayer() const {
	return multiplayer;
}
string Game::getPlatform() const {
	return platform;
}

void Game::setDeveloper(string gd) {
	gameDeveloper = gd;
}
void Game::setTitle(string t) {
	title = t;
}
void Game::setPublisher(string gp) {
	gamePublisher = gp;
}
void Game::setDate(string c) {
	date = c;
}
void Game::setPrice(double p){
	price = p;
}
void Game::setSingleplayer(int sp) {
	singleplayer = sp;
}
void Game::setMultiplayer(int mp) {
	multiplayer = mp;
}
void Game::setPlatform(string pl) {
	platform = pl;
}

void Game::printGameInfo() const
{
	cout << "Title: " << title << endl;
	cout << "Game Developer: " << gameDeveloper << endl;
	cout << "Game Publisher: " << gamePublisher << endl;
	cout << "Date: " << date << endl;
	cout << "Price: " << price << endl;
	cout << "Singleplayer: ";
	if (singleplayer == 0){
		cout << "No" << endl;
	}
	else {
		cout << "Yes" << endl;
	}
	cout << "Multiplayer: ";
	if (multiplayer == 0){
		cout << "No" << endl;
	}
	else {
		cout << "Yes" << endl;
	}
	cout << "Platform: " << platform << endl << endl;
}//printGameInfo

ostream& operator<<(ostream& os, const Game& c)
{
	return os << c.title << endl << c.gameDeveloper << endl << c.gamePublisher << endl << c.date << endl << c.price << endl << c.singleplayer << endl << c.multiplayer << endl << c.platform << endl;
}

bool Game::operator==(const Game& c)
{
    return (title == c.title && gameDeveloper== c.gameDeveloper);
}//operator==

bool Game::operator<=(const Game& c)
{
    return (title == c.title);
}//operator==

bool Game::operator>=(const Game& c)
{
    return (gameDeveloper == c.gameDeveloper);
}//operator==

bool Game::operator<(const Game& c)
{
	bool flag = false;

	if (title.compare(c.title) < 0){
		flag = true;
	}
	else if (title.compare(c.title) == 0){
		if (gameDeveloper.compare(c.gameDeveloper) < 0){
			flag = true;
		}
	}
	else {
		flag = false;
	}

	return flag;
}//

bool Game::operator>(const Game& c)
{
	bool flag = false;

	if (gameDeveloper.compare(c.gameDeveloper) > 0){
		flag = true;
	}
	else if (gameDeveloper.compare(c.gameDeveloper) == 0){
		if (title.compare(c.title) > 0){
			flag = true;
		}
	}
	else {
		flag = false;
	}

	return flag;
}


#endif /* GAME_H_ */
