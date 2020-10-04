#pragma once
#include <iostream>

using namespace std;

class Order
{
public:
	int playerID;

	Order() {
		playerID = -1;
	}

	Order(int thePlayerID){
		playerID = thePlayerID;
	}

	//copy constructor
	Order(const Order& o2) {
		playerID = o2.playerID;
	}

	bool validate();

	void execute();
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

	////copy constructor
	//Deploy(const Deploy& d2) {
	//	countryOwner = d2.countryOwner;
	//	countryName = d2.countryName;
	//	units = d2.units;
	//	playerID = d2.playerID;
	//}

	//not done yet
	bool validate(int thePlayerID, int theCountryOwner, int theUnits, int theAttCountryOwner, string theAttCountryName, int theAttUnits) {
		bool check1 = false;
		bool check2 = false;
		bool check3 = false;

		if (thePlayerID == theCountryOwner) {
			check1 = true;
		}
		if (theUnits >= 1) {
			check2 = true;
		}

		if (attUnits >= 1) {
			check3 = true;
		}
		return (check1 && check2);
	}

	//void execute(int thePlayerID, int theCountryOwner, string theCountryName, int theUnits) {

	//	if (validate(thePlayerID, theCountryOwner, theUnits)) {
	//		cout << "Player " << thePlayerID << " has deployed " << theUnits << " units to " << theCountryName << ".\n";
	//	}

	//}

};

int main()
{	
	//test
}

