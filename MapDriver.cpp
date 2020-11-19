//
// Created by Claudia on 2020-10-07.
//

//using namespace std;
#include <iostream>
#include "Map.h"
#include "MapLoader.h"
#include "Player.h"

int main(){
    vector<Territory*> playerTerritories = { new Territory("1 England 1 164 126", "1 8 21 6 7 5 2 3 4") };
    Hand* playerHand = new Hand();
    OrderList* playerOrders = new OrderList();
    vector<Player*> allies;
    Player* testPlayer = new Player(0, 5, playerTerritories, playerHand, playerOrders, allies);
    MapLoader loader;
    loader.loadMaps();
    vector<MapFile*> rawMaps = loader.getMaps();
    vector<Map*> maps;

    for (int i = 0; i < rawMaps.size(); i++) {
        Map* map = new Map(rawMaps[i]->name, rawMaps[i]->content);

        if(map->validate()) {
            maps.push_back(map);
            cout << *map << endl;

        } else {
            delete map;
            map = NULL;
        }
    }

    for (int i = 0; i < maps.size(); i++) {
        delete maps[i];
    }


    return 0;
}