#include "PlayerStrategies.h"
#include "Map.h"
#include <iostream>
using namespace std;

//PLAYER STRATEGY

int PlayerStrategy::issueOrder() {

}

vector<Territory*> PlayerStrategy::toAttack() {
	vector<Territory*> *toAttack = new vector<Territory*>{};

	return *toAttack;
}

vector<Territory*> PlayerStrategy::toDefend() {
	vector<Territory*> *toDefend = new vector<Territory*>{};

	return *toDefend;
}


//HUMAN PLAYER STRATEGY

int HumanPlayerStrategy::issueOrder() {

}

vector<Territory*> HumanPlayerStrategy::toAttack() {
    vector<Territory*> *toAttack = new vector<Territory*>{};
    cout<< "Choose a territory to attack: \n\n";
    string target;
    cin >> target;
   // toAttack->back(Map.getTerritoryByID(target));
    return *toAttack;
}

vector<Territory*> HumanPlayerStrategy::toDefend() {
    vector<Territory*> *toDefend = new vector<Territory*>{};

    return *toDefend;
}


//AGGRESSIVE PLAYER STRATEGY

int AggressivePlayerStrategy::issueOrder() {

}

vector<Territory*> AggressivePlayerStrategy::toAttack() {
    vector<Territory*> *toAttack = new vector<Territory*>{};

    return *toAttack;
}

vector<Territory*> AggressivePlayerStrategy::toDefend() {
    vector<Territory*> *toDefend = new vector<Territory*>{};

    return *toDefend;
}


//BENEVOLENT PLAYER STRATEGY

int BenevolentPlayerStrategy::issueOrder() {

}

vector<Territory*> BenevolentPlayerStrategy::toAttack() {
    vector<Territory*> *toAttack = new vector<Territory*>{};

    return *toAttack;
}

vector<Territory*> BenevolentPlayerStrategy::toDefend() {
    vector<Territory*> *toDefend = new vector<Territory*>{};

    return *toDefend;
}


//NEUTRAL PLAYER STRATEGY

int NeutralPlayerStrategy::issueOrder() {

}

vector<Territory*> NeutralPlayerStrategy::toAttack() {
    vector<Territory*> *toAttack = new vector<Territory*>{};

    return *toAttack;
}

vector<Territory*> NeutralPlayerStrategy::toDefend() {
    vector<Territory*> *toDefend = new vector<Territory*>{};

    return *toDefend;
}