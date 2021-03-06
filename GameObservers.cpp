
#include "GameObservers.h"
#include "Player.h"
#include "Map.h"
#include <list>
#include <iostream>

using namespace std;

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

ostream& operator<<(ostream &os, const Observable& o){

    cout<<"This is an observable object";
    return os;
}

Observable& Observable::operator = (const Observable& _file) {
    list<Observer*>::iterator _it = _observers->begin();
    list<Observer*>::iterator fit = _file._observers->begin();
    for(int i = 0; i < _file._observers->size(); i++)
    *_it = *fit;
    _it++;
    fit++;
    return *this;
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

ostream& operator<<(ostream &os, const Observer& o){

    cout<<"This is an observer";
    return os;
}

Observer& Observer::operator = (const Observer& _file) {
    return *this;
}

//////////PHASEOBSERVER//////////

PhaseObserver::PhaseObserver(){

}

PhaseObserver::PhaseObserver(Player* p){

  playerSubject = p;
  playerSubject->Attach(this);

}

PhaseObserver::~PhaseObserver(){
    delete playerSubject;
}

PhaseObserver::PhaseObserver(const PhaseObserver& po){

    playerSubject = po.playerSubject;

}

void PhaseObserver::Update(){
    display();
}

void PhaseObserver::display(){
    int name = playerSubject->name;
    int phase = playerSubject->phase;
    cout << "********PLAYER " << name << "********\n";

    switch(phase) {
        case 1:
                cout << "********STARTUP PHASE********\n\n\n";
                break;
        case 2:
                cout << "********REINFORCEMENT PHASE********\n\n\n";
                break;
        case 3:
                cout << "********ORDER ISSUING PHASE********\n\n\n";
                break;
        case 4:
                cout << "********ORDER EXECUTION PHASE********\n\n\n";
                break;
        case 5:
                cout << "********CONQUERED********\n\n\n";
                break;
        default:
                cout << "ERROR\n\n\n";
    }
}

ostream& operator<<(ostream &os, const PhaseObserver& po){

    cout<<"This is a phase observer, used to monitor the progression of the game";
    return os;
}


PhaseObserver& PhaseObserver::operator = (const PhaseObserver& _file) {
    playerSubject = _file.playerSubject;
    return *this;
}


//////////GAMESTATOBSERVER//////////

GameStatObserver::GameStatObserver(){
    delete mapSubject;

}

GameStatObserver::GameStatObserver(Map* m){
     mapSubject = m;
     mapSubject->Attach(this);

}

GameStatObserver::~GameStatObserver(){

}

GameStatObserver::GameStatObserver(const GameStatObserver& gso){

    mapSubject = gso.mapSubject;
}

void GameStatObserver::Update(){
    display();
}
/**
 * To display
 * 
 * 
 */
void GameStatObserver::display(){
    bool victory = false;
    cout << "\n\n********WORLD DOMINATION********\n\n";
        int dominationID[5]{0, 1, 2, 3, 4};
        string dominationCounter[5]{};
        string unconquered = "";
        //loop to determine which territory is conquered by whom
    for(int i = 0; i < mapSubject->territories.size(); i++) {

        if(mapSubject->territories.at(i)->getOwnerID() == NULL) {
            unconquered += " *";
            continue;
        }

        for (int j = 0; j < 5; j++) {

            if (mapSubject->territories.at(i)->getOwnerID() == dominationID[j])
                dominationCounter[j] += " *";
            }
    }

    for(int x = 0; x < 5; x++) {
        if(dominationCounter[x] != "") {
            cout << "PLAYER " << dominationID[x] << " " << dominationCounter[x] << "\n";
            if(dominationCounter[x].length() == mapSubject->territories.size()*2)
                victory = true;
        }
    }
        cout << "NEUTRAL: " << unconquered;
    if(victory == true)
        cout << "\n\n**********THE WORLD HAS BEEN CONQUERED!**********";
    cout<< "\n\n\n\n";
}


ostream& operator<<(ostream &os, const GameStatObserver& o){

    cout<<"This is a game statistics observer observer, used to monitor control of the board";
    return os;
}


GameStatObserver& GameStatObserver::operator = (const GameStatObserver& _file) {
    mapSubject = _file.mapSubject;
    return *this;
}