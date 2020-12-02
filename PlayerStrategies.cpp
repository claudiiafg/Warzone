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

vector<Territory*> PlayerStrategy::toAttack(Player* player) {
	vector<Territory*> *toAttack = new vector<Territory*>{};

	return (*toAttack);
}

vector<Territory*> PlayerStrategy::toDefend(Player* player) {
	vector<Territory*> *toDefend = new vector<Territory*>{};

	return (*toDefend);
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
             cout << player->playerTerritories.at(i)->id << ": " << player->playerTerritories.at(i)->name << "\n";
         }
         string terrID;
         cin >> terrID;
         Territory *terrChoice = stratMap->getTerritoryById(terrID);
         cout << "Units will be deployed to " << terrChoice->name << "\n\n";
         /**
         cout << "Enter the number of units you want to deploy: \n\n";

         int unitNum;
         cin>> unitNum;
         cout << unitNum << " Units will be deployed.\n\n";
          */
         player->getMyOrders()->addOrder(new Deploy(player, terrChoice, 500));
     }
    else if(player->phase == 2) {
         cout
                 << "Choose an order by number: \n\n 1. Advance \n 2. Bomb \n 3. Blockade \n 4. Airlift \n 5. Negotiate \n\n";

         int menuChoice;
         cin >> menuChoice;
         if(menuChoice == 1){
             cout << "Choose a territory to attack from by ID: ";
             for(int i = 0; i < player->playerTerritories.size(); i++){
                 cout << player->playerTerritories.at(i)->id << ": " << player->playerTerritories.at(i)->name << "\n" ;
             }
             
             string attackFromID;
             cin >> attackFromID;
             Territory *terrChoice = stratMap->getTerritoryById(attackFromID);
             cout << "Units will be deployed from " << terrChoice->name << "\n\n";

             cout << "Choose a territory to attack by ID: \n\n";
             for(int i = 0; i < stratMap->getAdjacentTerritories(terrChoice->id).size(); i++){
                 cout << stratMap->getAdjacentTerritories(terrChoice->id).at(i)->id << " " << stratMap->getAdjacentTerritories(terrChoice->id).at(i)->name << "\n";
             }
             string attackID;
             cin >> attackID;
             Territory *attackChoice = stratMap->getTerritoryById(attackID);
             cout << "You issued an order to attack " << attackChoice->name << "!\n\n";

             cout << "Enter the number of units you want to deploy: \n\n";
             int unitNum;
             cin>> unitNum;
             cout << "You will deploy " << unitNum << "units\n\n";
             player->getMyOrders()->addOrder(new Advance(player, terrChoice, attackChoice, unitNum));
         }

         if(menuChoice == 2){
             //Bomb(Player* pl, Territory* terr, Territory* attTerr)
             cout << "Choose a territory to bomb from by ID: \n\n";
             for(int i = 0; i < player->playerTerritories.size(); i++){
                 cout << player->playerTerritories.at(i)->id << ": " << player->playerTerritories.at(i)->name << "\n";
             }

             string attackFromID;
             cin >> attackFromID;
             Territory *terrChoice = stratMap->getTerritoryById(attackFromID);
             cout << "You will launch your bomb attack from " << terrChoice->name << "\n\n";
             cout << "Choose a territory to bomb by ID: \n\n";
             for(int i = 0; i < stratMap->getTerritories().size(); i++){
                 cout << stratMap->getTerritories().at(i)->id << " " << stratMap->getTerritories().at(i)->name << "\n";
             }
             string attackID;
             cin >> attackID;
             Territory *attackChoice = stratMap->getTerritoryById(attackID);
             cout << "You issued an order to bomb " << attackChoice->name << "!\n\n";
             player->getMyOrders()->addOrder(new Bomb(player, terrChoice, attackChoice));
         }

         if(menuChoice == 3){
             cout << "Choose a territory to blockade by ID: ";
             for(int i = 0; i < player->playerTerritories.size(); i++){
                 cout << player->playerTerritories.at(i)->id << ": " << player->playerTerritories.at(i)->name << "\n";
             }
             string blockadeID;
             cin >> blockadeID;
             Territory *terrChoice = stratMap->getTerritoryById(blockadeID);
             cout << "You issued an order to blockade" << terrChoice->name << "!\n\n";

                 player->getMyOrders()->addOrder(new Blockade(player, terrChoice));
         }

         if(menuChoice == 4){
             cout << "Choose a territory to airlift from by ID: ";
             for(int i = 0; i < player->playerTerritories.size(); i++){
                 cout << player->playerTerritories.at(i)->id << ": " << player->playerTerritories.at(i)->name << "\n";
             }

             string attackFromID;
             cin >> attackFromID;
             Territory *terrChoice = stratMap->getTerritoryById(attackFromID);
             cout << "Units will be airlifted from " << terrChoice->name << "\n\n";
             cout << "Choose a territory to airlift to by ID: \n\n";
             for(int i = 0; i < stratMap->getTerritories().size(); i++){
                 cout << stratMap->getTerritories().at(i)->id << " " << stratMap->getTerritories().at(i)->name << "\n";
             }
             string attackID;
             cin >> attackID;
             Territory *attackChoice = stratMap->getTerritoryById(attackID);
             cout << "Your units will be airlifted from " << attackChoice->name << "\n\n";
             cout << "Enter the number of units you want to airlift: \n\n";
             int unitNum;
             cin>> unitNum;
             cout << unitNum << " units will be airlifted.\n\n";
             player->getMyOrders()->addOrder(new Airlift(player, terrChoice, attackChoice, unitNum));
         }

         if(menuChoice == 5){
             cout << "Enter the ID of the player you want to negotiate with: \n\n";
             int negotiateID;
             cin >> negotiateID;
             cout << "You will enter into negotiations with player " << negotiateID << "\n\n";
             player->getMyOrders()->addOrder(new Negotiate(player, negotiateID));
         }
     }
}

vector<Territory*> HumanPlayerStrategy::toAttack(Player* player) {
    vector<Territory*> *toAttack = new vector<Territory*>{};
    cout << "Choose a territory to attack: \n\n";
    for(int i = 0; i < player->adjacentEnemies(stratMap).size(); i++){
        cout << player->adjacentEnemies(stratMap).at(i)->id << ": " << player->adjacentEnemies(stratMap).at(i)->name << "\n";
    }
    string target;
    cin >> target;
    cout << "You attacked " << stratMap->getTerritoryById(target)->name << "!\n\n";
    toAttack->push_back(stratMap->getTerritoryById(target));
    return (*toAttack);
}

vector<Territory*> HumanPlayerStrategy::toDefend(Player* player) {
    vector<Territory*> *toDefend = new vector<Territory*>{};
    cout<< "Choose a territory to defend: \n\n";
    for(int i = 0; i < player->playerTerritories.size(); i++){
        cout << player->playerTerritories.at(i)->id << ": " << player->playerTerritories.at(i)->name << "\n";
    }
    string target;
    cin >> target;
    cout << "You chose to defend " << stratMap->getTerritoryById(target)->name << ".\n\n";
    toDefend->push_back(stratMap->getTerritoryById(target));
    return (*toDefend);
}


//////////////////////////////////////////////////////////////
////             AGGRESSIVE PLAYER STRATEGY               ////
//////////////////////////////////////////////////////////////


void AggressivePlayerStrategy::issueOrder(Player* player) {
    Territory* strongest = toDefend(player).front(); //Find strongest territory

    //DEPLOY PHASE
    if (player->reinforcements > 0) { //Deploy all reinforcements to strongest territory
        player->deploy(strongest, player->reinforcements);
        player->orderPhase++; //Increment player phase (from deploy phase to other orders phase)
        return;
    }

    //OTHER ORDERS PHASE

    //Advance all armies but one from adjacent friendly territories to strongest territory
    vector<Territory*> adj = stratMap->getAdjacentTerritories(strongest->id);
    vector<Territory*>::iterator it = adj.begin();
    while (it != adj.end()) { 
        if ((*it)->getOwnerID() == player->name && (*it)->armiesNumber>1) {
            if (count(player->advanceList.begin(), player->advanceList.end(), (*it)) > 0) { //Check if country has already advanced their armies
                it = adj.erase(it);
                continue;
            }
            player->playerOrders->addOrder(new Advance(player, (*it), strongest, (*it)->armiesNumber-1));
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
    player->playerOrders->addOrder(new Advance(player, strongest, getWeakestEnemy(strongest, player), (strongest->armiesNumber)/2));
    player->orderPhase++; //Increment player phase from Other Orders Phase to Issuing Complete
}

vector<Territory*> AggressivePlayerStrategy::toAttack(Player* player) { //Every adjacent enemy is on the toAttack list
    vector<Territory*> toAttack = player->adjacentEnemies(stratMap);
    return toAttack;
}

vector<Territory*> AggressivePlayerStrategy::toDefend(Player* player) { //Protects its strongest countries first

    vector<Territory*> toDefend = player->getMyTerritories();
    sort(toDefend.begin(), toDefend.end()); //Sorts from weakest to strongest territory
    reverse(toDefend.begin(), toDefend.end()); //Reverses vector so strongest is first

    Territory* strong = toDefend.front();

    //Iterate down the list until the strongest territory with adjacent enemies is found
    while ((*stratMap).getAdjacentEnemyTerritories(strong->id, player).empty()) {
        toDefend.erase(toDefend.begin());
        strong = toDefend.front();
    };

    return toDefend;
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

    //DEPLOY PHASE
    if (player->reinforcements > 0) { //Reinforce weakest country
        Territory* weakest = toDefend(player).front();
        player->deploy(weakest, player->reinforcements);
        player->orderPhase++; //Increment player phase (from deploy phase to other orders phase)
        player->advanceList.push_back(weakest);
        return;
    }

    //OTHER ORDERS PHASE

    //Advance - Relocate armies from biggest territory to weakest adjacent
    Territory* biggest = getBiggest(player); //Find player's territory with most armies
    int toSend = biggest->armiesNumber / 2; //Send half of the strongest territory's armies

    for (auto terr : stratMap->getAdjacentTerritories(biggest->id)) {
        if (terr->getOwnerID() == player->name) { //Must be friendly territory
            if (count(player->advanceList.begin(), player->advanceList.end(), terr) > 0) { //Check if country has already been reinforced or advanced to
                continue;
            }
            player->playerOrders->addOrder(new Advance(player, terr, biggest, toSend));
            player->advanceList.push_back(terr); //Add territory to list that has been reinforce3d
            return;
        }
    }


    //Airlift - Use airlift from strongest to weakest territory
    if (player->getMyHand()->getAirCount() > 0) {
        Territory* biggest = getBiggest(player); //Find player's territory with most armies
        int toSend = biggest->armiesNumber / 2; //Send half of the strongest territory's armies
        Territory* weaker = toDefend(player).front();
        for (auto terr: toDefend(player)) {
            if (count(player->advanceList.begin(), player->advanceList.end(), terr) > 0) { //Check if country has already been reinforced or advanced to
                    continue;
                }
            weaker = terr; //Otherwise, airlift to this territory
            player->advanceList.push_back(weaker); //Add territory to list that has been reinforce3d
            return;
        }

        player->getMyHand()->play("airlift");
        player->playerOrders->addOrder(new Airlift(player, biggest, weaker, toSend));
        return;
    }


    //Negotiate - Use anytime available on any player
    int otherPlayer = player->name;

    for (auto terr : player->getMyTerritories()) {
        vector<Territory*> enemyTerrs = stratMap->getAdjacentEnemyTerritories(terr->id, player);
        if (!(enemyTerrs.empty())) { //Take the first player territory that has adjacent enemies
            otherPlayer = enemyTerrs.front()->getOwnerID(); //Take the enemy territory's owner id as a player to negotiate with
        }
    }
   
    if (player->getMyHand()->getDiplomCount() > 0) {
        player->getMyHand()->play("diplomacy");
        player->playerOrders->addOrder(new Negotiate(player, otherPlayer));
        return;
    }

    //Blockade - Use weakest territory
    if (player->getMyHand()->getBlockCount() > 0) {
        for (auto terr : toDefend(player)) {
            if (count(player->advanceList.begin(), player->advanceList.end(), terr) > 0) { //Check if country has already been reinforced or advanced to
                continue;
            }
            player->getMyHand()->play("blockade");
            player->playerOrders->addOrder(new Blockade(player, terr));
            player->advanceList.push_back(terr); //Add territory to list that has been reinforce3d
            return;
        }
    }

    player->orderPhase++; //No more orders to issue, increment to completed phase
}

vector<Territory*> BenevolentPlayerStrategy::toAttack(Player* player) { //Benevolent player never attacks
    vector<Territory*> toAttack{};
    return toAttack;
}

vector<Territory*> BenevolentPlayerStrategy::toDefend(Player* player) { //Benevolent player protects its weakest countries first
    vector<Territory*> toDefend = player->getMyTerritories();
    sort(toDefend.begin(), toDefend.end());
    return toDefend;
}

//Returns the player territory with the most armies
Territory* BenevolentPlayerStrategy::getBiggest(Player* player) {
    vector<Territory*> territories = player->getMyTerritories();
    Territory* biggest = territories.front();

    for (auto terr : player->getMyTerritories()) {
        if (terr->armiesNumber > biggest->armiesNumber) biggest = terr;
    }

    return biggest;
}

//////////////////////////////////////////////////////////////
////               NEUTRAL PLAYER STRATEGY                ////
//////////////////////////////////////////////////////////////



void NeutralPlayerStrategy::issueOrder(Player* player) {
}

vector<Territory*> NeutralPlayerStrategy::toAttack(Player* player) {
    vector<Territory*> *toAttack = new vector<Territory*>{};

    return (*toAttack);
}

vector<Territory*> NeutralPlayerStrategy::toDefend(Player* player) {
    vector<Territory*> *toDefend = new vector<Territory*>{};

    return (*toDefend);
}