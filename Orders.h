#pragma once
#include <iostream>
#include <list>
#include <iterator>
//#include <vector>

using namespace std;

class Order
{
public:
	// playerID;

	Order() {
		//playerID = -1;
	}

	//Order(int thePlayerID){
	//	playerID = thePlayerID;
	//}

	////copy constructor
	//Order(const Order& o2) {
	//	playerID = o2.playerID;
	//}

	bool validate();

	void execute();



	friend std::ostream& operator<<(std::ostream& out, const Order& b)
	{
		return b.print(out);
	}

	virtual std::ostream& print(std::ostream& out) const
	{
		//out << "Order";
		return out;
	}
};

class Deploy : public Order {
	int countryOwner;
	string countryName;
	int units;
	int playerID;

public:
	Deploy(int thePlayerID, string theCountryName, int theCountryOwner, int theUnits) {
		countryOwner = theCountryOwner;
		countryName = theCountryName;
		units = theUnits;
	}

	Deploy(const Deploy& d2) {
		countryOwner = d2.countryOwner;
		countryName = d2.countryName;
		units = d2.units;
		playerID = d2.playerID;
	}

	bool validate(int thePlayerID, int theCountryOwner, int theUnits) {
		bool playerOwnsCountry = false;
		bool validUnits = false;

		if (thePlayerID == theCountryOwner) {
			playerOwnsCountry = true;
		}
		if (theUnits >= 3) {
			validUnits = true;
		}
		return (playerOwnsCountry && validUnits);
	}

	void execute(int thePlayerID, int theCountryOwner, string theCountryName, int theUnits) {

		if (validate(thePlayerID, theCountryOwner, theUnits)) {
			cout << "Player " << thePlayerID << " has deployed " << theUnits << " units to " << theCountryName << ".\n";
		}

	}
};

class Advance : public Order {
	int countryOwner;
	string countryName;
	int units;
	int playerID;
	int attCountryOwner;
	string attCountryName;
	int attUnits;

public:
	Advance(int thePlayerID, string theCountryName, int theCountryOwner, int theUnits, int theAttCountryOwner, string theAttCountryName, int theAttUnits) {
		countryOwner = theCountryOwner;
		countryName = theCountryName;
		units = theUnits;
		attCountryOwner = theAttCountryOwner;
		attCountryName = theAttCountryName;
		attUnits = theAttUnits;
	}

	bool validate(int thePlayerID, int theCountryOwner, int theUnits, int theAttUnits) {
		bool playerOwnsCountry = false;
		bool validUnitsToMoveOrAtt = false;

		//check if the player owns the country
		if (thePlayerID == theCountryOwner) {
			playerOwnsCountry = true;
		}
		//check if player has more 1 or more units to attack with and if they are advancing with valid units
		if (attUnits >= 1 && attUnits <= theUnits) {
			validUnitsToMoveOrAtt = true;
		}
		//needed: assure the 2 countries and ajdacent
		//needed: check if players are negotiating

		return (playerOwnsCountry && validUnitsToMoveOrAtt);
	}

	void execute(int thePlayerID, int theCountryOwner, string theCountryName, int theUnits, int theAttUnits, int attCountryOwner, string attCountryName) {

		if (validate(thePlayerID, theCountryOwner, theUnits, theAttUnits)) {

			if (thePlayerID == attCountryOwner) {
				cout << "Player " << thePlayerID << " moved " << theUnits << " units to " << theCountryName << ".\n";
			}
			else {
				cout << "Player " << thePlayerID << " is attacking  " << attCountryOwner << " with " << theUnits << " units at " << attCountryName << ".\n";
			}
		}

	}


};

class Bomb : public Order {
	int playerID;
	int countryOwner;
	string countryName;
	int attCountryOwner;
	string attCountryName;

public:
	Bomb(int thePlayerID, string theCountryName, int theCountryOwner, int theAttCountryOwner, string theAttCountryName) {
		playerID = thePlayerID;
		countryOwner = theCountryOwner;
		countryName = theCountryName;
		attCountryOwner = theAttCountryOwner;
		attCountryName = theAttCountryName;
	}

	Bomb(const Bomb& b) {
		playerID = b.playerID;
		countryOwner = b.countryOwner;
		countryName = b.countryName;
		attCountryOwner = b.attCountryOwner;
		attCountryName = b.attCountryName;
		cout << "Copy constructor called " << endl;
	}

	Bomb& operator = (const Bomb& b) {
		cout << "Assignment operator called " << endl;
		return *this;
	}

	bool validate(int thePlayerID, int theCountryOwner, int theAttCountryOwner) {
		bool playerOwnsCountry = false;
		bool validOpponent = false;

		//check if the player owns the country
		if (thePlayerID == theCountryOwner) {
			playerOwnsCountry = true;
		}
		//
		if (thePlayerID != theAttCountryOwner) {
			validOpponent = true;
		}
		//needed: assure the 2 countries and ajdacent
		//needed: check if players are negotiating

		return (playerOwnsCountry && validOpponent);
	}

	void execute(int thePlayerID, int theCountryOwner, int theAttCountryOwner, string attCountryName) {

		if (validate(thePlayerID, theCountryOwner, theAttCountryOwner)) {
			cout << "Player " << thePlayerID << " bombed " << attCountryName << ".\n";
		}

	}

	virtual std::ostream& print(std::ostream& out) const override
	{
		out << "bomb(" << playerID << ", " << countryOwner << ", " << countryName << ", " << attCountryOwner << ", " << attCountryName << ")";
		return out;
	}
};

class Blockade : public Order {
	int countryOwner;
	string countryName;
	int units;
	int playerID;

public:
	Blockade(int thePlayerID, string theCountryName, int theCountryOwner, int theUnits) {
		countryOwner = theCountryOwner;
		countryName = theCountryName;
		units = theUnits;
	}

	bool validate(int thePlayerID, int theCountryOwner, int theUnits) {
		bool playerOwnsCountry = false;
		bool validUnits = false;

		if (thePlayerID == theCountryOwner) {
			playerOwnsCountry = true;
		}
		if (theUnits >= 0) {
			validUnits = true;
		}
		return (playerOwnsCountry && validUnits);
	}

	void execute(int thePlayerID, int theCountryOwner, string theCountryName, int theUnits) {

		if (validate(thePlayerID, theCountryOwner, theUnits)) {
			cout << "Player " << thePlayerID << " has blockaded " << theCountryName << ".\n";
			//logic to return that the player no longer owns the country and that the units have tripled
		}

	}
};

class Airlift : public Order {
	int countryOwner;
	string countryName;
	int units;
	int playerID;
	int attCountryOwner;
	string attCountryName;
	int attUnits;

public:
	Airlift(int thePlayerID, string theCountryName, int theCountryOwner, int theUnits, int theAttCountryOwner, string theAttCountryName, int theAttUnits) {
		countryOwner = theCountryOwner;
		countryName = theCountryName;
		units = theUnits;
		attCountryOwner = theAttCountryOwner;
		attCountryName = theAttCountryName;
		attUnits = theAttUnits;
	}

	bool validate(int thePlayerID, int theCountryOwner, int theUnits, int theAttUnits) {
		bool playerOwnsCountry = false;
		bool validUnitsToMoveOrAtt = false;

		//check if the player owns the country
		if (thePlayerID == theCountryOwner) {
			playerOwnsCountry = true;
		}
		//check if player has more 1 or more units to attack with and if they are advancing with valid units
		if (attUnits >= 1 && attUnits <= theUnits) {
			validUnitsToMoveOrAtt = true;
		}
		//needed: check if players are negotiating

		return (playerOwnsCountry && validUnitsToMoveOrAtt);
	}

	void execute(int thePlayerID, int theCountryOwner, string theCountryName, int theUnits, int theAttUnits, int attCountryOwner, string attCountryName) {

		if (validate(thePlayerID, theCountryOwner, theUnits, theAttUnits)) {

			if (thePlayerID == attCountryOwner) {
				cout << "Player " << thePlayerID << " airlifted " << theUnits << " units to " << theCountryName << ".\n";
			}
			else {
				cout << "Player " << thePlayerID << " is attacking  " << attCountryOwner << " with " << theUnits << " units at " << attCountryName << " via airlift" << ".\n";
			}
		}

	}

};

class Negotiate : public Order {
	int otherPlayer;

public:
	Negotiate(int thePlayerID, int theOtherPlayer) {
		otherPlayer = theOtherPlayer;
	}

	bool validate(int thePlayerID, int theOtherPlayer) {
		bool validOpponent = false;

		if (thePlayerID != theOtherPlayer) {
			validOpponent = true;
		}

		return (validOpponent);
	}

	void execute(int thePlayerID, int theOtherPlayer) {

		if (validate(thePlayerID, theOtherPlayer)) {
			cout << "Player " << thePlayerID << " and Player  " << theOtherPlayer << " are now negotiating" << ".\n";
		}

	}
};

class OrderList {
	list <Order> orders;

public:

	OrderList() {
	}

	void addOrder(Order* x) {
		//cout << *x << endl;
		if (typeid(*x) == typeid(Bomb)) {
			Bomb b = dynamic_cast<Bomb&>(*x);

			//cout << b << endl;
			//cout << "yesssss" << endl;

			orders.push_back(b);
		}
		//cout << (*x) << endl;
		//cout << orders.size() << endl;
	}

	void removeOrder(Order* x) {
		list <Order> ::iterator it;
		//cout << *x << endl;
		for (it = orders.begin(); it != orders.end(); ++it) {
			if (typeid(*x) == typeid(Bomb)) {
				cout << "hello" << endl;
				cout << *it << endl;
				//Bomb b = dynamic_cast<Bomb&>(*it);
				//cout << b << endl;
			}
			//cout << *it << endl;
			//if (orders[i] == *x ) {
			//	cout << "dfsdfsdf" << endl;
			//}
			//cout << dynamic_cast<Bomb*>(&orders[i]) << endl;
			//cout << *x << endl;
		}

		//orders.remove(*x);
		//cout << *i << " has been removed." << endl;
	}




	////copy constructor
	//Order(const Order& o2) {
	//	playerID = o2.playerID;
	//}




	//void executeList(list <Order> o) {
	//	list <Order> ::iterator it;
	//	for (it = o.begin(); it != o.end(); ++it) {

	//	}
	//		
	//	cout << '\n';
	//}


};
//void showList(list <Order> o) {
//	list <Order> ::iterator it;
//	for (it = o.begin(); it != o.end(); ++it)
//		cout << *it << endl;
//	cout << '\n';
//}

//std::ostream& operator<<(std::ostream& out, const Order& b)
//{
//	if (typeid(b).name() == "class Bomb") {
//		out << typeid(b).name();
//	}
//	out << typeid(b).name();
//	return out;
//}


int main()
{
	OrderList player1Orders;

	Bomb mybomb1 = Bomb(1, "Quebec", 1, 2, "Ontario");
	Bomb mybomb2 = Bomb(1, "Manitoba", 1, 2, "Yukon");

	Bomb* bombPtr1 = &mybomb1;
	Bomb* bombPtr2 = &mybomb2;

	//cout << *bombPtr1 << endl;

	player1Orders.addOrder(bombPtr1);
	player1Orders.addOrder(bombPtr2);
	//player1Orders.removeOrder(bombPtr1);
}

