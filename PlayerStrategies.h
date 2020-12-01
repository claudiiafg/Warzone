#pragma once

#include <list>
#include <iterator>
#include <iostream>

using namespace std;

class OrderList;
class Player;
class Map;
class Territory;

class PlayerStrategy
{
protected:
    OrderList* ol;
public:
	Player* player;
    Map* stratMap;
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