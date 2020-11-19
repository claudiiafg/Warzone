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

	OrderList player1Orders;

	Deploy* deploy1 = new Deploy(game->players[1], game->map->territories[0], 40);
	Deploy* deploy2 = new Deploy(game->players[1], game->map->territories[1], 4);
	Deploy* deploy3 = new Deploy(game->players[0], game->map->territories[2], 20);
	Deploy* deploy4 = new Deploy(game->players[0], game->map->territories[3], 12);
	Deploy* deploy5 = new Deploy(game->players[1], game->map->territories[4], 8);
	Deploy* deploy6 = new Deploy(game->players[0], game->map->territories[5], 9);
	Deploy* deploy7 = new Deploy(game->players[1], game->map->territories[6], 19);
	Deploy* deploy8 = new Deploy(game->players[1], game->map->territories[7], 31);
	Deploy* deploy9 = new Deploy(game->players[1], game->map->territories[8], 13);
	Deploy* deploy10 = new Deploy(game->players[1], game->map->territories[9], 4);
	Advance* advance1 = new Advance(game->players[1], game->map->territories[0], game->map->territories[1], 1); //move
	Advance* advance2 = new Advance(game->players[0], game->map->territories[3], game->map->territories[1], 7); //attack
	Bomb* bomb1 = new Bomb(game->players[0], game->map->territories[5], game->map->territories[7]);
	Blockade* blockade1 = new Blockade(game->players[0], game->map->territories[3]);
	Airlift* airlift1 = new Airlift(game->players[1], game->map->territories[7], game->map->territories[9], 2); //move
	Airlift* airlift2 = new Airlift(game->players[0], game->map->territories[5], game->map->territories[7], 4); //attack
	Negotiate* negotiate1 = new Negotiate(game->players[0], game->players[1]);
	Airlift* airlift3 = new Airlift(game->players[0], game->map->territories[5], game->map->territories[7], 4); //attack


	player1Orders.addOrder(deploy1);
	player1Orders.addOrder(deploy2);
	player1Orders.addOrder(deploy3);
	player1Orders.addOrder(deploy4);
	player1Orders.addOrder(deploy5);
	player1Orders.addOrder(deploy6);
	player1Orders.addOrder(deploy7);
	player1Orders.addOrder(deploy8);
	player1Orders.addOrder(deploy9);
	player1Orders.addOrder(deploy10);

	player1Orders.addOrder(advance1); //move
	player1Orders.addOrder(advance2); //attack

	player1Orders.addOrder(bomb1);
	player1Orders.addOrder(blockade1);

	player1Orders.addOrder(airlift1); //move
	player1Orders.addOrder(airlift2); //attack

	player1Orders.addOrder(negotiate1); //negotiate
	player1Orders.addOrder(airlift3);


	player1Orders.executeOrderList();
	

	deploy1 = NULL;
	delete deploy1;
	deploy2 = NULL;
	delete deploy1;
	deploy3 = NULL;
	delete deploy1;
	deploy4 = NULL;
	delete deploy1;
	deploy5 = NULL;
	delete deploy1;
	deploy6 = NULL;
	delete deploy1;
	deploy7 = NULL;
	delete deploy1;
	deploy8 = NULL;
	delete deploy1;
	deploy9 = NULL;
	delete deploy1;
	advance1 = NULL;
    delete advance1;
	advance2 = NULL;
	delete advance2;
	bomb1 = NULL;
    delete bomb1;
	blockade1 = NULL;
    delete blockade1;
	airlift1 = NULL;
    delete airlift1;
	airlift2 = NULL;
	delete airlift2;
	negotiate1 = NULL;
    delete negotiate1;
	airlift3 = NULL;
	delete airlift3;


    return 0;
}