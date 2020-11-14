//
// Created by Claudia on 2020-11-14.
//

#include "GameEngine.h"
#include "MapLoader.h"
#include "Map.h"

GameEngine::GameEngine() {

}

GameEngine::GameEngine(const GameEngine &_c) {

}

GameEngine::~GameEngine() {

}

ostream &operator<<(ostream &os, const GameEngine &n) {
    return os;
}


//GameEngine &GameEngine::operator=(const GameEngine &_file) {
//    return ;
//}

int main() {

    MapLoader loader;
    loader.loadMaps();
    vector<MapFile*> rawMaps = loader.getMaps();

    int option = 0;
    const int EXIT_SELECTION = rawMaps.size() + 1;

    while(option != EXIT_SELECTION) {
        cout << ">>>>>>>> Which Map do you wish to play?" << endl;

        for (int i = 0; i < rawMaps.size(); i++) {
            cout << i << ": "<< *rawMaps[i];
        }

        cout << EXIT_SELECTION << ": EXIT" << endl;

        cin >> option;

        if(option < EXIT_SELECTION) {
            Map* map = new Map(rawMaps[option]->name, rawMaps[option]->content);
            if(map->validate()) {
                cout << *map << endl;
                cout << "**** Great selection! ****" << endl;
                option = EXIT_SELECTION;
            } else {
                delete map;
                map = NULL;
                cout << "Please select a different map." << endl;
                continue;
            }
        }
    }

    cout << "continue" << endl;

    return 0;
}
