//
// Created by Claudia on 2020-10-07.
//

#include "Map.h"

//MAP>>>>>>>>>>>>>>>>>>>>>>>>>


Map::Map() = default;

// constructor
Map::Map(string _name, vector<string> mapData) {
    name = _name;

    int contI;
    int terrI;
    int borderI;

    // get indexes that limit the data necessary
    for (size_t i = 0; i < mapData.size(); ++i){
        if(mapData[i].find("continents") < mapData.size() && mapData[i].find("continents") > 0) {
            contI = i;
        } else if(mapData[i].find("countries") < mapData.size() && mapData[i].find("countries") > 0) {
            terrI = i;
        } else if(mapData[i].find("borders") < mapData.size() && mapData[i].find("borders") > 0) {
            borderI = i;
        }
    }

    // get all continent strings from map data
    vector<string> continents;
    for (size_t i = (contI + 1); i < (terrI - 1); ++i){
        continents.push_back(mapData[i]);
    }

    // get all country strings from map data
    vector<string> territories;
    for (size_t i = (terrI + 1); i < (borderI - 1); ++i){
        territories.push_back(mapData[i]);
    }

    // get nodes per country from map data
    vector<string> borders;
    for (size_t i = (borderI + 1); i < mapData.size(); ++i){
        borders.push_back(mapData[i]);
    }

    setTerritories(territories, borders);
    setContinents(continents);
    validate();
}

// copy constructor
Map::Map(const Map& _m){
    name = _m.name;
    territories = _m.territories;
    continents = _m.continents;
}

// destructor
Map::~Map() {
    for (int i = 0; i < territories.size(); i++) {
        delete territories[i];
    }
    for (int i = 0; i < continents.size(); i++) {
        delete continents[i];
    }
}

// validate map
bool Map::validate() {
    cout << ">>>>>>>>>>>>Map successfully created>>>>>>>>>>" << endl;
    return true;
}

// get territories
vector<Territory*> Map::getTerritories() {
    return territories;
}

// get continents
vector<Continent*> Map::getContinents() {
    return continents;
}

// set territories
void Map::setTerritories(vector<string> _territoriesData, vector<string> _bordersData) {
    for (int i = 0; i < _territoriesData.size(); i++) {
        Territory* tempTer = new Territory(_territoriesData[i], _bordersData[i]);
        territories.push_back(tempTer);
    }
}

// set continents
void Map::setContinents(vector<string> _continentsData) {
    // create continent objects from map data
    for (int i = 0; i < _continentsData.size(); i++) {
        Continent* tempCont = new Continent(to_string(i + 1), _continentsData[i]);
        continents.push_back(tempCont);
    }

    for (int i = 0; i < continents.size(); i++) {
        vector<string> adjacentCont;
        // find each continent's territories
        vector<Territory*> terr = getTerritoriesByContinentId(continents[i]->id);

        for (int j = 0; j < terr.size(); j++) {
            // find each territory adjacent nodes
            vector<Territory*> adjacentTerr = getAdjacentTerritories(terr[j]->id);

            for (int k = 0; k < adjacentTerr.size(); k++) {
                // push continent of adjacent territories of the continent's territories
                if(!(std::find(adjacentCont.begin(), adjacentCont.end(), adjacentTerr[k]->getContinentID()) != adjacentCont.end()) &&
                adjacentTerr[k]->getContinentID() != continents[i]->id) {
                    adjacentCont.push_back(adjacentTerr[k]->getContinentID());
                }
            }
        }
        cout << endl;

        // set continent of adjacent territories of the continent's territories, as the continents adjacent territorries
        continents[i]->adjacent = adjacentCont;
    }
}


// get territory object by its id
Territory* Map::getTerritoryById(string territoryID) {
    for (int i = 0; i < territories.size(); i++) {
        if(territories[i]->id == territoryID) {
            return territories[i];
        }
    }
    return NULL;
}

// get continent object by its id
Continent* Map::getContinentById(string id){
    for (int i = 0; i < continents.size(); i++) {
        if(continents[i]->id == id) {
            return continents[i];
        }
    }
    return NULL;
}

// get all territory objects of a continent
vector<Territory*> Map::getTerritoriesByContinentId(string id){
    vector<Territory*> terr;
    for (int i = 0; i < territories.size(); i++) {
        if(territories[i]->getContinentID() == id) {
            terr.push_back(territories[i]);
        }
    }
    return terr;
}


// get all Territories adjacent to a specific territory
vector<Territory*> Map::getAdjacentTerritories(string territoryID) {
    vector<Territory*> tempList;
    for (int i = 0; i < territories.size(); i++) {
        if(territories[i]->id == territoryID) {
            vector<string> nodesStrings = territories[i]->getAdjacentNodes();
            for (int i = 0; i < nodesStrings.size(); i++) {
                tempList.push_back(getTerritoryById(reinterpret_cast<basic_string<char> &&>(nodesStrings[i])));
            }
        }
    }
    return tempList;
}

// stream insertion operator
ostream &operator<<(ostream &os, const Map &n) {
    os << "Map " << n.name ;
    os << " has " << n.continents.size() << " continents";
    os << " and " << n.territories.size()<< " territories" << endl;

    os << endl;
    os << " The continent's are:"<< endl;
    for(int i = 0; i < n.continents.size(); i++) {
        os << *(n.continents[i]);
    }

    os << endl;
    os << " The territories' are:"<< endl;
    for(int i = 0; i < n.territories.size(); i++) {
        os << *(n.territories[i]);
    }
    return os;
}

// assignment operator
Map& Map::operator = (const Map& _file) {
    return *this;
}

//CONTINENT>>>>>>>>>>>>>>>>>>>>>>>>>
Continent::Continent() = default;

// constructor
Continent::Continent(string pos, string continentsString) {
    id = pos;

    //seperate string by spaces
    regex ws_re("\\s+");
    vector<string> result{
    sregex_token_iterator(continentsString.begin(), continentsString.end(), ws_re, -1), {}
    };

    name = result[0];
}

// copy constructor
Continent::Continent(const Continent& _c){
    id = _c.id;
    name = _c.name;
    adjacent = _c.adjacent;
}

// destructor
Continent::~Continent() = default;

// stream insertion operator
ostream &operator<<(ostream &os, const Continent& n) {
    os << n.name << " is continent #" << n.id;
    os << " and has " << n.adjacent.size() << " adjacent continents -> ";

    for(int i = 0; i < n.adjacent.size(); i++) {
        if(i == n.adjacent.size()-1) {
            os << n.adjacent.at(i) << ". "<< endl;
        } else {
            os << n.adjacent.at(i) << ", ";
        }
    }

    return os;
}

// assignment operator
Continent& Continent::operator = (const Continent& _file) {
    return *this;
}


//TERRITORY>>>>>>>>>>>>>>>>>>>>>>>>>

Territory::Territory() = default;

// contructor
Territory::Territory(string territoryString, string borderString) {
    armiesNumber = 0;
    owner = *new Player*();

    // seperate strings by spaces
    regex ws_re("\\s+");
    vector<string> result{
    sregex_token_iterator(territoryString.begin(), territoryString.end(), ws_re, -1), {}
    };
    vector<string> bordersResult{
    sregex_token_iterator(borderString.begin(), borderString.end(), ws_re, -1), {}
    };

    id = result[0];
    name = result[1];
    continentID = result[2];

    for (int i = 0; i < bordersResult.size(); i++) {
        if (i > 0) {
            adjacent.push_back(bordersResult[i]);
        }
    }
}

// copy contructor
Territory::Territory(const Territory& otherTerritory) {
    armiesNumber = otherTerritory.armiesNumber;
    owner = otherTerritory.owner;
    id = otherTerritory.id;
    name = otherTerritory.name;
    continentID = otherTerritory.continentID;
    adjacent = otherTerritory.adjacent;

}

// destructor
Territory::~Territory() {
    delete owner;
}

// get continent id
string Territory::getContinentID() {
    return continentID;
}

// get adjacent nodes
vector<string> Territory::getAdjacentNodes() {
    return adjacent;
}

// get armies
int Territory::getArmies() {
    return armiesNumber;
}

// check if nodes are adjacent
bool Territory::isAdjacentNode(string _node) {
    for (int i = 0; i < adjacent.size(); i++) {
        if(adjacent[i] == _node) {
            return true;
        }
    }
    return false;
}

// set armies
void Territory::setArmiesNumber(int amount) {
    armiesNumber = amount;
}

// get owner
Player* Territory::getOwner() {
    return owner;
}

// set owner
void Territory::setOwner(Player* _owner) {
    owner = _owner;
}

// stream insertion operator
ostream &operator<<(ostream &os, const Territory &n) {
    os << n.name << " is node #" << n.id;
    os << " and has " << n.adjacent.size() << " adjacent territories -> ";

    for(int i = 0; i < n.adjacent.size(); i++) {
        if(i == n.adjacent.size()-1) {
            os << n.adjacent.at(i) << ". "<< endl;
        } else {
            os << n.adjacent.at(i) << ", ";
        }
    }

    return os;
}

// assignment operator
Territory& Territory::operator = (const Territory& _file) {
    return *this;
}

