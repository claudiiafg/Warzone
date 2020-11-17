#pragma once

using namespace std;
#include <vector>
#include "Map.h"
#include "Cards.h"
#include "Orders.h"

class Player {

public:
    int name;
    int armies;
	int reinforcements;
	int phase;

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

	//Mutators
	void setTerritories(vector<Territory*> playerTerritories);
	void setHand(Hand* playerHand);
	void setOrders(OrderList* playerOrders);
	void setReinforcements(int reinforcements);
	void setPhase(int phase);

	//Required Methods
	vector<Territory *> toDefend();
	vector<Territory *> toAttack();
	void issueOrder();

	//Stream operator overload
	 friend ostream& operator << (ostream& out, const Player& p);

private:
	//Required data members
	vector<Territory *> playerTerritories;
	Hand *playerHand;
	OrderList *playerOrders;
};

