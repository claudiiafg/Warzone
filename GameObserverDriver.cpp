#include "GameObservers.h"
#include "Player.h"
#include "Cards.h"
#include "Orders.h"
#include "Map.h"
#include "MapLoader.h"
#include <iostream>
using namespace std;
int main(){

   /* //Demonstrating the phase observer
    Hand *h1 = new Hand();
    OrderList *ol1 = new OrderList;
    vector<Territory*> vt1;
    vector<Player*> allies1;

    Player *p1 = new Player(1, 500, vt1, h1, ol1, allies1);
    PhaseObserver *po1 = new PhaseObserver(p1);
    p1->Notify();

    Hand *h2 = new Hand();
    OrderList *ol2 = new OrderList;
    vector<Territory*> vt2;
    vector<Player*> allies2;


    Player *p2 = new Player(2, 500, vt2, h2, ol2, allies2);
    PhaseObserver *po2 = new PhaseObserver(p2);
    p2->Notify();

    Hand *h3 = new Hand();
    OrderList *ol3 = new OrderList;
    vector<Territory*> vt3;
    vector<Player*> allies3;

    Player *p3 = new Player(3, 500, vt3, h3, ol3, allies3);
    PhaseObserver *po3 = new PhaseObserver(p3);
    p3->Notify();

    p1->phase = 2;
    p1->Notify();
    p2->phase = 4;
    p2->Notify();
    p3->phase = 5;
    p3->Notify();

    //Demonstrating the game statistics observer
    MapLoader *ml = new MapLoader();
    ml->loadMaps();
    vector<MapFile*> rawMaps = ml->getMaps();
    Map* m = new Map(rawMaps[0]->name, rawMaps[0]->content);
    GameStatObserver *mo = new GameStatObserver(m);

    for(int i = 0; i < 5; i++){
        m->territories.at(i)->setOwner(1);
    }

    m->Notify();

    for(int i = 5; i < 10; i++){
        m->territories.at(i)->setOwner(2);
    }
    m->Notify();

    for(int i = 10; i < 15; i++){
        m->territories.at(i)->setOwner(3);
    }
    m->Notify();

    //Eliminating player 2
    for(int i = 5; i < 10; i++){
        m->territories.at(i)->setOwner(1);

    }
    m->Notify();

    //Victory for player 1
    for(int i = 10; i < m->territories.size(); i++){
        m->territories.at(i)->setOwner(1);
    }
    m->Notify();

    return 0;*/
}