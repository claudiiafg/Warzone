#pragma once

#include <vector>
#include <map>
#include "GameObservers.h"
#include "PlayerStrategies.h"
#include "Orders.h"
#include "Map.h"
#include "Cards.h"

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
	PlayerStrategy* strategy;
    vector<Player*> allies;
    vector<Territory *> playerTerritories;
	vector<int> defPriority = { 0 };
	vector<int> atkPriority = { 0 };
    Hand *playerHand;
    OrderList* playerOrders;

	//Constructors
	Player();
	Player(int name, int armies, vector<Territory*> playerTerritories, Hand* playerHand, OrderList* playerOrders, vector<Player*> allies, PlayerStrategy* strategy);
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
	void setStrategy(PlayerStrategy* newStrategy);


	//Old methods
	//vector<Territory*> toDefend(Map* map);
	//vector<string> toAttack(Map* map);
	//int issueOrder(Map* map, vector<string> toAttack, vector<Territory*> toDefend, Player* nextPlayer);

	//Methods
	vector<Territory*> toDefend();
	vector<Territory*> toAttack();
	void issueOrder();
	vector<Territory*> adjacentEnemies(string terrID, Map* map);
	bool checkForAllies(int playerName);
	bool hasTerritory(string terrId);

	//Stream operator overload
	 friend ostream& operator << (ostream& out, const Player& p);


};

