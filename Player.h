#pragma once
using namespace std;

class Player {
#include <vector>
#include "Map.h"
#include "Map.cpp"
#include "Orders.h"
#include "Cards.h"

public:
	Player();
	Player(Player const &otherPlayer);
	Player::~Player();
	Player::getMyTerritories() { return myTerritories; }
	Player::getMyHand() { return myHand; }
	Player::getMyOrders() { return myOrders; }
	vector<Territory> toDefend();
	vector<Territory> toAttack();
	void issueOrder();
private:
	vector<Territory> *myTerritories;
	Hand *myHand;
	OrdersList *myOrders;
};
