#include "Player.cpp"
#include "Player.h"
#include "Orders.h"
#include "Cards.h"
#include <vector>

using namespace std;

int main() {
	vector<Territory*> playerTerritories = { new Territory("terr1", "cont1") };
	Hand* playerHand = new Hand;
	OrderList* playerOrders = new OrderList;

	Player* testPlayer = new Player(playerTerritories, playerHand, playerOrders);
	Player* copyPlayer = testPlayer;

	vector<Territory*> toDefend = testPlayer->toDefend();
	vector<Territory*> toAttack = testPlayer->toAttack();
	testPlayer->issueOrder();

}
