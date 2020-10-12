#pragma once

#include <vector>
#include "Orders.h"

class Hand;


class Territory;

class Player {

public:
	//Constructors
	Player();
	Player(vector<Territory*> playerTerritories, Hand* playerHand, OrderList* playerOrders);
	Player(const Player& otherPlayer);


	//Destructor
	~Player();

    //Forward declaration
    Territory getTerritory();

	//Assignment operator overload
	Player& operator= (const Player& p);

	//Accessors
	vector<Territory *> getMyTerritories() { return playerTerritories; }
	Hand* getMyHand() { return playerHand; }
	OrderList* getMyOrders() { return playerOrders; }

	//Required Methods
	vector<Territory *> toDefend();
	vector<Territory *> toAttack();
	void issueOrder();

	//Stream operator overload
	 friend ostream& operator << (ostream& out, const Player& p);

protected:
	//Helper data members
    Territory* t;

private:
	//Required data members
	vector<Territory *> playerTerritories;
	Hand *playerHand;
	OrderList *playerOrders;
};

