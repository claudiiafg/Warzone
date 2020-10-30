#include "Orders.h"

using namespace std;


int main()
{
	OrderList player1Orders;

	Deploy* deploy1 = new Deploy(1, "Alberta", 1, 5);
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

	player1Orders.removeOrder(bomb1);
	player1Orders.moveOrder(airlift1, "up");
	player1Orders.executeOrderList();

	delete deploy1;
    delete advance1;
    delete bomb1;
    delete blockade1;
    delete airlift1;
    delete negotiate1;

    return 0;
}