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
    //constructor
    Continent(string pos, string continentsString);
    Continent(const Continent& _c);

    //Destructor
    ~Continent();

    //attributes
    string name;
    string id;                            // node number

    //methods
    friend ostream& operator<<(ostream &os, const Continent& n);
};

class Territory{
public:
    //constructor
    Territory(string territoryString, string borderString);
    Territory(const Territory& otherTerritory);

    //Destructor
    ~Territory();

    //attributes
    string name;
    string id;                             // node number

    //methods
    string getContinentID();
    vector<string*> getAdjacentNodes();
    bool isAdjacentNode(string _node);
    int getArmies();
    void setArmiesNumber(int amount);
    Player* getOwner();
    void setOwner(Player* _owner);
    friend ostream& operator<<(ostream &os, const  Territory& n);

private:
    //attributes
    string continentID;
    vector<string*> adjacent;                // adjacent nodes
    int armiesNumber;
    Player* owner;
};


class Map{
public:
    //constructor
    Map();
    Map(string _name, vector<string> mapData);
    Map(const Map& _m);

    //Destructor
    ~Map();

    //attributes
    string name;
    vector<Continent*> continents;
    vector<Territory*> territories;

    //methods
    bool validate();                        //  whether the map contains all necessary info
    vector<Territory*> getTerritories();
    vector<Continent*> getContinents();
    Territory* getTerritoryById(string territoryID);
    vector<Territory*> getAdjacentTerritories(string territoryID);
    friend ostream& operator<<(ostream &os, const  Map& n);

private:

    //methods
    void setTerritories(vector<string> _territoriesData, vector<string> _bordersData);
    void setContinents(vector<string> _continentsData);


};
