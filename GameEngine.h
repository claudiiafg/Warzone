//
// Created by Claudia on 2020-11-14.
//

#ifndef WARZONE_GAMEENGINE_H
#define WARZONE_GAMEENGINE_H

#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <regex>
#include <sstream>
#include <algorithm>
#include "Map.h"
#include "MapLoader.h"
#include "Player.h"

using namespace std;

class GameEngine{
public:
    // constructor
    GameEngine();
    GameEngine(const GameEngine& _c);

    // destructor
    ~GameEngine();

    //attributes
    Map* map;
    vector<Player*> players;

    // functions
    void selectMap();
    void selectPlayers();
    void activateObservers();

    void setMap(Map* mapToSet);
    void createPlayers(int amount);


    // operators
    friend ostream& operator<<(ostream &os, const GameEngine& n);
    GameEngine& operator = (const GameEngine& _game);
};

#endif //WARZONE_GAMEENGINE_H
