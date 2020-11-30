#pragma once

#include "Orders.h"
#include "Map.h"
#include "Cards.h"
#include <list>
#include <iterator>
#include <iostream>

using namespace std;

class GameEngine;
class OrderList;
class Players;

class PlayerStrategy
{
protected:
    static Map* map;
    static OrderList* ol;
    static Players* players;
public:
	Player* player;
	virtual int issueOrder();
	virtual vector<Territory*> toAttack();
	virtual vector<Territory*> toDefend();
	void setMap(Map *m);
	void setOrderList(OrderList *oList);
	void setPlayer(Player* player);
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