#include "PlayerStrategies.h"
#include "Player.h"
#include "Orders.h"
#include "Map.h"
#include "Cards.h"
#include <iostream>

using namespace std;

//////////////////////////////////////////////////////////////
////                  PLAYER STRATEGY                     ////
//////////////////////////////////////////////////////////////

void PlayerStrategy::issueOrder(Player* player) {
} 

Territory* PlayerStrategy::toAttack(Player* player) {
	vector<Territory*> *toAttack = new vector<Territory*>{};

	return (*toAttack).front();
}

Territory* PlayerStrategy::toDefend(Player* player) {
	vector<Territory*> *toDefend = new vector<Territory*>{};

	return (*toDefend).front();
}

void PlayerStrategy::setMap(Map *m){
    stratMap = m;
}

/*void PlayerStrategy::setOrderList(OrderList *oList) {
    list <Order*> ::iterator it;
    list <Order*> ::iterator it2;
    it2 = ol->orders.begin();
    for (it = oList->orders.begin(); it != oList->orders.end(); ++it) {
        it2 = it;
        it2++;
    }
}*/


//////////////////////////////////////////////////////////////
////               HUMAN PLAYER STRATEGY                  ////
//////////////////////////////////////////////////////////////



void HumanPlayerStrategy::issueOrder(Player* player) {

     if(player->phase == 1) {
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
         player->getMyOrders()->addOrder(new Deploy(player, terrChoice, unitNum));
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
             player->getMyOrders()->addOrder(new Advance(player, terrChoice, attackChoice, unitNum));
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
             player->getMyOrders()->addOrder(new Bomb(player, terrChoice, attackChoice));
         }

         if(menuChoice == 3){
             cout << "Choose a territory to blockade by ID: ";
             for(int i = 0; i < player->playerTerritories.size(); i++){
                 cout << player->playerTerritories.at(i)->id << ": " << player->playerTerritories.at(i)->name ;
             }

             string blockadeID;
             cin >> blockadeID;
             Territory *terrChoice = stratMap->getTerritoryById(blockadeID);
             player->getMyOrders()->addOrder(new Blockade(player, terrChoice));
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
             player->getMyOrders()->addOrder(new Airlift(player, terrChoice, attackChoice, unitNum));
         }

         if(menuChoice == 5){
             cout << "Enter the ID of the player you want to negotiate with: ";
             int negotiateID;
             cin >> negotiateID;
             player->getMyOrders()->addOrder(new Negotiate(player, negotiateID));
         }
     }
}

Territory* HumanPlayerStrategy::toAttack(Player* player) {
    vector<Territory*> *toAttack = new vector<Territory*>{};
    cout << "Choose a territory to attack: \n\n";
    string target;
    cin >> target;
    cout<<"It worked!";
    cout << "You attacked " << stratMap->getTerritoryById(target)->name << "!";
    toAttack->push_back(stratMap->getTerritoryById(target));
    return (*toAttack).front();
}

Territory* HumanPlayerStrategy::toDefend(Player* player) {
    vector<Territory*> *toDefend = new vector<Territory*>{};
    cout<< "Choose a territory to defend: \n\n";
    string target;
    cin >> target;
    toDefend->push_back(stratMap->getTerritoryById(target));
    return (*toDefend).front();
}


//////////////////////////////////////////////////////////////
////             AGGRESSIVE PLAYER STRATEGY               ////
//////////////////////////////////////////////////////////////


void AggressivePlayerStrategy::issueOrder(Player* player) {
    Territory* strongest = toDefend(player); //Find strongest territory

    //DEPLOY PHASE
    if (player->reinforcements > 0) { //Deploy all reinforcements to strongest territory
        player->deploy(strongest, player->reinforcements);
        player->orderPhase++; //Increment player phase (from deploy phase to other orders phase)
        return;
    }

    //OTHER ORDERS PHASE

    //Advance all armies from adjacent friendly territories to strongest territory
    vector<Territory*> adj = stratMap->getAdjacentTerritories(strongest->id);
    vector<Territory*>::iterator it = adj.begin();
    while (it != adj.end()) { 
        if ((*it)->getOwnerID() == player->name && (*it)->armiesNumber>0) {
            if (count(player->advanceList.begin(), player->advanceList.end(), (*it)) > 0) {
                it = adj.erase(it);
                continue;
            }
            player->playerOrders->addOrder(new Advance(player, (*it), strongest, (*it)->armiesNumber));
            player->advanceList.push_back(*it);
            return;
        }
        it=adj.erase(it);
    }
  
    //If airlift available, airlift armies from territory with most armies to current strongest
    if (player->getMyHand()->getAirCount() > 0) {
        if (getBiggest(player)->armiesNumber > strongest->armiesNumber) {
            player->getMyHand()->play("airlift");
            player->playerOrders->addOrder(new Airlift(player, getBiggest(player), strongest, getBiggest(player)->armiesNumber));
            return;
        }
    }

    //Use bomb on strongest enemy territory adjacent to strongest whenever available
    if (player->getMyHand()->getBombCount() > 0) {
        player->getMyHand()->play("bomb");
        player->playerOrders->addOrder(new Bomb(player,strongest, getStrongestEnemy(strongest, player)));
        return;
    }

    //Advance all armies from strongest territory to weakest adjacent enemy territory
    player->playerOrders->addOrder(new Advance(player, strongest, getWeakestEnemy(strongest, player), strongest->armiesNumber));
    player->orderPhase++; //Increment player phase from Other Orders Phase to Issuing Complete
}

Territory* AggressivePlayerStrategy::toAttack(Player* player) { //Every adjacent enemy is on the toAttack list
    vector<Territory*> toAttack = player->adjacentEnemies(stratMap);
    return toAttack.front();
}

Territory* AggressivePlayerStrategy::toDefend(Player* player) { //Protects its strongest countries first

    vector<Territory*> toDefend = player->getMyTerritories();
    sort(toDefend.begin(), toDefend.end()); //Sorts from weakest to strongest territory
    reverse(toDefend.begin(), toDefend.end()); //Reverses vector so strongest is first

    Territory* strong = toDefend.front();

    while ((*stratMap).getAdjacentEnemyTerritories(strong->id, player).empty()) { //Iterate down the list until one with adjacent enemies is found
        toDefend.erase(toDefend.begin());
        strong = toDefend.front();
    };

    return strong;
}

//Returns the player territory with the most armies
Territory* AggressivePlayerStrategy::getBiggest(Player* player) {
    vector<Territory*> territories = player->getMyTerritories();
    Territory* biggest = territories.front();

    for (auto terr : player->getMyTerritories()) {
        if (terr->armiesNumber > biggest->armiesNumber) biggest = terr;
    }

    return biggest;
}

//Returns the enemy territory with the least armies adjacent to strongest friendly territory - used for advance
Territory* AggressivePlayerStrategy::getWeakestEnemy(Territory* strongest, Player* player) {
    vector<Territory*> adj = (*stratMap).getAdjacentEnemyTerritories(strongest->id, player);
    Territory* weakestenemy = adj.front();

    for (auto terr : adj) {
        if (terr->armiesNumber < weakestenemy->armiesNumber) weakestenemy = terr;
    }

    return weakestenemy;
}

//Returns the enemy territory with the most armies adjacent to strongest friendly territory - used for bomb
Territory* AggressivePlayerStrategy::getStrongestEnemy(Territory* strongest, Player* player) {
    vector<Territory*> adj = (*stratMap).getAdjacentEnemyTerritories(strongest->id, player);
    Territory* strongestenemy = adj.front();

    for (auto terr : adj) {
        if (terr->armiesNumber > strongestenemy->armiesNumber) strongestenemy = terr;
    }

    return strongestenemy;
}


//////////////////////////////////////////////////////////////
////             BENEVOLENT PLAYER STRATEGY               ////
//////////////////////////////////////////////////////////////



void BenevolentPlayerStrategy::issueOrder(Player* player) {
    //Divide reinforcements between territories on defence list
    //Relocate any armies from territorities with above average units to those adjacent with below average
    //Use airlift from strongest to weakest territory
    //Use negotiate anytime available
    //Use blockade on weakest territory anytime available
    //Never use bomb
}

Territory* BenevolentPlayerStrategy::toAttack(Player* player) { //Benevolent player never attacks
    return nullptr;
}

Territory* BenevolentPlayerStrategy::toDefend(Player* player) { //Benevolent player protects its weakest countries first
    vector<Territory*> toDefend = player->getMyTerritories();
    sort(*toDefend.begin(), *toDefend.end());
    return toDefend.front();
}



//////////////////////////////////////////////////////////////
////               NEUTRAL PLAYER STRATEGY                ////
//////////////////////////////////////////////////////////////



void NeutralPlayerStrategy::issueOrder(Player* player) {
}

Territory* NeutralPlayerStrategy::toAttack(Player* player) {
    vector<Territory*> *toAttack = new vector<Territory*>{};

    return (*toAttack).front();
}

Territory* NeutralPlayerStrategy::toDefend(Player* player) {
    vector<Territory*> *toDefend = new vector<Territory*>{};

    return (*toDefend).front();
}