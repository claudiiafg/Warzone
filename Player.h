#pragma once

#include <vector>
#include <map>
#include "GameObservers.h"

class Territory;
class OrderList;
class Hand;

using namespace std;

class Player: public Observable {

public:
    int name;
    int armies;
	int reinforcements;
	int phase;
	int deployCounter = 1;
	int cardFlag = false;
    //Required data members
    vector<Player*> allies;
    vector<Territory *> playerTerritories;
    Hand *playerHand;
    OrderList* playerOrders;

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
    vector<Territory*> toDefend(vector<int> &defPriority, Map* map);
    vector<string> toAttack(vector<int>& atkPriority, Map* map);
	void issueOrder(Map* map, vector<string> toAttack, vector<Territory*> toDefend, vector<int> defPriorities, vector<int> atkPriorities, Player* player);
	vector<Territory*> adjacentEnemies(string terrID, Map* map);
	bool compare(Territory* x, Territory* y);
	bool checkForAllies(int playerName);

	//Stream operator overload
	 friend ostream& operator << (ostream& out, const Player& p);

    void Attach(PhaseObserver *pObserver);

};

