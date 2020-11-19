//
// Created by Claudia on 2020-10-07.
//
#pragma once

#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <regex>
#include <sstream>
#include <algorithm>
#include "GameObservers.h"


class Player;

using namespace std;

class Continent{
public:
    // constructor
    Continent();
    Continent(string pos, string continentsString);
    Continent(const Continent& _c);

    // destructor
    ~Continent();

    // attributes
    string name;
    string id;  // node number
    vector <string> adjacent;
    int bonus;

    // operators
    friend ostream& operator<<(ostream &os, const Continent& n);
    Continent& operator = (const Continent& _file);
};

class Territory{
public:
    // constructor
    Territory();
    Territory(string territoryString, string borderString);
    Territory(const Territory& otherTerritory);

    // destructor
    ~Territory();

    // attributes
    string name;
    string id;  // node number
    int priority;

    // methods
    string getContinentID();
    vector<string> getAdjacentNodes();
    bool isAdjacentNode(const string& _node);
    int getArmies();
    void setArmiesNumber(int amount);
    int getOwnerID();
    void setOwner(int _ownerID);

    // operators
    friend ostream& operator<<(ostream &os, const  Territory& n);
    Territory& operator = (const Territory& _file);
    bool operator <(const Territory& playerObj) const;

private:
    // attributes
    string continentID;
    vector<string> adjacent;   // adjacent nodes
    int armiesNumber{};
    int ownerID;
};


class Map: public Observable{
public:
    // constructors
    Map();
    Map(string _name, vector<string> mapData);
    Map(const Map& _m);

    // destructor
    ~Map();

    // attributes
    string name;
    vector<Continent*> continents;
    vector<Territory*> territories;

    // methods
    bool validate();    //  whether the map contains all necessary info
    vector<Territory*> getTerritories();
    vector<Continent*> getContinents();
    Territory* getTerritoryById(string territoryID);
    Continent* getContinentById(string id);
    vector<Territory*> getAdjacentTerritories(string territoryID);
    vector<Territory*> getTerritoriesByContinentId(string id);
    vector<Territory*> getTerritoriesByOwnerID(int ownerID);

    bool continentHasUniqueOwner(string continentID, int playerName);

    // operators
    friend ostream& operator<<(ostream &os, const  Map& n);
    Map& operator = (const Map& _file);

private:
    // methods
    void setTerritories(vector<string> _territoriesData, vector<string> _bordersData);
    void setContinents(vector<string> _continentsData);
};
