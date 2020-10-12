//
// Created by Claudia on 2020-10-05.
//

using namespace std;
#include "MapLoader.h"
#include "Map.h"
#include <iostream>

int main(){

    MapLoader loader;
    loader.loadMaps();
    vector<MapFile> rawMaps = loader.getMaps();

    for (int i = 0; i < rawMaps.size(); i++) {
//        Map* map = new Map(rawMaps[i].name, rawMaps[i].content);
        cout << rawMaps.size() << endl;
    }



    return 0;
}