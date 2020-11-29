#include "PlayerStrategies.h"

using namespace std;

//PLAYER STRATEGY

int PlayerStrategy::issueOrder() {
    return 1;
} 

vector<Territory*> PlayerStrategy::toAttack() {
	vector<Territory*> *toAttack = new vector<Territory*>{};

	return *toAttack;
}

vector<Territory*> PlayerStrategy::toDefend() {
	vector<Territory*> *toDefend = new vector<Territory*>{};

	return *toDefend;
}

void PlayerStrategy::setMap(Map *m){
    map = m;
}

void PlayerStrategy::setOrderList(OrderList *oList) {
    list <Order*> ::iterator it;
    list <Order*> ::iterator it2;
    it2 = ol->orders.begin();
    for (it = oList->orders.begin(); it != oList->orders.end(); ++it) {
        it2 = it;
        it2++;
    }
}

void PlayerStrategy::setPlayer(Player* p) {
    player = p;
}

//HUMAN PLAYER STRATEGY

int HumanPlayerStrategy::issueOrder() {
    cout<<"Choose an order: \n\n 1. Deploy \n 2. Advance \n 3. Bomb \n 4. Blockade 5. Airlift \n 6. Negotiate \n\n";
    int orderChoice;
    cin >> orderChoice;
    /**
    switch(orderChoice){
        case 1:
            ol->orders.push_back(new Deploy());
            break;
        case 2:
            ol->orders.push_back(new Advance());
            break;
        case 3:
            ol->orders.push_back(new Bomb());
            break;

    }

    ol->orders.push_back(newOrder);
     */

    return 1;
}

vector<Territory*> HumanPlayerStrategy::toAttack() {
    vector<Territory*> *toAttack = new vector<Territory*>{};
    cout<< "Choose a territory to attack: \n\n";
    string target;
    cin >> target;
    toAttack->push_back(map->getTerritoryById(target));
    return *toAttack;
}

vector<Territory*> HumanPlayerStrategy::toDefend() {
    vector<Territory*> *toDefend = new vector<Territory*>{};
    cout<< "Choose a territory to defend: \n\n";
    string target;
    cin >> target;
    toDefend->push_back(map->getTerritoryById(target));
    return *toDefend;
}


//AGGRESSIVE PLAYER STRATEGY: focuses on attack (deploys or advances armies on its strongest country, then always advances to enemy territories until it cannot do so anymore)

int AggressivePlayerStrategy::issueOrder() {
    return 1;
}

vector<Territory*> AggressivePlayerStrategy::toAttack() { //Every adjacent enemy is on the toAttack list
    vector<Territory*> toAttack = player->adjacentEnemies(map);
    return toAttack;
}

vector<Territory*> AggressivePlayerStrategy::toDefend() { //Protects its strongest countries first
    vector<Territory*> toDefend = player->getMyTerritories();
    sort(*toDefend.begin(), *toDefend.end()); //Sorts from weakest to strongest territory
    reverse(*toDefend.begin(), *toDefend.end()); //Reverses vector so strongest is first
    return toDefend;
}


//BENEVOLENT PLAYER STRATEGY: focuses on protecting its weak countries(deploys or advances armies on its weakest countries, never advances to enemy territories)

int BenevolentPlayerStrategy::issueOrder() {
    return 1;
}

vector<Territory*> BenevolentPlayerStrategy::toAttack() { //Benevolent player never attacks
    vector<Territory*>* toAttack = new vector<Territory*>{};
    return *toAttack;
}

vector<Territory*> BenevolentPlayerStrategy::toDefend() { //Benevolent player protects its weakest countries first
    vector<Territory*> toDefend = player->getMyTerritories();
    sort(*toDefend.begin(), *toDefend.end());
    return toDefend;
}


//NEUTRAL PLAYER STRATEGY

int NeutralPlayerStrategy::issueOrder() {
    return 1;
}

vector<Territory*> NeutralPlayerStrategy::toAttack() {
    vector<Territory*> *toAttack = new vector<Territory*>{};

    return *toAttack;
}

vector<Territory*> NeutralPlayerStrategy::toDefend() {
    vector<Territory*> *toDefend = new vector<Territory*>{};

    return *toDefend;
}