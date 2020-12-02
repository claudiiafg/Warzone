//
// Created by Claudia on 2020-10-05.
//

//using namespace std;
#include <iostream>
#include "MapLoader.h"
#include "Map.h"

int main(){

    cout << "* Loading all Maps files *" << endl;

    MapLoader loader;
    loader.loadMaps();
    vector<MapFile*> rawMaps = loader.getMaps();
    vector<Map*> maps;
    ConquestFileReaderAdapter* adapter;

    cout << endl;
    cout << "* Adapting maps with wrong structure *" << endl;

    for (int i = 0; i < rawMaps.size(); i++) {
        string firstLineOfMapFile = rawMaps[i]->content[0];
        string conquestMapIdentifier = "[Map]";
        size_t found = firstLineOfMapFile.find(conquestMapIdentifier);

        if(found!=std::string::npos){
            cout << rawMaps[i]->name << endl;
            ConquestFileReader * toAdapt = new ConquestFileReader(rawMaps[i]);
            adapter = new ConquestFileReaderAdapter(toAdapt);
            rawMaps[i]->content = adapter->getContent(loader.mainPath);
        }
    }

    cout << endl;
    cout << "* Validating all maps before creation *" << endl;

    for (int i = 0; i < rawMaps.size(); i++) {
        Map* map = new Map(rawMaps[i]->name, rawMaps[i]->content);
        if(map->validate()) {
            maps.push_back(map);
        } else {
            delete map;
            map = NULL;
        }
    }

    cout << endl;
    cout << "* Maps created *" << endl;

    for (int i = 0; i < maps.size(); i++) {
        cout << maps[i]->name << endl;
        delete maps[i];
    }


    return 0;
}