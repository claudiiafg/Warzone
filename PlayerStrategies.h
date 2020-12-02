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
	virtual void issueOrder(Player* player);
	virtual Territory* toAttack(Player* player);
	virtual Territory* toDefend(Player* player);
	void setMap(Map *m);
};

class HumanPlayerStrategy : public PlayerStrategy {
public:
	virtual void issueOrder(Player* player);
	virtual Territory* toAttack(Player* player);
	virtual Territory* toDefend(Player* player);
};

class AggressivePlayerStrategy : public PlayerStrategy {
public:
	virtual void issueOrder(Player* player);
	virtual Territory* toAttack(Player* player);
	virtual Territory* toDefend(Player* player);

	Territory* getBiggest(Player* player);
	Territory* getWeakestEnemy(Territory* strongest, Player* player);
	Territory* getStrongestEnemy(Territory* strongest, Player* player);
};

class BenevolentPlayerStrategy : public PlayerStrategy {
public:
	virtual void issueOrder(Player* player);
	virtual Territory* toAttack(Player* player);
	virtual Territory* toDefend(Player* player);
};

class NeutralPlayerStrategy : public PlayerStrategy {
public:
	virtual void issueOrder(Player* player);
	virtual Territory* toAttack(Player* player);
	virtual Territory* toDefend(Player* player);
};