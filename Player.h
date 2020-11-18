#pragma once

#include <vector>
#include <map>
#include "Map.h"
#include "Cards.h"
#include "Orders.h"
#include "GameObservers.h"

using namespace std;

class GameEngine;

class Player: public Observable {

public:
    int name;
    int armies;
	int reinforcements;
	int phase;
	int deployCounter = 1;

	//Constructors
	Player();
	Player(int name, int armies, vector<Territory*> playerTerritories, Hand* playerHand, OrderList* playerOrders);
	Player(const Player& otherPlayer);

	//Destructor
	~Player();

	//Assignment operator overload
	Player& operator= (const Player& p);

	//Accessors
	vector<Territory *> getMyTerritories() { return playerTerritories; }
	Hand* getMyHand() { return playerHand; }
	OrderList* getMyOrders() { return playerOrders; }
	int getReinforcements() { return reinforcements; }
	int getPhase() { return phase; }
	int getTerritoryNum() { return playerTerritories.size(); }

	//Mutators
	void setTerritories(vector<Territory*> playerTerritories);
	void setHand(Hand* playerHand);
	void setOrders(OrderList* playerOrders);
	void setReinforcements(int reinforcements);
	void setPhase(int phase);

	//Methods
	list<Territory*> toDefend(Map* map);
	list<Territory*> toAttack(Map* map);
	void issueOrder(Map* map);
	vector<Territory*> Player::adjacentEnemies(string terrID);
	bool compare(Territory* x, Territory* y);

	//Stream operator overload
	 friend ostream& operator << (ostream& out, const Player& p);

private:
	//Required data members
	vector<Territory *> playerTerritories;
	Hand *playerHand;
	OrderList *playerOrders;
};

