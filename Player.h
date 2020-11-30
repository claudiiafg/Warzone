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
	int phase; //Keeps track of player phase || Startup=1, Reinforcement=2, Issuing=3, Execute=4, Conquered=5
	int cardFlag = false; //Keeps track of whether player has received a card this turn
	int orderPhase = 0; //Keeps track of current order phase || Issuing: 1=Deploy, 2=Others, 3=Complete || Execution: Deploy=1, Airlift=2, Blockade=3, Others=4, Complete=5
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
	vector<Territory*> adjacentEnemies(Map* map);
	bool checkForAllies(int playerName);
	bool hasTerritory(string terrId);
	void deploy(Territory* terr, int units);

	//Stream operator overload
	 friend ostream& operator << (ostream& out, const Player& p);


	//Old methods
	//vector<Territory*> toDefend(Map* map);
	//vector<string> toAttack(Map* map);
	//int issueOrder(Map* map, vector<string> toAttack, vector<Territory*> toDefend, Player* nextPlayer);
};

class Players{
    public:
        Players();
        void add(Player *p);
        Player* getPlayerByID(int id);
    private:
        vector<Player*> playerHolder;
};

