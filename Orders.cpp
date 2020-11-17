#include "Orders.h"

#include <iostream>
#include <list>
#include <iterator>

using namespace std;

/////////////////////////////////////////////////////////////////////////////
///   ORDERS					   	                                      ///
/////////////////////////////////////////////////////////////////////////////

	//Default constructor
	Order::Order() {
		priority = NULL;
	}

	//Copy constructor
	Order::Order(const Order& b) {
		priority = b.priority;
	}

	//Assignment operator
	Order& Order::operator = (const Order& d2) {
		return *this;
	}

	//Get priority
	int Order::getPriority() {
		return priority;
	}

	//Less than operator for priority comparison
	bool Order::operator <(const Order& playerObj) const {
		return priority < playerObj.priority;
	}

	//Validates an order
	bool Order::validate() {
		return false;
	}

	//Executes an order
	void Order::execute() {
	}


    ostream &Order::operator<<(ostream &out) const {
        return out;
    }

/////////////////////////////////////////////////////////////////////////////
///   DEPLOY					   	                                      ///
/////////////////////////////////////////////////////////////////////////////

	//Overloaded constructor
	Deploy::Deploy(int thePlayerID, string theCountryName, int theCountryOwner, int theUnits) {
		countryOwner = theCountryOwner;
		countryName = theCountryName;
		units = theUnits;
		playerID = thePlayerID;
//		cout << *this << endl;
	}

	//Copy constructor
	Deploy::Deploy(const Deploy& d2) {
		countryOwner = d2.countryOwner;
		countryName = d2.countryName;
		units = d2.units;
		playerID = d2.playerID;
	}

	//Assignment operator
	Deploy& Deploy::operator = (const Deploy& d2) {
		countryOwner = d2.countryOwner;
		countryName = d2.countryName;
		units = d2.units;
		playerID = d2.playerID;
		return *this;
	}

	//Get priority
	int Deploy::getPriority() {
		return priority;
	}

	//Less than operator for priority comparison
	bool Deploy::operator <(const Deploy& playerObj) const {
		return priority < playerObj.priority;
	}

	//Validates a deploy order
	bool Deploy::validate() {
		bool playerOwnsCountry = false;
		bool validUnits = false;

		if (playerID == countryOwner) {
			playerOwnsCountry = true;
		}
		if (units >= 3) {
			validUnits = true;
		}
		return (playerOwnsCountry && validUnits);
	}

	//Executes a deploy order
	void Deploy::execute() {

		if (validate()) {
			cout << "Player " << playerID << " has deployed " << units << " units to " << countryName << ".\n";
		}

	}

	ostream& operator<<(std::ostream& out, const Deploy& b)
	{
		out << "A Deploy order has been created {" << "\n\tPlayerID: " << b.playerID << "\n\tcountryName: " << b.countryName << "\n\tcountryOwner: "
			<< b.countryOwner << "\n\tunits: " << b.units << "}\n";
		return out;
	}

/////////////////////////////////////////////////////////////////////////////
///   ADVANCE					   	                                      ///
/////////////////////////////////////////////////////////////////////////////

	//Overloaded constructor
	Advance::Advance(int thePlayerID, string theCountryName, int theCountryOwner, int theUnits, int theAttCountryOwner, string theAttCountryName, int theAttUnits) {
		playerID = thePlayerID;
		countryOwner = theCountryOwner;
		countryName = theCountryName;
		units = theUnits;
		attCountryOwner = theAttCountryOwner;
		attCountryName = theAttCountryName;
		attUnits = theAttUnits;
//		cout << *this << endl;
	}

	//Copy constructor
	Advance::Advance(const Advance& b) {
		playerID = b.playerID;
		countryOwner = b.countryOwner;
		countryName = b.countryName;
		attCountryOwner = b.attCountryOwner;
		attCountryName = b.attCountryName;
		units = b.units;
		attUnits = b.attUnits;
	}

	//Assignment operator
	Advance& Advance::operator = (const Advance& b) {
		playerID = b.playerID;
		countryOwner = b.countryOwner;
		countryName = b.countryName;
		attCountryOwner = b.attCountryOwner;
		attCountryName = b.attCountryName;
		units = b.units;
		attUnits = b.attUnits;
		return *this;
	}

	//Get priority
	int Advance::getPriority() {
		return priority;
	}

	//Less than operator for priority comparison
	bool Advance::operator <(const Advance& playerObj) const {
		return priority < playerObj.priority;
	}

	//Validates an advance order
	bool Advance::validate() {
		bool playerOwnsCountry = false;
		bool validUnitsToMoveOrAtt = false;

		//check if the player owns the country
		if (playerID == countryOwner) {
			playerOwnsCountry = true;
		}
		//check if player has more 1 or more units to attack with and if they are advancing with valid units
		if (attUnits >= 1 && attUnits <= units) {
			validUnitsToMoveOrAtt = true;
		}
		//needed: assure the 2 countries and ajdacent
		//needed: check if players are negotiating

		return (playerOwnsCountry && validUnitsToMoveOrAtt);
	}

	//Executes an advance order
	void Advance::execute() {

		if (validate()) {

			if (playerID == attCountryOwner) {
				cout << "Player " << playerID << " moved " << units << " units to " << countryName << ".\n";
			}
			else {
				cout << "Player " << playerID << " is attacking " << attCountryName << " owned by player " <<
					attCountryOwner << " with " << units << " units.\n";
			}
		}

	}

	ostream& operator<<(std::ostream& out, const Advance& b)
	{
		out << "An Advance order has been created {" << "\n\tPlayerID: " << b.playerID << "\n\tcountryName: " << b.countryName << "\n\tcountryOwner: "
			<< b.countryOwner << "\n\tunits: " << b.units << "\n\tattCountryOwner: " << b.attCountryOwner << "\n\tattCountryName: "
			<< b.attCountryName << "\n\tattUnits: " << b.attUnits << "}\n";
		return out;
	}

/////////////////////////////////////////////////////////////////////////////
///   BOMB					   	                                          ///
/////////////////////////////////////////////////////////////////////////////

	//Overloaded constructor
	Bomb::Bomb(int thePlayerID, string theCountryName, int theCountryOwner, int theAttCountryOwner, string theAttCountryName) {
		playerID = thePlayerID;
		countryOwner = theCountryOwner;
		countryName = theCountryName;
		attCountryOwner = theAttCountryOwner;
		attCountryName = theAttCountryName;
//		cout << *this << endl;
	}

	//Copy constructor
	Bomb::Bomb(const Bomb& b) {
		playerID = b.playerID;
		countryOwner = b.countryOwner;
		countryName = b.countryName;
		attCountryOwner = b.attCountryOwner;
		attCountryName = b.attCountryName;
	}

	//Assignment operator
	Bomb& Bomb::operator = (const Bomb& b) {
		playerID = b.playerID;
		countryOwner = b.countryOwner;
		countryName = b.countryName;
		attCountryOwner = b.attCountryOwner;
		attCountryName = b.attCountryName;
		return *this;
	}

	//Get priority
	int Bomb::getPriority() {
		return priority;
	}

	//Less than operator for priority comparison
	bool Bomb::operator <(const Bomb& playerObj) const {
		return priority < playerObj.priority;
	}

	//Validates a bomb order
	bool Bomb::validate() {
		bool playerOwnsCountry = false;
		bool validOpponent = false;

		//check if the player owns the country
		if (this->playerID == this->countryOwner) {
			playerOwnsCountry = true;
		}
		//
		if (this->playerID != this->attCountryOwner) {
			validOpponent = true;
		}
		//needed: assure the 2 countries and ajdacent
		//needed: check if players are negotiating

		return (playerOwnsCountry && validOpponent);
	}

	//Executes a bomb order
	void Bomb::execute() {
		if (validate()) {
			cout << "Player " << this->playerID << " bombed " << this->attCountryName << ".\n";
		}
	}

	ostream& operator<<(std::ostream& out, const Bomb& b)
	{
		out << "A Bomb order has been created {" << "\n\tPlayerID: " << b.playerID << "\n\tcountryName: " << b.countryName << "\n\tcountryOwner: "
			<< b.countryOwner << "\n\tattCountryOwner: " << b.attCountryOwner << "\n\tattCountryName: " << b.attCountryName << "}\n";
		return out;
	}

/////////////////////////////////////////////////////////////////////////////
///   BLOCKADE					   	                                      ///
/////////////////////////////////////////////////////////////////////////////

	//Overloaded constructor
	Blockade::Blockade(int thePlayerID, string theCountryName, int theCountryOwner, int theUnits) {
		playerID = thePlayerID;
		countryOwner = theCountryOwner;
		countryName = theCountryName;
		units = theUnits;
//		cout << *this << endl;
	}

	//Copy constructor
	Blockade::Blockade(const Blockade& b) {
		playerID = b.playerID;
		countryOwner = b.countryOwner;
		countryName = b.countryName;
		units = b.units;8
	}

	//Assignment operator
	Blockade& Blockade::operator = (const Blockade& b) {
		playerID = b.playerID;
		countryOwner = b.countryOwner;
		countryName = b.countryName;
		units = b.units;
		return *this;
	}

	//Get priority
	int Blockade::getPriority() {
		return priority;
	}

	//Less than operator for priority comparison
	bool Blockade::operator <(const Blockade& playerObj) const {
		return priority < playerObj.priority;
	}

	//Validates a blockade order
	bool Blockade::validate() {
		bool playerOwnsCountry = false;
		bool validUnits = false;

		if (playerID == countryOwner) {
			playerOwnsCountry = true;
		}
		if (units >= 0) {
			validUnits = true;
		}
		return (playerOwnsCountry && validUnits);
	}

	//Executes a blockade order
	void Blockade::execute() {

		if (validate()) {
			cout << "Player " << playerID << " has blockaded " << countryName << ".\n";
			//logic to return that the player no longer owns the country and that the units have tripled
		}

	}

	ostream& operator<<(std::ostream& out, const Blockade& b)
	{
		out << "A Blockade order has been created {" << "\n\tPlayerID: " << b.playerID << "\n\tcountryName: " << b.countryName << "\n\tcountryOwner: "
			<< b.countryOwner << "\n\tunits: " << b.units << "}\n";
		return out;
	}

/////////////////////////////////////////////////////////////////////////////
///   AIRLIFT					   	                                      ///
/////////////////////////////////////////////////////////////////////////////

	//Overloaded constructor
	Airlift::Airlift(int thePlayerID, string theCountryName, int theCountryOwner, int theUnits, int theAttCountryOwner, string theAttCountryName, int theAttUnits) {
		playerID = thePlayerID;
		countryOwner = theCountryOwner;
		countryName = theCountryName;
		units = theUnits;
		attCountryOwner = theAttCountryOwner;
		attCountryName = theAttCountryName;
		attUnits = theAttUnits;
//		cout << *this << endl;
	}

	//Copy constructor
	Airlift::Airlift(const Airlift& b) {
		playerID = b.playerID;
		countryOwner = b.countryOwner;
		countryName = b.countryName;
		attCountryOwner = b.attCountryOwner;
		attCountryName = b.attCountryName;
		units = b.units;
		attUnits = b.attUnits;
	}

	//Assignment operator
	Airlift& Airlift::operator = (const Airlift& b) {
		playerID = b.playerID;
		countryOwner = b.countryOwner;
		countryName = b.countryName;
		attCountryOwner = b.attCountryOwner;
		attCountryName = b.attCountryName;
		units = b.units;
		attUnits = b.attUnits;
		return *this;
	}

	//Get priority
	int Airlift::getPriority() {
		return priority;
	}

	//Less than operator for priority comparison
	bool Airlift::operator <(const Airlift& playerObj) const {
		return priority < playerObj.priority;
	}

	//Validates an airlift order
	bool Airlift::validate() {
		bool playerOwnsCountry = false;
		bool validUnitsToMoveOrAtt = false;

		//check if the player owns the country
		if (playerID == countryOwner) {
			playerOwnsCountry = true;
		}
		//check if player has more 1 or more units to attack with and if they are advancing with valid units
		if (attUnits >= 1 && attUnits <= units) {
			validUnitsToMoveOrAtt = true;
		}
		//needed: check if players are negotiating

		return (playerOwnsCountry && validUnitsToMoveOrAtt);
	}

	//Executes an airlift order
	void Airlift::execute() {

		if (validate()) {

			if (playerID == attCountryOwner) {
				cout << "Player " << playerID << " airlifted " << units << " units to " << countryName << ".\n";
			}
			else {
				cout << "Player " << playerID << " is attacking " << attCountryName << " owned by player " << attCountryOwner << " with " << units << " units via airlift" << ".\n";
			}
		}

	}

	ostream& operator<<(std::ostream& out, const Airlift& b)
	{
		out << "An Airlift order has been created {" << "\n\tPlayerID: " << b.playerID << "\n\tcountryName: " << b.countryName << "\n\tcountryOwner: "
			<< b.countryOwner << "\n\tunits: " << b.units << "\n\tattCountryOwner: " << b.attCountryOwner << "\n\tattCountryName: "
			<< b.attCountryName << "\n\tattUnits: " << b.attUnits << "}\n";
		return out;
	}

/////////////////////////////////////////////////////////////////////////////
///   NEGOTIATE					   	                                      ///
/////////////////////////////////////////////////////////////////////////////

	//Overloaded constructor
	Negotiate::Negotiate(int thePlayerID, int theOtherPlayer) {
		playerID = thePlayerID;
		otherPlayer = theOtherPlayer;
//		cout << *this << endl;
	}

	//Copy constructor
	Negotiate::Negotiate(const Negotiate& b) {
		playerID = b.playerID;
		otherPlayer = b.otherPlayer;
	}

	//Assignment operator
	Negotiate& Negotiate::operator = (const Negotiate& b) {
		playerID = b.playerID;
		otherPlayer = b.otherPlayer;
		return *this;
	}

	//Get priority
	int Negotiate::getPriority() {
		return priority;
	}

	//Less than operator for priority comparison
	bool Negotiate::operator <(const Negotiate& playerObj) const {
		return priority < playerObj.priority;
	}


	//Validates a negotiate order
	bool Negotiate::validate() {
		bool validOpponent = false;

		if (playerID != otherPlayer) {
			validOpponent = true;
		}

		return (validOpponent);
	}

	//Executes a negotiate order
	void Negotiate::execute() {

		if (validate()) {
			cout << "Player " << playerID << " and Player " << otherPlayer << " are now negotiating" << ".\n";
		}
	}

	ostream& operator<<(std::ostream& out, const Negotiate& b)
	{
		out << "A Negotiate order has been created {" << "\n\tPlayerID: " << b.playerID << "\n\totherPlayer: " << b.otherPlayer << "}\n";
		return out;
	}

/////////////////////////////////////////////////////////////////////////////
///   ORDERLIST					   	                                      ///
/////////////////////////////////////////////////////////////////////////////

	//Default Constructor
	OrderList::OrderList() = default;

	//destructor
	OrderList::~OrderList() {
		list <Order*> ::iterator it;
		for (it = orders.begin(); it != orders.end(); ++it) {
			delete* it;
		}
		orders.clear();
	}

	//Add order to list
	void OrderList::addOrder(Order* x) {
		orders.push_back(x);
	}

	//Remove order from list
	void OrderList::removeOrder(Order* x) {
		list <Order*> ::iterator it;
		for (it = orders.begin(); it != orders.end(); ++it) {
			if (*it == x) {
				orders.remove(x);
				break;
			}
		}
	}

	//Swap order x with order y in the list
	void OrderList::swapOrder(Order* x, Order* y) {
		list <Order*> ::iterator it;
		list <Order*> ::iterator jt;
		list <Order*> ::iterator temp1;
		list <Order*> ::iterator temp2;
		bool check1 = false;
		bool check2 = false;

		for (it = orders.begin(); it != orders.end(); ++it) {
			if (*it == x) {
				temp1 = it;
				check1 = true;
			}
			if (*it == y) {
				temp2 = it;
				check2 = true;
			}
			if (check1 && check2) {
				*temp1 = y;
				*temp2 = x;
			}
		}
	}

	//Move order up or down in the list
	void OrderList::moveOrder(Order* x, string move) {
		list <Order*> ::iterator it;
		list <Order*> ::iterator hold_it;
		list <Order*> ::iterator it_pos;
		bool check1 = false;
		bool check2 = true;
		for (it = orders.begin(); it != orders.end(); ++it) {
			if (move == "down") {
				it_pos = it;
			}
			if (check1) {
				Order* o = (*it_pos);
				if (move == "down") {
					*it = x;
					*hold_it = o;
				}
				break;
			}
			if (*it == x) {
				if (check2 && move == "up") {
					break;
				}
				hold_it = it;
				if (move == "up") {
					Order* o = (*it_pos);
					*it_pos = x;
					*it = o;
				}
				check1 = true;
			}
			check2 = false;
			if (move == "up") {
				it_pos = it;
			}
		}
	}

	//Compare priority of orders in list
	bool compare(Order* x,Order* y) {
		if (x->getPriority() < y->getPriority())
			return (true);
		else
			return(false);
	}

	//View the list of orders
	void OrderList::viewOrderList() {
		list <Order*> ::iterator it;
		for (it = orders.begin(); it != orders.end(); ++it) {
			cout << (*it) << endl;
		}
	}

	bool OrderList::containsDeployOrders() {
		list <Order*> ::iterator it;
		Deploy* t;
		for (it = orders.begin(); it != orders.end(); ++it) {
			if (typeid (t) == typeid(*it));
			return true;
		}
		return false;
	}

	//Execute orders then deletes pointers to objects and clears list
	void OrderList::executeOrderList() {
		orders.sort(compare);
		list <Order*> ::iterator it;
		for (it = orders.begin(); it != orders.end(); ++it) {
			(*it)->execute();
			delete *it;
		}
		orders.clear();
	}