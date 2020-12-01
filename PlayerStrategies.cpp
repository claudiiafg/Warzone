#include "PlayerStrategies.h"
#include "Player.h"
#include <iostream>
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
    stratMap = m;
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

     if(player->phase = 1) {
         cout << "Enter the ID of the territory you want to deploy your units to: ";
         for(int i = 0; i < player->playerTerritories.size(); i++){
             cout << player->playerTerritories.at(i)->id << ": " << player->playerTerritories.at(i)->name ;
         }
         string terrID;
         cin >> terrID;
         Territory *terrChoice = stratMap->getTerritoryById(terrID);
         cout << "Enter the number of units you want to deploy: ";

         int unitNum;
         cin>> unitNum;
         ol->orders.push_back(new Deploy(player, terrChoice, unitNum));
     }
    else if(player->phase == 2) {
         cout
                 << "Choose an order by number: \n\n 1. Advance \n 2. Bomb \n 3. Blockade \n 4. Airlift \n 5. Negotiate \n\n";

         int menuChoice;
         cin >> menuChoice;
         if(menuChoice == 1){
             cout << "Choose a territory to attack from by ID: ";
             for(int i = 0; i < player->playerTerritories.size(); i++){
                 cout << player->playerTerritories.at(i)->id << ": " << player->playerTerritories.at(i)->name ;
             }
             
             string attackFromID;
             cin >> attackFromID;
             Territory *terrChoice = stratMap->getTerritoryById(attackFromID);

             cout << "Choose a territory to attack by ID: ";
             for(int i = 0; i < stratMap->getAdjacentTerritories(terrChoice->id).size(); i++){
                 cout << stratMap->getAdjacentTerritories(terrChoice->id).at(i)->id << " " << stratMap->getAdjacentTerritories(terrChoice->id).at(i)->name;
             }
             string attackID;
             cin >> attackID;
             Territory *attackChoice = stratMap->getTerritoryById(attackID);

             cout << "Enter the number of units you want to deploy: ";
             int unitNum;
             cin>> unitNum;
             ol->orders.push_back(new Advance(player, terrChoice, attackChoice, unitNum));
         }

         if(menuChoice == 2){
             //Bomb(Player* pl, Territory* terr, Territory* attTerr)
             cout << "Choose a territory to bomb from by ID: ";
             for(int i = 0; i < player->playerTerritories.size(); i++){
                 cout << player->playerTerritories.at(i)->id << ": " << player->playerTerritories.at(i)->name ;
             }

             string attackFromID;
             cin >> attackFromID;
             Territory *terrChoice = stratMap->getTerritoryById(attackFromID);

             cout << "Choose a territory to bomb by ID: ";
             for(int i = 0; i < stratMap->getTerritories().size(); i++){
                 cout << stratMap->getTerritories().at(i)->id << " " << stratMap->getTerritories().at(i)->name;
             }
             string attackID;
             cin >> attackID;
             Territory *attackChoice = stratMap->getTerritoryById(attackID);
             ol->orders.push_back(new Bomb(player, terrChoice, attackChoice));
         }

         if(menuChoice == 3){
             cout << "Choose a territory to blockade by ID: ";
             for(int i = 0; i < player->playerTerritories.size(); i++){
                 cout << player->playerTerritories.at(i)->id << ": " << player->playerTerritories.at(i)->name ;
             }

             string blockadeID;
             cin >> blockadeID;
             Territory *terrChoice = stratMap->getTerritoryById(blockadeID);
             ol->orders.push_back(new Blockade(player, terrChoice));
         }

         if(menuChoice == 4){
             //Airlift(Player* pl, Territory* terr, Territory* attTerr, int unitsAttackingWith)
             cout << "Choose a territory to airlift from by ID: ";
             for(int i = 0; i < player->playerTerritories.size(); i++){
                 cout << player->playerTerritories.at(i)->id << ": " << player->playerTerritories.at(i)->name ;
             }

             string attackFromID;
             cin >> attackFromID;
             Territory *terrChoice = stratMap->getTerritoryById(attackFromID);

             cout << "Choose a territory to airlift to by ID: ";
             for(int i = 0; i < stratMap->getTerritories().size(); i++){
                 cout << stratMap->getTerritories().at(i)->id << " " << stratMap->getTerritories().at(i)->name;
             }
             string attackID;
             cin >> attackID;
             Territory *attackChoice = stratMap->getTerritoryById(attackID);

             cout << "Enter the number of units you want to airlift: ";
             int unitNum;
             cin>> unitNum;
             ol->orders.push_back(new Airlift(player, terrChoice, attackChoice, unitNum));
         }

         if(menuChoice == 5){
             cout << "Enter the ID of the player you want to negotiate with: ";
             int negotiateID;
             cin >> negotiateID;
             ol->orders.push_back(new Negotiate(player, negotiateID));
         }
     }
    return 1;
}

vector<Territory*> HumanPlayerStrategy::toAttack() {
    vector<Territory*> *toAttack = new vector<Territory*>{};
    cout << "Choose a territory to attack: \n\n";
    string target;
    cin >> target;
    cout<<"It worked!";
    cout << "You attacked " << stratMap->getTerritoryById(target)->name << "!";
    toAttack->push_back(stratMap->getTerritoryById(target));
    return *toAttack;
}

vector<Territory*> HumanPlayerStrategy::toDefend() {
    vector<Territory*> *toDefend = new vector<Territory*>{};
    cout<< "Choose a territory to defend: \n\n";
    string target;
    cin >> target;
    toDefend->push_back(stratMap->getTerritoryById(target));
    return *toDefend;
}


//AGGRESSIVE PLAYER STRATEGY: focuses on attack (deploys or advances armies on its strongest country, then always advances to enemy territories until it cannot do so anymore)

int AggressivePlayerStrategy::issueOrder() {
    return 1;
}

vector<Territory*> AggressivePlayerStrategy::toAttack() { //Every adjacent enemy is on the toAttack list
    vector<Territory*> toAttack = player->adjacentEnemies(stratMap);
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
    static vector<Territory*>* toAttack = new vector<Territory*>{};
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