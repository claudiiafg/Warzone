#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "Map.h"
//#include "Orders.h"
//#include "Cards.h"

class Player {

public:
	Player();
//	Player(const Player &otherPlayer) : 
	Player::~Player();
	Player::getMyTerritories() { return myTerritories; }
	Player::getMyHand() { return myHand; }
	Player::getMyOrders() { return myOrders; }
	vector<Territory*> toDefend();
	vector<Territory> toAttack();
	void issueOrder();
	friend ostream& operator << (ostream& out, const Player& p);
private:
	vector<Territory*> myTerritories;
	Hand *myHand;
	OrdersList *myOrders;
};

#endif