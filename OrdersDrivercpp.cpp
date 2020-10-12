#include "Orders.h"

using namespace std;


int main()
{
	OrderList player1Orders;

	Deploy deploy1 = Deploy(1, "Alberta", 1, 5);
	Advance advance1 = Advance(1, "China", 1, 10, 2, "Japan", 3);
	Bomb bomb1 = Bomb(1, "Quebec", 1, 2, "Ontario");
	Blockade blockade1 = Blockade(1, "Washington", 1, 15);
	Airlift airlift1 = Airlift(1, "Brazil", 1, 10, 2, "Eygpt", 9);
	Negotiate negotiate1 = Negotiate(1, 2);


	player1Orders.addOrder(&deploy1);
	player1Orders.addOrder(&advance1);
	player1Orders.addOrder(&bomb1);
	player1Orders.addOrder(&blockade1);
	player1Orders.addOrder(&airlift1);
	player1Orders.addOrder(&negotiate1);


	//player1Orders.removeOrder(&bomb1);
	//player1Orders.viewOrderList();
	cout << "\n";
	player1Orders.executeOrderList();

	//player1Orders.moveOrder(bombPtr2, "up");
	//player1Orders.executeOrderList();
	//player1Orders.viewOrderList();
}