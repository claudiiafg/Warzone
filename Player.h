#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "Orders.cpp"
#include "Cards.cpp"

class Territory;

class Player {

public:
	//Constructors and Destructors
	Player();
	Player(const Player& otherPlayer);
	~Player();

    // Forward declaration
    Territory getTerritory();

	//Assignment overload
	Player& operator= (const Player& p);

	//Accessors
	vector<Territory *> getMyTerritories() { return playerTerritories; }
	Hand* getMyHand() { return playerHand; }
	OrderList* getMyOrders() { return playerOrders; }

	//Methods
	vector<Territory *> toDefend();
	vector<Territory *> toAttack();
	void issueOrder();

	//Stream overload
	friend ostream& operator << (ostream& out, const Player& p);

protected:
    Territory* t;

private:
	//Data members
	vector<Territory *> playerTerritories;
	Hand *playerHand;
	OrderList *playerOrders;
};

#endif