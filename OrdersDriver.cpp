#include "Orders.h"
#include "Player.h"
#include "MapLoader.h"
#include "GameEngine.h"
#include <vector>

using namespace std;

int main()
{	
	GameEngine* game = new GameEngine();
	game->startupPhase();

	for (auto& m : game->map->getTerritories()) {
		cout << *m << endl;
	}


	OrderList player1Orders;

	Deploy* deploy1 = new Deploy(game->players[0], game->map->territories[0], 10);
	Deploy* deploy2 = new Deploy(game->players[1], game->map->territories[1], 40);
	Deploy* deploy3 = new Deploy(game->players[0], game->map->territories[3], 20);
	Deploy* deploy4 = new Deploy(game->players[0], game->map->territories[5], 7);
	Deploy* deploy5 = new Deploy(game->players[1], game->map->territories[6], 8);
	//Advance* advance1 = new Advance(game->players[0], game->map->territories[0], game->map->territories[1], 5); //move
	//Advance* advance2 = new Advance(game->players[0], game->map->territories[3], game->map->territories[1], 2); //attack
	Bomb* bomb1 = new Bomb(game->players[0], game->map->territories[3], game->map->territories[1]);
	Blockade* blockade1 = new Blockade(game->players[0], game->map->territories[3]);
	//Airlift* airlift1 = new Airlift(game->players[0], game->map->territories[3], game->map->territories[1], 15); //attack
	Negotiate* negotiate1 = new Negotiate(1, 2);

	player1Orders.addOrder(deploy1);
	player1Orders.addOrder(deploy2);
	player1Orders.addOrder(deploy3);
	player1Orders.addOrder(deploy4);
	player1Orders.addOrder(deploy5);
	player1Orders.addOrder(blockade1);
	player1Orders.addOrder(bomb1);

	//player1Orders.addOrder(airlift1);
	player1Orders.addOrder(negotiate1);
	//player1Orders.addOrder(advance1);
	//player1Orders.addOrder(advance2);

	//player1Orders.removeOrder(bomb1);
	//player1Orders.moveOrder(airlift1, "up");
	//player1Orders.executeOrderList();

	player1Orders.viewOrderList();
	
   // deploy1 = NULL;
	//delete deploy1;
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