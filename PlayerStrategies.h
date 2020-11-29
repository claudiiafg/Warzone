#pragma once

#include "Orders.h"
#include "Map.h"
#include "Cards.h"
#include <list>
#include <iterator>
#include <iostream>

using namespace std;

class GameEngine;

class OrderList; //This shouldn't have to be here if Orders.h is included, not sure what's going on

class PlayerStrategy
{
public:
	Map* map;
    OrderList* ol;
	virtual int issueOrder();
	virtual vector<Territory*> toAttack();
	virtual vector<Territory*> toDefend();
	void setMap(Map *m);
	void setOrderList(OrderList *oList);
};

class HumanPlayerStrategy : public PlayerStrategy {
public:
	virtual int issueOrder();
	virtual vector<Territory*> toAttack();
	virtual vector<Territory*> toDefend();
};

class AggressivePlayerStrategy : public PlayerStrategy {
public:
	virtual int issueOrder();
	virtual vector<Territory*> toAttack();
	virtual vector<Territory*> toDefend();
};

class BenevolentPlayerStrategy : public PlayerStrategy {
public:
	virtual int issueOrder();
	virtual vector<Territory*> toAttack();
	virtual vector<Territory*> toDefend();
};

class NeutralPlayerStrategy : public PlayerStrategy {
public:
	virtual int issueOrder();
	virtual vector<Territory*> toAttack();
	virtual vector<Territory*> toDefend();
};