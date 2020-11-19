#include "GameObservers.h"
#include "Player.h"
#include "Cards.h"
#include "Orders.h"
#include <iostream>
using namespace std;

int main(){

    Hand *h = new Hand;
    OrderList *ol = new OrderList;
    vector<Territories*> pt = new vector<Territories*>;

    Player *p1 = new Player("Player1", 500, h, pt, ol);
    PhaseObserver *po = new PhaseObserver(p1);
    p1->Attach(po);
    p1->update();

    return 0;
}