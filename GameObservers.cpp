
#include "GameObservers.h"
#include "Player.h"
#include "Orders.h"
#include "Map.h"
#include <list>
#include <iostream>
using namespace std;

//////////OBSERVABLE//////////

Observable::Observable(){
    _observers = new list<Observer*>;
}

Observable::Observable(){
    delete _observers;
}

void Observable::Attach(Observer* o){
    _observers->push_back(o);
}

void Observable::Detach(Observer* o){
    _observers->remove(o);
}

void Observable::Notify(){

    list<Observer *>::iterator i = _observers->begin();
    for(; i != _observers->end(); i++)
    (*i)->Update();
}


//////////MAPSUBJECT//////////

MapSubject::MapSubject(){

}

Map* ms = new Map;
MapSubject::MapSubject(Map* m){

 ms = m;
}

MapSubject::~MapSubject(){

    delete ms;
    ms = NULL;
}

void MapSubject::Attach(Observer* o){
    
}

void MapSubject::Detach(Observer* o){

}

void MapSubject::Notify(){

}


//////////PLAYERSUBJECT//////////

PlayerSubject::PlayerSubject(){

}

Player* ps = new Player;
PlayerSubject::PlayerSubject(Player* p){

 ps = p;
}

PlayerSubject::~PlayerSubject(){

    delete ps;
    ps = NULL;
}

void PlayerSubject::Attach(Observer* o){
    
}

void PlayerSubject::Detach(Observer* o){

}

void PlayerSubject::Notify(){

}


//////////OrderListSubject//////////

OrderListSubject::OrderListSubject(){

}

OrderList* ols = new OrderList;
OrderListSubject::OrderListSubject(OrderList* ol){

 ols = ol;
}

OrderListSubject::~OrderListSubject(){

    delete ps;
    ps = NULL;
}

void OrderListSubject::Attach(Observer* o){
    
}

void OrderListSubject::Detach(Observer* o){

}

void OrderListSubject::Notify(){

}