#pragma once

#include "Orders.h"
#include "Map.h"
#include "Cards.h"
#include <iostream>
using namespace std;

class PlayerStrategy
{
protected:
    static Map *map;
    static OrderList *ol;
public:
	virtual int issueOrder();
	virtual vector<Territory*> toAttack();
	virtual vector<Territory*> toDefend();
	static void setMap(Map *m);
	static void setOrderList(OrderList *oList);
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