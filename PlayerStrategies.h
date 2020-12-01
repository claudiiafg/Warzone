#pragma once

#include "Orders.h"
#include "Map.h"
#include "Cards.h"
#include <list>
#include <iterator>
#include <iostream>

using namespace std;

static Map* stratMap = new Map();

class OrderList;
class Player;

class PlayerStrategy
{
//protected:
    //OrderList* ol;
public:
	Player* player;
	virtual void issueOrder();
	virtual Territory* toAttack();
	virtual Territory* toDefend();
	void setMap(Map *m);
	void setOrderList(OrderList *oList);
	void setPlayer(Player* player);
};

class HumanPlayerStrategy : public PlayerStrategy {
public:
	virtual void issueOrder();
	virtual Territory* toAttack();
	virtual Territory* toDefend();
};

class AggressivePlayerStrategy : public PlayerStrategy {
public:
	Territory* strongest;

	virtual void issueOrder();
	virtual Territory* toAttack();
	virtual Territory* toDefend();

	Territory* getBiggest();
	Territory* getWeakestEnemy();
	Territory* getStrongestEnemy();
};

class BenevolentPlayerStrategy : public PlayerStrategy {
public:
	virtual void issueOrder();
	virtual Territory* toAttack();
	virtual Territory* toDefend();
};

class NeutralPlayerStrategy : public PlayerStrategy {
public:
	virtual void issueOrder();
	virtual Territory* toAttack();
	virtual Territory* toDefend();
};