
#include "GameObservers.h"

//////////OBSERVABLE//////////

Observable::Observable(){
    _observers = new list<Observer*>;
}

Observable::~Observable(){
    delete _observers;
}

Observable::Observable(const Observable& o){
    list<Observer*>::iterator _it = _observers->begin();
    list<Observer*>::iterator oit = o._observers->begin();
    for(int i = 0; i < o._observers->size(); i++)
    *_it = *oit;
    _it++;
    oit++;
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

list<Observer*> Observable::getObservers(){
    return *_observers;
}

//////////OBSERVER//////////


Observer::Observer(){
}

Observer::~Observer(){

}

Observer::Observer(const Observer& o){

}

void Observer::Update(){

}


//////////PHASEOBSERVER//////////

PhaseObserver::PhaseObserver(){

}

PhaseObserver::~PhaseObserver(){

}

PhaseObserver::PhaseObserver(const PhaseObserver& po){

}

void PhaseObserver::Update(){
    display();
}

void PhaseObserver::display(){
    int phase = 5; //To complete when phase tracker is added
    
}
