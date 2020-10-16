#include "Player.h"
#include "Map.cpp"
#include "Cards.cpp"
#include "Orders.cpp"
#include <vector>
#include <iostream>

using namespace std;

int main() {
	vector<Territory*> playerTerritories = { new Territory("1 England 1 164 126", "1 8 21 6 7 5 2 3 4") };
	Hand* playerHand = new Hand();
	OrderList* playerOrders = new OrderList();
	Player* testPlayer = new Player(playerTerritories, playerHand, playerOrders);
	cout << "Player info:" << *testPlayer;
	
	//Player* copyPlayer = testPlayer;

	//vector<Territory*> toDefend = testPlayer->toDefend();
	//vector<Territory*> toAttack = testPlayer->toAttack();
	//testPlayer->issueOrder();

}
