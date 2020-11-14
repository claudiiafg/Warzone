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

using namespace std;

class GameEngine{
public:
    // constructor
    GameEngine();
    GameEngine(const GameEngine& _c);

    // destructor
    ~GameEngine();

    // functions


    // operators
    friend ostream& operator<<(ostream &os, const GameEngine& n);
    GameEngine& operator = (const GameEngine& _file);
};

#endif //WARZONE_GAMEENGINE_H
