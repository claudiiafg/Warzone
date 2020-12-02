//
// Created by Claudia on 2020-10-05.
//

//using namespace std;
#include <iostream>
#include "MapLoader.h"
#include "Map.h"

int main(){

    MapLoader loader;
    loader.loadMaps();
    vector<MapFile*> rawMaps = loader.getMaps();
    vector<Map*> maps;
    ConquestFileReaderAdapter* adapter;

    for (int i = 0; i < rawMaps.size(); i++) {
        string firstLineOfMapFile = rawMaps[i]->content[0];
        string conquestMapIdentifier = "[Map]";
        size_t found = firstLineOfMapFile.find(conquestMapIdentifier);

        if(found!=std::string::npos){
            cout << rawMaps[i]->content[0] << endl;
            ConquestFileReader * toAdapt = new ConquestFileReader(rawMaps[i]);
            adapter = new ConquestFileReaderAdapter(toAdapt);
            rawMaps[i]->content = adapter->getContent(loader.mainPath);
        }
    }

    for (int i = 0; i < rawMaps.size(); i++) {
        Map* map = new Map(rawMaps[i]->name, rawMaps[i]->content);
        if(map->validate()) {
            maps.push_back(map);
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