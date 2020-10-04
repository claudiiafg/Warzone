#pragma once
using namespace std;

class Player {
#include <vector>
#include "Map.h"
#include "Orders.h"
#include "Cards.h"

public:
	Player();
	Player(Player otherPlayer);
	vector<Territory> toDefend();
	vector<Territory> toAttack();
	void issueOrder(Order newOrder);
private:
	vector<Territory> *myTerritories;
	Hand *myHand;
	OrdersList *myOrders;
};
