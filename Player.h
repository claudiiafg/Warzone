#pragma once

#include <vector>
#include <map>
#include "Map.h"
#include "Cards.h"
#include "Orders.h"
#include "GameObservers.h"

using namespace std;

class Player: public PhaseObserver, public GameStatObserver {

public:
    int name;
    int armies;
	int reinforcements;
	int phase;
	int deployCounter = 1;
	int cardFlag = false;
	vector<Player*> allies;

	//Constructors
	Player();
	Player(int name, int armies, vector<Territory*> playerTerritories, Hand* playerHand, OrderList* playerOrders, vector<Player*> allies);
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
	void addAlly(Player* player);
	void setCardFlag(bool flag);

	//Methods
	list<Territory*> toDefend(Map* map);
	list<Territory*> toAttack(Map* map);
	void issueOrder(Map* map);
	vector<Territory*> adjacentEnemies(string terrID);
	bool compare(Territory* x, Territory* y);
	bool checkForAllies(int playerName);

	//Stream operator overload
	 friend ostream& operator << (ostream& out, const Player& p);

private:
	//Required data members
	vector<Territory *> playerTerritories;
	Hand *playerHand;
	OrderList *playerOrders;
};

