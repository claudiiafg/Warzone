#include "PlayerStrategies.h"
#include "MapLoader.h"
#include "Player.h"
#include "Map.h"
#include <iostream>
using namespace std;


/**
 -At each step, display the countries that are being attacked/reinforced/defended and the number of units on each country
 */


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
    cout << m->name << "\n";
    GameStatObserver *mo = new GameStatObserver(m);

    aggressive->setMap(m);
    benevolent->setMap(m);

    for(int i = 0; i < 5; i++){
        m->territories.at(i)->setOwner(1);
        p1->playerTerritories.push_back(m->territories.at(i));
    }
    strategy->setMap(m);

    for(int i = 5; i < 10; i++){
        m->territories.at(i)->setOwner(2);
        p2->playerTerritories.push_back(m->territories.at(i));
    }

    p1->issueOrder();
    p1->toAttack();
    p1->toDefend();
    //p2->issueOrder();
    //p2->toAttack();
    //p2->toDefend();

    HumanPlayerStrategy *human = new HumanPlayerStrategy;
    NeutralPlayerStrategy *neutral = new NeutralPlayerStrategy;
    human->setMap(m);
    neutral->setMap(m);
    p1->setStrategy(human);
    p2->setStrategy(neutral);
    cout <<"Preparing to issue order... \n\n";
   // p1->issueOrder();
    cout << "Preparing to defend... \n\n";
   // p1->toAttack();
    cout << "Preparing to defend... \n\n";
   // p1->toDefend();

    //p2->issueOrder();
    //p2->toAttack();
    //p2->toDefend();


    delete neutral;
    neutral = NULL;
    cout << "Break point 1";
    delete human;
    human = NULL;
    cout << "Break point 2";

    delete m;
    m = NULL;
    cout << "Break point 3";

    delete ml;
    ml = NULL;
    cout << "Break point 4";
/**
    delete p2;
    p2 = NULL;
    cout << "Break point 6";
*/
    delete benevolent;
    benevolent = NULL;
    cout << "Break point 7";

    for(int i = 0; i < allies2.size(); i++){
        delete allies2.at(i);
        allies2.at(i) = NULL;
    }
    cout << "Break point 8";

    for(int i = 0; i < vt2.size(); i++) {
        delete vt2.at(i);
        vt2.at(i) = NULL;
    }
    cout << "Break point 9";

    delete ol2;
    ol2 = NULL;
    cout << "Break point 10";

    delete h2;
    h2 = NULL;
    cout << "Break point 11";

/**
    delete p1;
    p1 = NULL;
    cout << "Break point 13";
*/
    delete benevolent;
    benevolent = NULL;
    cout << "Break point 14";

    for(int i = 0; i < allies1.size(); i++) {
        delete allies1.at(i);
        allies1.at(i) = NULL;
        cout << "Break point 15";

    }
    for(int i = 0; i < vt1.size(); i++) {
        delete vt1.at(i);
        vt1.at(i) = NULL;
        cout << "Break point 16";

    }
    delete ol1;
    ol1 = NULL;
    cout << "Break point 17";

    delete h1;
    h1 = NULL;

    return 0;
}