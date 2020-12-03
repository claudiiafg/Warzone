#include "PlayerStrategies.h"
#include "MapLoader.h"
#include "Player.h"
#include "Map.h"
#include <iostream>
using namespace std;


/**
 -At each step, display the countries that are being attacked/reinforced/defended and the number of units on each country
 */

void showMap(Map *m){
    cout << "Current state of the world: \n\n";
    for(int i = 0; i < m->getTerritories().size(); i++){
        cout << "ID: " << m->getTerritories().at(i)->id << "   Name: " << m->getTerritories().at(i)->name
             << "    Owner: " << m->getTerritories().at(i)->getOwnerID() << "      Units: " << m->getTerritories().at(i)->getArmies() << "\n";
    }
    cout<< "\n\n";
}


int main(){
//Player(int name, int armies, vector<Territory*> playerTerritories, Hand* playerHand, OrderList* playerOrders, vector<Player*> allies, PlayerStrategy* strategy)
    Hand *h1 = new Hand();
    OrderList *ol1 = new OrderList;
    PlayerStrategy *strategy = new PlayerStrategy();
    vector<Territory*> vt1;
    vector<Player*> allies1;
    AggressivePlayerStrategy *aggressive = new AggressivePlayerStrategy();

    Player *p1 = new Player(1, 500, vt1, h1, ol1, aggressive);

    Hand *h2 = new Hand();
    OrderList *ol2 = new OrderList;
    vector<Territory*> vt2;
    vector<Player*> allies2;
    BenevolentPlayerStrategy *benevolent = new BenevolentPlayerStrategy();


    Player *p2 = new Player(2, 500, vt2, h2, ol2, benevolent);


    MapLoader *ml = new MapLoader();
    ml->loadMaps();
    vector<MapFile*> rawMaps = ml->getMaps();
    Map* m = new Map(rawMaps[0]->name, rawMaps[0]->content);

    aggressive->setMap(m);
    benevolent->setMap(m);

    for(int i = 0; i < 5; i++){
        m->territories.at(i)->setOwner(1);
        p1->playerTerritories.push_back(m->territories.at(i));
        m->territories.at(i)->setArmiesNumber(10);
    }
    strategy->setMap(m);

    for(int i = 5; i < 10; i++){
        m->territories.at(i)->setOwner(2);
        p2->playerTerritories.push_back(m->territories.at(i));
        m->territories.at(i)->setArmiesNumber(10);

    }

    for(int i = 10; i < m->getTerritories().size(); i++){
        m->territories.at(i)->setArmiesNumber(100);
    }

    showMap(m);


    cout << "Enemies adjacent to player 1: \n";
    for(int i = 0; i < p1->adjacentEnemies(m).size(); i++){
        cout << p1->adjacentEnemies(m).at(i)->name << "\n";
    }

    cout << "Enemies on player 1's attack list: \n";
    for(int i = 0; i < p1->toAttack().size(); i++){
        cout << p1->toAttack().at(i)->name << "\n";
    }

    p1->setReinforcements(20);
    p1->getMyTerritories().at(1)->setArmiesNumber(20);
    cout << "Player 1 (aggressive) has 20 reinforcements and its strongest country is " << p1->getMyTerritories().at(1)->name << "\n\n";
    cout << "Player 1 (aggressive) defends\n\n";
    cout << "Player 1 chooses to defend " << p1->toDefend().back()->name << "\n\n";
    cout << "Player 1 (aggressive) issues an order\n\n";
    p1->issueOrder();

    showMap(m);

    cout << "Player 2 (benevolent) does not attack \n\n";
    //Implementing this function creates an error, since the vector that's returned will be empty
    //cout << "Player 2 chooses to attack" << p2->toAttack().front()->name << "\n\n";

    p2->getMyTerritories().at(1)->setArmiesNumber(1);
    cout<<"Player 2 (benevolent)'s weakest country is now " << p2->getMyTerritories().at(1)->name << "\n\n";

    cout << "Player 2 (benevolent) defends\n\n";
    cout << "Player 2 chooses to defend " << p2->toDefend().front()->name << "\n\n";
    cout << "Player 2 (benevolent) issues an order\n\n";
    p2->issueOrder();

    showMap(m);

    HumanPlayerStrategy *human = new HumanPlayerStrategy;
    NeutralPlayerStrategy *neutral = new NeutralPlayerStrategy;
    human->setMap(m);
    neutral->setMap(m);
    p1->setStrategy(human);
    p2->setStrategy(neutral);

   p1->issueOrder();
   p1->toAttack();
   p1->toDefend();

    p2->issueOrder();
    p2->toAttack();
    p2->toDefend();


    delete neutral;
    neutral = NULL;
    delete human;
    human = NULL;

    delete m;
    m = NULL;

    delete ml;
    ml = NULL;
/**
    delete p2;
    p2 = NULL;
    cout << "Break point 6";
*/
    delete benevolent;
    benevolent = NULL;

    for(int i = 0; i < allies2.size(); i++){
        delete allies2.at(i);
        allies2.at(i) = NULL;
    }

    for(int i = 0; i < vt2.size(); i++) {
        delete vt2.at(i);
        vt2.at(i) = NULL;
    }

    delete ol2;
    ol2 = NULL;

    delete h2;
    h2 = NULL;

/**
    delete p1;
    p1 = NULL;
    cout << "Break point 13";
*/
    delete benevolent;
    benevolent = NULL;

    for(int i = 0; i < allies1.size(); i++) {
        delete allies1.at(i);
        allies1.at(i) = NULL;
    }

    for(int i = 0; i < vt1.size(); i++) {
        delete vt1.at(i);
        vt1.at(i) = NULL;
    }

    delete ol1;
    ol1 = NULL;

    delete h1;
    h1 = NULL;

    return 0;
}