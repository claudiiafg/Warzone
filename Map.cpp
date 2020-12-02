//
// Created by Claudia on 2020-10-07.
//

#include "Map.h"
#include "Player.h"

/////////////////////////////////////////////////////////////////////////////
///   MAP   					   	                                      ///
/////////////////////////////////////////////////////////////////////////////

Map::Map() = default;

// constructor
Map::Map(string _name, vector<string> mapData){
    name = _name;

    int contI = 0;
    int terrI = 0;
    int borderI = 0;

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
    vector<string> sequence;
    int idInt = 0;
    int nodeInt = 0;
    bool isInvalid = false;

    sequence.push_back(territories[0]->id);
    for (auto & initialAdjacent : territories[0]->getAdjacentNodes()) {
        sequence.push_back(initialAdjacent);
    }
     // attention! t starts at 1 -> territory[0] is node with id 1
    for (int i = 0; i < territories.size(); i++) {
        // turn string to int
        stringstream geek(territories[i]->id);
        geek >> idInt;

        // check if enough
        if(sequence.size() == territories.size()){
            break;
        }

        // check each adjacent of current node in the sequence
        for (auto & node : territories[idInt - 1]->getAdjacentNodes()) {
            stringstream geek(node);
            geek >> nodeInt;
            vector<string> tempAdjacent = territories[nodeInt - 1]->getAdjacentNodes();

            // look territory id inside it's adjacent node's adjacentList (must have each other)
            if (!(std::count(tempAdjacent.begin(), tempAdjacent.end(), territories[idInt - 1]->id))) {
                cout << "Invalid Map: " << name << endl;
                return false;
            }

            // check ft enough
            if (sequence.size() == territories.size()) {
                break;
            }

            // if not in the sequence yet add it
            if (!(std::find(sequence.begin(), sequence.end(), node) != sequence.end())) {
                sequence.push_back(node);
            }
        }

        if(sequence.size() == territories.size()){
            cout << "->VALID Map: " << name << endl;
            return true;
        }
    }

    cout << "Invalid Map: " << name << endl;
    return false;
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

// get all enemy Territories adjacent to a specific territory
vector<Territory*> Map::getAdjacentEnemyTerritories(string territoryID, Player* p) {
    vector<Territory*> enemyList;
    for (auto& territorie : territories) {
        if (territorie->id == territoryID) {
            vector<string> nodesStrings = territorie->getAdjacentNodes();
            for (auto& nodesString : nodesStrings) {
                Territory* t = getTerritoryById(reinterpret_cast<basic_string<char>&&>(nodesString));
                if (t->getOwnerID()!=p->name) enemyList.push_back(t);
            }
        }
    }
    return enemyList;
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

bool Map::continentHasUniqueOwner(string continentID, int playerName) {
    vector<Territory*> territories = getTerritoriesByContinentId(continentID);

    for(auto terr : territories) {
        // if one has different owner -> not true
        if(terr->getOwnerID() != playerName) {
            return false;
        }
    }
    // if finish loop -> all the same
    return true;
}

vector<Territory *> Map::getTerritoriesByOwnerID(int ownerID) {
    vector<Territory *> tempList = {};
    for (auto &t : territories) {
        if(t->getOwnerID() == ownerID) {
            tempList.push_back(t);
        }
    }
    return tempList;
}

/////////////////////////////////////////////////////////////////////////////
///   CONTINENT					   	                                      ///
/////////////////////////////////////////////////////////////////////////////

Continent::Continent() = default;

// constructor
Continent::Continent(string pos, string continentsString) {
    id = pos;

    //seperate string by spaces
    regex ws_re("\\s{1}");
    vector<string> result{
            sregex_token_iterator(continentsString.begin(), continentsString.end(), ws_re, -1), {}
    };

    name = result[0];

    try{
        bonus = stoi(result[1]);

    } catch(exception) {
        bonus = 0;
    }
}

// copy constructor
Continent::Continent(const Continent& _c){
    id = _c.id;
    name = _c.name;
    adjacent = _c.adjacent;
    bonus = _c.bonus;
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


/////////////////////////////////////////////////////////////////////////////
///   TERRITORY					   	                                      ///
/////////////////////////////////////////////////////////////////////////////

Territory::Territory() = default;

// contructor
Territory::Territory(string territoryString, string borderString) {
    armiesNumber = 0;
    ownerID = 99;

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
    ownerID = otherTerritory.ownerID;
    id = otherTerritory.id;
    name = otherTerritory.name;
    continentID = otherTerritory.continentID;
    adjacent = otherTerritory.adjacent;

}

// destructor
Territory::~Territory() = default;

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
int Territory::getOwnerID() {
    return ownerID;
}

// set owner
void Territory::setOwner(int _ownerID) {
    ownerID = _ownerID;
}

// stream insertion operator
ostream &operator<<(ostream &os, const Territory &n) {
    os << n.name << " is node #" << n.id << " from continent #" << n.continentID;
    os << ", has " << n.adjacent.size() << " adjacent territories -> ";

    for(int i = 0; i < n.adjacent.size(); i++) {
        if(i == n.adjacent.size()-1) {
            os << n.adjacent.at(i) << " ";
        } else {
            os << n.adjacent.at(i) << ", ";
        }
    }
    os << " is owned by: " << n.ownerID;
    os << " and has " << n.armiesNumber << " armies." << endl;

    return os;
}

// assignment operator
Territory& Territory::operator = (const Territory& _file) {
    name = _file.name;
    id = _file.id;
    continentID = _file.continentID;
    adjacent = _file.adjacent;
    armiesNumber = _file.armiesNumber;
    ownerID = _file.ownerID;
    return *this;
}

//comparison operator
bool Territory::operator< (const Territory& otherTerritory) const {
    return armiesNumber < otherTerritory.armiesNumber;
}

