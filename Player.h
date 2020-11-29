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
class PlayerStrategy;

using namespace std;

class Player: public Observable {

public:

	//Data members
    int name;
    int armies;
	int reinforcements;
	int phase; //Keeps track of player phase: 1-
	int deployCounter = 0; //Keeps track of current territory to deploy to within toDefend list
	int cardFlag = false; //Keeps track of whether player has received a card this turn
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

	//Methods
	vector<Territory*> toDefend();
	vector<Territory*> toAttack();
	int issueOrder();
	vector<Territory*> adjacentEnemies(string terrID, Map* map);
	bool checkForAllies(int playerName);
	bool hasTerritory(string terrId);
	void deploy(vector<Territory*> toDefend, int units);

	//Stream operator overload
	 friend ostream& operator << (ostream& out, const Player& p);


	//Old methods
	//vector<Territory*> toDefend(Map* map);
	//vector<string> toAttack(Map* map);
	//int issueOrder(Map* map, vector<string> toAttack, vector<Territory*> toDefend, Player* nextPlayer);
};

