#include "GameObservers.h"
#include "Player.h"
#include "Cards.h"
#include "Orders.h"
#include "Map.h"
#include <iostream>
using namespace std;

int main(){
    Hand *h1 = new Hand;
    OrderList *ol1 = new OrderList;
    vector<Territory*> vt1;

    Player *p1 = new Player(1, 500, vt1, h1, ol1);
    PhaseObserver *po1 = new PhaseObserver(p1);
    p1->Attach(po1);
    p1->Notify();

    Hand *h2 = new Hand;
    OrderList *ol2 = new OrderList;
    vector<Territory*> vt2;

    Player *p2 = new Player(2, 500, vt2, h2, ol2);
    PhaseObserver *po2 = new PhaseObserver(p2);
    p2->Attach(po2);
    p2->Notify();

    Hand *h3 = new Hand;
    OrderList *ol3 = new OrderList;
    vector<Territory*> vt3;

    Player *p3 = new Player(3, 500, vt3, h3, ol3);
    PhaseObserver *po3 = new PhaseObserver(p3);
    p3->Attach(po3);
    p3->Notify();


    return 0;
}