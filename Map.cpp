//
// Created by Claudia on 2020-10-07.
//

#include "Map.h"
#include "Player.h"

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
    vector<string> tempContinents;
    for (size_t i = (contI + 1); i < (terrI - 1); ++i){
        tempContinents.push_back(mapData[i]);
    }

    // get all country strings from map data
    vector<string> tempTerritories;
    for (size_t i = (terrI + 1); i < (borderI - 1); ++i){
        tempTerritories.push_back(mapData[i]);
    }

    // get nodes per country from map data
    vector<string> borders;
    for (size_t i = (borderI + 1); i < mapData.size(); ++i){
        borders.push_back(mapData[i]);
    }

    setTerritories(tempTerritories, borders);
    setContinents(tempContinents);
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
    for (auto & territorie : territories) {
        delete territorie;
    }
    for (auto & continent : continents) {
        delete continent;
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

    for (auto & continent : continents) {
        vector<string> adjacentCont;
        // find each continent's territories
        vector<Territory*> terr = getTerritoriesByContinentId(continent->id);

        for (auto & j : terr) {
            // find each territory adjacent nodes
            vector<Territory*> adjacentTerr = getAdjacentTerritories(j->id);

            for (auto & k : adjacentTerr) {
                // push continent of adjacent territories of the continent's territories
                if(!(std::find(adjacentCont.begin(), adjacentCont.end(), k->getContinentID()) != adjacentCont.end()) &&
                k->getContinentID() != continent->id) {
                    adjacentCont.push_back(k->getContinentID());
                }
            }
        }
        cout << endl;

        // set continent of adjacent territories of the continent's territories, as the continents adjacent territorries
        continent->adjacent = adjacentCont;
    }
}


// get territory object by its id
Territory* Map::getTerritoryById(string territoryID) {
    for (auto & territorie : territories) {
        if(territorie->id == territoryID) {
            return territorie;
        }
    }
    return NULL;
}

// get continent object by its id
Continent* Map::getContinentById(string id){
    for (auto & continent : continents) {
        if(continent->id == id) {
            return continent;
        }
    }
    return NULL;
}

// get all territory objects of a continent
vector<Territory*> Map::getTerritoriesByContinentId(string id){
    vector<Territory*> terr;
    for (auto & territorie : territories) {
        if(territorie->getContinentID() == id) {
            terr.push_back(territorie);
        }
    }
    return terr;
}


// get all Territories adjacent to a specific territory
vector<Territory*> Map::getAdjacentTerritories(string territoryID) {
    vector<Territory*> tempList;
    for (auto & territorie : territories) {
        if(territorie->id == territoryID) {
            vector<string> nodesStrings = territorie->getAdjacentNodes();
            for (auto & nodesString : nodesStrings) {
                tempList.push_back(getTerritoryById(reinterpret_cast<basic_string<char> &&>(nodesString)));
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
    for(auto continent : n.continents) {
        os << *continent;
    }

    os << endl;
    os << " The territories' are:"<< endl;
    for(auto territorie : n.territories) {
        os << *territorie;
    }
    return os;
}

// assignment operator
Map& Map::operator = (const Map& _file) {
    name = _file.name;
    continents = _file.continents;
    territories = _file.territories;
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
    name = _file.name;
    id = _file.id;
    adjacent = _file.adjacent;
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
bool Territory::isAdjacentNode(const string& _node) {
    for (auto & i : adjacent) {
        if(i == _node) {
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
    name = _file.name;
    id = _file.id;
    continentID = _file.continentID;
    adjacent = _file.adjacent;
    armiesNumber = _file.armiesNumber;
    owner = _file.owner;
    return *this;
}

