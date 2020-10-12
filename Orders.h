#include <iostream>
#include <list>
#include <iterator>

using namespace std;

class Order{
public:

	Order();

	//Copy constructor
	Order(const Order& b);

	//Assignment operator
	Order& operator = (const Order& d2);

	virtual bool validate();

	virtual void execute();

	friend std::ostream& operator<<(std::ostream& out, const Order& b);

};

class Deploy : public Order {
	int playerID;
	string countryName;
	int countryOwner;
	int units;


public:
	Deploy(int thePlayerID, string theCountryName, int theCountryOwner, int theUnits);

	//Copy constructor
	Deploy(const Deploy& d2);

	//Assignment operator
	Deploy& operator = (const Deploy& d2);

	bool validate();

	void execute();

	friend std::ostream& operator<<(std::ostream& out, const Deploy& b);
};

class Advance : public Order {
	int playerID;
	string countryName;
	int countryOwner;
	int units;
	int attCountryOwner;
	string attCountryName;
	int attUnits;

public:
	Advance(int thePlayerID, string theCountryName, int theCountryOwner, int theUnits, int theAttCountryOwner, string theAttCountryName, int theAttUnits);

	//Copy constructor
	Advance(const Advance& b);

	//Assignment operator
	Advance& operator = (const Advance& b);

	bool validate();

	void execute();

	friend std::ostream& operator<<(std::ostream& out, const Advance& b);
};

class Bomb : public Order {
	int playerID;
	int countryOwner;
	string countryName;
	int attCountryOwner;
	string attCountryName;

public:
	Bomb(int thePlayerID, string theCountryName, int theCountryOwner, int theAttCountryOwner, string theAttCountryName);

	//Copy constructor
	Bomb(const Bomb& b);

	//Assignment operator
	Bomb& operator = (const Bomb& b);

	bool validate();

	void execute();

	friend std::ostream& operator<<(std::ostream& out, const Bomb& b);
};

class Blockade : public Order {
	int playerID;
	string countryName;
	int countryOwner;
	int units;


public:
	Blockade(int thePlayerID, string theCountryName, int theCountryOwner, int theUnits);

	//Copy constructor
	Blockade(const Blockade& b);

	//Assignment operator
	Blockade& operator = (const Blockade& b);

	bool validate();

	void execute();

	friend std::ostream& operator<<(std::ostream& out, const Blockade& b);
};

class Airlift : public Order {
	int playerID;
	string countryName;
	int countryOwner;
	int units;
	int attCountryOwner;
	string attCountryName;
	int attUnits;

public:
	Airlift(int thePlayerID, string theCountryName, int theCountryOwner, int theUnits, int theAttCountryOwner, string theAttCountryName, int theAttUnits);

	//Copy constructor
	Airlift(const Airlift& b);

	//Assignment operator
	Airlift& operator = (const Airlift& b);

	bool validate();

	void execute();

	friend std::ostream& operator<<(std::ostream& out, const Airlift& b);

};

class Negotiate : public Order {
	int playerID;
	int otherPlayer;

public:
	Negotiate(int thePlayerID, int theOtherPlayer);

	//Copy constructor
	Negotiate(const Negotiate& b);

	//Assignment operator
	Negotiate& operator = (const Negotiate& b);

	bool validate();

	void execute();
	
	friend std::ostream& operator<<(std::ostream& out, const Negotiate& b);
};

class OrderList {
	list <Order*> orders;

public:

	OrderList();

	void addOrder(Order* x);

	void removeOrder(Order* x);

	
	void swapOrder(Order* x, Order* y);

	void moveOrder(Order* x, string move);

	void viewOrderList();

	void executeOrderList();
};
