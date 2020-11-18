#include "Orders.h"
#include "Player.h"
#include <vector>


using namespace std;


int main()
{

	vector<Territory*> playerTerritories = { new Territory("1 England 1 164 126", "1 8 21 6 7 5 2 3 4") };
	Hand* playerHand = new Hand();
	OrderList* playerOrders = new OrderList();
	Player* testPlayer = new Player(0, 5, playerTerritories, playerHand, playerOrders);

	OrderList player1Orders;

	Deploy* deploy1 = new Deploy(1, "Alberta", 1, 5);
	Deploy* deploy2 = new Deploy(1, "Italy", 1, 10);
	Advance* advance1 = new Advance(1, "China", 1, 10, 2, "Japan", 3);
	Bomb* bomb1 = new Bomb(1, "Quebec", 1, 2, "Ontario");
	Blockade* blockade1 = new Blockade(1, "Washington", 1, 15);
	Airlift* airlift1 = new Airlift(1, "Brazil", 1, 10, 2, "Eygpt", 9);
	Negotiate* negotiate1 = new Negotiate(1, 2);

	player1Orders.addOrder(deploy1);
	player1Orders.addOrder(advance1);
	player1Orders.addOrder(bomb1);
	player1Orders.addOrder(blockade1);
	player1Orders.addOrder(airlift1);
	player1Orders.addOrder(negotiate1);
	player1Orders.addOrder(deploy2);

	//player1Orders.removeOrder(bomb1);
	//player1Orders.moveOrder(airlift1, "up");
	//player1Orders.executeOrderList();

	
    deploy1 = NULL;
	delete deploy1;
 //   delete advance1;
 //   advance1 = NULL;
 //   delete bomb1;
 //   bomb1 = NULL;
 //   delete blockade1;
 //   blockade1 = NULL;
 //   delete airlift1;
 //   airlift1 = NULL;
 //   delete negotiate1;
 //   negotiate1 = NULL;

    return 0;
}