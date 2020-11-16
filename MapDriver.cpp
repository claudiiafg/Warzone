//
// Created by Claudia on 2020-10-07.
//

//using namespace std;
#include <iostream>
#include "Map.h"
#include "MapLoader.h"

int main(){

    MapLoader loader;
    loader.loadMaps();
    vector<MapFile*> rawMaps = loader.getMaps();
    vector<Map*> maps;

    for (int i = 0; i < rawMaps.size(); i++) {
        Map* map = new Map(rawMaps[i]->name, rawMaps[i]->content);
        if(map->validate()) {
            maps.push_back(map);

        } else {
            delete map;
            map = NULL;
        }
        cout << *map << endl;
    }

    for (int i = 0; i < maps.size(); i++) {
        delete maps[i];
    }


    return 0;
}