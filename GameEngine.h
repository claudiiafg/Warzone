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
#include <typeinfo>

class Map;
class Player;
class Territory;

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
    int orderPhase = 1; //Keeps track of current order phase || Issuing: 1=Deploy, 2=Others, 3=Complete || Execution: Deploy=1, Airlift=2, Blockade=3, Others=4, Complete=5
    bool playerDeletedFlag = false;

    // startup functions
    void startupPhase();
    void selectMap();
    void selectStrategy();
    void selectPlayers();
    void activateObservers();
    void setMap(Map* mapToSet);
    void createPlayers(int amount);

    //update functions
    void updateTerritoryOwner(int ownerID, string territoryID);
    void updateMapTerritories();
    void updateOrderPhase();

    //main game functions
    void mainGameLoop();
    void reinforcementPhase();
    void issueOrdersPhase();
    void executeOrdersPhase();

    // operators
    friend ostream& operator<<(ostream &os, const GameEngine& n);
    GameEngine& operator = (const GameEngine& _game);

private:
    int getInitialArmies(int amount);
    vector<vector<Territory*>> getTerritoriesPerPlayer(int amount, vector<Territory*> tempTerr);
};

//Driver free functions
void MainGameLoopDriver(GameEngine* game);

#endif //WARZONE_GAMEENGINE_H
