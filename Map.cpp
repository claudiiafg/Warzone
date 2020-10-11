//
// Created by Claudia on 2020-10-07.
//

#include "Map.h"

//MAP>>>>>>>>>>>>>>>>>>>>>>>>>

Map::Map(string _name, vector<string> mapData) {
    name = _name;

    int contI;
    int terrI;
    int borderI;

    //get indexes that limit the data necessary
    for (size_t i = 0; i < mapData.size(); ++i){
        if(mapData[i].find("continents") < mapData.size() && mapData[i].find("continents") > 0) {
            contI = i;
        } else if(mapData[i].find("countries") < mapData.size() && mapData[i].find("countries") > 0) {
            terrI = i;
        } else if(mapData[i].find("borders") < mapData.size() && mapData[i].find("borders") > 0) {
            borderI = i;
        }
    }

    //get all continent strings from map data
    vector<string> continents;
    for (size_t i = (contI + 1); i < (terrI - 1); ++i){
        continents.push_back(mapData[i]);
    }

    //get all country strings from map data
    vector<string> territories;
    for (size_t i = (terrI + 1); i < (borderI - 1); ++i){
        territories.push_back(mapData[i]);
    }

    //get nodes per country from map data
    vector<string> borders;
    for (size_t i = (borderI + 1); i < mapData.size(); ++i){
        borders.push_back(mapData[i]);
    }

    setContinents(continents);
    setTerritories(territories, borders);
    validate();
}

bool Map::validate() {
    cout << ">>>>>>>>>>>>Map successfully created>>>>>>>>>>" << endl;
    return true;
}

vector<Territory> Map::getTerritories() {
    return territories;
}

vector<Continent> Map::getContinents() {
    return continents;
}

Territory Map::getTerritoryById(string territoryID) {
    for (int i = 0; i < territories.size(); i++) {
        if(territories[i].id == territoryID) {
            return territories[i];
        }
    }
}

//get all Territories adjacent to a specific territory
vector<Territory> Map::getAdjacentTerritories(string territoryID) {
    vector<Territory> tempList;
    for (int i = 0; i < territories.size(); i++) {
        if(territories[i].id == territoryID) {
            vector<string> nodesStrings = territories[i].getAdjacentNodes();
            for (int i = 0; i < nodesStrings.size(); i++) {
                tempList.push_back(getTerritoryById(nodesStrings[i]));
            }
        }
    }
    return tempList;
}

void Map::setTerritories(vector<string> _territoriesData, vector<string> _bordersData) {

    for (int i = 0; i < _territoriesData.size(); i++) {
        Territory *tempTer = new Territory(_territoriesData[i], _bordersData[i]);
        territories.push_back(*tempTer);
        delete tempTer;
    }
}

void Map::setContinents(vector<string> _continentsData) {
    for (int i = 0; i < _continentsData.size(); i++) {
        Continent *tempCont = new Continent(to_string(i+1), _continentsData[i]);
        continents.push_back(*tempCont);
        delete tempCont;
    }

}

ostream &operator<<(ostream &os, Map &n) {
    os << "Map " << n.name ;
    os << " has " << n.getContinents().size() << " continents";
    os << " and " << n.getTerritories().size()<< " territories";
    return os;
}


//CONTINENT>>>>>>>>>>>>>>>>>>>>>>>>>

Continent::Continent(string pos, string continentsString) {
    id = pos;

    //seperate string by spaces
    regex ws_re("\\s+");
    vector<string> result{
            sregex_token_iterator(continentsString.begin(), continentsString.end(), ws_re, -1), {}
    };

    //result is in form [name, (useless info for now...)]
        for (int i = 0; i < result.size(); i++) {
            if(i == 0) {
                name = result[i];
            }
        }

}

ostream &operator<<(ostream &os, const Continent &n) {
    os << "Continent " << n.name << endl;
    return os;
}


//TERRITORY>>>>>>>>>>>>>>>>>>>>>>>>>


Territory::Territory(string territoryString, string borderString) {
    armiesNumber = 0;
    owner = *new Player*();

    //seperate strings by spaces
    regex ws_re("\\s+");
    vector<string> result{
            sregex_token_iterator(territoryString.begin(), territoryString.end(), ws_re, -1), {}
    };
    vector<string> bordersResult{
            sregex_token_iterator(borderString.begin(), borderString.end(), ws_re, -1), {}
    };

    //result is in form [id, name, continentID, (useless..)]
    for (int i = 0; i < result.size(); i++) {
        if (i == 0) {
            id = result[i];
        } else if (i == 1) {
            name = result[i];
        } else if (i == 2) {
            continentID = result[i];
        }
    }

    for (int i = 0; i < bordersResult.size(); i++) {
        if (i > 0) {
            adjacent.push_back(result[i]);
        }
    }
}

Territory::Territory(const Territory& otherTerritory) {
    armiesNumber = otherTerritory.armiesNumber;
    owner = otherTerritory.owner;
    id = otherTerritory.id;
    name = otherTerritory.name;
    continentID = otherTerritory.continentID;
    adjacent = otherTerritory.adjacent;

}

string Territory::getContinentID() {
    return continentID;
}

vector<string> Territory::getAdjacentNodes() {
    return adjacent;
}

bool Territory::isAdjacentNode(string _node) {
    for (int i = 0; i < adjacent.size(); i++) {
        if(adjacent[i] == _node) {
            return true;
        }
    }
    return false;
}

int Territory::getArmies() {
    return armiesNumber;
}

void Territory::setArmiesNumber(int amount) {
    armiesNumber = amount;
}

Player* Territory::getOwner() {
    return owner;
}

void Territory::setOwner(Player* _owner) {
    owner = _owner;
}

ostream &operator<<(ostream &os, const Territory &n) {
    os << "Territory: " << n.name << endl;
    os << "has " << n.adjacent.size() << " adjacent territories" << endl;
    return os;
}

