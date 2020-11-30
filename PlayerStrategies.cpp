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
    /**
     * Deploy(Player* pl, Territory* terr, int theUnits)
     * Advance(Player* pl, Territory* terr, Territory* attTerr, int unitsAttackingWith)
     * Bomb(Player* pl, Territory* terr, Territory* attTerr)
     * Blockade(Player* pl, Territory* terr)
     * Airlift(Player* pl, Territory* terr, Territory* attTerr, int unitsAttackingWith)
     * Negotiate(Player* pl, Player* otherPl)
     */
     if(player->phase = 1) {
         cout << "Enter the ID of the territory you want to deploy your units to: ";
         for(int i = 0; i < player->playerTerritories.size(); i++){
             cout << player->playerTerritories.at(i)->id << ": " << player->playerTerritories.at(i)->name ;
         }
         string terrID;
         cin >> terrID;
         Territory *terrChoice = map->getTerritoryById(terrID);
         cout << "Enter the number of units you want to deploy: ";

         int unitNum;
         cin>> unitNum;
         ol->orders.push_back(new Deploy(player, terrChoice, unitNum));
     }
    else if(player->phase = 2) {
         cout
                 << "Choose an order by number: \n\n 1. Advance \n 2. Bomb \n 3. Blockade 4. \n Airlift \n 5. Negotiate \n\n";

         int menuChoice;
         cin >> menuChoice;
         //Advance(Player* pl, Territory* terr, Territory* attTerr, int unitsAttackingWith)
         if(menuChoice == 1){
             cout << "Choose a territory to attack from by ID: ";
             for(int i = 0; i < player->playerTerritories.size(); i++){
                 cout << player->playerTerritories.at(i)->id << ": " << player->playerTerritories.at(i)->name ;
             }
             
             string terrID;
             cin >> terrID;
             Territory *terrChoice = map->getTerritoryById(terrID);

         }



     }
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