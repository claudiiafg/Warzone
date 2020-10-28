#include <vector>
#include <iostream>

#include "Player.h"4

using namespace std;

int main() {
	cout << "Creating new player...";
	vector<Territory*> playerTerritories = { new Territory("1 England 1 164 126", "1 8 21 6 7 5 2 3 4") };
	Hand* playerHand = new Hand();
	OrderList* playerOrders = new OrderList();
	Player* testPlayer = new Player(playerTerritories, playerHand, playerOrders);
	cout << "\nPlayer info:" << *testPlayer;
	
	cout << "\nCopying player...";
	Player* copyPlayer = testPlayer;
	cout << "\nCopied player info: " << *copyPlayer;

	vector<Territory*> toDefend = testPlayer->toDefend();
	vector<Territory*> toAttack = testPlayer->toAttack();
	testPlayer->issueOrder();

}
