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
    HumanPlayerStrategy *aggressive = new HumanPlayerStrategy();

    Player *p1 = new Player(1, 500, vt1, h1, ol1, aggressive);
    PhaseObserver *po1 = new PhaseObserver(p1);
    p1->Notify();

    Hand *h2 = new Hand();
    OrderList *ol2 = new OrderList;
    vector<Territory*> vt2;
    vector<Player*> allies2;
    BenevolentPlayerStrategy *benevolent = new BenevolentPlayerStrategy();


    Player *p2 = new Player(2, 500, vt2, h2, ol2, benevolent);
    PhaseObserver *po2 = new PhaseObserver(p2);
    p2->Notify();

    MapLoader *ml = new MapLoader();
    ml->loadMaps();
    vector<MapFile*> rawMaps = ml->getMaps();
    Map* m = new Map(rawMaps[0]->name, rawMaps[0]->content);
    cout << rawMaps[0]->name << "\n";
    GameStatObserver *mo = new GameStatObserver(m);

    for(int i = 0; i < 5; i++){
        m->territories.at(i)->setOwner(1);
    }
    strategy->stratMap = m;
    m->Notify();

    for(int i = 5; i < 10; i++){
        m->territories.at(i)->setOwner(2);
    }
    m->Notify();

    p1->toAttack();
    p1->toDefend();
    p1->issueOrder();
    p2->toAttack();
    p2->toDefend();

    HumanPlayerStrategy *human = new HumanPlayerStrategy;
    NeutralPlayerStrategy *neutral = new NeutralPlayerStrategy;
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
    delete po2;
    po2 = NULL;
    delete p2;
    p2 = NULL;
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

    delete po1;
    po1 = NULL;
    delete p1;
    p1 = NULL;
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