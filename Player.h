#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "Map.h"
#include "Orders.h"
#include "Cards.h"

class Player {

public:
	//Constructors and Destructors
	Player();
	Player(const Player& otherPlayer);
	~Player();

	//Assignment overload
	Player& operator= (const Player& p);

	//Accessors
	vector<Territory*> getMyTerritories() { return playerTerritories; }
	Hand* getMyHand() { return playerHand; }
	OrdersList* getMyOrders() { return playerOrders; }

	//Methods
	vector<Territory*> toDefend();
	vector<Territory*> toAttack();
	void issueOrder();

	//Stream overload
	friend ostream& operator << (ostream& out, const Player& p);

private:
	//Data members
	vector<Territory*> playerTerritories;
	Hand *playerHand;
	OrdersList *playerOrders;
};

#endif