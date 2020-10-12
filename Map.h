//
// Created by Claudia on 2020-10-07.
//
#pragma once

#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <regex>

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

    // methods
    string getContinentID();
    vector<string> getAdjacentNodes();
    bool isAdjacentNode(string _node);
    int getArmies();
    void setArmiesNumber(int amount);
    Player* getOwner();
    void setOwner(Player* _owner);

    // operators
    friend ostream& operator<<(ostream &os, const  Territory& n);
    Territory& operator = (const Territory& _file);

private:
    // attributes
    string continentID;
    vector<string> adjacent;   // adjacent nodes
    int armiesNumber;
    Player* owner;
};


class Map{
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

    // operators
    friend ostream& operator<<(ostream &os, const  Map& n);
    Map& operator = (const Map& _file);

private:
    // methods
    void setTerritories(vector<string> _territoriesData, vector<string> _bordersData);
    void setContinents(vector<string> _continentsData);


};
