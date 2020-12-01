#pragma once
#include <list>
#include <iterator>
#include <fstream>
#include <istream>
#include <string>
#include <iostream>
#include <map>

#include "Cards.h"
#include "Map.h"

class Player;
using namespace std;

class Order {

public:
	int priority;
	map<int, int> allies{};

	//Default Constructor
	Order();

	//Copy constructor
	Order(const Order& b);

	//Assignment operator
	Order& operator = (const Order& d2);

	//Get Priority
	virtual int getPriority();

	//Less than operator for priority comparison
	virtual bool operator <(const Order& playerObj) const;

	//Validates an order
	virtual bool validate();

	//Executes an order
	virtual void execute() = 0;

    virtual ostream& operator<< (ostream& out) const;

	//Check if players are negotiating
	bool checkForAllies(int player1, int player2);
};

class Deploy : public Order {
    int priority = 1;
	int playerID;
	string countryName;
	int countryOwner;
	int units;
	Player* player;
	Territory* territory;


public:
    Deploy() = default;

    //Copy constructor
    Deploy(const Deploy& d2);

	//Overloaded constructor
	Deploy(Player* pl, Territory* terr, int theUnits);

	//Assignment operator
	Deploy& operator = (const Deploy& d2);

	//Get Priority
	int getPriority();

	//Less than operator for priority comparison
	bool operator <(const Deploy& playerObj) const;

	//Validates a deploy order
	bool validate();

	//Executes a deploy order
	void execute();

	friend std::ostream& operator<<(std::ostream& out, const Deploy& b);
};

class Advance : public Order {
    int priority = 4;
	int playerID;
	int countryOwner;
	int units;
	Player* player;
	Territory* territory;
	Territory * attTerritory;
	int attCountryOwner;

public:
	//Overloaded constructor
	Advance(Player* pl, Territory* terr, Territory* attTerr, int unitsAttackingWith);

    //Copy constructor
	Advance(const Advance& b);

	//Assignment operator
	Advance& operator = (const Advance& b);

	//Get Priority
	int getPriority();

	//Less than operator for priority comparison
	bool operator <(const Advance& playerObj) const;

	//Validates an advance order
	bool validate();

	//Executes an advance order
	void execute();

	friend std::ostream& operator<<(std::ostream& out, const Advance& b);

};

class Bomb : public Order {
	int priority = 4;
	int playerID;
	int countryOwner;
	Player* player;
	Territory* territory;
	Territory* attTerritory;
	int attCountryOwner;

public:
	//Overloaded constructor
	Bomb(Player* pl, Territory* terr, Territory* attTerr);

	//Copy constructor
	Bomb(const Bomb& b);

	//Assignment operator
	Bomb& operator = (const Bomb& b);

	//Get Priority
	int getPriority();

	//Less than operator for priority comparison
	bool operator <(const Bomb& playerObj) const;

	//Validates a bomb order
	bool validate();

	//Executes a bomb order
	void execute();

	friend std::ostream& operator<<(std::ostream& out, const Bomb& b);
};

class Blockade : public Order {
	int priority = 3;
	int playerID;
	string countryName;
	int countryOwner;
	Player* player;
	Territory* territory;


public:
	//Overloaded constructor
	Blockade(Player* pl, Territory* terr);

	//Copy constructor
	Blockade(const Blockade& b);

	//Assignment operator
	Blockade& operator = (const Blockade& b);

	//Get Priority
	int getPriority();

	//Less than operator for priority comparison
	bool operator <(const Blockade& playerObj) const;

	//Validates a blockade order
	bool validate();

	//Executes a blockade order
	void execute();

	friend std::ostream& operator<<(std::ostream& out, const Blockade& b);
};

class Airlift : public Order {
	int priority = 2;
	int playerID;
	int countryOwner;
	int units;
	Player* player;
	Territory* territory;
	Territory* attTerritory;
	int attCountryOwner;

public:
	//Overloaded constructor
	Airlift(Player* pl, Territory* terr, Territory* attTerr, int unitsAttackingWith);

	//Copy constructor
	Airlift(const Airlift& b);

	//Assignment operator
	Airlift& operator = (const Airlift& b);

	//Get Priority
	int getPriority();

	//Less than operator for priority comparison
	bool operator <(const Airlift& playerObj) const;

	//Validates an airlift order
	bool validate();

	//Executes an airlift order
	void execute();

	friend std::ostream& operator<<(std::ostream& out, const Airlift& b);

};

class Negotiate : public Order {
	int priority = 4;
	int playerID;
	int otherPlayerID;
	Player* player;
	Player* otherPlayer;

public:
	//Overloaded constructor
	Negotiate(Player* pl, int otherpID);

	//Copy constructor
	Negotiate(const Negotiate& b);

	//Assignment operator
	Negotiate& operator = (const Negotiate& b);

	//Get Priority
	int getPriority();

	//Less than operator for priority comparison
	bool operator <(const Negotiate& playerObj) const;

	//Validates a negotiate order
	bool validate();

	//Executes a negotiate order
	void execute();
	
	friend std::ostream& operator<<(std::ostream& out, const Negotiate& b);
};

class OrderList {

public:
    list <Order*> orders;

    //Default Constructor
	OrderList();
	
	//Destructor
	~OrderList();

	//Add order to list
	void addOrder(Order* x);

	//Remove order to list
	void removeOrder(Order* x);

	//Swap order x with order y in the list
	void swapOrder(Order* x, Order* y);

	//Move order up or down in the list
	void moveOrder(Order* x, string move);

	//Returns first order in list
	Order* front();

	//Returns true if OrderList is empty, false otherwise
	bool isEmpty();

	//View the list of orders
	void viewOrderList();

	//Check if any deploy orders have been issued
	bool containsDeployOrders();

	//Execute orders then deletes pointers to objects and clears list
	void executeOrderList();

	//Sorts orderlist by order priority
	void sortOrderList();
};
